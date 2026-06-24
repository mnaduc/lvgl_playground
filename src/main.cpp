#include "lvgl.h"
#include "lvgl/drivers/sdl/lv_sdl_window.h"
#include "lvgl/drivers/sdl/lv_sdl_mouse.h"
#include "lvgl/drivers/sdl/lv_sdl_keyboard.h"

#include "app/AppHeader.h"
#include "app/AppHeaderViewModel.h"
#include "app/ViewManager.h"
#include "models/TemperatureModel.h"
#include "views/ViewId.h"
#include "views/home/HomeView.h"
#include "views/home/HomeViewModel.h"
#include "views/climate/ClimateView.h"
#include "views/climate/ClimateViewModel.h"

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

    // Shared model
    TemperatureModel tempModel;

    // Global header (lives on lv_layer_top, persists across screens)
    AppHeaderViewModel headerVM;
    AppHeader appHeader(headerVM);

    // ViewManager owns all views and drives the header
    ViewManager viewManager(headerVM);

    // ViewModels
    HomeViewModel    homeVM(tempModel);
    ClimateViewModel climateVM(tempModel);

    // Register views
    viewManager.registerView(ViewId::Home,
        std::make_unique<HomeView>(homeVM),
        "Home", /*showBack=*/false);
    viewManager.registerView(ViewId::Climate,
        std::make_unique<ClimateView>(climateVM),
        "Climate", /*showBack=*/true);

    // Navigation callbacks
    homeVM.onNavigateToClimate = [&]() {
        viewManager.navigateTo(ViewId::Climate);
    };

    headerVM.onBackRequested = [&]() {
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
