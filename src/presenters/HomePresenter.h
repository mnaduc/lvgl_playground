#pragma once

#include <functional>
#include "lvgl.h"
#include "models/TemperatureModel.h"

class IHomeView;

class HomePresenter {
public:
    explicit HomePresenter(TemperatureModel& model);
    ~HomePresenter();

    std::function<void()> onNavigateToClimate;

    void attach(IHomeView& view);
    void handleClimateRequested();

private:
    static void onTempChanged(lv_observer_t* obs, lv_subject_t* sub);

    IHomeView*        m_view{nullptr};
    TemperatureModel& m_model;
    lv_observer_t*    m_obs{nullptr};
};
