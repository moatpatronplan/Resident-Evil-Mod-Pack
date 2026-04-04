/*
 * VRAM Manager — Resident Evil 4 Remake Mod Pack
 */
#include <windows.h>
#include <dxgi.h>
#include <iostream>
#pragma comment(lib, "dxgi.lib")

namespace RE4Tweaks {

class VRAMManager {
    size_t vramMB = 0; int maxTex = 2048; bool active = false;
    size_t Detect() {
        IDXGIFactory1* f = nullptr; CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&f);
        if (!f) return 4096;
        IDXGIAdapter1* a = nullptr; f->EnumAdapters1(0, &a);
        if (!a) { f->Release(); return 4096; }
        DXGI_ADAPTER_DESC1 d; a->GetDesc1(&d);
        size_t mb = d.DedicatedVideoMemory / 1048576;
        a->Release(); f->Release(); return mb;
    }
public:
    bool Init() {
        vramMB = Detect();
        maxTex = vramMB >= 12000 ? 4096 : vramMB >= 8000 ? 4096 : vramMB >= 6000 ? 2048 : 1024;
        active = true;
        std::cout << "[RE4 VRAM] " << vramMB << " MB — tex " << maxTex << "px" << std::endl;
        return true;
    }
    void Shutdown() { active = false; }
};

} // namespace RE4Tweaks
