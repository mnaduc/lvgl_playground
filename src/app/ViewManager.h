#pragma once

#include "app/AppHeaderPresenter.h"
#include "views/IView.h"
#include "views/ViewId.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

struct ViewIdHash {
    std::size_t operator()(ViewId id) const noexcept {
        return static_cast<std::size_t>(id);
    }
};

class ViewManager {
public:
    explicit ViewManager(AppHeaderPresenter& presenter);

    void registerView(ViewId id, std::unique_ptr<IView> view,
                      std::string title, bool showBack = false);

    void navigateTo(ViewId id);
    void navigateBack();

private:
    struct ViewEntry {
        std::unique_ptr<IView> view;
        std::string            title;
        bool                   showBack{false};
    };

    void showView(ViewId id);

    AppHeaderPresenter&                                       m_presenter;
    std::unordered_map<ViewId, ViewEntry, ViewIdHash>         m_views;
    std::vector<ViewId>                                       m_history;
};
