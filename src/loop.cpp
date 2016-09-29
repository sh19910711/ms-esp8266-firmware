#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Schedule.h>
#include "update.h"

extern "C" {
#include <user_interface.h>
}

extern "C" void __yield();

static void (*app_loop)() = nullptr;
void set_loop(void (*func)()) {

    app_loop = func;

    for (;;) {
        run_scheduled_functions();
        __yield();
        ESP.wdtFeed();
        if (app_loop)
            app_loop();

        update_status();
    }
}


void loop() {
    // unused
}
