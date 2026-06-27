#pragma once

#include <kdbindings/property.h>
#include <string>

struct HeaderState {
    explicit HeaderState(std::string initialTitle = {}, bool initialBackVisible = false)
        : title(std::move(initialTitle))
        , backVisible(initialBackVisible)
    {}

    KDBindings::Property<std::string> title;
    KDBindings::Property<bool>        backVisible;
};
