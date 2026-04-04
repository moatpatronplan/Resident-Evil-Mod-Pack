/*
 * Draw Distance — Resident Evil 4 Remake Mod Pack
 */
#include <iostream>
#include <fstream>

namespace RE4Tweaks {

struct DrawProfile {
    float terrain = 3000, enemies = 200, props = 600, shadows = 120;
};

static const DrawProfile POTATO   = {1500, 100, 300, 50};
static const DrawProfile BALANCED = {3000, 200, 600, 120};
static const DrawProfile QUALITY  = {5000, 350, 1000, 200};

class DrawDistance {
    DrawProfile p; bool active = false;
public:
    bool Init(const std::string& preset = "balanced") {
        if (preset == "potato") p = POTATO;
        else if (preset == "quality") p = QUALITY;
        else p = BALANCED;
        active = true;
        std::cout << "[RE4 Draw] " << preset << std::endl;
        return true;
    }
    void Shutdown() { active = false; }
};

} // namespace RE4Tweaks
