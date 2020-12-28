#pragma once

#include <iostream>
#include <chrono>

class Timer {
    std::chrono::time_point< std::chrono::high_resolution_clock> StartTimePoint;
    unsigned int _step;
public:
    Timer() : _step(0) {
        StartTimePoint = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        auto EndTimePoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(StartTimePoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimePoint).time_since_epoch().count();

        auto duration = end - start;

        std::cout << duration << "us (" << duration * 0.001 << "ms) - END" << std::endl;
    }
    void lap() {
        auto EndTimePoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(StartTimePoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimePoint).time_since_epoch().count();

        auto duration = end - start;

        std::cout << duration << "us (" << duration * 0.001 << "ms) - STEP_" << ++_step << std::endl;
    }
    void lap_reset() {
        auto EndTimePoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(StartTimePoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimePoint).time_since_epoch().count();

        auto duration = end - start;

        _step = 0;
        std::cout << duration << "us (" << duration * 0.001 << "ms) - RESET_STEP_" << _step << std::endl;

        StartTimePoint = std::chrono::high_resolution_clock::now();
    }
};