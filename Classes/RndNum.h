#ifndef __MillionCode__RandomNumber__
#define __MillionCode__RandomNumber__

#include <iostream>
#include <random>

class RndNum
{
private:
    static int uniformIntDistribution(const int min, const int max);
    static double uniformRealDistribution(const double min, const double max);
public:

    static void setSeed();

    static int mtRand(void);

    static int getIntMt(const int max);

    static int getIntMt(const int min, const int max);

    static double getDoubleMt(const double max);

    static double getDoubleMt(const double min, const double max);
};

#endif /* defined(__MillionCode__RandomNumber__) */
