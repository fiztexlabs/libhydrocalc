#include <gtest/gtest.h>
#include <libhydrocalc/cylindrical_confuser_curve.h>
#include <libhydrocalc/cylindrical_diffuser_curve.h>
#include <libmath/boolean.h>

namespace hr = hydrocalc;

TEST(CurveConfuser, Create)
{
    EXPECT_NO_THROW(
        hr::CylindricalConfuserCurve confuser(
            1.e6,
            {
                2.e-5,
                3.e-3,
                0.,
                20.e-3,
                3.e-3,
                6.e-3
            }, "confuser");

        confuser.evaluate();

    );
}

TEST(CurveConfuser, ReverseFlow)
{
    hr::CylindricalConfuserCurve confuser(
        1.e6,
        {
            2.e-5,
            3.e-3,
            0.,
            20.e-3,
            23.e-3,
            6.e-3
        }, "confuser");

    confuser.setRe(-1.e6);

    confuser.evaluate();

    hr::CylindricalDiffuserCurve diffuser(
        1.e6,
        {
            2.e-5,
            3.e-3,
            20.e-3,
            0.,
            23.e-3,
            6.e-3
        }, "diffuser");

    diffuser.evaluate();

    EXPECT_EQ(
        math::isEqual(
            confuser.getLocalResistanceCoeff(),
            diffuser.getLocalResistanceCoeff()
        ),
        true
    );

}