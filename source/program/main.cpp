#include "lib.hpp"
#include "starlight.hpp"
#include "moonlight_menu.hpp"

extern "C" void exl_main(void *x0, void *x1)
{
    envSetOwnProcessHandle(exl::util::proc_handle::Get());

    /* Setup hooking enviroment. */
    exl::hook::Initialize();

    Moonlight::UI::g_menu = new Moonlight::UI::Menu();

    Starlight::Initialize(Moonlight::UI::g_menu);
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}