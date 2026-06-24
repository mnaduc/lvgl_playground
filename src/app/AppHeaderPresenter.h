#pragma once

#include <functional>
#include "app/IAppHeaderView.h"

class AppHeaderPresenter {
public:
    std::function<void()> onBackRequested;

    void attachView(IAppHeaderView& view) { m_view = &view; }

    void setTitle(const char* t) { if (m_view) m_view->setTitle(t); }
    void setBackVisible(bool v)  { if (m_view) m_view->setBackVisible(v); }
    void requestBack()           { if (onBackRequested) onBackRequested(); }

private:
    IAppHeaderView* m_view{nullptr};
};
