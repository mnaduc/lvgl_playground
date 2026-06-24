#include "views/climate/ClimateView.h"
#include "app/AppConstants.h"

#include <cstdio>

ClimateView::ClimateView(ClimateViewModel& vm)
    : m_vm(vm)
{
    m_screen = lv_obj_create(NULL);
    buildUi();
}

ClimateView::~ClimateView()
{
    m_tempConn.disconnect();
    if (m_screen)
        lv_obj_delete(m_screen);
}

void ClimateView::show()
{
    lv_scr_load(m_screen);
}

void ClimateView::buildUi()
{
    lv_obj_set_style_bg_color(m_screen, lv_color_hex(0xF0F4F8), 0);

    lv_obj_t* label = lv_label_create(m_screen);
    lv_label_set_text(label, "Adjust Temperature");
    lv_obj_set_style_text_color(label, lv_palette_main(LV_PALETTE_GREY), 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -100);

    // Minus button — circular, blue (cool)
    lv_obj_t* minusBtn = lv_button_create(m_screen);
    lv_obj_set_size(minusBtn, 80, 80);
    lv_obj_set_style_radius(minusBtn, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(minusBtn, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_obj_align(minusBtn, LV_ALIGN_CENTER, -150, 0);
    lv_obj_add_event_cb(minusBtn, onMinusClicked, LV_EVENT_CLICKED, this);
    lv_obj_t* minusLabel = lv_label_create(minusBtn);
    lv_label_set_text(minusLabel, LV_SYMBOL_MINUS);
    lv_obj_set_style_text_font(minusLabel, &lv_font_montserrat_28, 0);
    lv_obj_center(minusLabel);

    // Temperature value
    m_tempLabel = lv_label_create(m_screen);
    lv_obj_set_style_text_font(m_tempLabel, &lv_font_montserrat_48, 0);
    updateTempLabel(m_vm.targetTemperature().get());
    lv_obj_align(m_tempLabel, LV_ALIGN_CENTER, 0, 0);

    // Plus button — circular, orange (warm)
    lv_obj_t* plusBtn = lv_button_create(m_screen);
    lv_obj_set_size(plusBtn, 80, 80);
    lv_obj_set_style_radius(plusBtn, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_color(plusBtn, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_obj_align(plusBtn, LV_ALIGN_CENTER, 150, 0);
    lv_obj_add_event_cb(plusBtn, onPlusClicked, LV_EVENT_CLICKED, this);
    lv_obj_t* plusLabel = lv_label_create(plusBtn);
    lv_label_set_text(plusLabel, LV_SYMBOL_PLUS);
    lv_obj_set_style_text_font(plusLabel, &lv_font_montserrat_28, 0);
    lv_obj_center(plusLabel);

    m_tempConn = m_vm.targetTemperature().valueChanged().connect([this](int temp) {
        updateTempLabel(temp);
    });
}

void ClimateView::updateTempLabel(int temp)
{
    char buf[16];
    snprintf(buf, sizeof(buf), "%d\xc2\xb0""C", temp);
    lv_label_set_text(m_tempLabel, buf);
}

void ClimateView::onPlusClicked(lv_event_t* e)
{
    auto* self = static_cast<ClimateView*>(lv_event_get_user_data(e));
    self->m_vm.increment();
}

void ClimateView::onMinusClicked(lv_event_t* e)
{
    auto* self = static_cast<ClimateView*>(lv_event_get_user_data(e));
    self->m_vm.decrement();
}
