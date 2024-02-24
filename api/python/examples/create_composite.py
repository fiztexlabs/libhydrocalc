import hydrocalc as hr

tube1 = hr.createHydraulicResistance(
    "CylindricalFriction",
    10e6,
    [
        2.e-5,
        50.e-3,
        1.
    ],
    "tube1",
    1.
)

tube2 = hr.createHydraulicResistance(
    "CylindricalFriction",
    10e6,
    [
        2.e-5,
        50.e-3,
        1.
    ],
    "tube2",
    1.
)

composite = hr.createComposite(
    10.e6,
    [
        50.e-3,
        1
    ],
    [
        tube1,
        tube2
    ],
    "composite",
    1.,
    1
)

composite.evaluate()

print(composite.getLocalResistanceCoeff())