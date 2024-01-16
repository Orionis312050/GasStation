//
// Created by Goura on 15/01/2024.
//

#include "CapteurInterface.h"

namespace CapteurInterface {

        /*void CapteurInterface::calibrate() {
            Serial.println("Calibration");
        }

        void CapteurInterface::initCalibration() {
            Serial.println("Init Calibration");
        }*/

        int CapteurInterface::isCalibrate() {
            return this->sensorIsCalibrate;
        }

        int CapteurInterface::getCalibrationStep() {
            return this->calibrationStep;
        }

        int CapteurInterface::getCalibrationCurrentStep() {
            return this->calibrationCurrentStep;
        }

        void CapteurInterface::setCalibrationCurrentStep(int stepNumber) {
            this->calibrationCurrentStep = stepNumber;
        }

        string CapteurInterface::getUnit() {
            return this->unit;
        }
} // CapteurInterface