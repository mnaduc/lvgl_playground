#include "lvgl.h"
#include "lvgl/drivers/sdl/lv_sdl_window.h"
#include "lvgl/drivers/sdl/lv_sdl_mouse.h"
#include "lvgl/drivers/sdl/lv_sdl_keyboard.h"

#include "app/AppHeader.h"
#include "app/AppHeaderViewModel.h"
#include "app/ViewManager.h"
#include "views/ViewId.h"
#include "views/main/MainView.h"
#include "views/main/MainViewModel.h"
#include "views/button_overview/ButtonOverviewView.h"
#include "views/button_overview/ButtonOverviewViewModel.h"

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

    // Global header (lives on lv_layer_top, persists across screens)
    AppHeaderViewModel headerVM;
    AppHeader appHeader(headerVM);

    // ViewManager owns all views and drives the header
    ViewManager viewManager(headerVM);

    // ViewModels
    MainViewModel mainVM;
    ButtonOverviewViewModel buttonOverviewVM;

    // Register views with their header title and back-button visibility
    viewManager.registerView(ViewId::Main,
        std::make_unique<MainView>(mainVM),
        "LVGL Playground", /*showBack=*/false);
    viewManager.registerView(ViewId::ButtonOverview,
        std::make_unique<ButtonOverviewView>(buttonOverviewVM),
        "Button Overview", /*showBack=*/true);

    // Navigation signals from ViewModels
    auto conn1 = mainVM.navigateToButtonOverview.connect([&]() {
        viewManager.navigateTo(ViewId::ButtonOverview);
    });

    // Header back button -> ViewManager history pop
    auto conn2 = headerVM.backRequested.connect([&]() {
        viewManager.navigateBack();
    });

    viewManager.navigateTo(ViewId::Main);

    printf("LVGL SDL app started\n");

    while (true) {
        lv_timer_handler();
        lv_delay_ms(5);
    }

    return 0;
}
