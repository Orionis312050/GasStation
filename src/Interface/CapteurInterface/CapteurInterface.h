//
// Created by Goura on 15/01/2024.
//

#ifndef GASSTATION_CAPTEURINTERFACE_H
#define GASSTATION_CAPTEURINTERFACE_H
#include "Arduino.h"
#include <iostream>
#include <string>
using namespace std;
#pragma once

namespace CapteurInterface {

    class CapteurInterface {
    protected:
        int ledPin;
        int _sensorId;
        string sensorName;
        string unit;
        int calibrationStep;
        int calibrationCurrentStep;
        bool sensorIsCalibrate;
    public:
        virtual void setup()		= 0;
        virtual void update()		= 0;
        virtual double getValue()	= 0;
        virtual string getCalibrationMessage() = 0;
        virtual void calibrate(); // Can be overriden for specific sensors ( Ph / EC / ... )
        virtual void initCalibration(); // Can be overriden for specific sensors ( Ph / EC / ... )
        int isCalibrate();
        int getCalibrationStep();
        int getCalibrationCurrentStep();
        void setCalibrationCurrentStep(int stepNumber);
        string getUnit();

    };

} // CapteurInterface

#endif //GASSTATION_CAPTEURINTERFACE_H
