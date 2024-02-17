#include <iostream>
#include <libhydrocalc/cylindrical_friction.h>


namespace hr = hydrocalc;

int main()
{
    hr::CylindricalFriction tube(1.e6, { 2.e-5, 50.e-3, 1.0 }, "tube");

    tube.evaluate();

    std::cout << tube.getLocalResistanceCoeff() << std::endl;

    return 0;
}