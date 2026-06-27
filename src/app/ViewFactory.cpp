#include "app/ViewFactory.h"
#include "app/ViewManager.h"
#include "views/ViewId.h"
#include "views/home/HomeView.h"
#include "views/climate/ClimateView.h"

#include <memory>

ViewFactory::ViewFactory(TemperatureModel& model)
    : m_homeVM(model)
    , m_climateVM(model)
{}

void ViewFactory::registerViews(ViewManager& viewManager)
{
    viewManager.registerView(ViewId::Home,
        std::make_unique<HomeView>(m_homeVM));

    viewManager.registerView(ViewId::Climate,
        std::make_unique<ClimateView>(m_climateVM));

    m_climateNavConn = m_homeVM.navigateToClimate.connect([&viewManager]() {
        viewManager.navigateTo(ViewId::Climate);
    });
}
