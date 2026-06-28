#pragma once

#include <kdbindings/signal.h>
#include "views/IViewModel.h"
#include "models/TemperatureModel.h"

class HomeViewModel : public IViewModel {
public:
    explicit HomeViewModel(TemperatureModel& model)
        : m_model(model)
        , m_headerState("Home", /*backVisible=*/false)
    {}

    HeaderState& headerState() override { return m_headerState; }

    KDBindings::Signal<> navigateToClimate;

    KDBindings::Property<int>& targetTemperature() { return m_model.targetTemperature; }

    void requestClimate() { navigateToClimate.emit(); }

private:
    TemperatureModel& m_model;
    HeaderState       m_headerState;
};
