/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct grass_lod_range_param_st {
    /**
     * @brief LOD0-distance
     */
    float LOD0_range{0.f};

    /**
     * @brief LOD0-play
     */
    float LOD0_play{0.f};

    /**
     * @brief LOD1-distance
     */
    float LOD1_range{0.f};

    /**
     * @brief LOD1-Play
     */
    float LOD1_play{0.f};

    /**
     * @brief LOD2-distance
     */
    float LOD2_range{0.f};

    /**
     * @brief LOD2-Play
     */
    float LOD2_play{0.f};
};

};
};

static_assert(sizeof(er::paramdef::grass_lod_range_param_st) == 24,
              "GRASS_LOD_RANGE_PARAM_ST paramdef size does not match detected size");
