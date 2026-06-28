#pragma once

#include "views/IViewModel.h"
#include "models/TemperatureModel.h"

class ClimateViewModel : public IViewModel {
public:
    explicit ClimateViewModel(TemperatureModel& model)
        : m_model(model)
        , m_headerState("Climate", /*backVisible=*/true)
    {}

    HeaderState& headerState() override { return m_headerState; }

    KDBindings::Property<int>& targetTemperature() { return m_model.targetTemperature; }

    void increment() { m_model.targetTemperature = m_model.targetTemperature.get() + 1; }
    void decrement() { m_model.targetTemperature = m_model.targetTemperature.get() - 1; }

private:
    TemperatureModel& m_model;
    HeaderState       m_headerState;
};
