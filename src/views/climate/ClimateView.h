#pragma once

#include "lvgl.h"
#include "views/IView.h"
#include "views/climate/ClimateViewModel.h"

#include <kdbindings/signal.h>

class ClimateView : public IView {
public:
    explicit ClimateView(ClimateViewModel& vm);
    ~ClimateView() override;

    void show() override;
    IViewModel& viewModel() override { return m_vm; }

private:
    static void onPlusClicked(lv_event_t* e);
    static void onMinusClicked(lv_event_t* e);
    void buildUi();
    void updateTempLabel(int temp);

    lv_obj_t*     m_screen{nullptr};
    lv_obj_t*     m_tempLabel{nullptr};
    ClimateViewModel& m_vm;

    KDBindings::ConnectionHandle m_tempConn;
};
