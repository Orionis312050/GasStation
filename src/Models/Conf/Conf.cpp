//
// Created by Goura on 15/01/2024.
//

#include "Conf.h"

namespace Conf {
        const char* Conf::ssid = "WifiRaspi";
        const char* Conf::password = "wifiraspi";
        const char* Conf::mqtt_server = "172.24.1.1";
        const char* Conf::mqtt_output = "esp32/update";
        const char* Conf::mqtt_input = "esp32/input";
        const char* Conf::mqtt_log = "esp32/log";
        const char* Conf::mqtt_user = "ESP32_Proto_Exemple";
        const int Conf::ledPin = 4;
        int Conf::timeInterval = 7500;

        /// Mysql configuration
        IPAddress Conf::MYSQLDB_SERVER = IPAddress(127, 0, 0, 1);
        const char* Conf::MYSQLDB_NAME = "valeur";
        int Conf::MYSQLDB_PORT = 3306;
        const char* Conf::MYSQLDB_USER = "root";
        const char* Conf::MYSQLDB_PASSWORD = "root";
} // Conf