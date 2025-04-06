#pragma once

#include "menu_window.hpp"

namespace er {
namespace CS {

class CSMenuMan;

class CSPopupMenu {
public:
    virtual ~CSPopupMenu() = default;

    CS::CSMenuMan *owner;
    CS::MenuWindow *window;
};

}
}
