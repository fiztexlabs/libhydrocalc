import hydrocalc as hr

tube = hr.createHydraulicResistance(
    "CylindricalFriction",
    10e6,
    [
        2.e-5,
        50.e-3,
        1.
    ],
    "tube",
    1.
)

tube.evaluate()

print(tube.getLocalResistanceCoeff())