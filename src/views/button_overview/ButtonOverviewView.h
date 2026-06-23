#pragma once

#include "lvgl.h"
#include "views/IView.h"
#include "views/button_overview/ButtonOverviewViewModel.h"

#include <functional>
#include <kdbindings/signal.h>

class ButtonOverviewView : public IView {
public:
    explicit ButtonOverviewView(ButtonOverviewViewModel& viewModel);
    ~ButtonOverviewView() override;

    void show() override;

private:
    static void onToggleClicked(lv_event_t* e);

    void buildUi();
    static lv_obj_t* makeRow(lv_obj_t* parent);
    static void addRow(lv_obj_t* parent, const char* label,
                       std::function<void(lv_obj_t*)> buildContent);

    lv_obj_t* m_screen{nullptr};
    lv_obj_t* m_toggleStatusLabel{nullptr};
    ButtonOverviewViewModel& m_vm;

    KDBindings::ConnectionHandle m_toggleConnection;
};
