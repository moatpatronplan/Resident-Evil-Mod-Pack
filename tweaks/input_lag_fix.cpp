/*
 * Input Lag Fix — Resident Evil 4 Remake Mod Pack
 */
#include <windows.h>
#include <iostream>
#include <thread>
#include <atomic>

namespace RE4Tweaks {

class InputLagFix {
    std::atomic<bool> polling{false}; std::thread pt;
    void Poll() {
        while (polling) {
            MSG m; while (PeekMessage(&m, nullptr, WM_INPUT, WM_INPUT, PM_REMOVE)) {
                TranslateMessage(&m); DispatchMessage(&m); }
            Sleep(1);
        }
    }
public:
    void Init() {
        SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
        polling = true; pt = std::thread(&InputLagFix::Poll, this);
        SetThreadPriority(pt.native_handle(), THREAD_PRIORITY_HIGHEST);
        std::cout << "[RE4 Input] Low latency active" << std::endl;
    }
    void Shutdown() {
        polling = false; if (pt.joinable()) pt.join();
        SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
    }
};

} // namespace RE4Tweaks
