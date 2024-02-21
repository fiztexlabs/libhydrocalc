#include <iostream>
#include <libhydrocalc/cylindrical_friction.h>
#include <libhydrocalc/cylindrical_bend.h>
#include <libhydrocalc/cylindrical_confuser_straight.h>
#include <libhydrocalc/composite.h>
#include <libhydrocalc/hydrocalc.h>
#include <memory>
#include <exception>


namespace hr = hydrocalc;

int main()
{
    /*hr::CylindricalFriction tube(1.e6, { 2.e-5, 35.e-3, 1.0 }, "tube");

    tube.evaluate();

    std::cout << tube.getLocalResistanceCoeff() << std::endl;


    hr::CylindricalBend bend(
        1.e6,
        {
            2.e-5,
            20.e-3,
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

    std::cout << confuser.getLocalResistanceCoeff() << std::endl;

    hr::Composite composite(
        3.e6,
        {
            50.e-3,
            1.0
        },
        {
            &tube,
            &bend,
            &confuser
        },
        "composite"
    );

    composite.evaluate();*/


    try
    {
        std::unique_ptr<hydrocalc::HydraulicResistance> tube1(hydrocalc::createHydraulicResistance(
            "CylindricalFriction",
            1.e6,
            { 2.e-5, 35.e-3 }
        ));

        tube1->evaluate();

        std::cout << tube1->getLocalResistanceCoeff() << std::endl;
    }
    catch (const std::exception& exec)
    //catch (const hydrocalc::Exception& exec)
    {
        std::cout << "fail "<< std::endl;
    }

    return 0;
}