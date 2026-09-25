#pragma once

#include <chrono>
#include <string>

enum class SensorType {
    Temperature,
    Pressure,
    Position,
};

// Single measurement published by a sensor thread into the shared queue.
struct SensorEvent {
    std::string sensorId;
    std::chrono::system_clock::time_point timestamp;
    double value;
    SensorType type;
};