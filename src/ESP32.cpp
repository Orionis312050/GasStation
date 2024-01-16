/*
* Description:
* This sample code is mainly used to monitor sensorHub and sending through Mqtt Json data
* temperature, dissolved oxygen, ec and orp,etc.
*
* Software Environment: Arduino IDE 1.8.9
* Software download link: https://www.arduino.cc/en/Main/Software
*
* Install the library file：
* Copy the files from the github repository folder libraries to the libraries
* in the Arduino IDE 1.8.9 installation directory
*
* Hardware platform   : ESP32
*
* author  :  Rominco(rtourte@yahoo.fr)
* version :  V1.0
* date    :  2021-03-29
**********************************************************************
 */

#include "Models/Conf/Conf.h"
#include "WiFi.h"
#include "PubSubClient.h"
#include "Adafruit_CCS811.h"
#include "SparkFunBME280.h"
#include "Models/Mqtt/Mqtt.h"
#include "Models/DatabaseManager/DatabaseManager.h"

// DS18B20 Library
/*#include <OneWire.h>
#include <DallasTemperature.h>*/

// DEfine the WIRE onto ESP32
/*#define ONE_WIRE_BUS 14
OneWire oneWire(ONE_WIRE_BUS); 
// variable to hold device addresses
DeviceAddress Thermometer;
int deviceCount = 0;
DallasTemperature sensorDS18B20(&oneWire);

BME280 sensorBME280;
Adafruit_CCS811 ccs;*/

Conf::Conf conf;

/*const char* ssid = conf.ssid;
char* password = "wifiraspi";
char* mqtt_server = "172.24.1.1";
char* mqtt_output = "esp32/update";
char* mqtt_input = "esp32/input";
char* mqtt_log = "esp32/log";
char* mqtt_user = "ESP32_Proto_Exemple";*/

/*const int ledPin = 4;
int timeInterval = 7500;*/

WiFiClient espClient;
PubSubClient client(espClient);

Mqtt::Mqtt mqtt(conf.ssid, conf.password, conf.mqtt_server, conf.mqtt_output, conf.mqtt_input, conf.mqtt_log, conf.mqtt_user, client, conf.ledPin, conf.timeInterval);

/*long lastMsg = 0;
char msg[50];
int value = 0;*/

/* ----------------------
 *  WIFI SETUP
 *  ---------------------
 */
/*void setup_wifi() {
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
}*/

/* ----------------------
 *  printAddress
 *  ---------------------
 */
/*void printAddress(DeviceAddress deviceAddress)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        Serial.print("0x");
        if (deviceAddress[i] < 0x10) Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
        if (i < 7) Serial.print(", ");
    }
    Serial.println("");
}*/

/*
 *  ------------------
 *  RECONNECT MQTT
 *  ------------------
 */
/*void reconnect() {
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
}*/

/* ------------------------
 *  MQTT CALLBACK
 *  -----------------------
 */
/*void callback(char* topic, byte* message, unsigned int length) {
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
}*/

/* ------------------------
 *  MAIN SETUP 
 *  -----------------------
 */
void setup()
{
    Conf::Conf conf;
    DatabaseManager::DatabaseManager databaseManager(conf.MYSQLDB_NAME, conf.MYSQLDB_USER, conf.MYSQLDB_PASSWORD, conf.MYSQLDB_SERVER, conf.MYSQLDB_PORT);
    databaseManager.push();
//    Serial.begin(115200);
//    delay(10);
//
//    mqtt.setup_wifi();
//    client.setServer(mqtt.getMqttServer(), 1883);
//    client.setCallback(mqtt.callbackFunction());
//
//    /* ************************ */
//    /*  DS18B20 Sensor          */
//    /* ************************ */
//    Serial.println("DS18B20 Dallas Temperature begin");
//    sensorDS18B20.begin();
//    // locate devices on the bus
//    Serial.println("Locating devices...");
//    Serial.print("Found ");
//    deviceCount = sensorDS18B20.getDeviceCount();   // counting number of devices on the bus
//    Serial.print(deviceCount, DEC);
//    Serial.println(" devices.");
//    Serial.println("");
//
//    Serial.println("Printing addresses...");
//    for (int i = 0;  i < deviceCount;  i++)
//    {
//      Serial.print("Sensor ");
//      Serial.print(i+1);
//      Serial.print(" : ");
//      sensorDS18B20.getAddress(Thermometer, i);   // get each DS18b20 64bits address
//      mqtt.printAddress(Thermometer);            // function at the end of this code
//      //Serial.print(Thermometer);
//    }
//
//    /* ********************* */
//    /*  BME280 SENSOR        */
//    /* ********************* */
//    Serial.println("BME280 begin");
//    // I2C device found at address 0x76
//    Wire.begin();
//    if (sensorBME280.beginI2C() == false) //Begin communication over I2C
//    {
//      Serial.println("The sensor did not respond. Please check wiring.");
//      while(1); //Freeze
//    }
//    else
//    {
//      Serial.println("BME280 started & configured");
//    }

}

/* 
 *  ------------------
 *  MAIN LOOP
 *  ------------------
 */
void loop() {
  
//  long now = millis();
//  if (now - lastMsg > mqtt.getTimeInterval()) {
//    lastMsg = now;
//    if (!client.connected()) {
//      Serial.println("Reconnect to Mqtt");
//      mqtt.reconnect();
//    }
//    client.loop();
//
//    Serial.print(" Requesting temperatures...");
//    sensorDS18B20.requestTemperatures();
//    Serial.println("DONE");
//
//    Serial.print(" Water Temperature : ");
//    Serial.print(sensorDS18B20.getTempCByIndex(0), 2);
//
//    Serial.print(" Air Temperature : ");
//    Serial.print(sensorBME280.readTempC(), 2);
//
//    Serial.print(" Humidity: ");
//    Serial.print(sensorBME280.readFloatHumidity(), 0);
//
//    Serial.print(" Pressure: ");
//    Serial.print(sensorBME280.readFloatPressure(), 0);
//
//    Serial.print(" Altitude : ");
//    Serial.print(sensorBME280.readFloatAltitudeMeters(), 1);
//    Serial.println();
//
//    String json = "{\"user\":\""+(String)mqtt.getMqttUser()+"\",\"Humidity\":\""+(String)sensorBME280.readFloatHumidity()+"\",\"Pressure\":\""+(String)sensorBME280.readFloatPressure()+"\",\"Altitude\":\""+(String)sensorBME280.readFloatAltitudeMeters()+"\",\"AirTemperature\":\""+(String)sensorBME280.readTempC()+"\",\"WaterTemperature\":\""+(String)sensorDS18B20.getTempCByIndex(0)+"\"}";
//    client.publish(mqtt.getMqttOutput(), json.c_str() );
//    client.disconnect();
//
//    Serial.println("Mqtt sent to : " + (String)mqtt.getMqttOutput() );
//    Serial.println(json);
//    delay(500);
//  }
}
