#include <iostream>
#include <libhydrocalc/cylindrical_friction.h>
#include <libhydrocalc/cylindrical_bend.h>
#include <libhydrocalc/cylindrical_confuser_straight.h>


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


    hr::CylindricalConfuserStraight confuser(
        1.e6,
        {
            2.e-5,
            50.e-3,
            0.,
            250.e-3,
            84.85e-3,
            8.
        },
        "confuser"
    );

    confuser.setGeometry(
        {
            2.e-5,
            50.e-3,
            0.,
            250.e-3,
            84.85e-3,
            8.
        }
    );

    confuser.evaluate();

    return 0;
}