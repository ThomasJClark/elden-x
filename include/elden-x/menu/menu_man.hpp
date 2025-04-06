#pragma once

#include "popup_menu.hpp"

#include "../singletons.hpp"

namespace er {
namespace CS {

class CSMenuManImp : public FD4::FD4Singleton<CSMenuManImp, FD4::singleton_index::CSMenuMan> {
public:
    virtual ~CSMenuManImp() = default;

    unsigned char unk8[0x78];

    CS::CSPopupMenu *popup_menu;
};

}
}
