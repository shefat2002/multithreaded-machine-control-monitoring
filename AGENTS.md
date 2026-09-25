# AGENTS.md — MachineControlSimulator

Instructions for AI agents working in this repo. Hard timeline: **implement by Sept 26, apply Sept 27, 2026; Sept 28 = deadline/backup day, not build day.** Keep changes small, buildable, committed after every task.

## Project

**Multithreaded Machine Control & Monitoring Simulator** — C++17 console app simulating an industrial machine: concurrent sensor threads → thread-safe queue → processor → machine state manager with fault detection, plus a TCP command server and thread-safe logging. No GUI, no database, no real hardware. Purpose: demonstrate C++ / multithreading / networking / design-pattern skills for a job application.

## Tech & constraints

- C++23, CMake ≥ 3.20, STL only, no external dependencies.
- `std::thread`, `std::mutex`, `std::condition_variable`, `std::atomic`, `std::queue`, `std::unique_ptr`.
- TCP via POSIX sockets (dev on macOS); keep all socket code isolated in `network/` for later Windows portability.
- Design patterns: Producer–Consumer (queue), State (machine lifecycle; enum + controller acceptable — full State pattern only if time allows), Command (TCP command handling).

## Architecture

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
cmake -S . -B build
cmake --build build
./build/MachineControlSimulator
```

## Implementation plan

Task checklist with day-by-day schedule: [TASKS.md](TASKS.md).

## Outcomes

On completion: working simulator (sensors → queue → processor → state machine), TCP server + client with 5 commands, thread-safe logging, performance metrics, passing basic tests, polished README on GitHub — every component explainable in an interview without AI assistance.

### Theory checklist (interview must be defensible without AI)

C++ memory model; stack vs heap; pointer vs reference; RAII; smart pointers; move semantics; STL containers; process vs thread; context switching; race conditions; mutex; atomic; condition variable; deadlock; producer–consumer; thread pool concept; TCP vs UDP; sockets; client–server; OS scheduling; State pattern; Command pattern; latency vs throughput.

## Rules

1. Never break the build; commit after each task (`feat: T2 thread-safe queue`).
2. Build component → immediately learn the theory behind it. No copy-paste without comprehension; theory is 60% of the effort.
3. No scope creep: no GUI, DB, MFC/WPF, SECS/GEM, extra frameworks.
4. Socket code stays in `network/` only.
5. Apply Sept 27 even if polish remains.
