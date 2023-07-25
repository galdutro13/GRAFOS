//
// Created by galdu on 25/07/2023.
//

#ifndef GRAFOS_LATECONST_H
#define GRAFOS_LATECONST_H

#include <optional>

template <typename T>
class LateConstant
{
public:
    LateConstant() = default;
    LateConstant(const LateConstant&) = delete;
    LateConstant& operator=(const LateConstant&) = delete;

    LateConstant& operator=(const T& x)
    {
        if (!v.has_value())
        {
            v = std::make_optional<T>(x);
        }
        else
        {
            std::terminate();
        }

        return *this;
    }

    [[nodiscard]] bool has_value() const
    {
        return v.has_value();
    }

    [[nodiscard]] const T& value() const
    {
        return v.value();
    }

    T operator+(const LateConstant<T>& other);
    T operator+(const int& i);

private:
    std::optional<T> v;
};

template<>
int LateConstant<int>::operator+(const LateConstant<int>& other)
{
    if(this->has_value() && other.has_value())
    {
        return this->value() + other.value();
    }
    else
    {
        std::terminate();
    }
}

template <>
int LateConstant<int>::operator+(const int &i) {
    if(this->has_value())
    {
        return this->value() + 1;
    } else
    {
        std::terminate();
    }
}


#endif //GRAFOS_LATECONST_H
