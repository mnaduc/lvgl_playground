#include "views/home/HomeView.h"
#include "app/AppConstants.h"

#include <cstdio>

HomeView::HomeView(HomeViewModel& vm)
    : m_vm(vm)
{
    m_screen = lv_obj_create(NULL);
    buildUi();
}

HomeView::~HomeView()
{
    m_tempConn.disconnect();
    if (m_screen)
        lv_obj_delete(m_screen);
}

void HomeView::show()
{
    lv_scr_load(m_screen);
}

void HomeView::buildUi()
{
    lv_obj_t* label = lv_label_create(m_screen);
    lv_label_set_text(label, "Target Temperature");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -60);

    m_tempLabel = lv_label_create(m_screen);
    lv_obj_set_style_text_font(m_tempLabel, &lv_font_montserrat_48, 0);
    updateTempLabel(m_vm.targetTemperature().get());
    lv_obj_align(m_tempLabel, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t* btn = lv_button_create(m_screen);
    lv_obj_set_size(btn, 200, 48);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 70);
    lv_obj_add_event_cb(btn, onClimateClicked, LV_EVENT_CLICKED, this);

    lv_obj_t* btnLabel = lv_label_create(btn);
    lv_label_set_text(btnLabel, "Set Temperature");
    lv_obj_center(btnLabel);

    m_tempConn = m_vm.targetTemperature().valueChanged().connect([this](int temp) {
        updateTempLabel(temp);
    });
}

void HomeView::updateTempLabel(int temp)
{
    char buf[16];
    snprintf(buf, sizeof(buf), "%d\xc2\xb0""C", temp);
    lv_label_set_text(m_tempLabel, buf);
}

void HomeView::onClimateClicked(lv_event_t* e)
{
    auto* self = static_cast<HomeView*>(lv_event_get_user_data(e));
    self->m_vm.requestClimate();
}
