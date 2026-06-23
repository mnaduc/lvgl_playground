#include "views/button_overview/ButtonOverviewView.h"

ButtonOverviewView::ButtonOverviewView(ButtonOverviewViewModel& viewModel)
    : m_vm(viewModel)
{
    m_screen = lv_obj_create(NULL);
    buildUi();

    // Bind toggleState property to the status label
    m_toggleConnection = m_vm.toggleState.valueChanged().connect([this](bool state) {
        lv_label_set_text(m_toggleStatusLabel, state ? "State: ON" : "State: OFF");
    });
}

ButtonOverviewView::~ButtonOverviewView()
{
    m_toggleConnection.disconnect();
    if (m_screen) {
        lv_obj_delete(m_screen);
    }
}

void ButtonOverviewView::show()
{
    lv_scr_load(m_screen);
}

void ButtonOverviewView::buildUi()
{
    // Header
    lv_obj_t* title = lv_label_create(m_screen);
    lv_label_set_text(title, "Button Overview");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_20, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 16);

    // Back button (top-left)
    lv_obj_t* backBtn = lv_button_create(m_screen);
    lv_obj_set_size(backBtn, 80, 36);
    lv_obj_align(backBtn, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(backBtn, onBackClicked, LV_EVENT_CLICKED, this);
    lv_obj_t* backLabel = lv_label_create(backBtn);
    lv_label_set_text(backLabel, LV_SYMBOL_LEFT " Back");
    lv_obj_center(backLabel);

    // Scrollable content container
    lv_obj_t* cont = lv_obj_create(m_screen);
    lv_obj_set_size(cont, LV_PCT(90), LV_PCT(75));
    lv_obj_align(cont, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(cont, 12, 0);

    // 1. Default button
    {
        lv_obj_t* row = lv_obj_create(cont);
        lv_obj_set_size(row, LV_PCT(100), LV_SIZE_CONTENT);
        lv_obj_set_style_border_width(row, 0, 0);
        lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, 0);
        lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(row, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        lv_obj_t* lbl = lv_label_create(row);
        lv_label_set_text(lbl, "Default:");

        lv_obj_t* btn = lv_button_create(row);
        lv_obj_set_size(btn, 140, 40);
        lv_obj_t* btnLbl = lv_label_create(btn);
        lv_label_set_text(btnLbl, "Click Me");
        lv_obj_center(btnLbl);
    }

    // 2. Toggle button
    {
        lv_obj_t* row = lv_obj_create(cont);
        lv_obj_set_size(row, LV_PCT(100), LV_SIZE_CONTENT);
        lv_obj_set_style_border_width(row, 0, 0);
        lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, 0);
        lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(row, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        lv_obj_t* lbl = lv_label_create(row);
        lv_label_set_text(lbl, "Toggle:");

        lv_obj_t* col = lv_obj_create(row);
        lv_obj_set_size(col, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_border_width(col, 0, 0);
        lv_obj_set_style_bg_opa(col, LV_OPA_TRANSP, 0);
        lv_obj_set_style_pad_all(col, 0, 0);
        lv_obj_set_flex_flow(col, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(col, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_style_pad_column(col, 8, 0);

        lv_obj_t* btn = lv_button_create(col);
        lv_obj_set_size(btn, 140, 40);
        lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
        lv_obj_add_event_cb(btn, onToggleClicked, LV_EVENT_VALUE_CHANGED, this);
        lv_obj_t* btnLbl = lv_label_create(btn);
        lv_label_set_text(btnLbl, "Toggle");
        lv_obj_center(btnLbl);

        m_toggleStatusLabel = lv_label_create(col);
        lv_label_set_text(m_toggleStatusLabel, "State: OFF");
    }

    // 3. Button with symbol
    {
        lv_obj_t* row = lv_obj_create(cont);
        lv_obj_set_size(row, LV_PCT(100), LV_SIZE_CONTENT);
        lv_obj_set_style_border_width(row, 0, 0);
        lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, 0);
        lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(row, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        lv_obj_t* lbl = lv_label_create(row);
        lv_label_set_text(lbl, "With Icon:");

        lv_obj_t* btn = lv_button_create(row);
        lv_obj_set_size(btn, 140, 40);
        lv_obj_t* btnLbl = lv_label_create(btn);
        lv_label_set_text(btnLbl, LV_SYMBOL_OK "  Confirm");
        lv_obj_center(btnLbl);
    }

    // 4. Disabled button
    {
        lv_obj_t* row = lv_obj_create(cont);
        lv_obj_set_size(row, LV_PCT(100), LV_SIZE_CONTENT);
        lv_obj_set_style_border_width(row, 0, 0);
        lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, 0);
        lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(row, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        lv_obj_t* lbl = lv_label_create(row);
        lv_label_set_text(lbl, "Disabled:");

        lv_obj_t* btn = lv_button_create(row);
        lv_obj_set_size(btn, 140, 40);
        lv_obj_add_state(btn, LV_STATE_DISABLED);
        lv_obj_t* btnLbl = lv_label_create(btn);
        lv_label_set_text(btnLbl, LV_SYMBOL_CLOSE "  Disabled");
        lv_obj_center(btnLbl);
    }
}

void ButtonOverviewView::onBackClicked(lv_event_t* e)
{
    auto* self = static_cast<ButtonOverviewView*>(lv_event_get_user_data(e));
    self->m_vm.requestBack();
}

void ButtonOverviewView::onToggleClicked(lv_event_t* e)
{
    auto* self = static_cast<ButtonOverviewView*>(lv_event_get_user_data(e));
    lv_obj_t* btn = lv_event_get_target_obj(e);
    bool checked = lv_obj_has_state(btn, LV_STATE_CHECKED);
    self->m_vm.onToggleChanged(checked);
}
