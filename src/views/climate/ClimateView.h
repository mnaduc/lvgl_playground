#pragma once

#include "lvgl.h"
#include "views/IView.h"
#include "views/climate/IClimateView.h"

class ClimatePresenter;

class ClimateView : public IView, public IClimateView {
public:
    explicit ClimateView(ClimatePresenter& presenter);
    ~ClimateView() override;

    void show() override;
    void showTemperature(int temp) override;

private:
    static void onPlusClicked(lv_event_t* e);
    static void onMinusClicked(lv_event_t* e);
    void buildUi();

    lv_obj_t*      m_screen{nullptr};
    lv_obj_t*      m_tempLabel{nullptr};
    ClimatePresenter& m_presenter;
};
