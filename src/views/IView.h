#pragma once

#include "app/HeaderState.h"

class IView {
public:
    virtual ~IView() = default;
    virtual void show() = 0;
    virtual HeaderState& headerState() = 0;
};
