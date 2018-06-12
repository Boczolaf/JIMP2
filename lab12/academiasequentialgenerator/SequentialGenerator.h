//
// Created by Noxianin on 2018-06-12.
//

#ifndef JIMP_EXERCISES_SEQUENTIALGENERATOR_H
#define JIMP_EXERCISES_SEQUENTIALGENERATOR_H
#include <string>

using ::std::string;

class Value {
public:
    Value() : value(0) {}
    explicit Value(int val) : value(val){}
    int operator++(int value) {return this->value++;}
    int operator++() {return this->value++;}

private:
    int value;
};


template <typename Type, typename Value1>
class SequentialIdGenerator {
public:

    SequentialIdGenerator() : id(0) {}
    explicit SequentialIdGenerator(int value) : id(value) {}
    Type NextValue() {
        return ++this->id;
    }

private:
    Value id;
};
#endif //JIMP_EXERCISES_SEQUENTIALGENERATOR_H
