#pragma once

#include "models/TemperatureModel.h"
#include "views/home/HomeViewModel.h"
#include "views/climate/ClimateViewModel.h"

#include <kdbindings/signal.h>

class ViewManager;

class ViewFactory {
public:
    explicit ViewFactory(TemperatureModel& model);

    void registerViews(ViewManager& viewManager);

private:
    HomeViewModel    m_homeVM;
    ClimateViewModel m_climateVM;

    KDBindings::ConnectionHandle m_climateNavConn;
};
