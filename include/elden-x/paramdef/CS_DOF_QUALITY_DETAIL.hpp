/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct cs_dof_quality_detail {
    /**
     * @brief DOF permission
     */
    bool enabled{true};

    /**
     * @brief dmy
     */
    unsigned char dmy[3];

    /**
     * @brief Change HiResolutionBlur settings
     *
     * Change the HiResolutionBlur setting (-1: forced off, 0: as-is, 1: forced
     * on)
     */
    int forceHiResoBlur{-1};

    /**
     * @brief Maximum blur level
     *
     * Maximum blur level. 2: Maximum, 1: Level to one paragraph, 0: Further
     * reduce accuracy
     */
    int maxBlurLevel{1};
};

};
};
