#pragma once

#include <functional>
#include "models/TemperatureModel.h"

class HomeViewModel {
public:
    explicit HomeViewModel(TemperatureModel& model) : m_model(model) {}

    std::function<void()> onNavigateToClimate;

    lv_subject_t* targetTemperature() { return &m_model.targetTemperature; }

    void requestClimate() { if (onNavigateToClimate) onNavigateToClimate(); }

private:
    TemperatureModel& m_model;
};
