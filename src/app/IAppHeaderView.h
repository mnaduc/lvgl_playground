#pragma once

class IAppHeaderView {
public:
    virtual ~IAppHeaderView() = default;
    virtual void setTitle(const char* title) = 0;
    virtual void setBackVisible(bool visible) = 0;
};
