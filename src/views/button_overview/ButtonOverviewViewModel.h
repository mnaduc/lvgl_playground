#pragma once

#include <kdbindings/signal.h>
#include <kdbindings/property.h>

class ButtonOverviewViewModel {
public:
    KDBindings::Signal<> navigateBack;

    KDBindings::Property<bool> toggleState{false};

    void requestBack() {
        navigateBack.emit();
    }

    void onToggleChanged(bool state) {
        toggleState = state;
    }
};
