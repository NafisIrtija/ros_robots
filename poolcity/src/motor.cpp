#include <wiringPi.h>
#include <iostream>
#include "motor.hpp"

Motor::Motor(int pinFwd, int pinRev, int frequency) : _frequency(frequency)
{
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "wiringPi initialization failed." << std::endl;
        return;
    }
    pinMode(pinFwd, PWM_OUTPUT);
    pinMode(pinRev, PWM_OUTPUT);

    pwmSetMode(PWM_MODE_MS);

    pwmSetRange(1024); // Set PWM range (default is 1024)
    pwmSetClock(19200000 / _frequency / 1024);

    stop();
}

void Motor::forward(int speed) {
    setSpeed(speed);
}

void Motor::backward(int speed) {
    setSpeed(-1 * speed);
}

void Motor::stop() {
    setSpeed(0);
}

void Motor::setSpeed(int speed) {
    speed = min(_maxSpeed, speed);
    speed = max(-_maxSpeed, speed);

    if(speed < 0) {
        pwmWrite(_pwmFwd, 0);
        pwmWrite(_pwmRev, speed * -1024 / 100);
    } else {
        pwmWrite(_pwmFwd, speed * 1024 / 100);
        pwmWrite(_pwmRev, 0);
    }
}