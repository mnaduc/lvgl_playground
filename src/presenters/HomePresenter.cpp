#include "presenters/HomePresenter.h"
#include "views/home/IHomeView.h"

HomePresenter::HomePresenter(TemperatureModel& model)
    : m_model(model)
{}

HomePresenter::~HomePresenter()
{
    if (m_obs)
        lv_observer_remove(m_obs);
}

void HomePresenter::attach(IHomeView& view)
{
    m_view = &view;
    // Fires the callback immediately with the current value
    m_obs = lv_subject_add_observer(&m_model.targetTemperature, onTempChanged, this);
}

void HomePresenter::handleClimateRequested()
{
    if (onNavigateToClimate) onNavigateToClimate();
}

void HomePresenter::onTempChanged(lv_observer_t* obs, lv_subject_t* sub)
{
    auto* self = static_cast<HomePresenter*>(lv_observer_get_user_data(obs));
    self->m_view->showTemperature(lv_subject_get_int(sub));
}
