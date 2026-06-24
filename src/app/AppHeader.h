#pragma once

#include "lvgl.h"
#include "app/AppHeaderViewModel.h"

class AppHeader {
public:
    explicit AppHeader(AppHeaderViewModel& vm);
    ~AppHeader();

private:
    static void onBackClicked(lv_event_t* e);

    lv_obj_t* m_container{nullptr};
};
