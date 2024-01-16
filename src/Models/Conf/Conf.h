//
// Created by Goura on 15/01/2024.
//

#ifndef GASSTATION_CONF_H
#define GASSTATION_CONF_H
#pragma once
#include "Ethernet.h"

namespace Conf {

    class Conf {
    public:
        static const char* ssid;
        static const char* password;
        static const char* mqtt_server;
        static const char* mqtt_output;
        static const char* mqtt_input;
        static const char* mqtt_log;
        static const char* mqtt_user;
        static const int ledPin;
        static int timeInterval;
        static IPAddress MYSQLDB_SERVER;
        static const char* MYSQLDB_NAME;
        static int MYSQLDB_PORT;
        static const char* MYSQLDB_USER;
        static const char* MYSQLDB_PASSWORD;
    };

} // Conf

#endif //GASSTATION_CONF_H
