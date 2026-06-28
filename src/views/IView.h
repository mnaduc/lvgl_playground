#pragma once

#include "views/IViewModel.h"

class IView {
public:
    virtual ~IView() = default;
    virtual void show() = 0;
    virtual IViewModel& viewModel() = 0;
};
