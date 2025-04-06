/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct direction_camera_param_st {
    /**
     * @brief Affected by options
     *
     * Is it affected by the production camera ON / OFF option?
     */
    bool isUseOption : 1 {false};

    unsigned char pad2 : 3;

    unsigned char pad1[15];
};

};
};

static_assert(sizeof(er::paramdef::direction_camera_param_st) == 16,
              "DIRECTION_CAMERA_PARAM_ST paramdef size does not match detected size");
