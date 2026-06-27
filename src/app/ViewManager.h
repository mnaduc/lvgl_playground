#pragma once

#include "app/AppHeaderViewModel.h"
#include "views/IView.h"
#include "views/ViewId.h"

#include <kdbindings/signal.h>
#include <memory>
#include <unordered_map>
#include <vector>

struct ViewIdHash {
    std::size_t operator()(ViewId id) const noexcept {
        return static_cast<std::size_t>(id);
    }
};

class ViewManager {
public:
    explicit ViewManager(AppHeaderViewModel& headerVM);

    void registerView(ViewId id, std::unique_ptr<IView> view);

    void navigateTo(ViewId id);
    void navigateBack();

private:
    struct ViewEntry {
        std::unique_ptr<IView> view;
    };

    void showView(ViewId id);

    AppHeaderViewModel&                                       m_headerVM;
    std::unordered_map<ViewId, ViewEntry, ViewIdHash>         m_views;
    std::vector<ViewId>                                       m_history;

    KDBindings::ConnectionHandle                              m_headerTitleConn;
    KDBindings::ConnectionHandle                              m_headerBackConn;
    KDBindings::ConnectionHandle                              m_backRequestedConn;
};
