#include "presenters/ClimatePresenter.h"
#include "views/climate/IClimateView.h"

ClimatePresenter::ClimatePresenter(TemperatureModel& model)
    : m_model(model)
{}

ClimatePresenter::~ClimatePresenter()
{
    if (m_obs)
        lv_observer_remove(m_obs);
}

void ClimatePresenter::attach(IClimateView& view)
{
    m_view = &view;
    m_obs = lv_subject_add_observer(&m_model.targetTemperature, onTempChanged, this);
}

void ClimatePresenter::handleIncrement()
{
    lv_subject_set_int(&m_model.targetTemperature,
                       lv_subject_get_int(&m_model.targetTemperature) + 1);
}

void ClimatePresenter::handleDecrement()
{
    lv_subject_set_int(&m_model.targetTemperature,
                       lv_subject_get_int(&m_model.targetTemperature) - 1);
}

void ClimatePresenter::onTempChanged(lv_observer_t* obs, lv_subject_t* sub)
{
    auto* self = static_cast<ClimatePresenter*>(lv_observer_get_user_data(obs));
    self->m_view->showTemperature(lv_subject_get_int(sub));
}
