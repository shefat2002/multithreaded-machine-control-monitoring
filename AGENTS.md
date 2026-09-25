# AGENTS.md

## Project
Multithreaded Machine Control & Monitoring Simulator.

## Goal
Build a small C++23 industrial machine simulator demonstrating:
- Multithreading and thread synchronization
- Thread-safe producer-consumer processing
- Machine state management and fault detection
- TCP/IP client-server communication
- Logging and basic performance metrics

## Tech
- C++23
- STL
- CMake
- TCP/IP sockets
- No unnecessary frameworks or dependencies

## Architecture
- `machine/` — machine controller and state management
- `sensors/` — simulated sensors
- `concurrency/` — thread-safe data structures
- `network/` — TCP server/client
- `models/` — shared data models
- `tests/` — basic tests

```text
Control Client ──TCP──► Machine Server
                            │
   Temperature ─┐           │
   Pressure ────┼─► ThreadSafeQueue ─► Processor ─► MachineController ─► NORMAL / ERROR (+ alarm)
   Position ────┘                                      │
                                              Logger (thread-safe) + Metrics
```
- Each sensor thread generates values every 100–500 ms and publishes `SensorEvent{sensorId, timestamp, value, type}`.
- Processor thread consumes events, updates controller, prints values.
- States: `Idle → Starting → Running → {Stopped | Error}`. Fault: temperature ≥ 70 °C or pressure outside 90–110 kPa while Running → `Error` + emergency stop; `RESET` → `Idle`.
- TCP commands (plain text): `START`, `STOP`, `STATUS`, `RESET`, `EMERGENCY_STOP`. Responses: state, sensor values, ack/error. Thread per client.

## Project layout

```text
MachineControlSimulator/
├── CMakeLists.txt
├── CMakePresets.json
├── src/
│   ├── main.cpp
│   ├── machine/MachineController.h/.cpp, MachineState.h
│   ├── sensors/TemperatureSensor.h/.cpp, PressureSensor.h/.cpp, PositionSensor.h/.cpp
│   ├── concurrency/ThreadSafeQueue.h
│   ├── network/TcpServer.h/.cpp
│   ├── models/SensorEvent.h
│   └── util/Logger.h/.cpp, Metrics.h/.cpp
├── tests/
└── README.md
```

## Build & run

```bash
cmake --preset debug && cmake --build --preset debug
./out/debug/MachineControlSimulator
```

Build dirs live in `out/` (gitignored). Never commit build artifacts.

## Implementation plan

Task checklist: [TASKS.md](TASKS.md).

## Outcomes

On completion: working simulator (sensors → queue → processor → state machine), TCP server + client with 5 commands, thread-safe logging, performance metrics, passing basic tests, polished README on GitHub — every component explainable in an interview without AI assistance.

## Implementation Rules
- Prefer simple, readable C++ over over-engineering.
- Use RAII and smart pointers where ownership is required.
- Avoid global mutable state.
- Protect shared data with appropriate synchronization.
- Avoid detached threads; manage thread lifetime explicitly.
- Keep components small and independently testable.
- Use `std::mutex`, `std::condition_variable`, and `std::atomic` appropriately.
- Do not add features outside the project scope without necessity.

## Process Rules
1. Never break the build; commit after each task (`feat: T2 thread-safe queue`).
2. Build component → immediately learn the theory behind it. No copy-paste without comprehension; theory is 60% of the effort.
3. No scope creep: no GUI, DB, MFC/WPF, SECS/GEM, extra frameworks.
4. Socket code stays in `network/` only.

## Development Priority
1. Machine + sensors
2. Multithreading
3. Thread-safe queue
4. Data processing
5. State/fault management
6. TCP communication
7. Logging
8. Performance metrics
9. Tests and documentation

## Code Quality
Every implementation should be explainable by the developer in an interview. Favor correctness, clarity, and demonstrable C++/systems concepts over feature count.
