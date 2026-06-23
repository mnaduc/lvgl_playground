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

    m_backBtn = lv_button_create(m_container);
    lv_obj_set_size(m_backBtn, 80, 36);
    lv_obj_align(m_backBtn, LV_ALIGN_LEFT_MID, 8, 0);
    lv_obj_add_event_cb(m_backBtn, onBackClicked, LV_EVENT_CLICKED, &vm);
    lv_obj_t* backLabel = lv_label_create(m_backBtn);
    lv_label_set_text(backLabel, LV_SYMBOL_LEFT " Back");
    lv_obj_center(backLabel);

    m_titleLabel = lv_label_create(m_container);
    lv_obj_set_style_text_font(m_titleLabel, &lv_font_montserrat_20, 0);
    lv_obj_align(m_titleLabel, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(m_titleLabel, vm.title.get().c_str());

    // Bind property changes to UI
    m_titleConn = vm.title.valueChanged().connect([this](const std::string& t) {
        lv_label_set_text(m_titleLabel, t.c_str());
    });
    m_backVisibleConn = vm.backVisible.valueChanged().connect([this](bool visible) {
        if (visible)
            lv_obj_remove_flag(m_backBtn, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(m_backBtn, LV_OBJ_FLAG_HIDDEN);
    });

    // Apply initial back-button visibility
    if (!vm.backVisible.get())
        lv_obj_add_flag(m_backBtn, LV_OBJ_FLAG_HIDDEN);
}

AppHeader::~AppHeader()
{
    m_titleConn.disconnect();
    m_backVisibleConn.disconnect();
    if (m_container)
        lv_obj_delete(m_container);
}

void AppHeader::onBackClicked(lv_event_t* e)
{
    auto* vm = static_cast<AppHeaderViewModel*>(lv_event_get_user_data(e));
    vm->requestBack();
}
