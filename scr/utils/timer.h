// timer_advanced.h
//Edición: Junio 9 2025
//Por: Shekhina Velasquez
#pragma once
#include <chrono>
#include <string>
#include <vector>
#include <iostream>

class Timer {
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
        running = true;
    }
    
    void stop() {
        if (running) {
            auto end_time = std::chrono::high_resolution_clock::now();
            last_interval = std::chrono::duration<float, std::chrono::milliseconds::period>(end_time - start_time).count();
            intervals.push_back(last_interval);
            running = false;
        }
    }
    
    float elapsed() const {
        if (running) {
            auto current_time = std::chrono::high_resolution_clock::now();
            return std::chrono::duration<float, std::chrono::milliseconds::period>(current_time - start_time).count();
        }
        return last_interval;
    }
    
    void log(const std::string& message) {
        stop();
        std::cout << message << ": " << last_interval << " ms\n";
    }
    
    void statistics() const {
        float total = 0.0f;
        for (float t : intervals) total += t;
        
        std::cout << "Total time: " << total << " ms\n";
        std::cout << "Average: " << total/intervals.size() << " ms\n";
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    float last_interval = 0.0f;
    bool running = false;
    std::vector<float> intervals;
};
