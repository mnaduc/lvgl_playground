#include "app/ViewManager.h"

#include <cstdio>

ViewManager::ViewManager(AppHeaderPresenter& presenter)
    : m_presenter(presenter)
{}

void ViewManager::registerView(ViewId id, std::unique_ptr<IView> view,
                                std::string title, bool showBack)
{
    m_views[id] = {std::move(view), std::move(title), showBack};
}

void ViewManager::navigateTo(ViewId id)
{
    if (m_views.find(id) == m_views.end()) {
        printf("ViewManager: unknown view %d\n", static_cast<int>(id));
        return;
    }
    m_history.push_back(id);
    showView(id);
}

void ViewManager::navigateBack()
{
    if (m_history.size() <= 1) return;
    m_history.pop_back();
    showView(m_history.back());
}

void ViewManager::showView(ViewId id)
{
    auto& entry = m_views[id];
    m_presenter.setTitle(entry.title.c_str());
    m_presenter.setBackVisible(entry.showBack);
    entry.view->show();
}
