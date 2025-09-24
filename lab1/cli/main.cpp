#include <iostream>

#include <lab1/counter.h>

int main() {
    std::int32_t a, b;

    std::cout << "Enter a & b numbers, where 0 <= a <= b: ";
    std::cin >> a >> b;
    if (std::cin.get() != '\n') {
        std::cout << "You must enter only two numbers!" << std::endl;

        return 1;
    }

    if (!((0 <= a)
       && (a <= b))) {
        std::cout << "[ERROR] a & b numbers must satisfy the rule 0 <= a <= b!" << std::endl;

        return 1;
    }

    std::uint32_t count = CountOnesInSequence(a, b);

    std::cout << "Count of ones in sequence [" << a << "; " << b << "] is " << count << std::endl;

    return 0;
}
