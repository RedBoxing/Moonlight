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
/*
HOOK_DEFINE_TRAMPOLINE(MD5_HASH_HOOK){
    static void Callback(void *dstBuffer, u64 dstBufferSize, const void *srcBuffer, u64 srcBufferSize){
        Orig(dstBuffer, dstBufferSize, srcBuffer, srcBufferSize);

// md5Hashes.push_back(std::string((char *)dstBuffer, dstBufferSize) + " : " + std::to_string(srcBufferSize) + " bytes");
}
}
;

HOOK_DEFINE_TRAMPOLINE(SHA1_HASH_HOOK){
    static void Callback(void *dstBuffer, u64 dstBufferSize, const void *srcBuffer, u64 srcBufferSize){
        Orig(dstBuffer, dstBufferSize, srcBuffer, srcBufferSize);

// sha1Hashes.push_back(std::string((char *)dstBuffer, dstBufferSize) + " : " + std::to_string(srcBufferSize) + " bytes");
}
}
;

HOOK_DEFINE_TRAMPOLINE(SHA256_HASH_HOOK){
    static void Callback(void *dstBuffer, u64 dstBufferSize, const void *srcBuffer, u64 srcBufferSize){
        Orig(dstBuffer, dstBufferSize, srcBuffer, srcBufferSize);

// sha256Hashes.push_back(std::string((char *)dstBuffer, dstBufferSize) + " : " + std::to_string(srcBufferSize) + " bytes");
}
}
;

HOOK_DEFINE_TRAMPOLINE(SHA512_HASH_HOOK){
    static void Callback(void *dstBuffer, u64 dstBufferSize, const void *srcBuffer, u64 srcBufferSize){
        Orig(dstBuffer, dstBufferSize, srcBuffer, srcBufferSize);

// sha512Hashes.push_back(std::string((char *)dstBuffer, dstBufferSize) + " : " + std::to_string(srcBufferSize) + " bytes");
}
}
;

HOOK_DEFINE_TRAMPOLINE(HMAC_SHA1_HASH_HOOK){
    static void Callback(void *dstBuffer, u64 dstBufferSize, const void *srcBuffer, u64 srcBufferSize, const void *hmacKey, u64 hmacKeySize){
        Orig(dstBuffer, dstBufferSize, srcBuffer, srcBufferSize, hmacKey, hmacKeySize);

/// hmacSha1Hashes.push_back(std::string((char *)dstBuffer, dstBufferSize) + " : " + std::to_string(srcBufferSize) + " bytes");
}
}
;

HOOK_DEFINE_TRAMPOLINE(HMAC_SHA256_HASH_HOOK){
    static void Callback(void *dstBuffer, u64 dstBufferSize, const void *srcBuffer, u64 srcBufferSize, const void *hmacKey, u64 hmacKeySize){
        Orig(dstBuffer, dstBufferSize, srcBuffer, srcBufferSize, hmacKey, hmacKeySize);

// hmacSha256Hashes.push_back(std::string((char *)dstBuffer, dstBufferSize) + " : " + std::to_string(srcBufferSize) + " bytes");
}
}
;*/

extern "C" void exl_main(void *x0, void *x1)
{
    envSetOwnProcessHandle(exl::util::proc_handle::Get());

    /* Setup hooking enviroment. */
    exl::hook::Initialize();

    MainInitHook::InstallAtSymbol("nnMain");
    /*  MD5_HASH_HOOK::InstallAtFuncPtr(nn::crypto::GenerateMd5Hash);
      SHA1_HASH_HOOK::InstallAtFuncPtr(nn::crypto::GenerateSha1Hash);
      SHA256_HASH_HOOK::InstallAtFuncPtr(nn::crypto::GenerateSha256Hash);
      SHA512_HASH_HOOK::InstallAtFuncPtr(nn::crypto::GenerateSha512Hash);
      HMAC_SHA1_HASH_HOOK::InstallAtFuncPtr(nn::crypto::GenerateHmacSha1Mac);
      HMAC_SHA256_HASH_HOOK::InstallAtFuncPtr(nn::crypto::GenerateHmacSha256Mac);*/

    Starlight::Initialize(new Moonlight::UI::Overlay());
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}