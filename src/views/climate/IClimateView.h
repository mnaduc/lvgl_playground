#pragma once

class IClimateView {
public:
    virtual ~IClimateView() = default;
    virtual void showTemperature(int temp) = 0;
};
