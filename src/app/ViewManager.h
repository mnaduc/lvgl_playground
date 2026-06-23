#pragma once

#include "views/IView.h"
#include "views/ViewId.h"

#include <memory>
#include <unordered_map>

struct ViewIdHash {
    std::size_t operator()(ViewId id) const noexcept {
        return static_cast<std::size_t>(id);
    }
};

class ViewManager {
public:
    void registerView(ViewId id, std::unique_ptr<IView> view);
    void navigateTo(ViewId id);

private:
    std::unordered_map<ViewId, std::unique_ptr<IView>, ViewIdHash> m_views;
};
