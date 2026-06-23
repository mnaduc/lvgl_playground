#include "views/button_overview/ButtonOverviewView.h"
#include "app/AppConstants.h"

ButtonOverviewView::ButtonOverviewView(ButtonOverviewViewModel& viewModel)
    : m_vm(viewModel)
{
    m_screen = lv_obj_create(NULL);
    buildUi();

    m_toggleConnection = m_vm.toggleState.valueChanged().connect([this](bool state) {
        lv_label_set_text(m_toggleStatusLabel, state ? "State: ON" : "State: OFF");
    });
}

ButtonOverviewView::~ButtonOverviewView()
{
    m_toggleConnection.disconnect();
    if (m_screen)
        lv_obj_delete(m_screen);
}

void ButtonOverviewView::show()
{
    lv_scr_load(m_screen);
}

void ButtonOverviewView::buildUi()
{
    // Scrollable content container below the global header
    lv_obj_t* cont = lv_obj_create(m_screen);
    lv_obj_set_pos(cont, 0, HEADER_HEIGHT);
    lv_obj_set_size(cont, DISPLAY_WIDTH, DISPLAY_HEIGHT - HEADER_HEIGHT);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(cont, 12, 0);
    lv_obj_set_style_pad_all(cont, 16, 0);

    // 1. Default button
    addRow(cont, "Default:", [](lv_obj_t* row) {
        lv_obj_t* btn = lv_button_create(row);
        lv_obj_set_size(btn, 160, 40);
        lv_obj_t* lbl = lv_label_create(btn);
        lv_label_set_text(lbl, "Click Me");
        lv_obj_center(lbl);
    });

    // 2. Toggle button
    {
        lv_obj_t* row = makeRow(cont);

        lv_obj_t* descLbl = lv_label_create(row);
        lv_label_set_text(descLbl, "Toggle:");

        lv_obj_t* btn = lv_button_create(row);
        lv_obj_set_size(btn, 160, 40);
        lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
        lv_obj_add_event_cb(btn, onToggleClicked, LV_EVENT_VALUE_CHANGED, this);
        lv_obj_t* btnLbl = lv_label_create(btn);
        lv_label_set_text(btnLbl, "Toggle");
        lv_obj_center(btnLbl);

        m_toggleStatusLabel = lv_label_create(row);
        lv_label_set_text(m_toggleStatusLabel, "State: OFF");
    }

    // 3. Button with symbol
    addRow(cont, "With Icon:", [](lv_obj_t* row) {
        lv_obj_t* btn = lv_button_create(row);
        lv_obj_set_size(btn, 160, 40);
        lv_obj_t* lbl = lv_label_create(btn);
        lv_label_set_text(lbl, LV_SYMBOL_OK "  Confirm");
        lv_obj_center(lbl);
    });

    // 4. Disabled button
    addRow(cont, "Disabled:", [](lv_obj_t* row) {
        lv_obj_t* btn = lv_button_create(row);
        lv_obj_set_size(btn, 160, 40);
        lv_obj_add_state(btn, LV_STATE_DISABLED);
        lv_obj_t* lbl = lv_label_create(btn);
        lv_label_set_text(lbl, LV_SYMBOL_CLOSE "  Disabled");
        lv_obj_center(lbl);
    });
}

lv_obj_t* ButtonOverviewView::makeRow(lv_obj_t* parent)
{
    lv_obj_t* row = lv_obj_create(parent);
    lv_obj_set_size(row, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_style_border_width(row, 0, 0);
    lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, 0);
    lv_obj_set_style_pad_all(row, 0, 0);
    lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(row, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    return row;
}

void ButtonOverviewView::addRow(lv_obj_t* parent, const char* label,
                                 std::function<void(lv_obj_t*)> buildContent)
{
    lv_obj_t* row = makeRow(parent);
    lv_obj_t* lbl = lv_label_create(row);
    lv_label_set_text(lbl, label);
    buildContent(row);
}

void ButtonOverviewView::onToggleClicked(lv_event_t* e)
{
    auto* self = static_cast<ButtonOverviewView*>(lv_event_get_user_data(e));
    lv_obj_t* btn = lv_event_get_target_obj(e);
    self->m_vm.onToggleChanged(lv_obj_has_state(btn, LV_STATE_CHECKED));
}
