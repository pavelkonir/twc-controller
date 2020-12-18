/*
TWC Manager for ESP32
Copyright (C) 2020 Jarl Nicolson
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <EasyButton.h>
#include <SPIFFS.h>
#include "twc_controller.h"
#include "wifi.h"
#include "ota.h"
#include "config.h"
#include "twc_protocol.h"
TWCConfig twc_config("/config.json");
EasyButton button(RST_BUTTON);
void IRAM_ATTR buttonIsr() {
    button.read();
}

void buttonHeld() {
    wifi.Reset();
}

// This is blocking and will restart the ESP32
// at the end
void StartConfigMode() {
}

void setup() {
    Serial.begin(115200);
    Serial.println("Booting...");
    button.begin();

    if(!SPIFFS.begin()) {
        Serial.println("Cannot start SPIFFS!  Starting in configure mode... ");
        StartConfigMode();
    };

    if (!twc_config.Begin()) {
        Serial.println("Config initialisation failed.  Starting in configure mode.. ");
        StartConfigMode();
    };

    wifi.Begin(twc_config);
    ota.Begin();

    button.onPressedFor(3000, buttonHeld);
    if (button.supportsInterrupt()) {
        button.enableInterrupt(buttonIsr);
    };
    Serial.println("Starting loop...");
}



void loop() {
    ota.Handle();
    button.update();
}
