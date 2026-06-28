#pragma once

#include "app/HeaderState.h"

class IViewModel {
public:
    virtual ~IViewModel() = default;
    virtual HeaderState& headerState() = 0;
};
