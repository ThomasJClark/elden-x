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
struct SOUND_ASSET_SOUND_OBJ_ENABLE_DIST_PARAM_ST
{
    /**
     * @brief Asset sound sound source effective distance setting [m]
     *
     * Asset sound sound source effective distance [m] (less than 0: invalid)
     */
    float SoundObjEnableDist{-1.f};
};

}; // namespace paramdef
}; // namespace er

static_assert(sizeof(er::paramdef::SOUND_ASSET_SOUND_OBJ_ENABLE_DIST_PARAM_ST) == 4,
              "SOUND_ASSET_SOUND_OBJ_ENABLE_DIST_PARAM_ST paramdef size does not match "
              "detected size");
