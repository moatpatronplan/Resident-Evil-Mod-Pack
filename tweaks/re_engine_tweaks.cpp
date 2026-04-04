/*
 * RE Engine Tweaks — Resident Evil 4 Remake Mod Pack
 * Hidden engine variables, mesh/hair/SSS quality
 */
#include <windows.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

namespace RE4Tweaks {

struct REEngineConfig {
    float meshQuality = 1.0f;
    int hairStrandCount = 64;
    float sssQuality = 1.0f;
    float volumetricFogDensity = 1.0f;
    int shadowMapRes = 2048;
    float contactShadowLength = 0.02f;
    bool enableHairPhysics = true;
    float clothSimQuality = 1.0f;
    int maxDecals = 256;
    float waterReflectionRes = 0.5f;
};

static const REEngineConfig PRESET_POTATO   = {0.5f, 16, 0.3f, 0.3f, 512, 0.005f, false, 0.3f, 64, 0.25f};
static const REEngineConfig PRESET_BALANCED = {0.8f, 32, 0.7f, 0.6f, 1024, 0.01f, true, 0.7f, 128, 0.5f};
static const REEngineConfig PRESET_QUALITY  = {1.0f, 64, 1.0f, 1.0f, 2048, 0.02f, true, 1.0f, 256, 0.75f};
static const REEngineConfig PRESET_ULTRA    = {1.5f, 128, 1.5f, 1.5f, 4096, 0.04f, true, 1.5f, 512, 1.0f};

class REEngineTweaks {
    REEngineConfig cfg;
    std::unordered_map<std::string, float*> varMap;
    bool active = false;

    void BuildVarMap() {
        varMap["mesh_quality"] = &cfg.meshQuality;
        varMap["sss_quality"] = &cfg.sssQuality;
        varMap["fog_density"] = &cfg.volumetricFogDensity;
        varMap["contact_shadow"] = &cfg.contactShadowLength;
        varMap["cloth_quality"] = &cfg.clothSimQuality;
        varMap["water_reflect"] = &cfg.waterReflectionRes;
    }
public:
    bool Init(const std::string& preset = "balanced") {
        if (preset == "potato")        cfg = PRESET_POTATO;
        else if (preset == "balanced") cfg = PRESET_BALANCED;
        else if (preset == "quality")  cfg = PRESET_QUALITY;
        else if (preset == "ultra")    cfg = PRESET_ULTRA;

        BuildVarMap();
        active = true;
        std::cout << "[RE4 Engine] Preset: " << preset << std::endl;
        std::cout << "  Mesh: " << cfg.meshQuality << " Hair: " << cfg.hairStrandCount << std::endl;
        std::cout << "  SSS: " << cfg.sssQuality << " Fog: " << cfg.volumetricFogDensity << std::endl;
        std::cout << "  Shadows: " << cfg.shadowMapRes << "px Decals: " << cfg.maxDecals << std::endl;
        return true;
    }

    bool SetVar(const std::string& name, float value) {
        auto it = varMap.find(name);
        if (it == varMap.end()) return false;
        *it->second = value;
        std::cout << "[RE4 Engine] " << name << " = " << value << std::endl;
        return true;
    }

    void SetHairStrands(int count) { cfg.hairStrandCount = std::clamp(count, 8, 256); }
    void SetShadowRes(int res) { cfg.shadowMapRes = std::clamp(res, 256, 8192); }
    void ToggleHairPhysics(bool on) { cfg.enableHairPhysics = on; }

    void Shutdown() {
        active = false;
        std::cout << "[RE4 Engine] Shutdown" << std::endl;
    }
};

} // namespace RE4Tweaks
