/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er
{
namespace paramdef
{

struct sign_puddle_sub_category_param_st
{
    /**
     * @brief startPad
     */
    unsigned char startPad[4];

    /**
     * @brief signPuddleCategoryText
     */
    int signPuddleCategoryText{0};

    /**
     * @brief signPuddleTabId
     */
    unsigned short signPuddleTabId{0};

    unsigned short unknown_0xa{0};

    /**
     * @brief endPad
     */
    unsigned char endPad[4];
};

}; // namespace paramdef
}; // namespace er
