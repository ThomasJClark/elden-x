/* This file was automatically generated from XML paramdefs. */
#pragma once

namespace er {
namespace paramdef {
/**
 * @brief This struct was automatically generated from XML paramdefs.
 *
 */
struct menu_value_table_spec {
    /**
     * @brief Value to compare
     */
    int value{0};

    /**
     * @brief Converted text ID
     */
    int textId{0};

    /**
     * @brief Comparison type
     */
    signed char compareType{0};

    unsigned char padding[3];
};

};
};

static_assert(sizeof(er::paramdef::menu_value_table_spec) == 12,
              "MENU_VALUE_TABLE_SPEC paramdef size does not match detected size");
