#include "CarPartFactory.h"


void main()
{
    SteelCarPartFactory steel_factory;
    WoodenCarPartFactory wooden_factory;
    UnknownCarPartFactory unknown_factory;

    auto frame = steel_factory.Create<Frame>();
    auto i = frame->get_info();

    auto part = wooden_factory.Create<Wheel>();
    auto j = part->get_info();

    auto upart = unknown_factory.Create<Frame>();
    auto k = upart->get_info();
}