#include "lib.hpp"
#include "starlight.hpp"
#include "moonlight_overlay.hpp"

HOOK_DEFINE_TRAMPOLINE(MainInitHook){
    static void Callback(){
        R_ABORT_UNLESS(nn::fs::MountSdCardForDebug("sd"));

Orig();
}
}
;

extern "C" void exl_main(void *x0, void *x1)
{
    envSetOwnProcessHandle(exl::util::proc_handle::Get());

    /* Setup hooking enviroment. */
    exl::hook::Initialize();

    MainInitHook::InstallAtSymbol("nnMain");

    Starlight::Initialize(new Moonlight::UI::Overlay());
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}