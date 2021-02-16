#pragma warning(push)
#pragma warning(disable: 5105)
#include <Windows.h>
#pragma warning(pop)

#ifdef NDEBUG
#include <stdio.h>
#define LOG_ERROR(message) printf("[error](%03u): %s\n", __LINE__, (message))
#else
#define LOG_ERROR(message)
#endif

#define SLEEP_TIME 30000
#define HIDE_CONSOLE 1

int main() {
    int returnValue = 0;

#if defined NDEBUG && defined HIDE_CONSOLE // Hide console for Release build
    FreeConsole();
#endif

    int mousePosIncrement = 5;
    
    INPUT input = {
        .type = INPUT_MOUSE
        , .mi.dx = 0
        , .mi.dy = 0
        , .mi.mouseData = 0
        , .mi.dwFlags = 0
        , .mi.time = 0
        , .mi.dwExtraInfo = 0
        , .mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK // | MOUSEEVENTF_ABSOLUTE
    };

    do {
        if (0 == SetThreadExecutionState(
            ES_CONTINUOUS
            | ES_SYSTEM_REQUIRED
            | ES_AWAYMODE_REQUIRED)) {
            LOG_ERROR("Could not perform SetThreadExecutionState");

            returnValue = -1;
            break;
        }

        input.mi.dx = mousePosIncrement;
        input.mi.dy = (mousePosIncrement *= -1);

        if (1 != SendInput(1, &input, sizeof(input))) {
            LOG_ERROR("Could not perform SendInput");

            returnValue = -1;
            break;
        }

        SwitchToThread();

        Sleep(SLEEP_TIME);
    } while (1);
    return returnValue;
}