#pragma once

#include "lvgl.h"

class TemperatureModel {
public:
    TemperatureModel()  { lv_subject_init_int(&targetTemperature, 20); }
    ~TemperatureModel() { lv_subject_deinit(&targetTemperature); }

    lv_subject_t targetTemperature;
};
