/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct cs_lighting_quality_detail {
    /**
     * @brief Local light effective distance coefficient
     *
     * Local light effective distance coefficient (smaller, it disappears at a
     * short distance)
     */
    float localLightDistFactor{0.75f};

    /**
     * @brief Local light shadow enabled
     */
    bool localLightShadowEnabled{true};

    /**
     * @brief Forward pass writing enabled
     */
    bool forwardPassLightingEnabled{true};

    /**
     * @brief Local light shadow spec level
     *
     * Local light shadow spec level. The larger the value, the more light
     * sources will be shadowed.
     */
    unsigned char localLightShadowSpecLevelMax{1};

    /**
     * @brief dmy
     */
    unsigned char dmy[1];
};

};
};
