#pragma once

#include "lvgl.h"
#include "views/IView.h"
#include "views/home/HomeViewModel.h"

#include <kdbindings/signal.h>

class HomeView : public IView {
public:
    explicit HomeView(HomeViewModel& vm);
    ~HomeView() override;

    void show() override;
    IViewModel& viewModel() override { return m_vm; }

private:
    static void onClimateClicked(lv_event_t* e);
    void buildUi();
    void updateTempLabel(int temp);

    lv_obj_t*    m_screen{nullptr};
    lv_obj_t*    m_arc{nullptr};
    lv_obj_t*    m_tempLabel{nullptr};
    HomeViewModel& m_vm;

    KDBindings::ConnectionHandle m_tempConn;
};
