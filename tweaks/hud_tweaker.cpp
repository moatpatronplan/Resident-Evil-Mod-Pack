/*
 * HUD Tweaker — Resident Evil 4 Remake Mod Pack
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

namespace RE4Tweaks {

struct HUDEl { std::string name; bool vis = true; float x, y, scale = 1, alpha = 1; };

class HUDTweaker {
    std::unordered_map<std::string, HUDEl> els;
    void Reg(const std::string& n, float x, float y) { els[n] = {n, true, x, y}; }
public:
    void Init() {
        Reg("health_bar", 0.05f, 0.92f); Reg("ammo_counter", 0.9f, 0.92f);
        Reg("crosshair", 0.5f, 0.5f); Reg("interaction_prompt", 0.5f, 0.7f);
        Reg("knife_durability", 0.12f, 0.88f); Reg("grenade_counter", 0.85f, 0.88f);
        Reg("boss_health", 0.3f, 0.05f); Reg("typewriter_prompt", 0.5f, 0.6f);
        Reg("map_overlay", 0.5f, 0.5f); Reg("objective_marker", 0.5f, 0.15f);
        std::cout << "[RE4 HUD] " << els.size() << " elements" << std::endl;
    }
    void SetScale(const std::string& n, float s) {
        if (els.count(n)) els[n].scale = std::clamp(s, 0.1f, 5.0f);
    }
    void SetVis(const std::string& n, bool v) { if (els.count(n)) els[n].vis = v; }
    void Shutdown() { std::cout << "[RE4 HUD] Shutdown" << std::endl; }
};

} // namespace RE4Tweaks
