#include "lvgl.h"
#include "lvgl/drivers/sdl/lv_sdl_window.h"
#include "lvgl/drivers/sdl/lv_sdl_mouse.h"
#include "lvgl/drivers/sdl/lv_sdl_keyboard.h"

#include "app/AppHeader.h"
#include "app/AppHeaderViewModel.h"
#include "app/ViewFactory.h"
#include "app/ViewManager.h"
#include "models/TemperatureModel.h"

#include <cstdio>

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

    TemperatureModel tempModel;

    AppHeaderViewModel headerVM;
    AppHeader appHeader(headerVM);

    ViewManager viewManager(headerVM);

    ViewFactory viewFactory(tempModel);
    viewFactory.registerViews(viewManager);

    viewManager.navigateTo(ViewId::Home);

    printf("LVGL SDL app started\n");

    while (true) {
        lv_timer_handler();
        lv_delay_ms(5);
    }

    return 0;
}
