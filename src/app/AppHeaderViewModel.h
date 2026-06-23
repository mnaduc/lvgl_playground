#pragma once

#include <kdbindings/signal.h>
#include <kdbindings/property.h>

#include <string>

class AppHeaderViewModel {
public:
    KDBindings::Property<std::string> title{std::string{}};
    KDBindings::Property<bool>        backVisible{false};
    KDBindings::Signal<>              backRequested;

    void requestBack() { backRequested.emit(); }
};
