#pragma once

#include "lvgl.h"
#include "views/IView.h"
#include "views/home/HomeViewModel.h"

class HomeView : public IView {
public:
    explicit HomeView(HomeViewModel& vm);
    ~HomeView() override;

    void show() override;

private:
    static void onClimateClicked(lv_event_t* e);
    void buildUi();

    lv_obj_t*    m_screen{nullptr};
    HomeViewModel& m_vm;
};
