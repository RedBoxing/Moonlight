#include "common.hpp"
#include "lib.hpp"
#include "nn/pl.h"
#include "nvn/nvn.h"
#include "nvn/nvn_Cpp.h"
#include "nvn/nvn_CppFuncPtrImpl.h"
#include "logger/logger.hpp"
#include "starlight.hpp"
#include "imgui/imgui_impl_nvn.hpp"

nvn::Device *nvnDevice;
nvn::Queue *nvnQueue;
nvn::CommandBuffer *nvnCmdBuf;

nvn::DeviceGetProcAddressFunc tempGetProcAddressFuncPtr;

nvn::CommandBufferInitializeFunc tempBufferInitFuncPtr;
nvn::DeviceInitializeFunc tempDeviceInitFuncPtr;
nvn::QueueInitializeFunc tempQueueInitFuncPtr;
nvn::QueuePresentTextureFunc tempPresentTexFunc;
nvn::TextureGetWidthFunc tempTexGetWidthFunc;
nvn::TextureGetHeightFunc tempTexGetHeightFunc;
nvn::WindowBuilderSetTexturesFunc tempWindowBuilderSetTexFunc;
nvn::WindowSetCropFunc tempWindowSetCropFunc;

bool isUIInitialized = false;

static void *(*mallocFuncPtr)(size_t size);
static void (*freeFuncPtr)(void *ptr);

void setStyle(ImGuiStyle *style)
{
    ImVec4 *colors = style->Colors;

    colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.95f);
    colors[ImGuiCol_Border] = ImVec4(0, 1, 0.86, 1);

    colors[ImGuiCol_Button] = ImVec4(0, 0, 0, 0);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0, 0, 0, 1);
    colors[ImGuiCol_ButtonActive] = ImVec4(0, 0.13, 0.13, 1);

    style->WindowBorderSize = 0;
    style->ButtonTextAlign = ImVec2(0.1f, 0.5f);
}

bool Starlight::UI::Initialize()
{
    if (nvnDevice && nvnQueue && nvnCmdBuf)
    {
        Logger::log("Initializing UI.\n");
        IMGUI_CHECKVERSION();

        ImGuiMemAllocFunc allocFunc = [](size_t size, void *user_data)
        {
            return mallocFuncPtr(size);
        };

        ImGuiMemFreeFunc freeFunc = [](void *ptr, void *user_data)
        {
            freeFuncPtr(ptr);
        };

        Logger::log("Setting Allocator Functions.\n");
        ImGui::SetAllocatorFunctions(allocFunc, freeFunc, nullptr);
        Logger::log("Creating ImGui Context.\n");

        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NoMouse | ImGuiConfigFlags_NavEnableGamepad;

        Logger::log("Loading Font.\n");

        if (nn::pl::GetSharedFontSize(nn::pl::SharedFontType_Standard) != 1)
        {
            bool load_started = false;
            u32 loadState = 0;

            while (true)
            {
                if (load_started)
                    svcSleepThread(1000000000ULL / 60);

                loadState = nn::pl::GetSharedFontLoadState(nn::pl::SharedFontType_Standard);
                if (loadState == 1)
                    break;

                if (!load_started)
                {
                    nn::pl::RequestSharedFontLoad(nn::pl::SharedFontType_Standard);
                    load_started = true;
                }
            }
        }

        size_t size = nn::pl::GetSharedFontSize(nn::pl::SharedFontType_Standard);
        void *data = (void *)nn::pl::GetSharedFontAddress(nn::pl::SharedFontType_Standard);

        io.Fonts->AddFontFromMemoryTTF(data, size, 26.0f, nullptr, nullptr);
        io.Fonts->Build();
        (void)io;

        Logger::log("Setting Style to Dark.\n");
        ImGui::StyleColorsDark();
        setStyle(&ImGui::GetStyle());

        ImguiNvnBackend::NvnBackendInitInfo initInfo = {
            .device = nvnDevice,
            .queue = nvnQueue,
            .cmdBuf = nvnCmdBuf};

        Logger::log("Initializing Backend.\n");
        ImguiNvnBackend::InitBackend(initInfo);
        Starlight::HID::Initialize();

        Logger::log("Initializing Menu Framework.\n");

        Starlight::UI::mainMenu = std::make_unique<Starlight::UI::Menu>();
        Starlight::UI::mainMenu->Initialize();

        Logger::log("UI Initialized.\n");

        return true;
    }
    else
    {
        Logger::log("Unable to Initialize UI!\n");
        return false;
    }
}

void presentTexture(nvn::Queue *queue, nvn::Window *window, int texIndex)
{
    if (isUIInitialized && Starlight::UI::mainMenu != nullptr)
    {
        Starlight::UI::mainMenu->update();
    }

    tempPresentTexFunc(queue, window, texIndex);
}

void windowBuilderSetTextures(nvn::WindowBuilder *builder, int count, nvn::Texture *const *textures)
{
    tempWindowBuilderSetTexFunc(builder, count, textures);

    if (isUIInitialized)
    {
        int h = tempTexGetHeightFunc(textures[0]);
        int w = tempTexGetWidthFunc(textures[0]);

        ImguiNvnBackend::getBackendData()->viewportSize = ImVec2(w, h);
    }
}

void setCrop(nvn::Window *window, int x, int y, int w, int h)
{
    tempWindowSetCropFunc(window, x, y, w, h);

    if (isUIInitialized)
    {
        ImguiNvnBackend::getBackendData()->viewportSize = ImVec2(w, h);
    }
}

NVNboolean deviceInit(nvn::Device *device, const nvn::DeviceBuilder *builder)
{
    NVNboolean result = tempDeviceInitFuncPtr(device, builder);
    nvnDevice = device;
    nvn::nvnLoadCPPProcs(nvnDevice, tempGetProcAddressFuncPtr);
    return result;
}

NVNboolean queueInit(nvn::Queue *queue, const nvn::QueueBuilder *builder)
{
    NVNboolean result = tempQueueInitFuncPtr(queue, builder);
    nvnQueue = queue;
    return result;
}

NVNboolean cmdBufInit(nvn::CommandBuffer *buffer, nvn::Device *device)
{
    NVNboolean result = tempBufferInitFuncPtr(buffer, device);
    nvnCmdBuf = buffer;

    if (!isUIInitialized)
    {
        isUIInitialized = Starlight::UI::Initialize();
    }

    return result;
}

nvn::GenericFuncPtrFunc getProc(nvn::Device *device, const char *procName)
{
    nvn::GenericFuncPtrFunc ptr = tempGetProcAddressFuncPtr(nvnDevice, procName);

    if (strcmp(procName, "nvnQueueInitialize") == 0)
    {
        tempQueueInitFuncPtr = (nvn::QueueInitializeFunc)ptr;
        return (nvn::GenericFuncPtrFunc)&queueInit;
    }
    else if (strcmp(procName, "nvnCommandBufferInitialize") == 0)
    {
        tempBufferInitFuncPtr = (nvn::CommandBufferInitializeFunc)ptr;
        return (nvn::GenericFuncPtrFunc)&cmdBufInit;
    }
    else if (strcmp(procName, "nvnQueuePresentTexture") == 0)
    {
        tempPresentTexFunc = (nvn::QueuePresentTextureFunc)ptr;
        return (nvn::GenericFuncPtrFunc)&presentTexture;
    }
    else if (strcmp(procName, "nvnWindowBuilderSetTextures") == 0)
    {
        tempWindowBuilderSetTexFunc = (nvn::WindowBuilderSetTexturesFunc)ptr;
        return (nvn::GenericFuncPtrFunc)&windowBuilderSetTextures;
    }
    else if (strcmp(procName, "nvnTextureGetWidth") == 0)
    {
        tempTexGetWidthFunc = (nvn::TextureGetWidthFunc)ptr;
    }
    else if (strcmp(procName, "nvnTextureGetHeight") == 0)
    {
        tempTexGetHeightFunc = (nvn::TextureGetHeightFunc)ptr;
    }
    else if (strcmp(procName, "nvnWindowSetCrop") == 0)
    {
        tempWindowSetCropFunc = (nvn::WindowSetCropFunc)ptr;
        return (nvn::GenericFuncPtrFunc)&setCrop;
    }

    return ptr;
}

HOOK_DEFINE_TRAMPOLINE(NvnBootstrapHook){
    static void * Callback(const char *funcName){
                      void *result = Orig(funcName);

Logger::log("Installing nvn Hooks.\n");

if (strcmp(funcName, "nvnDeviceInitialize") == 0)
{
    tempDeviceInitFuncPtr = (nvn::DeviceInitializeFunc)result;
    return (void *)&deviceInit;
}
if (strcmp(funcName, "nvnDeviceGetProcAddress") == 0)
{
    tempGetProcAddressFuncPtr = (nvn::DeviceGetProcAddressFunc)result;
    return (void *)&getProc;
}

return result;
}
}
;

#define INPUT_HOOK(type)                                                                           \
    HOOK_DEFINE_TRAMPOLINE(Disable##type){                                                         \
        static int Callback(int *unkInt, nn::hid::Npad##type *state, int count, uint const &port){ \
            int result = Orig(unkInt, state, count, port);                                         \
    if (!Starlight::HID::isReadingInput())                                                         \
    {                                                                                              \
        if (Starlight::UI::mainMenu->isFocused())                                                  \
        {                                                                                          \
            *state = nn::hid::Npad##type();                                                        \
        }                                                                                          \
    }                                                                                              \
    return result;                                                                                 \
    }                                                                                              \
    }                                                                                              \
    ;

INPUT_HOOK(FullKeyState);
INPUT_HOOK(HandheldState);
INPUT_HOOK(JoyDualState);
INPUT_HOOK(JoyLeftState);
INPUT_HOOK(JoyRightState);

void Starlight::UI::InitializeHooks()
{
    Logger::log("Initializing UI Hooks.\n");
    nn::ro::LookupSymbol(reinterpret_cast<uintptr_t *>(&mallocFuncPtr), "malloc");
    nn::ro::LookupSymbol(reinterpret_cast<uintptr_t *>(&freeFuncPtr), "free");

    NvnBootstrapHook::InstallAtSymbol("nvnBootstrapLoader");
    DisableFullKeyState::InstallAtSymbol("_ZN2nn3hid6detail13GetNpadStatesEPiPNS0_16NpadFullKeyStateEiRKj");
    DisableHandheldState::InstallAtSymbol("_ZN2nn3hid6detail13GetNpadStatesEPiPNS0_17NpadHandheldStateEiRKj");
    DisableJoyDualState::InstallAtSymbol("_ZN2nn3hid6detail13GetNpadStatesEPiPNS0_16NpadJoyDualStateEiRKj");
    DisableJoyLeftState::InstallAtSymbol("_ZN2nn3hid6detail13GetNpadStatesEPiPNS0_16NpadJoyLeftStateEiRKj");
    DisableJoyRightState::InstallAtSymbol("_ZN2nn3hid6detail13GetNpadStatesEPiPNS0_17NpadJoyRightStateEiRKj");
}

void Starlight::UI::Utils::drawSeparator(int x, int y, int width, int tickness, ImU32 color)
{
    float x2 = x + width;
    float y2 = y + tickness;

    ImGui::GetWindowDrawList()->AddLine(ImVec2(x, y), ImVec2(x2, y2), color);
}