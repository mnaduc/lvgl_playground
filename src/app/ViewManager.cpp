#include "app/ViewManager.h"

#include <cstdio>

void ViewManager::registerView(ViewId id, std::unique_ptr<IView> view)
{
    m_views[id] = std::move(view);
}

void ViewManager::navigateTo(ViewId id)
{
    auto it = m_views.find(id);
    if (it == m_views.end()) {
        printf("ViewManager: unknown view %d\n", static_cast<int>(id));
        return;
    }
    it->second->show();
}
