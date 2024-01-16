//
// Created by Goura on 15/01/2024.
//

#ifndef GASSTATION_CAPTEURTHERMIQUE_H
#define GASSTATION_CAPTEURTHERMIQUE_H

#include "Interface/CapteurInterface/CapteurInterface.h"

namespace CapteurThermique {

    // implementation of CapteurInterface
    class CapteurThermique : public CapteurInterface::CapteurInterface {
        /// Déclaration des attributs de la classe CapteurThermique.
        private:
            string name;
        public:
        void setup() override;
        void update() override;
        double getValue() override;
        string getCalibrationMessage() override;
        void calibrate() override;
        void initCalibration() override;

    };

} // CapteurThermique

#endif //GASSTATION_CAPTEURTHERMIQUE_H
