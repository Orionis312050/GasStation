//
// Created by Goura on 16/01/2024.
//

#ifndef GASSTATION_DATABASEMANAGER_H
#define GASSTATION_DATABASEMANAGER_H
#include "Ethernet.h"
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <iostream>
#include "ArduinoJson.h"

namespace DatabaseManager {

    class DatabaseManager {
    private:
        const char* nom;
        const char* user;
        const char* password;
        IPAddress server;
        int port;
        EthernetClient client;
        MySQL_Connection conn = MySQL_Connection(nullptr);
        bool connected;
    public:
        DatabaseManager(const char* nom, const char* user, const char* password, IPAddress server, int port){
            this->nom = nom;
            this->user = user;
            this->password = password;
            this->server = server;
            this->port = port;
            this->client = EthernetClient();
            this->conn = MySQL_Connection((Client *)&client);
            this->connected = connect();
        }
        bool connect();
        bool push();
        void deserializeJsonToObject(String json);
    };

} // DatabaseManager

#endif //GASSTATION_DATABASEMANAGER_H
