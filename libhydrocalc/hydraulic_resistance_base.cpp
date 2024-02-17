#include <libhydrocalc/hydraulic_resistance_base.h>
#include <libhydrocalc/exceptions.h>
#include <iostream>

using namespace hydrocalc;


real hydrocalc::HydraulicResistanceBase::procInvalidValue(const std::string& msg, const Exception& exec)
{
	switch (CurrentSettings_.InvalidValueMode)
	{
	case settings::InvalidValuesBehaviorMode::QuitNaN:
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::InvalidValuesBehaviorMode::WarnNan:
		std::cerr << "%%err element: " << name_ << " " << msg << std::endl;
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::InvalidValuesBehaviorMode::Stop:
		throw(exec);
		break;
	default:
		throw(exec);
		break;
	}

	return real();
}

real hydrocalc::HydraulicResistanceBase::procUnphysicalValue(const real val, const real true_val, const std::string& msg, const Exception& exec)
{
	switch (CurrentSettings_.UnphysicalMode)
	{
	case settings::UnphysicalValueBehaviorMode::QuietTrue:
		return true_val;
		break;
	case settings::UnphysicalValueBehaviorMode::WarnTrue:
		std::cerr << "%%err " + msg << std::endl;
		return true_val;
		break;
	case settings::UnphysicalValueBehaviorMode::Stop:
		throw(exec);
		break;
	case settings::UnphysicalValueBehaviorMode::QuitCalc:
		return val;
		break;
	case settings::UnphysicalValueBehaviorMode::WarnCalc:
		std::cerr << "%%err " + msg << std::endl;
		return val;
		break;
	default:
		throw(exec);
		break;
	}

	return real();
}

real hydrocalc::HydraulicResistanceBase::procNonExixtantFunc(const std::string& FuncName, const Exception& exec)
{
	switch (CurrentSettings_.NonExistentFunc)
	{
	case settings::NonExistentFuncBehaviorMode::QuietNaN:
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::NonExistentFuncBehaviorMode::WarnNaN:
		std::cerr << "%%err Element " << name_ << ": Function """ << FuncName << """ does not exist" << std::endl;
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::NonExistentFuncBehaviorMode::Stop:
		throw(exec);
		break;
	default:
		throw(exec);
		break;
	}

	return real();
}

real hydrocalc::HydraulicResistanceBase::checkReversedFlow(const std::string& msg, const Exception& exec)
{
	if (Re_ < 0.0)
	{
		switch (CurrentSettings_.ReversedFlowMode)
		{
		case settings::ReversedFlowBehaviorMode::Quiet:
			break;
		case settings::ReversedFlowBehaviorMode::Warn:
			std::cerr << "%%err Reversed flow detected in element: " << name_ << ": " << msg << std::endl;
			break;
		case settings::ReversedFlowBehaviorMode::QuietNaN:
			return std::numeric_limits<real>::quiet_NaN();
			break;
		case settings::ReversedFlowBehaviorMode::WarnNaN:
			std::cerr << "%%err Reversed flow detected in element: " << name_ << ": " << msg << std::endl;
			return std::numeric_limits<real>::quiet_NaN();
			break;
		case settings::ReversedFlowBehaviorMode::Stop:
			throw(exec);
			break;
		default:
			throw(exec);
			break;
		}
	}
	else
	{
		return real();
	}

	return real();
}

real hydrocalc::HydraulicResistanceBase::procOutOfRange(const std::string& msg, const Exception& exec, const real nearest)
{
	switch (CurrentSettings_.OutOfRangeMode)
	{
	case settings::OutOfRangeRangeBehaviorMode::NoCheck:
		break;
	case settings::OutOfRangeRangeBehaviorMode::Warn:
		std::cerr << "%%err Value out of range in element: " << name_ << ": " << msg << std::endl;
		break;
	case settings::OutOfRangeRangeBehaviorMode::QuietNaN:
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::OutOfRangeRangeBehaviorMode::WarnNaN:
		std::cerr << "%%err Value out of range in element: " << name_ << ": " << msg << std::endl;
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::OutOfRangeRangeBehaviorMode::NearestValidWithNoWarn:
		return nearest;
		break;
	case settings::OutOfRangeRangeBehaviorMode::NearestValidWithWarn:
		std::cerr << "%%err Value out of range in element: " << name_ << " and was set to nearest valid (" << nearest << "): " << msg << std::endl;
		return nearest;
		break;
	case settings::OutOfRangeRangeBehaviorMode::Stop:
		throw(exec);
		break;
	default:
		throw(exec);
		break;
	}

	return real();
}

void HydraulicResistanceBase::setName(const std::string& name)
{
	name_ = name;
}

void HydraulicResistanceBase::setRe(const real Re)
{
	Re_ = Re;
}

void HydraulicResistanceBase::setRou(const real rou)
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

Type HydraulicResistanceBase::getType()
{
	return type_;
}

real HydraulicResistanceBase::getHydraulicDiameter()
{
	return D0_;
}

real HydraulicResistanceBase::getRe()
{
	return Re_;
}

real HydraulicResistanceBase::getRou()
{
	return rou_;
}

void HydraulicResistanceBase::getName(std::string& name)
{
	name = name_;
}

size_t HydraulicResistanceBase::getId()
{
	return id_;
}

real HydraulicResistanceBase::getFrictionPartCoeff()
{
	return CSIlf_;
}

real HydraulicResistanceBase::getGeometryPartCoeff()
{
	return CSIlr_;
}

real HydraulicResistanceBase::getRelFrictionCoeff()
{
	return lf_;
}

real HydraulicResistanceBase::getLocalResistanceCoeff()
{
	return CSI_;
}

real HydraulicResistanceBase::getCrossSectionArea()
{
	return A_;
}

void HydraulicResistanceBase::getDiagram(std::string& diagram)
{
	diagram = diagram_;
}

HydraulicResistance* HydraulicResistanceBase::getElement(HydraulicResistance* Element)
{
	real err = procNonExixtantFunc("getElement", ExceptionCompositeFunction("Try to call composite only function ""getElement"" for element: " + name_));

	return nullptr;
}

void HydraulicResistanceBase::addToComposite(const std::vector<HydraulicResistance*>& elementsToComposite)
{
	real err = procNonExixtantFunc("addToComposite", ExceptionCompositeFunction("Try to call composite only function ""addToComposite"" for element: " + name_));

	return void();
}

void HydraulicResistanceBase::deleteFromComposite(const std::vector<HydraulicResistance*>& elementsToDelete)
{
	real err = procNonExixtantFunc("deleteFromComposite", ExceptionCompositeFunction("Try to call composite only function ""deleteFromComposite"" for element: " + name_));

	return void();
}
