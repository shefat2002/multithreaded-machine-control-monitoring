#include <iostream>

#include "models/SensorEvent.h"

int main() {
    SensorEvent smoke{.sensorId = "temp-1",
                      .timestamp = std::chrono::system_clock::now(),
                      .value = 25.0,
                      .type = SensorType::Temperature};

    std::cout << "Hello, World!\n";
    std::cout << "sensor=" << smoke.sensorId << " value=" << smoke.value << '\n';
    return 0;
}
