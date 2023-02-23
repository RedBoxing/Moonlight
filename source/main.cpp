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

HOOK_DEFINE_TRAMPOLINE(SHA1_HASH_HOOK){
    static void Callback(void *dstBuffer, u64 dstBufferSize, const void *srcBuffer, u64 srcBufferSize){
        Orig(dstBuffer, dstBufferSize, srcBuffer, srcBufferSize);

sha1Hashes.push_back(std::to_string(srcBufferSize) + " bytes");
}
}
;

extern "C" void exl_main(void *x0, void *x1)
{
    envSetOwnProcessHandle(exl::util::proc_handle::Get());

    /* Setup hooking enviroment. */
    exl::hook::Initialize();

    MainInitHook::InstallAtSymbol("nnMain");
    SHA1_HASH_HOOK::InstallAtFuncPtr(nn::crypto::GenerateSha1Hash);

    Starlight::Initialize(new Moonlight::UI::Overlay());
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}