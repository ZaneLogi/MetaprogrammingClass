#pragma once

#include <tuple>

//
// the purpose of Type2Type is for the compiler to recognize the function overloading
template <typename T>
struct Type2Type
{
    typedef T type;   // just for the creation of a new type, it's meaningless.
};


//
// template of the unit of the abstract factory
//

template <class T>
class AbstractFactoryUnit
{
public:
    virtual T* DoCreate(Type2Type<T>) = 0;
};


//
// template of class GenScatterHierachy
//

// template prototype
template <
    typename product_tuple_list,
    template <class> class abstract_factory_unit
> class GenScatterHierachy;

// template specialization 1
template <typename Head, typename ...Tail, template <typename> class abstract_factory_unit>
class GenScatterHierachy<std::tuple<Head, Tail...>, abstract_factory_unit> :
    public abstract_factory_unit<Head>,
    public GenScatterHierachy<std::tuple<Tail...>, abstract_factory_unit>
{};

// template specialization 2
template <typename T, template <typename> class abstract_factory_unit>
class GenScatterHierachy<std::tuple<T>, abstract_factory_unit> : public abstract_factory_unit<T>
{};


//
// template of class AbstractFactory
//

template <
    class product_tuple_list,
    template <class> class abstract_factory_unit = AbstractFactoryUnit
>
class AbstractFactory
    : public GenScatterHierachy<product_tuple_list, abstract_factory_unit>
{
public:
    template <class T>
    T* Create()
    {
        return (*(abstract_factory_unit<T>*)(this)).DoCreate(Type2Type<T>());
    }
};














template <class T, class Base>
class ConcreteFactroyUnit : public Base
{
public:
    virtual T* DoCreate(Type2Type<T>) override
    {
        return new T;
    }
};


// template prototype
template <
    typename product_tuple_list,
    template <class, class> class concrete_factory_unit,
    typename abstract_factory
> class GenLinearHierachy;

// template specialization 1
template <typename Head, typename ...Tail, template <class, class> class concrete_factory_unit, typename abstract_factory>
class GenLinearHierachy<std::tuple<Head, Tail...>, concrete_factory_unit, abstract_factory>
    : public concrete_factory_unit<Head, GenLinearHierachy<std::tuple<Tail...>, concrete_factory_unit, abstract_factory>>
{
};

// template specialization 2
template <template <class, class> class concrete_factory_unit, typename abstract_factory>
class GenLinearHierachy<std::tuple<>, concrete_factory_unit, abstract_factory> : public abstract_factory
{};


//
// template of class ConcreteFactory
//

template <
    class abstract_factory,
    class product_tuple_list,
    template <class, class> class concrete_factory_unit = ConcreteFactroyUnit
>
class ConcreteFactory
    : public GenLinearHierachy<product_tuple_list, concrete_factory_unit, abstract_factory>
{

};
