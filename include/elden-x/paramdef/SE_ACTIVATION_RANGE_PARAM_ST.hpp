/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er
{
namespace paramdef
{
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct SE_ACTIVATION_RANGE_PARAM_ST
{
    /**
     * @brief Activate distance
     *
     * Distance to enable placement SE (m) (0 or less: always enabled)
     */
    float activateRange{0.f};
};

}; // namespace paramdef
}; // namespace er

static_assert(sizeof(er::paramdef::SE_ACTIVATION_RANGE_PARAM_ST) == 4,
              "SE_ACTIVATION_RANGE_PARAM_ST paramdef size does not match detected size");
