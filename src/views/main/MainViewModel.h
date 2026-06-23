#pragma once

#include <kdbindings/signal.h>

class MainViewModel {
public:
    KDBindings::Signal<> navigateToButtonOverview;

    void requestButtonOverview() {
        navigateToButtonOverview.emit();
    }
};
