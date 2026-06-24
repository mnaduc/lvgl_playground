#pragma once

#include <kdbindings/property.h>

class TemperatureModel {
public:
    KDBindings::Property<int> targetTemperature{20};
};
