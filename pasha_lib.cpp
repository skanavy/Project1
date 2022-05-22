#include "pasha_lib.hpp"

#include <cmath>

namespace pasha_lib {

bool randomWasInitialized = false;

int64_t randInt64(int64_t min, int64_t max) {
    if (min >= max) {
        throw std::invalid_argument(format("min should be less than max, but min = %d and max = %d", min, max));
    }
    if (!randomWasInitialized) {
        srand((unsigned)time(0));
        rand();
        randomWasInitialized = true;
    }
    return min + std::rand() * (max - min) / (RAND_MAX + 1u);
}

int64_t randInt64(int64_t max) { return randInt64(0, max); }
int randInt(int min, int max) { return (int)randInt64(min, max); }
int randInt(int max) { return randInt(0, max); }

double randDouble(int64_t min, int64_t max, uint8_t precision) {
    double precisionFactor = std::pow(10.0, 3.0);
    return randInt64(min * precisionFactor, max * precisionFactor) / precisionFactor;
}

double randDouble(int64_t min, int64_t max) { return randDouble(min, max, 3); }
double randDouble(int64_t max) { return randDouble(0, max, 3); }
float randFloat(int64_t min, int64_t max, uint8_t precision) { return randDouble(min, max, precision); }
float randFloat(int64_t min, int64_t max) { return randFloat(min, max, 3); }
float randFloat(int64_t max) { return randFloat(0, max, 3); }

std::string toString(TimeMeasureUnit timeMeasureUnit)
{
    switch (timeMeasureUnit) {
        case TimeMeasureUnit::nanoseconds: return "nanoseconds";
        case TimeMeasureUnit::microseconds: return "microseconds";
        case TimeMeasureUnit::milliseconds: return "milliseconds";
        case TimeMeasureUnit::seconds: return "seconds";
        case TimeMeasureUnit::minutes: return "minutes";
        case TimeMeasureUnit::hours: return "hours";
        default: throw std::invalid_argument("Unknown time type"); return "";
    }
}

long long duration(const std::chrono::steady_clock::time_point& begin, const std::chrono::steady_clock::time_point& end, TimeMeasureUnit timeMeasureUnit)
{
    auto duration = end - begin;
    switch (timeMeasureUnit) {
        case TimeMeasureUnit::nanoseconds: return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
        case TimeMeasureUnit::microseconds: return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
        case TimeMeasureUnit::milliseconds: return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        case TimeMeasureUnit::seconds: return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
        case TimeMeasureUnit::minutes: return std::chrono::duration_cast<std::chrono::minutes>(duration).count();
        case TimeMeasureUnit::hours: return std::chrono::duration_cast<std::chrono::hours>(duration).count();
        default: throw std::invalid_argument("Unknown time type"); return 0;
    }
}

void executeAndPrintTime(const std::string& printPrefix, TimeMeasureUnit timeMeasureUnit, const std::function<void()>& block) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    block();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << printPrefix << duration(begin, end, timeMeasureUnit) << " " << toString(timeMeasureUnit) << std::endl;
}

}  // end of pasha_lib namespace
