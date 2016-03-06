#ifndef UTIL_H
#define UTIL_H

#include <random>

class Util {
public:
	static int getRandomSignal();
	static int getRandomInt(int a, int b);
	static float getRandomFloat(float a, float b);
private:
    static std::mt19937 _rng;
};

#endif // UTIL_H
