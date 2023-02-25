#include "exlaunch.hpp"
#include "starlight.hpp"
#include "moonlight_overlay.hpp"
#include "logger.hpp"

HOOK_DEFINE_TRAMPOLINE(MainInitHook){
    static void Callback(){
        R_ABORT_UNLESS(nn::fs::MountSdCardForDebug("sd"));

Orig();
}
}
;

HOOK_DEFINE_TRAMPOLINE(TEST_HOOK){
    static void * Callback(void *packetReaderInstance, char *x1){
                      void *ret = Orig(packetReaderInstance, x1);

Moonlight::Logger::log("PacketReader");

return ret;
}
}
;

HOOK_DEFINE_TRAMPOLINE(LOG1_HOOK){
    static void Callback(void *x0, void *x1, void *x2, bool x3, char *str){
        Moonlight::Logger::log(str);
Orig(x0, x1, x2, x3, str);
}
}
;

HOOK_DEFINE_TRAMPOLINE(LOG2_HOOK){
    static void Callback(void *x0, void *x1, void *x2, char *str){
        Moonlight::Logger::log(str);
Orig(x0, x1, x2, str);
}
}
;

extern "C" void exl_main(void *x0, void *x1)
{
    envSetOwnProcessHandle(exl::util::proc_handle::Get());

    /* Setup hooking enviroment. */
    exl::hook::Initialize();

    MainInitHook::InstallAtSymbol("nnMain");
    TEST_HOOK::InstallAtOffset(0x257D510);

    // LOG1_HOOK::InstallAtOffset(0x25BA000);
    // LOG2_HOOK::InstallAtOffset(0x25BA010);

    Starlight::Initialize(new Moonlight::UI::Overlay());
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}