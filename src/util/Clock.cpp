//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#include "Clock.h"
#include <chrono>
#include <thread>

namespace util {

    long long now(){
        return std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }

    Clock::Clock() : time() {
        reset();
    }

    void Clock::reset() {
        time = now();
    }

    double Clock::elapsed() {
        long long diff = now() - time;
        return (double) diff / 1000.0 / 1000.0 / 1000.0;
    }

    double Clock::round() {
        long long nowTime = now();
        long long diff = nowTime - time;
        time = nowTime;
        return (double)diff / 1000.0 / 1000.0 / 1000.0;
    }

    void Clock::sleep(double seconds) {
        std::this_thread::sleep_for(std::chrono::microseconds((long long)(seconds * 1000 * 1000)));
    }

}
