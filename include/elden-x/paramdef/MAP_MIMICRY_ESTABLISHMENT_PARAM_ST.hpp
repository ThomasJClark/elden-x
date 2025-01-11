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
struct map_mimicry_establishment_param_st
{
    /**
     * @brief Mimicry weight 0
     */
    float mimicryEstablishment0{-1.f};

    /**
     * @brief Mimicry weight 1
     */
    float mimicryEstablishment1{-1.f};

    /**
     * @brief Mimicry weight 2
     */
    float mimicryEstablishment2{-1.f};

    /**
     * @brief Mimicry 0 SFXID Forward swing
     */
    int mimicryBeginSfxId0{-1};

    /**
     * @brief Mimicry 0 SFXID body
     */
    int mimicrySfxId0{-1};

    /**
     * @brief Mimicry 0 SFXID release
     */
    int mimicryEndSfxId0{-1};

    /**
     * @brief Mimicry 1 SFXID Forward swing
     */
    int mimicryBeginSfxId1{-1};

    /**
     * @brief Mimicry 1 SFXID body
     */
    int mimicrySfxId1{-1};

    /**
     * @brief Mimicry 1 SFXID release
     */
    int mimicryEndSfxId1{-1};

    /**
     * @brief Mimicry 2 SFXID Forward swing
     */
    int mimicryBeginSfxId2{-1};

    /**
     * @brief Mimicry 2 SFXID body
     */
    int mimicrySfxId2{-1};

    /**
     * @brief Mimicry 2 SFXID cancellation
     */
    int mimicryEndSfxId2{-1};

    unsigned char pad1[16];
};

}; // namespace paramdef
}; // namespace er

static_assert(sizeof(er::paramdef::map_mimicry_establishment_param_st) == 64,
              "MAP_MIMICRY_ESTABLISHMENT_PARAM_ST paramdef size does not match detected "
              "size");
