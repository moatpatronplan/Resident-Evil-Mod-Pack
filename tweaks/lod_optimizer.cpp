/*
 * LOD Optimizer — Resident Evil 4 Remake Mod Pack
 */
#include <iostream>
#include <algorithm>

namespace RE4Tweaks {

struct LODCfg { float bias = 1.5f, speed = 2.0f; int maxLOD = 4; };

class LODOptimizer {
    LODCfg cfg; bool active = false;
public:
    void Init(const LODCfg& c = {}) {
        cfg = c; active = true;
        std::cout << "[RE4 LOD] Bias " << cfg.bias << "x" << std::endl;
    }
    void SetBias(float b) { cfg.bias = std::clamp(b, 0.5f, 3.0f); }
    void Shutdown() { active = false; }
};

} // namespace RE4Tweaks
