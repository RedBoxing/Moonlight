#include "common.hpp"
#include "lib.hpp"
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
    // style->FramePadding = ImVec2(8, 6);
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
        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;

        Logger::log("Loading Font.\n");

        void *data = nullptr;
        size_t size = 0;
        Starlight::FS::readFile("sd:/starlight/Tenacity.ttf", &data, &size);

        // io.Fonts->AddFontFromMemoryTTF(loadData.buffer, loadData.bufSize, 16.0f, nullptr, io.Fonts->GetGlyphRangesDefault());
        // io.Fonts->AddFontFromFileTTF("sd:/starlight/Tenacity.ttf", 15.0f);
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

        Logger::log("UI Initialized.\n");

        return true;
    }
    else
    {
        Logger::log("Unable to Initialize UI!\n");
        return false;
    }
}

bool CenteredButton(const char *label, ImVec2 _size, float alignment = 0.5f)
{
    ImGuiStyle &style = ImGui::GetStyle();

    float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;

    float off = (avail - size) * alignment;
    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

    return ImGui::Button(label, _size);
}

void presentTexture(nvn::Queue *queue, nvn::Window *window, int texIndex)
{
    if (isUIInitialized)
    {
        // procDraw();
        Starlight::HID::updatePadState();

        if (Starlight::HID::isInputToggled())
        {
            ImguiNvnBackend::newFrame();
            ImGui::NewFrame();

            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

            ImGuiViewport *viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize({448, viewport->Size.y});

            ImGui::Begin("Starlight", nullptr, window_flags);
            ImGui::Text("Starlight");
            ImGui::Text("V1.0.0 - PRIVATE");

            ImGui::Spacing();
            ImGui::Separator();

            ImGui::SetCursorPosX(32);
            ImGui::Button("Save Options", {363, 69});

            ImGui::SetCursorPosX(32);
            ImGui::Button("Movement Options", {363, 69});

            ImGui::SetCursorPosX(32);
            ImGui::Button("Player Options", {363, 69});

            ImGui::End();

            ImGui::Render();
            ImguiNvnBackend::renderDrawData(ImGui::GetDrawData());
        }
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

void Starlight::UI::InitializeHooks()
{
    Logger::log("Initializing UI Hooks.\n");
    nn::ro::LookupSymbol(reinterpret_cast<uintptr_t *>(&mallocFuncPtr), "malloc");
    nn::ro::LookupSymbol(reinterpret_cast<uintptr_t *>(&freeFuncPtr), "free");

    NvnBootstrapHook::InstallAtSymbol("nvnBootstrapLoader");
}