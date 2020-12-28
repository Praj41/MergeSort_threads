#include <iostream>
#include <chrono>
#include <random>

long long int* RNG(unsigned int nos = 10, int min = 0, int max = 1000) {

    std::random_device rd;

    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count() );

    std::mt19937 gen(seed);
    std::uniform_int_distribution<long long int> distrib(min, max);

    auto *arr = new long long int[nos];

    for (unsigned long j = 0; j < nos; ++j)
    {
        arr[j] = distrib(gen);
    }

    return arr;
}

long long int RNG_s(int min = 0, int max = 1000) {

    std::random_device rd;

    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count() );

    std::mt19937 gen(seed);
    std::uniform_int_distribution<long long int> distrib(min, max);

    return distrib(gen);
}
