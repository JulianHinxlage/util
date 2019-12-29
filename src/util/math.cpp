//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#include "math.h"
#include <random>

namespace util{

    template<>
    void cycle<double>(double &value, double min, double max){
        double diff = max - min;
        value -= min;
        value = value - (double)(int)(value / diff) * diff;
        if(value < 0){
            value += diff;
        }
        value += min;
    }

    template<>
    void cycle<float>(float &value, float min, float max){
        float diff = max - min;
        value -= min;
        value = value - (float)(int)(value / diff) * diff;
        if(value < 0){
            value += diff;
        }
        value += min;
    }

    float randf() {
        return (float)(rand()) / RAND_MAX;
    }

    float randf(float min, float max) {
        return randf() * (max - min) + min;
    }

    int randi(int min, int max) {
        return (int)rand() % (max - min) + min;
    }

    void rands(int seed) {
        if(seed == 0){
            srand((unsigned int)time(nullptr));
        }else{
            srand((unsigned int)seed);
        }
    }

}
