#include "app/AppHeader.h"
#include "app/AppConstants.h"

AppHeader::AppHeader(AppHeaderPresenter& presenter)
    : m_presenter(presenter)
{
    buildUi();
    presenter.attachView(*this);
}

AppHeader::~AppHeader()
{
    if (m_container)
        lv_obj_delete(m_container);
}

void AppHeader::buildUi()
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
    lv_obj_add_event_cb(m_backBtn, onBackClicked, LV_EVENT_CLICKED, &m_presenter);
    lv_obj_t* backLabel = lv_label_create(m_backBtn);
    lv_label_set_text(backLabel, LV_SYMBOL_LEFT " Back");
    lv_obj_center(backLabel);
    lv_obj_add_flag(m_backBtn, LV_OBJ_FLAG_HIDDEN);

    m_titleLabel = lv_label_create(m_container);
    lv_obj_set_style_text_font(m_titleLabel, &lv_font_montserrat_20, 0);
    lv_obj_align(m_titleLabel, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(m_titleLabel, "");
}

void AppHeader::setTitle(const char* title)
{
    lv_label_set_text(m_titleLabel, title);
}

void AppHeader::setBackVisible(bool visible)
{
    if (visible)
        lv_obj_remove_flag(m_backBtn, LV_OBJ_FLAG_HIDDEN);
    else
        lv_obj_add_flag(m_backBtn, LV_OBJ_FLAG_HIDDEN);
}

void AppHeader::onBackClicked(lv_event_t* e)
{
    auto* presenter = static_cast<AppHeaderPresenter*>(lv_event_get_user_data(e));
    presenter->requestBack();
}
