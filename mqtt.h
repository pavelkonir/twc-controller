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

#ifndef MQTT_H
#define MQTT_H

#include <PangolinMQTT.h>

#include "config.h"
#include "twc_controller.h"
#include "io.h"


class TeslaMqttIO : public TeslaControllerIO {
    public:
        TeslaMqttIO(PangolinMQTT &mqttClient);

        void Begin(TWCConfig &twc_config);
        void onChargeChangeMessage();
        void onCurrentMessage(std::function<void(uint8_t)>);
        void onRawMessage(std::function<void(uint8_t*, size_t)> callback);
        void onDebugMessage(std::function<void(bool)> callback);
        void writeRaw(uint8_t *data, size_t length);
        void writeRawPacket(uint8_t *data, size_t length);
        void stopCharging();
        void writeState();

    private:
        void onMqttConnect(bool sessionPresent);
        void onMqttDisconnect(int8_t reason);
        void onMqttMessage(const char* topic, uint8_t* payload, struct PANGO_PROPS props, size_t len, size_t index, size_t total);
        
    
        PangolinMQTT *mqttClient_;
        std::function<void(uint8_t*, size_t)> onRawMessageCallback_=nullptr;
        std::function<void(uint8_t)> onCurrentMessageCallback_=nullptr;
        std::function<void(bool)> onDebugMessageCallback_=nullptr;
};

#endif /* MQTT_H */