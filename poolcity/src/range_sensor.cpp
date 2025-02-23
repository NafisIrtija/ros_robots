#include "range_sensor.hpp"
#include <wiringPi.h>
#include <thread>
#include <chrono>
#include <iostream>

UltrasonicDistanceSensor::UltrasonicDistanceSensor(int pinTrigger, int pinEcho)
: _pinTrigger(pinTrigger), _pinEcho(pinEcho)
{
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "wiringPi initialization failed." << std::endl;
        return;
    }
    pinMode(_pinTrigger, OUTPUT);
    pinMode(_pinEcho, INPUT);
}

double UltrasonicDistanceSensor::measure () {
    double elapsed_time;

    //  Send a 10us pulse
    digitalWrite(_pinTrigger, HIGH);
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    digitalWrite(_pinTrigger, LOW);
    
    //  Wait for echo to go high, then low
    auto StartTime = std::chrono::high_resolution_clock::now();
    while(digitalRead(_pinEcho) == 0) {
        StartTime = std::chrono::high_resolution_clock::now();
    }
    auto StopTime = std::chrono::high_resolution_clock::now();
    while(digitalRead(_pinEcho) == 1) {
        StopTime = std::chrono::high_resolution_clock::now();
        elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(StopTime - StartTime).count();
        if(elapsed_time >= 0.04) {
            StopTime = StartTime;
            break;
        }
    }
    return elapsed_time * speed_of_sound / 2;
}
