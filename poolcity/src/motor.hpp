#ifndef motor
#define motor
class Motor {
private:
    int _frequency;
    constexpr static int _maxSpeed = 100;
public:
    Motor(int pinFwd, int pinRev, int frequency = 20);
    void forward(int speed = _maxSpeed);
    void backward(int speed = -_maxSpeed);
    void stop();
    void setSpeed(int speed = _maxSpeed);
};
#endif