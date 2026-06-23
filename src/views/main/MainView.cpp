#include "views/main/MainView.h"

MainView::MainView(MainViewModel& viewModel)
    : m_vm(viewModel)
{
    m_screen = lv_obj_create(NULL);
    buildUi();
}

MainView::~MainView()
{
    if (m_screen) {
        lv_obj_delete(m_screen);
    }
}

void MainView::show()
{
    lv_scr_load(m_screen);
}

void MainView::buildUi()
{
    lv_obj_t* title = lv_label_create(m_screen);
    lv_label_set_text(title, "LVGL Playground");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_20, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 24);

    lv_obj_t* subtitle = lv_label_create(m_screen);
    lv_label_set_text(subtitle, "Select a widget to explore:");
    lv_obj_align(subtitle, LV_ALIGN_TOP_MID, 0, 60);

    // Button Overview navigation button
    lv_obj_t* btn = lv_button_create(m_screen);
    lv_obj_set_size(btn, 220, 50);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(btn, onNavButtonClicked, LV_EVENT_CLICKED, this);

    lv_obj_t* btnLabel = lv_label_create(btn);
    lv_label_set_text(btnLabel, LV_SYMBOL_RIGHT "  Button Overview");
    lv_obj_center(btnLabel);
}

void MainView::onNavButtonClicked(lv_event_t* e)
{
    auto* self = static_cast<MainView*>(lv_event_get_user_data(e));
    self->m_vm.requestButtonOverview();
}
