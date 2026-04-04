/*
 * FPS Booster — Resident Evil 4 Remake Mod Pack
 */
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>

namespace RE4Tweaks {

class FramePacer {
    double targetMs; std::chrono::high_resolution_clock::time_point last;
public:
    FramePacer(int fps = 60) : targetMs(1000.0 / fps) { last = std::chrono::high_resolution_clock::now(); }
    void Wait() {
        auto now = std::chrono::high_resolution_clock::now();
        double el = std::chrono::duration<double, std::milli>(now - last).count();
        if (el < targetMs) std::this_thread::sleep_for(std::chrono::microseconds((int)((targetMs - el) * 900)));
        last = std::chrono::high_resolution_clock::now();
    }
};

class MemPool {
    void* base = nullptr; size_t sz = 0, used = 0;
public:
    bool Init(float mb) {
        sz = (size_t)(mb * 1048576);
        base = VirtualAlloc(nullptr, sz, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        std::cout << "[RE4 FPS] Pool: " << mb << " MB" << std::endl;
        return base != nullptr;
    }
    void Reset() { used = 0; }
    ~MemPool() { if (base) VirtualFree(base, 0, MEM_RELEASE); }
};

class FPSBooster {
    FramePacer pacer; MemPool pool; bool active = false;
public:
    bool Init(int fps = 60) {
        pacer = FramePacer(fps); pool.Init(640); active = true;
        std::cout << "[RE4 FPS] Target " << fps << " FPS" << std::endl;
        return true;
    }
    void OnFrameEnd() { if (active) pacer.Wait(); }
    void Shutdown() { active = false; }
};

} // namespace RE4Tweaks
