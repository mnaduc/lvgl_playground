#include "lvgl.h"
#include "lvgl/drivers/sdl/lv_sdl_window.h"
#include "lvgl/drivers/sdl/lv_sdl_mouse.h"
#include "lvgl/drivers/sdl/lv_sdl_keyboard.h"

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

    // ViewModels
    MainViewModel mainVM;
    ButtonOverviewViewModel buttonOverviewVM;

    // ViewManager
    ViewManager viewManager;

    // Register views
    viewManager.registerView(ViewId::Main,
        std::make_unique<MainView>(mainVM));
    viewManager.registerView(ViewId::ButtonOverview,
        std::make_unique<ButtonOverviewView>(buttonOverviewVM));

    // Wire navigation signals
    mainVM.navigateToButtonOverview.connect([&]() {
        viewManager.navigateTo(ViewId::ButtonOverview);
    });
    buttonOverviewVM.navigateBack.connect([&]() {
        viewManager.navigateTo(ViewId::Main);
    });

    // Start on MainView
    viewManager.navigateTo(ViewId::Main);

    printf("LVGL SDL app started\n");

    while (true) {
        lv_timer_handler();
        lv_delay_ms(5);
    }

    return 0;
}
