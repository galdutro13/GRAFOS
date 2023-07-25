//
// Created by galdu on 25/07/2023.
//

/*
A classe LateConstant foi implementada para representar
 uma constante que pode ser atribuída apenas uma vez em
 sua vida útil. Essa classe é útil em situações onde uma
 variável precisa ser inicializada tardiamente, ou seja,
 seu valor inicial não é conhecido no momento da criação,
 mas uma vez que o valor é estabelecido, ele não deve mais
 ser alterado.

Além disso, a classe oferece segurança adicional para
 impedir a reatribuição acidental do valor, lançando um
 término de programa caso uma segunda tentativa de
 atribuição seja feita.

A classe LateConstant é um template, permitindo que ela seja
 usada com qualquer tipo de dados. A classe também foi estendida
 para suportar adição de um valor inteiro à constante (apenas
 para o tipo int), permitindo expressões do tipo
 `LateConstant<int> = LateConstant<int> + int`,
 o que pode ser útil em alguns contextos específicos.

As funções has_value e value são usadas para verificar se um valor
 foi atribuído à constante e para acessar o valor da constante,
 respectivamente. Além disso, o atributo [[nodiscard]] foi adicionado
 à função has_value para indicar que o valor de retorno desta função
 não deve ser ignorado, ajudando assim a evitar erros sutis.

Por fim, vale ressaltar que o uso de std::optional internamente permite
 que a classe LateConstant lide elegantemente com a situação em que o
 valor da constante ainda não foi atribuído.
*/


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
