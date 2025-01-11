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
struct final_damage_rate_param_st
{
    /**
     * @brief The physical damage rate multiplier.
     *
     */
    float physRate{0.f};

    /**
     * @brief The magic damage rate multiplier.
     *
     */
    float magRate{0.f};

    /**
     * @brief The fire damage rate multiplier.
     *
     */
    float fireRate{0.f};

    /**
     * @brief The lightning damage rate multiplier.
     *
     */
    float thunRate{0.f};

    /**
     * @brief The holy damage rate multiplier.
     *
     */
    float darkRate{0.f};

    /**
     * @brief The stamina damage rate multiplier.
     *
     */
    float staminaRate{0.f};

    /**
     * @brief The super armor damage rate multiplier.
     *
     */
    float saRate{0.f};
};

}; // namespace paramdef
}; // namespace er

static_assert(sizeof(er::paramdef::final_damage_rate_param_st) == 28,
              "FINAL_DAMAGE_RATE_PARAM_ST paramdef size does not match detected size");
