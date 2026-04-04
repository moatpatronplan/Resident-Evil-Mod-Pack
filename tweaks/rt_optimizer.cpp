/*
 * RT Optimizer — Resident Evil 4 Remake Mod Pack
 * Ray tracing performance tuning for RE Engine
 */
#include <windows.h>
#include <iostream>
#include <algorithm>

namespace RE4Tweaks {

struct RTConfig {
    float rtResolutionScale = 0.5f;
    int rtReflectionBounces = 1;
    float rtShadowDistance = 30.0f;
    bool rtGlobalIllum = false;
    bool rtReflections = true;
    bool rtShadows = true;
    int rtSamplesPerPixel = 1;
    bool denoiserEnabled = true;
    float denoiserStrength = 0.8f;
};

static const RTConfig RT_OFF     = {0, 0, 0, false, false, false, 0, false, 0};
static const RTConfig RT_LOW     = {0.25f, 1, 15.0f, false, true, false, 1, true, 0.9f};
static const RTConfig RT_MEDIUM  = {0.5f, 1, 30.0f, false, true, true, 1, true, 0.8f};
static const RTConfig RT_HIGH    = {0.75f, 2, 50.0f, true, true, true, 2, true, 0.6f};
static const RTConfig RT_ULTRA   = {1.0f, 3, 80.0f, true, true, true, 4, true, 0.4f};

class RTOptimizer {
    RTConfig cfg;
    bool active = false;
public:
    bool Init(const std::string& preset = "medium") {
        if (preset == "off")        cfg = RT_OFF;
        else if (preset == "low")   cfg = RT_LOW;
        else if (preset == "medium")cfg = RT_MEDIUM;
        else if (preset == "high")  cfg = RT_HIGH;
        else if (preset == "ultra") cfg = RT_ULTRA;
        active = true;
        std::cout << "[RE4 RT] Preset: " << preset << std::endl;
        std::cout << "  Resolution scale: " << cfg.rtResolutionScale << std::endl;
        std::cout << "  Bounces: " << cfg.rtReflectionBounces << std::endl;
        std::cout << "  GI: " << (cfg.rtGlobalIllum ? "ON" : "OFF") << std::endl;
        std::cout << "  Shadows: " << (cfg.rtShadows ? "ON" : "OFF") << std::endl;
        return true;
    }
    void SetResScale(float s) { cfg.rtResolutionScale = std::clamp(s, 0.1f, 1.0f); }
    void SetBounces(int b) { cfg.rtReflectionBounces = std::clamp(b, 0, 4); }
    void ToggleGI(bool on) { cfg.rtGlobalIllum = on; }
    void ToggleShadows(bool on) { cfg.rtShadows = on; }
    void Shutdown() { active = false; std::cout << "[RE4 RT] Shutdown" << std::endl; }
};

} // namespace RE4Tweaks
