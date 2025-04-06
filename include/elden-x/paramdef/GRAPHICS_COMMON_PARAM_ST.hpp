/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct graphics_common_param_st {
    /**
     * @brief Decal generation position offset when a bullet hits HIT INS
     *
     * The position where the decal that occurs when hitting HIT INS is offset
     * by this value in the normal direction.
     */
    float hitBulletDecalOffset_HitIns{0.05f};

    unsigned char reserved02[8];

    /**
     * @brief Decal fade range when the character gets wet [m]
     *
     * Fade range that erases decals when the character gets wet [m]
     */
    float charaWetDecalFadeRange{0.6f};

    unsigned char reserved04[240];
};

};
};

static_assert(sizeof(er::paramdef::graphics_common_param_st) == 256,
              "GRAPHICS_COMMON_PARAM_ST paramdef size does not match detected size");
