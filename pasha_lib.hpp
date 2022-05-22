#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace pasha_lib {

// generates random integer number from min (including) to max (excluding)
int64_t randInt64(int64_t min, int64_t max);
int64_t randInt64(int64_t max); // min = 0
int randInt(int min, int max);
int randInt(int max); // min = 0

// generates random fractional nubmer from min (including) to max (excluding)
// where precision is number of signs after point
double randDouble(int64_t min, int64_t max, uint8_t precision);
double randDouble(int64_t min, int64_t max); // precision = 3
double randDouble(int64_t max); // min = 0, precision = 3
float randFloat(int64_t min, int64_t max, uint8_t precision);
float randFloat(int64_t min, int64_t max); // precision = 3
float randFloat(int64_t max); // min = 0, precision = 3

template <typename Elem>
std::vector<Elem> generateVector(size_t size, const std::function<Elem()>& elemGenerator) {
    std::vector<Elem> result;
    result.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        result.push_back(elemGenerator());
    }
    return result;
}

template <typename ... Args>
std::string format(const std::string& formatString, Args ... args) {
    int size_s = std::snprintf(nullptr, 0, formatString.c_str(), args ... ) + 1;
    if (size_s <= 0) throw std::runtime_error("Error during formatting string: '" + formatString + "'");
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, formatString.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1);
}

enum class TimeMeasureUnit { nanoseconds, microseconds, milliseconds, seconds, minutes, hours };
std::string toString(TimeMeasureUnit timeMeasureUnit);
long long duration(const std::chrono::steady_clock::time_point& begin, const std::chrono::steady_clock::time_point& end, TimeMeasureUnit timeMeasureUnit);

void executeAndPrintTime(const std::string& printPrefix, TimeMeasureUnit timeMeasureUnit, const std::function<void()>& block);

template <typename Result>
Result executeAndPrintTime(const std::string& printPrefix, TimeMeasureUnit timeMeasureUnit, const std::function<Result()>& block) {
    Result result;
    executeAndPrintTime(printPrefix, timeMeasureUnit, [&] { result = block(); });
    return result;
}

template <typename Elem>
void printVector(const std::vector<Elem>& v, const std::function<void(const Elem&)>& printElem) {
    if (v.empty()) {
        std::cout << "[]" << std::endl;
        return;
    }

    std::cout << "[";
    
    for (size_t i = 0; i < v.size() - 1; ++i) {
        printElem(v[i]);
        std::cout << ", ";
    }
    
    printElem(v[v.size() - 1]);
    std::cout << "]" << std::endl;
}

template <typename Elem>
void printVector(const std::vector<Elem>& v) {
    printVector<Elem>(v, [](const Elem& elem){
        std::cout << elem;
    });
}

}  // end of pasha_lib namespace
