# TASKS.md — Implementation task list

Context, architecture, goals, constraints: see [AGENTS.md](AGENTS.md).

Timeline: implement by Sept 26, **apply Sept 27, 2026**; Sept 28 = deadline/backup day, not build day. Commit after each task (`feat: T2 thread-safe queue`).


- [x] **T0** Fix `CMakeLists.txt`: C++23, single `src/main.cpp` entry (was listed 3×), `find_package(Threads)` + link `Threads::Threads`, `CMAKE_CXX_EXTENSIONS OFF`. Build verified via `out/`.
- [ ] **T1** `models/SensorEvent.h`: `sensorId`, `timestamp`, `value`, `type`.
- [ ] **T2** `concurrency/ThreadSafeQueue<T>`: `push`, blocking `pop`, `tryPop`, `size`, `close` (wakes waiters, ends consumer). Mutex + condition_variable.
- [ ] **T3** `TemperatureSensor`: value 24–28 °C, publish interval 100–500 ms, atomic stop flag.
- [ ] **T4** `PressureSensor` (95–105 kPa) and `PositionSensor` (X/Y mm), same interface.
- [ ] **T5** Processor thread: consume queue, print events, feed controller.
- [ ] **T6** `main.cpp` wiring: sensors as threads, queue, processor, clean join/shutdown.

Theory to learn alongside: process vs thread, race conditions, critical sections, mutex, condition_variable, producer–consumer, join/detach.


- [ ] **T7** `MachineState` enum + `MachineController`: start/stop/reset/emergencyStop with legal transitions only.
- [ ] **T8** Fault detection: temperature ≥ 70 °C or pressure outside 90–110 kPa while Running → Error state + `[ALARM]` output.
- [ ] **T9** `network/TcpServer`: socket/bind/listen/accept loop, thread per client, line-based protocol, handles disconnects.
- [ ] **T10** Command execution: `START`, `STOP`, `STATUS`, `RESET`, `EMERGENCY_STOP` → responses; unknown command and bad state handled gracefully.
- [ ] **T11** Control client (second console app or `--client` mode): connect, send commands, print responses.

Theory to learn alongside: TCP vs UDP, sockets, client–server, thread-per-connection, State pattern, Command pattern.

- [ ] **T12** `util/Logger`: thread-safe, `logs/machine.log`, levels INFO/WARNING/ERROR, timestamped lines like `09:42:10 [INFO] Machine started`.
- [ ] **T13** `util/Metrics`: events generated/received/processed/dropped, avg processing time, max queue size, commands processed; `PERFORMANCE` report block (periodic or on exit).
- [ ] **T14** Tests (plain asserts, no framework): machine starts; machine stops; temp over limit → Error; 1000 events all processed; multiple concurrent TCP clients stable; concurrent logging does not corrupt log.
- [ ] **T15** README rewrite: overview, features, architecture diagram, technologies, example terminal output, concepts demonstrated.
- [ ] **T16** Polish: fix warnings, remove dead code, push to GitHub, update CV with project entry + bullets, rehearse explanations. **Apply Sept 27.**

Theory to learn alongside: latency vs throughput, deadlock, atomics, OS scheduling, debugging races/deadlocks.
