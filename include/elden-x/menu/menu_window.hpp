#pragma once

namespace er {
namespace CS {

/**
 * Base class of all menu windows, such as talkscript dialogs, HUDs, pause menus, etc.
 */
class MenuWindow {
public:
    virtual ~MenuWindow() = default;

    unsigned char unk8[0xa30];
};

}
}
