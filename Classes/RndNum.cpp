#include "RndNum.h"

namespace MT
{
    std::mt19937 mt;
}


void RndNum::setSeed()
{
    std::random_device rd;
    MT::mt.seed(rd());
}

int RndNum::mtRand()
{
    return MT::mt();
}

int RndNum::uniformIntDistribution(const int min, const int max)
{
    std::uniform_int_distribution<int> rnd(min, max);
    return rnd(MT::mt);
}

double RndNum::uniformRealDistribution(const double min, const double max)
{
    std::uniform_real_distribution<double> rnd(min, max);
    return rnd(MT::mt);
}

int RndNum::getIntMt(const int max)
{
    return uniformIntDistribution(0, max);
}

int RndNum::getIntMt(const int min, const int max)
{
    return uniformIntDistribution(min, max);
}

double RndNum::getDoubleMt(const double max)
{
    return uniformRealDistribution(0.0, max);
}

double RndNum::getDoubleMt(const double min, const double max)
{
    return uniformRealDistribution(min, max);
}

