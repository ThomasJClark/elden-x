/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct se_activation_range_param_st {
    /**
     * @brief Activate distance
     *
     * Distance to enable placement SE (m) (0 or less: always enabled)
     */
    float activateRange{0.f};
};

};
};

static_assert(sizeof(er::paramdef::se_activation_range_param_st) == 4,
              "SE_ACTIVATION_RANGE_PARAM_ST paramdef size does not match detected size");
