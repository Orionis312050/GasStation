//
// Created by Goura on 16/01/2024.
//

#include "DatabaseManager.h"

namespace DatabaseManager {
    bool DatabaseManager::connect() {
        MySQL_Cursor cur = MySQL_Cursor(&conn);
        bool connect = conn.connect(server, port, const_cast<char *>(user), const_cast<char *>(password),
                                    const_cast<char *>(nom));
        return connect;
    }

    // fonction de déserialisation JSON
    void DatabaseManager::deserializeJsonToObject(String json) {
        // On déclare un objet JSON
        DynamicJsonDocument doc(1024);
        // On parse le JSON
        deserializeJson(doc, json);
        // On récupère les valeurs
        const char *data_name = doc["data_name"];
        const char *unite = doc["unite"];
        float valeur = doc["valeur"];
        // On affiche les valeurs
        Serial.println(data_name);
        Serial.println(unite);
        Serial.println(valeur);
    }

    bool DatabaseManager::push() {
        MySQL_Cursor cur = MySQL_Cursor(&conn);
        if (connected) {
            cur.execute("INSERT INTO `valeur` (`data_name`, `unite`, `valeur`) VALUES (`temperature`, `Celsius`, 34.2);");
            cur.close();
            return true;
        } else {
            return false;
        }
    }
} // DatabaseManager