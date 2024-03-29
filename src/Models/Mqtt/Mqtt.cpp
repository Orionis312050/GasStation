//
// Created by Goura on 15/01/2024.
//

#include "Mqtt.h"

namespace Mqtt {
void Mqtt::begin() {
    Wire.begin();
}

    void Mqtt::setup_wifi() {
        delay(10);
        // We start by connecting to a WiFi network
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(ssid);

        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }

    /*uint8_t Mqtt::readReg(uint8_t reg, const void* pBuf, size_t size) {
        if (pBuf == NULL) {
            Serial.println("pBuf ERROR!! : null pointer");
        }
        uint8_t * _pBuf = (uint8_t *)pBuf;
        Wire.beginTransmission(address);
        Wire.write(&reg, 1);
        if (Wire.endTransmission() != 0) {
            return 0;
        }
        delay(20);
        Wire.requestFrom(address, (uint8_t)size);
        for (uint16_t i = 0; i < size; i++) {
            _pBuf[i] = Wire.read();
        }
        return size;
    }*/

    void Mqtt::printAddress(DeviceAddress deviceAddress)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            Serial.print("0x");
            if (deviceAddress[i] < 0x10) Serial.print("0");
            Serial.print(deviceAddress[i], HEX);
            if (i < 7) Serial.print(", ");
        }
        Serial.println("");
    }

    void Mqtt::reconnect() {
        // Loop until we're reconnected
        while (!client.connected()) {
            delay(100);
            Serial.print("Attempting MQTT connection...");
            // Attempt to connect
            if (client.connect("ESP8266Client")) {
                Serial.println("connected");
                // Subscribe
                client.subscribe(mqtt_input);
            } else {
                Serial.print("failed, rc=");
                Serial.print(client.state());
                Serial.println(" try again in 5 seconds");
                // Wait 5 seconds before retrying
                delay(3000);
            }
        }
    }

    const char* Mqtt::getSsid() {
        return ssid;
    }

    const char* Mqtt::getPassword() {
        return password;
    }

    const char* Mqtt::getMqttServer() {
        return mqtt_server;
    }

    const char* Mqtt::getMqttOutput() {
        return mqtt_output;
    }

    const char* Mqtt::getMqttInput() {
        return mqtt_input;
    }

    const char* Mqtt::getMqttLog() {
        return mqtt_log;
    }

    const char* Mqtt::getMqttUser() {
        return mqtt_user;
    }

    PubSubClient Mqtt::getClient() {
        return client;
    }

    int Mqtt::getLedPin() {
        return ledPin;
    }

    int Mqtt::getTimeInterval() {
        return timeInterval;
    }


    void Mqtt::callback(char* topic, byte* message, unsigned int length) {
        Serial.print("Message arrived on topic: ");
        Serial.print(topic);
        Serial.print(". Message: ");
        String messageTemp;

        for (int i = 0; i < length; i++) {
            Serial.print((char)message[i]);
            messageTemp += (char)message[i];
        }
        Serial.println();

        // Feel free to add more if statements to control more GPIOs with MQTT

        // If a message is received on the topic esp32/input, you check if the message is either "on" or "off".
        // Changes the output state according to the message
        if (String(topic) == mqtt_input ) {
            Serial.print("Changing output to ");

            if(messageTemp == "on"){
                Serial.println("MessageTemp = on");
                client.publish(mqtt_log, "changing to ON" );
                digitalWrite(ledPin, HIGH);
            }
            else if(messageTemp == "Message Temp = off"){
                Serial.println("off");
                client.publish(mqtt_log, "changing to OFF" );
                digitalWrite(ledPin, LOW);
            }
            else if(messageTemp == "timeInterval_1000") {
                Serial.println("Time Interval order received");
                timeInterval = 1000;
                client.publish(mqtt_log, "Interval set to 1000" );
            }
            else if(messageTemp == "timeInterval_5000") {
                Serial.println("Time Interval order received");
                timeInterval = 5000;
                client.publish(mqtt_log, "Interval set to 5000" );
            }

            else if(messageTemp == "reboot") {
                Serial.println("Reboot order received");
                String msg = "Reboot for : " + (String)mqtt_user;
                client.publish(mqtt_log, msg.c_str() );
                ESP.restart();
            }

        }
    }

    function<void(char*, byte*, unsigned int)> Mqtt::callbackFunction() {
        return bind(&Mqtt::callback, this, placeholders::_1, placeholders::_2, placeholders::_3);
    }

} // Mqtt