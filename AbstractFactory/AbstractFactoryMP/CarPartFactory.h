#pragma once

#include <string>
#include <sstream>
#include "AbstractFactoryTemplate.h"

//
// CarPart (virtual base)
//
class CarPart
{
public:
    virtual const char* get_info() = 0;
};

//
// Wheel (CarPart-derived)
//
class Wheel : public CarPart
{
    std::string _info;
public:
    Wheel(const std::string& type = "unknown")
    {
        std::stringstream ss;
        ss << "CarPart: " << type << " wheel";
        _info = ss.str();
    }

    const char* get_info() override
    {
        return _info.c_str();
    }
};

//
// Frame (CarPart-derived)
//
class Frame : public CarPart
{
    std::string _info;
public:
    Frame(const std::string& type = "unknown")
    {
        std::stringstream ss;
        ss << "CarPart: " << type << " frame";
        _info = ss.str();
    }

    const char* get_info() override
    {
        return _info.c_str();
    }
};

typedef AbstractFactory<std::tuple<Wheel, Frame>> AbstractCarPartFactory;


template <class T, class Base>
class SteelFactroyUnit : public Base
{
public:
    virtual T* DoCreate(Type2Type<T>) override
    {
        return new T("steel");
    }
};

template <class T, class Base>
class WoodenFactroyUnit : public Base
{
public:
    virtual T* DoCreate(Type2Type<T>) override
    {
        return new T("wooden");
    }
};


typedef ConcreteFactory<AbstractCarPartFactory, std::tuple<Wheel, Frame>>                       UnknownCarPartFactory;

typedef ConcreteFactory<AbstractCarPartFactory, std::tuple<Wheel, Frame>, SteelFactroyUnit>     SteelCarPartFactory;
typedef ConcreteFactory<AbstractCarPartFactory, std::tuple<Wheel, Frame>, WoodenFactroyUnit>    WoodenCarPartFactory;

