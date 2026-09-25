# Multithreaded Machine Control & Monitoring Simulator

## Overview

A C++23 simulation of an industrial machine control system
designed to demonstrate concurrent sensor processing,
thread-safe communication and TCP-based machine control.

## Features

- Multithreaded sensor simulation
- Thread-safe producer-consumer queue
- Machine state management
- Fault detection
- TCP/IP communication
- Multi-client handling
- Thread-safe logging
- Performance monitoring

## Architecture
```
                    ┌──────────────────────┐
                    │    Control Client    │
                    │                      │
                    │ START / STOP / STATUS│
                    └──────────┬───────────┘
                               │
                              TCP
                               │
                               ▼
┌──────────────────────────────────────────────────────┐
│                 MACHINE CONTROLLER                   │
│                                                      │
│  ┌─────────────┐   ┌─────────────┐   ┌────────────┐ │
│  │ Temperature │   │  Pressure   │   │  Position  │ │
│  │   Thread    │   │   Thread    │   │   Thread   │ │
│  └──────┬──────┘   └──────┬──────┘   └─────┬──────┘ │
│         │                 │                 │        │
│         └─────────────────┼─────────────────┘        │
│                           ▼                          │
│                  ┌─────────────────┐                │
│                  │ Thread-Safe Queue│                │
│                  └────────┬────────┘                │
│                           ▼                          │
│                  ┌─────────────────┐                │
│                  │ Data Processor  │                │
│                  └────────┬────────┘                │
│                           ▼                          │
│                  ┌─────────────────┐                │
│                  │ Machine State   │                │
│                  │    Manager      │                │
│                  └────────┬────────┘                │
│                           │                          │
│                    ┌──────┴──────┐                   │
│                    ▼             ▼                   │
│                  NORMAL        ERROR                 │
└──────────────────────────────────────────────────────┘
```

## Technologies

C++23
STL
Multithreading
TCP/IP
CMake

## Example

## Concepts Demonstrated

- Thread synchronization
- Race condition prevention
- Producer-consumer pattern
- Socket programming
- State management
- Performance measurement