#include "views/home/HomeView.h"
#include "app/AppConstants.h"

HomeView::HomeView(HomeViewModel& vm)
    : m_vm(vm)
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

void HomeView::buildUi()
{
    lv_obj_set_style_bg_color(m_screen, lv_color_hex(0xF0F4F8), 0);

    // Arc gauge — non-interactive, 270° sweep, 0–40°C range
    lv_obj_t* arc = lv_arc_create(m_screen);
    lv_obj_set_size(arc, 220, 220);
    lv_obj_align(arc, LV_ALIGN_CENTER, 0, -10);
    lv_arc_set_rotation(arc, 135);
    lv_arc_set_bg_angles(arc, 0, 270);
    lv_arc_set_range(arc, 0, 40);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
    lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_arc_color(arc, lv_palette_main(LV_PALETTE_BLUE), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(arc, 14, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc, lv_palette_lighten(LV_PALETTE_BLUE, 4), LV_PART_MAIN);
    lv_obj_set_style_arc_width(arc, 14, LV_PART_MAIN);
    lv_arc_bind_value(arc, m_vm.targetTemperature());

    // Temperature value centered inside the arc
    lv_obj_t* tempLabel = lv_label_create(m_screen);
    lv_obj_set_style_text_font(tempLabel, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(tempLabel, lv_palette_darken(LV_PALETTE_BLUE, 2), 0);
    lv_obj_align(tempLabel, LV_ALIGN_CENTER, 0, -15);
    lv_label_bind_text(tempLabel, m_vm.targetTemperature(), "%d\xc2\xb0""C");

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
    self->m_vm.requestClimate();
}
