#ifndef MAI_OOP_2025_MONEY_H
#define MAI_OOP_2025_MONEY_H

#include <cstdint>
#include <string>


class Money {
public:

    Money();

    Money(const std::size_t &size,
          unsigned char number = 0);

    Money(const std::initializer_list<unsigned char> &numbers);

    Money(const std::string &string);

private:

    Money(unsigned char *numbers,
          std::uint64_t size);

public:

    Money(const Money &money);

    Money(Money &&money) noexcept;

public:

    virtual ~Money() noexcept;

public:

    Money Add(const Money &money) const;

    Money Sub(const Money &money) const;

    Money Clone() const;

    bool Less(const Money &money) const;

    bool Greater(const Money &money) const;

    bool Eq(const Money &money) const;

    Money AddEq(const Money &money) const;

    Money SubEq(const Money &money) const;

private:

    void RemoveLeadingZeros();

public:

    Money &operator=(const Money &money) = delete;

    Money &operator=(Money &&money) noexcept = delete;

private:

    unsigned char *_numbers;

    std::uint64_t _size;
};

#endif //MAI_OOP_2025_MONEY_H
