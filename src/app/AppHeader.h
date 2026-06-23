#pragma once

#include "lvgl.h"
#include "app/AppHeaderViewModel.h"

#include <kdbindings/signal.h>

class AppHeader {
public:
    explicit AppHeader(AppHeaderViewModel& vm);
    ~AppHeader();

private:
    static void onBackClicked(lv_event_t* e);

    lv_obj_t* m_container{nullptr};
    lv_obj_t* m_backBtn{nullptr};
    lv_obj_t* m_titleLabel{nullptr};

    KDBindings::ConnectionHandle m_titleConn;
    KDBindings::ConnectionHandle m_backVisibleConn;
};
