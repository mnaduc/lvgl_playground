#pragma once

#include "models/TemperatureModel.h"

class ClimateViewModel {
public:
    explicit ClimateViewModel(TemperatureModel& model) : m_model(model) {}

    KDBindings::Property<int>& targetTemperature() { return m_model.targetTemperature; }

    void increment() { m_model.targetTemperature = m_model.targetTemperature.get() + 1; }
    void decrement() { m_model.targetTemperature = m_model.targetTemperature.get() - 1; }

private:
    TemperatureModel& m_model;
};
