#pragma once
#include <libhydrocalc/hydraulic_resistance.h>
#include <libhydrocalc/settings.h>
#include <string>
#include <vector>

namespace hydrocalc
{
    HydraulicResistance *createHydraulicResistance(
        const std::string &type,
        const real Re,
        const std::vector<real> &G,
        const std::string &name = "",
        const real vis = 1.0);

    HydraulicResistance* createHydraulicResistance(const std::string& type);
}