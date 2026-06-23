#pragma once

#include "lvgl.h"
#include "views/IView.h"
#include "views/main/MainViewModel.h"

class MainView : public IView {
public:
    explicit MainView(MainViewModel& viewModel);
    ~MainView() override;

    void show() override;

private:
    static void onNavButtonClicked(lv_event_t* e);
    void buildUi();

    lv_obj_t* m_screen{nullptr};
    MainViewModel& m_vm;
};
