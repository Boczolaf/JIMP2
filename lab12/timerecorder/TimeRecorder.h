//
// Created by Noxianin on 2018-06-11.
//

#ifndef JIMP_EXERCISES_TIMERECORDER_H
#define JIMP_EXERCISES_TIMERECORDER_H
#include <vector>
#include <chrono>
namespace profiling
{
    template <typename T>
    auto TimeRecorder(T object)
    {
        auto from = std::chrono::high_resolution_clock::now();
        auto output = object();
        auto to = std::chrono::high_resolution_clock::now();

        auto time = std::chrono::duration<double,std::milli>(to-from).count();
        return std::make_pair(output,time);
    }
}

#endif //JIMP_EXERCISES_TIMERECORDER_H
