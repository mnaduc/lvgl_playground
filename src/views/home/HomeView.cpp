#include "views/home/HomeView.h"
#include "presenters/HomePresenter.h"
#include "app/AppConstants.h"

#include <cstdio>

HomeView::HomeView(HomePresenter& presenter)
    : m_presenter(presenter)
{
    m_screen = lv_obj_create(NULL);
    buildUi();
}

HomeView::~HomeView()
{
    if (m_screen)
        lv_obj_delete(m_screen);
}

void HomeView::show()
{
    lv_scr_load(m_screen);
}

void HomeView::showTemperature(int temp)
{
    char buf[16];
    snprintf(buf, sizeof(buf), "%d\xc2\xb0""C", temp);
    lv_label_set_text(m_tempLabel, buf);
    lv_arc_set_value(m_arc, temp);
}

void HomeView::buildUi()
{
    lv_obj_set_style_bg_color(m_screen, lv_color_hex(0xF0F4F8), 0);

    m_arc = lv_arc_create(m_screen);
    lv_obj_set_size(m_arc, 220, 220);
    lv_obj_align(m_arc, LV_ALIGN_CENTER, 0, -10);
    lv_arc_set_rotation(m_arc, 135);
    lv_arc_set_bg_angles(m_arc, 0, 270);
    lv_arc_set_range(m_arc, 0, 40);
    lv_obj_remove_style(m_arc, NULL, LV_PART_KNOB);
    lv_obj_remove_flag(m_arc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_color(m_arc, lv_palette_main(LV_PALETTE_BLUE), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(m_arc, 14, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(m_arc, lv_palette_lighten(LV_PALETTE_BLUE, 4), LV_PART_MAIN);
    lv_obj_set_style_arc_width(m_arc, 14, LV_PART_MAIN);

    m_tempLabel = lv_label_create(m_screen);
    lv_obj_set_style_text_font(m_tempLabel, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(m_tempLabel, lv_palette_darken(LV_PALETTE_BLUE, 2), 0);
    lv_obj_align(m_tempLabel, LV_ALIGN_CENTER, 0, -15);

    lv_obj_t* subtitle = lv_label_create(m_screen);
    lv_label_set_text(subtitle, "Target Temperature");
    lv_obj_set_style_text_color(subtitle, lv_palette_main(LV_PALETTE_GREY), 0);
    lv_obj_align(subtitle, LV_ALIGN_CENTER, 0, 35);

    lv_obj_t* btn = lv_button_create(m_screen);
    lv_obj_set_size(btn, 200, 48);
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -25);
    lv_obj_add_event_cb(btn, onClimateClicked, LV_EVENT_CLICKED, this);
    lv_obj_t* btnLabel = lv_label_create(btn);
    lv_label_set_text(btnLabel, "Set Temperature");
    lv_obj_center(btnLabel);
}

void HomeView::onClimateClicked(lv_event_t* e)
{
    auto* self = static_cast<HomeView*>(lv_event_get_user_data(e));
    self->m_presenter.handleClimateRequested();
}
