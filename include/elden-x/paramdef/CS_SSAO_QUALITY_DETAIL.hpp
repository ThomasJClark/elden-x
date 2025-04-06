/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct cs_ssao_quality_detail {
    /**
     * @brief SSAO enabled
     */
    bool enabled{true};

    /**
     * @brief Reprojection enabled
     *
     * When reprojection is forcibly enabled, Prevent Ghost is also enabled.
     */
    unsigned char cs_reprojEnabledType{1};

    /**
     * @brief Bilateral upscale effective
     */
    unsigned char cs_upScaleEnabledType{0};

    /**
     * @brief Valid to use normals
     */
    unsigned char cs_useNormalEnabledType{1};

    /**
     * @brief dmy
     */
    unsigned char dmy[1];
};

};
};
