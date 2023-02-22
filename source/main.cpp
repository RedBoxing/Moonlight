#include "exlaunch.hpp"
#include "starlight.hpp"
#include "moonlight_overlay.hpp"
#include "nn/crypto.h"

HOOK_DEFINE_TRAMPOLINE(MainInitHook){
    static void Callback(){
        R_ABORT_UNLESS(nn::fs::MountSdCardForDebug("sd"));

Orig();
}
}
;

HOOK_DEFINE_TRAMPOLINE(MD5_HASH_HOOK){
    static void Callback(void *dstBuffer, u64 dstBufferSize, const void *srcBuffer, u64 srcBufferSize){
        Orig(dstBuffer, dstBufferSize, srcBuffer, srcBufferSize);
}
}
;

extern "C" void exl_main(void *x0, void *x1)
{
    envSetOwnProcessHandle(exl::util::proc_handle::Get());

    /* Setup hooking enviroment. */
    exl::hook::Initialize();

    MainInitHook::InstallAtSymbol("nnMain");
    MD5_HASH_HOOK::InstallAtFuncPtr(nn::crypto::GenerateMd5Hash);

    Starlight::Initialize(new Moonlight::UI::Overlay());
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}