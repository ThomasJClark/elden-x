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
struct KEY_ASSIGN_PARAM_ST
{
    int padKeyId{-1};

    /**
     * @brief Keyboard modifier
     *
     * Keyboard modifier keys
     */
    int keyboardModifyKey{0};

    /**
     * @brief keyboard
     *
     * Keyboard (physical keys)
     */
    int keyboardKeyId{-1};

    /**
     * @brief Mouse modification
     *
     * Mouse modifier key
     */
    int mouseModifyKey{0};

    /**
     * @brief mouse
     *
     * Mouse (physical key)
     */
    int mouseKeyId{0};

    unsigned char reserved[12];
};

}; // namespace paramdef
}; // namespace er

static_assert(sizeof(er::paramdef::KEY_ASSIGN_PARAM_ST) == 32,
              "KEY_ASSIGN_PARAM_ST paramdef size does not match detected size");
