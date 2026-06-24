#pragma once

#include "models/TemperatureModel.h"

class ClimateViewModel {
public:
    explicit ClimateViewModel(TemperatureModel& model) : m_model(model) {}

    lv_subject_t* targetTemperature() { return &m_model.targetTemperature; }

    void increment() { lv_subject_set_int(&m_model.targetTemperature, lv_subject_get_int(&m_model.targetTemperature) + 1); }
    void decrement() { lv_subject_set_int(&m_model.targetTemperature, lv_subject_get_int(&m_model.targetTemperature) - 1); }

private:
    TemperatureModel& m_model;
};
