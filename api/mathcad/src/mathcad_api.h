#pragma once
#include <libhydrocalc/hydraulic_resistance.h>
#include <MCADINCL.H>
#include <math.h>
#include <windows.h>
#include <SDKDDKVer.h>
#include <vector>
#include <memory>
#include <string>
#include <exception>
#include <iostream>
#include <algorithm>

namespace hydrocalc::mathcad
{
	inline std::vector<std::unique_ptr<hydrocalc::HydraulicResistance>> hr_vec;
}

const int ERR_NUM = 15;

char* HydrocalcFunctionErrors[ERR_NUM] =
{
  "Value must be real", // 1
  "Not enougth geometry parameters", // 2
  "Incorrect element type", // 3
  "Incorrect element geometry", // 4
  "Incorrect viscosity", // 5
  "Value must be boolean", // 6
  "Element id must be integer", // 7
  "Incorrect element id", // 8
  "Geometry out of range throw eveluating in the element", // 9
  "Flow out of range throw eveluating in the element", // 10
  "Reversed flow in the element", // 11
  "Not enougth memory", // 12
  "Element is not in the composite", // 13
  "", // 14
  "", // 15
};