#pragma once

template <typename Iterable, typename F>
Iterable& performOperation(Iterable &first, const Iterable &second, F operation)
{
    auto firstIt = first.begin();
    auto secondIt = second.begin();

    for (;firstIt < first.end(); ++firstIt, ++secondIt)
    {
        operation(*firstIt, *secondIt);
    }

    return first;
}

template <typename Iterable>
Iterable& operator+=(Iterable &first, const Iterable &second)
{
    return performOperation(first, second,
        [](auto &f, const auto &s)
            {
                f += s;
            });
}

template <typename Iterable>
Iterable operator+(const Iterable &first, const Iterable &second)
{
    Iterable copy = first;
    return (copy += second);
}

template <typename Iterable>
Iterable& operator*=(Iterable &first, const Iterable &second)
{
    return performOperation(first, second,
        [](auto &f, const auto &s)
            {
                f *= s;
            });
}

template <typename Iterable>
Iterable operator*(const Iterable &first, const Iterable &second)
{
    Iterable copy = first;
    return (copy *= second);
}

template <typename Iterable>
Iterable& operator-=(Iterable &first, const Iterable &second)
{
    return performOperation(first, second,
        [](auto &f, const auto &s)
            {
                f -= s;
            });
}

template <typename Iterable>
Iterable operator-(const Iterable &first, const Iterable &second)
{
    Iterable copy = first;
    return (copy -= second);
}

template <typename Iterable>
Iterable& operator/=(Iterable &first, const Iterable &second)
{
    return performOperation(first, second,
        [](auto &f, const auto &s)
            {
                f /= s;
            });
}

template <typename Iterable>
Iterable operator/(const Iterable &first, const Iterable &second)
{
    Iterable copy = first;
    return (copy /= second);
}

