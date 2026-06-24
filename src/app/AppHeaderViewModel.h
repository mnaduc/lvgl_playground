#pragma once

#include "lvgl.h"
#include <functional>

class AppHeaderViewModel {
public:
    static constexpr size_t TITLE_SIZE = 64;

    AppHeaderViewModel() {
        lv_subject_init_string(&title, m_titleBuf, m_titlePrevBuf, TITLE_SIZE, "");
        lv_subject_init_int(&backVisible, 0);
    }
    ~AppHeaderViewModel() {
        lv_subject_deinit(&title);
        lv_subject_deinit(&backVisible);
    }

    lv_subject_t title;
    lv_subject_t backVisible;

    std::function<void()> onBackRequested;

    void setTitle(const char* t)    { lv_subject_copy_string(&title, t); }
    void setBackVisible(bool v)     { lv_subject_set_int(&backVisible, v ? 1 : 0); }
    void requestBack()              { if (onBackRequested) onBackRequested(); }

private:
    char m_titleBuf[TITLE_SIZE]{};
    char m_titlePrevBuf[TITLE_SIZE]{};
};
