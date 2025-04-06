#pragma once

#include "popup_menu.hpp"

#include "../singletons.hpp"

namespace er {
namespace CS {

class CSMenuMan : public FD4::FD4Singleton<CSMenuMan, FD4::singleton_index::CSMenuMan> {
public:
    virtual ~CSMenuMan() = default;

    unsigned char unk8[0x78];

    CS::CSPopupMenu *popup_menu;
};

typedef CSMenuMan CSMenuManImp;
}
}
