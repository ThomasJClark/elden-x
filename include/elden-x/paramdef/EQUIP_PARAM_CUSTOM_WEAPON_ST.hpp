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
struct equip_param_custom_weapon_st
{
    /**
     * @brief Weapon base ID
     */
    int baseWepId{0};

    /**
     * @brief Magic stone ID
     */
    int gemId{0};

    /**
     * @brief Enhancement value
     */
    unsigned char reinforceLv{0};

    unsigned char pad[7];
};

}; // namespace paramdef
}; // namespace er

static_assert(sizeof(er::paramdef::equip_param_custom_weapon_st) == 16,
              "EQUIP_PARAM_CUSTOM_WEAPON_ST paramdef size does not match detected size");
