#include <iostream>
#include <libhydrocalc/cylindrical_friction.h>
#include <libhydrocalc/cylindrical_bend.h>


namespace hr = hydrocalc;

int main()
{
    hr::CylindricalFriction tube(1.e6, { 2.e-5, 50.e-3, 1.0 }, "tube");

    tube.evaluate();

    std::cout << tube.getLocalResistanceCoeff() << std::endl;


    hr::CylindricalBend bend(
        1.e6,
        {
            2.e-5,
            50.e-3,
            0.,
            90.,
            0.
        },
        "bend"
    );

    bend.evaluate();

    std::cout << bend.getLocalResistanceCoeff() << std::endl;

    return 0;
}