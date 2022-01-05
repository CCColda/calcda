#ifndef CALCDA_TEST_RANDOM_H
#define CALCDA_TEST_RANDOM_H

#include <random>
#include <vector>

std::vector<float> generateRandomFloats(unsigned count, float min, float max) {
    static std::random_device dev;
    static std::mt19937 gen(dev());

    std::uniform_real_distribution<float> distribution(min, max);

    std::vector<float> result(count, 0.0f);
    for (unsigned i = 0; i < count; ++i)
        result[i] = distribution(gen);

    return result;
}

#define CALCDA_DEFINE_RANDOM(varname) auto varname = std::vector<float>();

#define CALCDA_REQUIRE_RANDOM(varname, n)                                      \
    varname = generateRandomFloats(n, 1.0f, 20.0f);

#define CALCDA_REQUIRE_RANDOM_SORTED(varname, n)                               \
    {                                                                          \
        varname = generateRandomFloats(n, 1.0f, 20.0f);                        \
        std::sort(varname.begin(), varname.end());                             \
    }

#endif // !defined(CALCDA_TEST_RANDOM_H)