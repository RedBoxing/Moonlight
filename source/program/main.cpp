#include "lib.hpp"
#include "nn.hpp"
#include "starlight.hpp"
#include "socket/socket.hpp"
#include "logger/logger.hpp"

// #define USE_SOCKET

#ifdef USE_SOCKET
static Socket gSocket;

void logToSocket(const char *str)
{
    gSocket.sendMessage(str);
}
#endif

HOOK_DEFINE_TRAMPOLINE(MainInitHook){
    static void Callback(){

        R_ABORT_UNLESS(nn::fs::MountSdCardForDebug("sd"));

// nn::fs::DeleteFile("sd:/starlight.log");

// Logger::addListener(&logToFile);

#ifdef USE_SOCKET
if (gSocket.init("10.0.0.10", 3080).isFailure())
{
    *(u32 *)0 = 0;
    Logger::log("Failed to connect to logging server!\n");
}
else
{
    Logger::addListener(&logToSocket);
    Logger::log("Connected to logging server!\n");
}
#endif

Logger::log("Starlight Loaded!\n");
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

    Starlight::UI::InitializeHooks();
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}