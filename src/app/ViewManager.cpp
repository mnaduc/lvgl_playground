#include "app/ViewManager.h"

#include <cstdio>

ViewManager::ViewManager(AppHeaderViewModel& headerVM)
    : m_headerVM(headerVM)
{
    m_backRequestedConn = m_headerVM.backRequested.connect([this]() {
        navigateBack();
    });
}

void ViewManager::registerView(ViewId id, std::unique_ptr<IView> view)
{
    m_views[id] = {std::move(view)};
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
    m_headerTitleConn.disconnect();
    m_headerBackConn.disconnect();

    auto& entry = m_views[id];
    auto& hs    = entry.view->viewModel().headerState();

    m_headerVM.title       = hs.title.get();
    m_headerVM.backVisible = hs.backVisible.get();

    m_headerTitleConn = hs.title.valueChanged().connect([this](const std::string& t) {
        m_headerVM.title = t;
    });
    m_headerBackConn = hs.backVisible.valueChanged().connect([this](bool v) {
        m_headerVM.backVisible = v;
    });

    entry.view->show();
}
