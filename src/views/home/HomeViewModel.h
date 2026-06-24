#pragma once

#include <kdbindings/signal.h>
#include "models/TemperatureModel.h"

class HomeViewModel {
public:
    explicit HomeViewModel(TemperatureModel& model) : m_model(model) {}

    KDBindings::Signal<> navigateToClimate;

    KDBindings::Property<int>& targetTemperature() { return m_model.targetTemperature; }

    void requestClimate() { navigateToClimate.emit(); }

private:
    TemperatureModel& m_model;
};
