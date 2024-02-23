#include <libhydrocalc/complex_resistance.h>
#include <cmath>

using namespace hydrocalc;

void hydrocalc::ComplexResistance::setExternalElementName(const std::string& name)
{
	HydraulicResistanceBase::setExternalElementName(name);

	for (auto& hr : internal_resistances_)
	{
		hr->setExternalElementName(name_);
	}
}

void hydrocalc::ComplexResistance::setName(const std::string& name)
{
	name_base_ = name;

	name_ = "[" + name_external_ + "]{" + name_base_ + "}";

	for (auto& hr : internal_resistances_)
	{
		hr->setExternalElementName(name);
	}
}

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
			rou_ = procInvalidValue("Try to set rou < 0.0", ExceptionInvalidRou(type_+ " element: " + name_ + " Try to set rou < 0.0"));
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
			err = procInvalidValue("setLength L < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set L < 0.0"));

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

void hydrocalc::ComplexResistance::setViscosity(const real vis)
{
	if (CurrentSettings_.checkInputs)
	{
		if (vis <= 0.0)
		{
			vis_ = procInvalidValue("Try to set vis (kinematic viscosity) <= 0.0", ExceptionInvalidRou(type_ + " element: " + name_ + " Try to set vis (kinematic viscosity) <= 0.0"));
		}
		else
		{
			vis_ = vis;
		}
	}
	else
	{
		vis_ = vis;
	}

	for (auto& hr : internal_resistances_)
	{
		hr->setViscosity(vis);
	}
}
