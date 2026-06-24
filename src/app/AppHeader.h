#pragma once

#include "lvgl.h"
#include "app/IAppHeaderView.h"
#include "app/AppHeaderPresenter.h"

class AppHeader : public IAppHeaderView {
public:
    explicit AppHeader(AppHeaderPresenter& presenter);
    ~AppHeader() override;

    void setTitle(const char* title) override;
    void setBackVisible(bool visible) override;

private:
    static void onBackClicked(lv_event_t* e);
    void buildUi();

    lv_obj_t* m_container{nullptr};
    lv_obj_t* m_backBtn{nullptr};
    lv_obj_t* m_titleLabel{nullptr};
    AppHeaderPresenter& m_presenter;
};
