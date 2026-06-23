#pragma once

#include "lvgl.h"
#include "views/IView.h"
#include "views/button_overview/ButtonOverviewViewModel.h"

#include <kdbindings/binding.h>

class ButtonOverviewView : public IView {
public:
    explicit ButtonOverviewView(ButtonOverviewViewModel& viewModel);
    ~ButtonOverviewView() override;

    void show() override;

private:
    static void onBackClicked(lv_event_t* e);
    static void onToggleClicked(lv_event_t* e);
    void buildUi();

    lv_obj_t* m_screen{nullptr};
    lv_obj_t* m_toggleStatusLabel{nullptr};
    ButtonOverviewViewModel& m_vm;

    KDBindings::ConnectionHandle m_toggleConnection;
};
