//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#ifndef UTIL_MATH_H
#define UTIL_MATH_H

namespace util{

    template<typename T>
    T min(const T &a, const T &b) {
        return a < b ? a : b;
    }

    template<typename T>
    T max(const T &a, const T &b) {
        return a > b ? a : b;
    }

    template<typename T>
    T abs(const T &a) {
        return a > (T) 0 ? a : -a;
    }

    template<typename T>
    int sign(const T &a) {
        return a > (T) 0 ? 1 : (a < (T) 0 ? -1 : 0);
    }

    template<typename T>
    void swap(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }

    template<typename T>
    T pow2(T x) {
        return x * x;
    }

    template<typename T>
    void clamp(T &value, T minValue, T maxValue){
        value = max(value, minValue);
        value = min(value, maxValue);
    }

    template<typename T>
    void cycle(T &value, T min, T max){
        T diff = max - min + 1;
        value -= min;
        if(diff == 0){
            value = 0;
        }else{
            value = value % diff;
        }
        if(value < 0){
            value += diff;
        }
        value += min;
    }

    template<>
    void cycle<double>(double &value, double min, double max);

    template<>
    void cycle<float>(float &value, float min, float max);

    float randf();
    float randf(float min, float max);
    int randi(int min, int max);
    void rands(int seed = 0);

}

#endif //UTIL_MATH_H
