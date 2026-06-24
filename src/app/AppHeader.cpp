#include "app/AppHeader.h"
#include "app/AppConstants.h"

AppHeader::AppHeader(AppHeaderViewModel& vm)
{
    m_container = lv_obj_create(lv_layer_top());
    lv_obj_set_size(m_container, LV_PCT(100), HEADER_HEIGHT);
    lv_obj_set_pos(m_container, 0, 0);
    lv_obj_set_style_radius(m_container, 0, 0);
    lv_obj_set_style_border_width(m_container, 0, 0);
    lv_obj_set_style_pad_all(m_container, 0, 0);
    lv_obj_remove_flag(m_container, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t* backBtn = lv_button_create(m_container);
    lv_obj_set_size(backBtn, 80, 36);
    lv_obj_align(backBtn, LV_ALIGN_LEFT_MID, 8, 0);
    lv_obj_add_event_cb(backBtn, onBackClicked, LV_EVENT_CLICKED, &vm);
    lv_obj_t* backLabel = lv_label_create(backBtn);
    lv_label_set_text(backLabel, LV_SYMBOL_LEFT " Back");
    lv_obj_center(backLabel);

    // Hide back button when backVisible == 0, show when == 1
    lv_obj_bind_flag_if_eq(backBtn, &vm.backVisible, LV_OBJ_FLAG_HIDDEN, 0);

    lv_obj_t* titleLabel = lv_label_create(m_container);
    lv_obj_set_style_text_font(titleLabel, &lv_font_montserrat_20, 0);
    lv_obj_align(titleLabel, LV_ALIGN_CENTER, 0, 0);

    // Bind title label text directly to the string subject
    lv_label_bind_text(titleLabel, &vm.title, NULL);
}

AppHeader::~AppHeader()
{
    if (m_container)
        lv_obj_delete(m_container);
}

void AppHeader::onBackClicked(lv_event_t* e)
{
    auto* vm = static_cast<AppHeaderViewModel*>(lv_event_get_user_data(e));
    vm->requestBack();
}
