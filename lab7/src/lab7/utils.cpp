#include <random>

#include <lab7/utils.h>


auto RandomInRange(int begin,
                   int end) -> int {
    std::random_device device;
    std::mt19937 generator(device());

    std::uniform_int_distribution distribution(begin, end);

    return distribution(generator);
}
