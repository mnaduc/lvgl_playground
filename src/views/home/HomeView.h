#pragma once

#include "lvgl.h"
#include "views/IView.h"
#include "views/home/IHomeView.h"

class HomePresenter;

class HomeView : public IView, public IHomeView {
public:
    explicit HomeView(HomePresenter& presenter);
    ~HomeView() override;

    void show() override;
    void showTemperature(int temp) override;

private:
    static void onClimateClicked(lv_event_t* e);
    void buildUi();

    lv_obj_t*     m_screen{nullptr};
    lv_obj_t*     m_arc{nullptr};
    lv_obj_t*     m_tempLabel{nullptr};
    HomePresenter& m_presenter;
};
