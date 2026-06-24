#pragma once

#include "lvgl.h"
#include "views/IView.h"
#include "views/climate/ClimateViewModel.h"

class ClimateView : public IView {
public:
    explicit ClimateView(ClimateViewModel& vm);
    ~ClimateView() override;

    void show() override;

private:
    static void onPlusClicked(lv_event_t* e);
    static void onMinusClicked(lv_event_t* e);
    void buildUi();

    lv_obj_t*     m_screen{nullptr};
    ClimateViewModel& m_vm;
};
