////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Util.h"
#include <chrono>


////////////////////////////////////////////////////////////
std::mt19937 Util::_rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());


////////////////////////////////////////////////////////////
int Util::getRandomSignal()
{
    std::bernoulli_distribution bern;
    return (bern(_rng) ? 1 : -1);
}


////////////////////////////////////////////////////////////
int Util::getRandomInt(int a, int b)
{
    std::uniform_int_distribution<int> dist(a, b);
    return dist(_rng);
}


////////////////////////////////////////////////////////////
float Util::getRandomFloat(float a, float b)
{
    std::uniform_real_distribution<float> dist(a, b);
    return dist(_rng);
}
