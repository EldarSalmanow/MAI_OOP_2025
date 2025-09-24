#include <lab1/counter.h>

std::uint8_t CountOnesInNumber(std::uint64_t number) {
    std::uint8_t count = 0;

    while (number > 0) {
        if (number & 0b1) {
            ++count;
        }

        number >>= 1;
    }

    return count;
}

std::uint64_t CountOnesInSequence(std::uint32_t a,
                                  std::uint32_t b) {
    std::uint64_t count = 0;

    for (std::uint32_t i = a; i <= b; ++i) {
        count += CountOnesInNumber(i);
    }

    return count;
}
