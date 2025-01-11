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
struct cs_texture_filter_quality_detail
{
    /**
     * @brief filter
     */
    unsigned char filter{3};

    /**
     * @brief dmy
     */
    unsigned char dmy[3];

    /**
     * @brief Aniso level
     */
    unsigned int maxAnisoLevel{4};
};

}; // namespace paramdef
}; // namespace er
