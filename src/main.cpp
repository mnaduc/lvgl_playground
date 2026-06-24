#include "lvgl.h"
#include "lvgl/drivers/sdl/lv_sdl_window.h"
#include "lvgl/drivers/sdl/lv_sdl_mouse.h"
#include "lvgl/drivers/sdl/lv_sdl_keyboard.h"

#include "app/AppHeader.h"
#include "app/AppHeaderPresenter.h"
#include "app/ViewManager.h"
#include "models/TemperatureModel.h"
#include "presenters/HomePresenter.h"
#include "presenters/ClimatePresenter.h"
#include "views/ViewId.h"
#include "views/home/HomeView.h"
#include "views/climate/ClimateView.h"

#include <cstdio>
#include <memory>

int main()
{
    lv_init();

    lv_display_t* display = lv_sdl_window_create(800, 480);
    if (!display) {
        printf("Failed to create SDL display\n");
        return 1;
    }

    lv_sdl_mouse_create();
    lv_sdl_keyboard_create();

    // Model
    TemperatureModel tempModel;

    // App header (presenter drives the passive header view)
    AppHeaderPresenter headerPresenter;
    AppHeader appHeader(headerPresenter);
    ViewManager viewManager(headerPresenter);

    // Presenters
    HomePresenter    homePresenter(tempModel);
    ClimatePresenter climatePresenter(tempModel);

    // Views — heap-allocated so unique_ptr can be moved to ViewManager
    // while Presenter retains a valid reference to the object
    auto homeView    = std::make_unique<HomeView>(homePresenter);
    auto climateView = std::make_unique<ClimateView>(climatePresenter);

    // Attach: Presenter subscribes to model and pushes initial value to View
    homePresenter.attach(*homeView);
    climatePresenter.attach(*climateView);

    viewManager.registerView(ViewId::Home,    std::move(homeView),    "Home",    false);
    viewManager.registerView(ViewId::Climate, std::move(climateView), "Climate", true);

    homePresenter.onNavigateToClimate = [&]() {
        viewManager.navigateTo(ViewId::Climate);
    };

    headerPresenter.onBackRequested = [&]() {
        viewManager.navigateBack();
    };

    viewManager.navigateTo(ViewId::Home);

    printf("LVGL SDL app started\n");

    while (true) {
        lv_timer_handler();
        lv_delay_ms(5);
    }

    return 0;
}
