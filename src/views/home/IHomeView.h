#pragma once

class IHomeView {
public:
    virtual ~IHomeView() = default;
    virtual void showTemperature(int temp) = 0;
};
