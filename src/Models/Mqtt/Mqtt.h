//
// Created by Goura on 15/01/2024.
//

#ifndef GASSTATION_MQTT_H
#define GASSTATION_MQTT_H

#include "Arduino.h"
#include <WiFi.h>
#include "Wire.h"
#include "DallasTemperature.h"
#include "PubSubClient.h"
#include <iostream>
#include <string>
using namespace std;

namespace Mqtt {

    class Mqtt {
        /// Déclaration des attributs de la classe Mqtt.
    private:
        const char* ssid;
        const char* password;
        const char* mqtt_server;
        const char* mqtt_output;
        const char* mqtt_input;
        const char* mqtt_log;
        const char* mqtt_user;
        PubSubClient client;
        int ledPin;
        int timeInterval;

        /// Déclaration des fonctions publiques.
    public:
        /// Constructeur Mqtt.
        Mqtt(const char* ssid, const char* password, const char* mqtt_server, const char* mqtt_output, const char* mqtt_input, const char* mqtt_log, const char* mqtt_user, PubSubClient client, int ledPin, int timeInterval) {
            this->ssid = ssid;
            this->password = password;
            this->mqtt_server = mqtt_server;
            this->mqtt_output = mqtt_output;
            this->mqtt_input = mqtt_input;
            this->mqtt_log = mqtt_log;
            this->mqtt_user = mqtt_user;
            this->client = client;
            this->ledPin = ledPin;
            this->timeInterval = timeInterval;
        }

        Mqtt() {
            this->ssid = "";
            this->password = "";
            this->mqtt_server = "";
            this->mqtt_output = "";
            this->mqtt_input = "";
            this->mqtt_log = "";
            this->mqtt_user = "";
            this->ledPin = 4 ;
            this->timeInterval = 7500;
        }
        void begin();
        void setup_wifi();
        //uint8_t readReg(uint8_t reg, const void* pBuf, size_t size);
        void printAddress(DeviceAddress deviceAddress);
        void reconnect();
        const char* getMqttServer();
        const char* getMqttOutput();
        const char* getMqttInput();
        const char* getMqttLog();
        const char* getMqttUser();
        const char* getSsid();
        const char* getPassword();
        PubSubClient getClient();
        int getLedPin();
        int getTimeInterval();
        void callback(char* topic, byte* payload, unsigned int length);
        function<void(char*, byte*, unsigned int)> callbackFunction();
    };

} // Mqtt

#endif //GASSTATION_MQTT_H
