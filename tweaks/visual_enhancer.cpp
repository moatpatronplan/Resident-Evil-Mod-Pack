/*
 * Visual Enhancer — Resident Evil 4 Remake Mod Pack
 */
#include <iostream>
#include <algorithm>

namespace RE4Tweaks {

struct VisualCfg {
    float sharpen = 0.4f, contrast = 1.08f, saturation = 1.0f;
    bool removeGrain = true, removeCA = true, removeMotionBlur = false;
    float horrorAtmosphere = 1.2f;
};

class VisualEnhancer {
    VisualCfg cfg; bool active = false;
public:
    void Init(const VisualCfg& c = {}) {
        cfg = c; active = true;
        std::cout << "[RE4 Visual] Sharpen " << cfg.sharpen
                  << " Horror boost " << cfg.horrorAtmosphere << "x" << std::endl;
    }
    void SetSharpen(float s) { cfg.sharpen = std::clamp(s, 0.f, 2.f); }
    void SetHorror(float h) { cfg.horrorAtmosphere = std::clamp(h, 0.5f, 2.0f); }
    void Shutdown() { active = false; }
};

} // namespace RE4Tweaks
