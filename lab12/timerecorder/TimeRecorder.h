//
// Created by Noxianin on 2018-06-11.
//

#ifndef JIMP_EXERCISES_TIMERECORDER_H
#define JIMP_EXERCISES_TIMERECORDER_H
#include <vector>
#include <chrono>
namespace profiling {
    template <typename T>
    auto TimeRecorder(const T &object){
        auto start = std::chrono::system_clock::now();
        auto toReturn = object();
        auto end = std::chrono::system_clock::now();
        double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        auto p = std::make_pair(toReturn, time/1000000);
        return p;
    };
}

#endif //JIMP_EXERCISES_TIMERECORDER_H
