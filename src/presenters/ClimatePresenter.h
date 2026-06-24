#pragma once

#include "lvgl.h"
#include "models/TemperatureModel.h"

class IClimateView;

class ClimatePresenter {
public:
    explicit ClimatePresenter(TemperatureModel& model);
    ~ClimatePresenter();

    void attach(IClimateView& view);
    void handleIncrement();
    void handleDecrement();

private:
    static void onTempChanged(lv_observer_t* obs, lv_subject_t* sub);

    IClimateView*     m_view{nullptr};
    TemperatureModel& m_model;
    lv_observer_t*    m_obs{nullptr};
};
