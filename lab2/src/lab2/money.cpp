#include <algorithm>
#include <stdexcept>

#include <lab2/money.h>


bool IsDigit(unsigned char symbol) {
    return symbol <= 9;
}

Money::Money() {
    _numbers = new unsigned char[1];
    _size = 1;

    std::fill_n(_numbers, _size, 0);
}

Money::Money(const std::size_t &size,
             unsigned char number) {
    if (size == 0) {
        throw std::invalid_argument("[ERROR] Input size must be positive number!");
    } else if (!IsDigit(number)) {
        throw std::invalid_argument("[ERROR] Input symbol must be a digit!");
    }

    _numbers = new unsigned char[size];
    _size = size;

    std::fill_n(_numbers, _size, number);

    RemoveLeadingZeros();
}

Money::Money(const std::initializer_list<unsigned char> &numbers) {
    if (numbers.size() == 0) {
        throw std::invalid_argument("[ERROR] Initializer list can`t be empty!");
    }

    for (const auto &number : numbers) {
        if (!IsDigit(number)) {
            throw std::invalid_argument("[ERROR] Initializer list must contain only digits!");
        }
    }

    _numbers = new unsigned char[numbers.size()];
    _size = numbers.size();

    std::copy_n(numbers.begin(), _size, _numbers);

    RemoveLeadingZeros();
}

Money::Money(const std::string &string) {
    if (string.size() < 4) {
        throw std::invalid_argument("[ERROR] Minimum size of money string is 4!");
    }

    for (std::uint64_t i = 0; i < string.size(); ++i) {
        if (i == string.size() - 3) {
            if (string[i] != '.') {
                throw std::invalid_argument("[ERROR] Money string must contain only one dot in the right place!");
            }
        } else if (!std::isdigit(string[i])) {
            throw std::invalid_argument("[ERROR] Money string must contain only digits and dot in the right place!");
        }
    }

    _numbers = new unsigned char[string.size() - 1];
    _size = string.size() - 1;

    for (std::int64_t i = 0, j = string.size() - 1; i < static_cast<std::int64_t>(_size); ++i, --j) {
        if (string[j] == '.') {
            --i;

            continue;
        }

        _numbers[i] = string[j] - '0';
    }

    RemoveLeadingZeros();
}

Money::Money(unsigned char *numbers,
             std::uint64_t size)
        : _numbers(numbers),
          _size(size) {
    RemoveLeadingZeros();
}

Money::Money(const Money &money)
        : _numbers(new unsigned char[money._size]),
          _size(money._size) {
    std::copy_n(money._numbers, _size, _numbers);
}

Money::Money(Money &&money) noexcept
        : _numbers(nullptr),
          _size(0) {
    std::swap(_numbers, money._numbers);
    std::swap(_size, money._size);
}

Money::~Money() noexcept {
    delete[] _numbers;
    _numbers = nullptr;
    _size = 0;
}

Money Money::Add(const Money &money) const {
    bool this_is_min = _size <= money._size;

    std::uint64_t min_size = this_is_min ? _size : money._size;
    unsigned char *min_buffer = this_is_min ? _numbers : money._numbers;
    std::uint64_t max_size = this_is_min ? money._size : _size;
    unsigned char *max_buffer = this_is_min ? money._numbers : _numbers;

    unsigned char *buffer = new unsigned char[max_size + 1];
    std::uint64_t buffer_size = max_size;

    std::uint64_t carry = 0;
    for (std::uint64_t i = 0; i < max_size; ++i) {
        std::uint64_t digit = max_buffer[i] + carry;

        if (i < min_size) {
            digit += min_buffer[i];
        }

        buffer[i] = digit % 10;
        carry = digit / 10;
    }

    buffer[buffer_size] = carry;
    if (carry > 0) {
        ++buffer_size;
    }

    return Money {
        buffer,
        buffer_size
    };
}

Money Money::Sub(const Money &money) const {
    if (Less(money)) {
        throw std::invalid_argument("[ERROR] After substraction operation money must be a non-negative!");
    }

    unsigned char *buffer = new unsigned char[_size];
    std::copy_n(_numbers, _size, buffer);

    for (std::uint64_t i = 0, borrow = 0; i < _size; ++i) {
        std::int64_t digit = static_cast<std::int64_t>(_numbers[i]) - borrow;

        if (i < money._size) {
            digit -= money._numbers[i];
        }

        if (digit < 0) {
            digit += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        buffer[i] = digit;

        if (borrow == 0 && i >= money._size) {
            break;
        }
    }

    return {
        buffer,
        _size
    };
}

Money Money::Clone() const {
    return {
        *this
    };
}

bool Money::Less(const Money &money) const {
    if (_size != money._size) {
        return _size < money._size;
    }

    for (std::int64_t i = static_cast<std::int64_t>(_size) - 1; i >= 0; --i) {
        if (_numbers[i] == money._numbers[i]) {
            continue;
        }

        return _numbers[i] < money._numbers[i];
    }

    return false;
}

bool Money::Greater(const Money &money) const {
    if (_size != money._size) {
        return _size > money._size;
    }

    for (std::int64_t i = static_cast<std::int64_t>(_size) - 1; i >= 0; --i) {
        if (_numbers[i] == money._numbers[i]) {
            continue;
        }

        return _numbers[i] > money._numbers[i];
    }

    return false;
}

bool Money::Eq(const Money &money) const {
    if (_size != money._size) {
        return false;
    }

    for (std::uint64_t i = 0; i < _size; ++i) {
        if (_numbers[i] != money._numbers[i]) {
            return false;
        }
    }

    return true;
}

Money Money::AddEq(const Money &money) const {
    return Add(money);
}

Money Money::SubEq(const Money &money) const {
    return Sub(money);
}

void Money::RemoveLeadingZeros() {
    std::int64_t non_zero_index = static_cast<std::int64_t>(_size) - 1;

    for (; non_zero_index >= 0; --non_zero_index) {
        if (_numbers[non_zero_index] != 0) {
            break;
        }
    }

    if (non_zero_index != static_cast<std::int64_t>(_size) - 1) {
        unsigned char *buffer = new unsigned char[non_zero_index + 1];
        std::uint64_t buffer_size = non_zero_index + 1;

        std::copy_n(_numbers, buffer_size, buffer);

        delete[] _numbers;

        _numbers = buffer;
        _size = buffer_size;
    }
}
