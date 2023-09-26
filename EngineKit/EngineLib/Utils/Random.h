#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <cstdint>
#include <random>

namespace fts {

    class Random {
    public:
        static float Rnd(float min, float max);
        static double Rnd(double min, double max);
        static int Rnd(int min, int max);

        static void Init(uint32_t seed);

    private:
        static double Uniform();
    };

}  // namespace SD
#endif // __RANDOM_H__