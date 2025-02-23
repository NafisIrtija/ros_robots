#ifndef RANGE_SENSOR
#define RANGE_SENSOR
class UltrasonicDistanceSensor {
private:
        int _pinTrigger;
        int _pinEcho;

        constexpr double Pi = 3.14159265358979323846;
        // assumes dry air at 20C
        constexpr double speed_of_sound = 343.0;

        // these come from the sensor datasheet and are used in creating
        // a ROS Range message.
        // https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
        constexpr double min_range = 0.030;
        constexpr double max_range = 4.000;
        constexpr double angle = 15.0 * Pi / 180.0;  //degrees to radians

        // pre-compute some static values
        constexpr double min_travel_time = 2.0 * min_range / speed_of_sound;
        constexpr double max_travel_time = 2.0 * max_range / speed_of_sound;

public:
    UltrasonicDistanceSensor(int pinTrigger, int pinEcho); 
    double measure ();
};
#endif