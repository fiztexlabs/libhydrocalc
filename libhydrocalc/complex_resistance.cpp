#include <libhydrocalc/complex_resistance.h>
#include <cmath>

using namespace hydrocalc;

void hydrocalc::ComplexResistance::setRe(const real Re)
{
	Re_ = Re;

	for (auto& hr : internal_resistances_)
	{
		hr->setRe(Re);
	}
}

void hydrocalc::ComplexResistance::setRou(const real rou)
{
	if (CurrentSettings_.checkInputs)
	{
		if (rou < 0.0)
		{
			rou_ = procInvalidValue("Try to set rou < 0.0", ExceptionInvalidRou("%%err element: " + name_ + " Try to set rou < 0.0"));
		}
		else
		{
			rou_ = rou;
		}
	}
	else
	{
		rou_ = rou;
	}

	for (auto& hr : internal_resistances_)
	{
		hr->setRou(rou_);
	}
}

void hydrocalc::ComplexResistance::setLength(const real L)
{
	real err{ 0.0 };

	if (CurrentSettings_.checkInputs)
	{
		if (L < 0.0)
		{
			err = procInvalidValue("setLength L < 0.0", ExceptionInvalidValue("Friction element " + name_ + ": try to set L < 0.0"));

			if (std::isnan(err))
			{
				L_ = err;
			}
		}
		else
		{
			L_ = L;
		}
	}
	else
	{
		L_ = L;
	}

	for (auto& hr : internal_resistances_)
	{
		hr->setLength(L);
	}
}
