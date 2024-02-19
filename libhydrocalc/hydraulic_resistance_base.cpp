#include <libhydrocalc/hydraulic_resistance_base.h>
#include <libhydrocalc/exceptions.h>
#include <iostream>
#include <limits>
#include <cmath>

using namespace hydrocalc;


real hydrocalc::HydraulicResistanceBase::procInvalidValue(const std::string& msg, const Exception& exec)
{
	switch (CurrentSettings_.InvalidValueMode)
	{
	case settings::InvalidValuesBehaviorMode::QuitNaN:
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::InvalidValuesBehaviorMode::WarnNan:
		std::cerr << "%%err " << type_ << " element: " << name_ << " " << msg << std::endl;
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
		std::cerr << "%%warn " + msg << std::endl;
		return true_val;
		break;
	case settings::UnphysicalValueBehaviorMode::Stop:
		throw(exec);
		break;
	case settings::UnphysicalValueBehaviorMode::QuitCalc:
		return val;
		break;
	case settings::UnphysicalValueBehaviorMode::WarnCalc:
		std::cerr << "%%warn " + msg << std::endl;
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
		std::cerr << "%%err " << type_ << " element " << name_ << ": Function """ << FuncName << """ does not exist" << std::endl;
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
			std::cerr << "%%warn Reversed flow detected in " << type_ << " element " << name_ << ": " << msg << std::endl;
			break;
		case settings::ReversedFlowBehaviorMode::QuietNaN:
			return std::numeric_limits<real>::quiet_NaN();
			break;
		case settings::ReversedFlowBehaviorMode::WarnNaN:
			std::cerr << "%%err Reversed flow detected in " << type_ << " element " << name_ << ": " << msg << std::endl;
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

real hydrocalc::HydraulicResistanceBase::procGeometryOutOfRange(const std::string& msg, const Exception& exec, const real nearest)
{
	switch (CurrentSettings_.GeometryOutOfRangeMode)
	{
	case settings::GeometryOutOfRangeBehaviorMode::NoCheck:
		break;
	case settings::GeometryOutOfRangeBehaviorMode::Warn:
		std::cerr << "%%warn Geometry value out of range in " << type_ << " element " << name_ << ": " << msg << std::endl;
		break;
	case settings::GeometryOutOfRangeBehaviorMode::QuietNaN:
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::GeometryOutOfRangeBehaviorMode::WarnNaN:
		std::cerr << "%%err Geometry value out of range in " << type_ << " element " << name_ << ": " << msg << std::endl;
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::GeometryOutOfRangeBehaviorMode::NearestValidWithNoWarn:
		return nearest;
		break;
	case settings::GeometryOutOfRangeBehaviorMode::NearestValidWithWarn:
		std::cerr << "%%warn Geometry value out of range in " << type_ << " element " << name_ << " and was set to nearest valid (" << nearest << "): " << msg << std::endl;
		return nearest;
		break;
	case settings::GeometryOutOfRangeBehaviorMode::Stop:
		throw(exec);
		break;
	default:
		throw(exec);
		break;
	}

	return real();
}

real hydrocalc::HydraulicResistanceBase::procFlowOutOfRange(const std::string& msg, const Exception& exec, const real nearest)
{
	switch (CurrentSettings_.FlowOutOfRangeMode)
	{
	case settings::FlowOutOfRangeBehaviorMode::NoCheck:
		break;
	case settings::FlowOutOfRangeBehaviorMode::Warn:
		std::cerr << "%%err Flow value out of range in " << type_ << " element " << name_ << ": " << msg << std::endl;
		break;
	case settings::FlowOutOfRangeBehaviorMode::QuietNaN:
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::FlowOutOfRangeBehaviorMode::WarnNaN:
		std::cerr << "%%err Flow value out of range in " << type_ << " element " << name_ << ": " << msg << std::endl;
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::FlowOutOfRangeBehaviorMode::NearestValidWithNoWarn:
		return nearest;
		break;
	case settings::FlowOutOfRangeBehaviorMode::NearestValidWithWarn:
		std::cerr << "%%err Flow value out of range in " << type_ << " element " << name_ << " and was set to nearest valid (" << nearest << "): " << msg << std::endl;
		return nearest;
		break;
	case settings::FlowOutOfRangeBehaviorMode::Stop:
		throw(exec);
		break;
	default:
		throw(exec);
		break;
	}

	return real();
}

void hydrocalc::HydraulicResistanceBase::setExternalElementName(const std::string& name)
{
	name_external_ = name;

	name_ = "[" + name_external_ + "]{" + name_base_ + "}";
}

void HydraulicResistanceBase::setRe(const real Re)
{
	Re_ = Re;
}

void HydraulicResistanceBase::setRou(const real rou)
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
}

std::string HydraulicResistanceBase::getType()
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

void hydrocalc::HydraulicResistanceBase::setName(const std::string& name)
{
	name_base_ = name;

	name_ = "[" + name_external_ + "]{" + name_base_ + "}";
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

HydraulicResistanceBase& hydrocalc::HydraulicResistanceBase::operator=(const HydraulicResistanceBase& HR)
{
	if (this != &HR)
	{
		diagram_ = HR.diagram_;
		CurrentSettings_ = HR.CurrentSettings_;
		name_ = "[]{" + HR.name_base_ + "}";
		name_base_ = HR.name_base_;
		Re_ = HR.Re_;
		D0_ = HR.D0_;
		A_ = HR.A_;
		rou_ = HR.rou_;
		relRou_ = HR.relRou_;
		L_ = HR.L_;
		type_ = HR.type_;
		lf_ = HR.lf_;
		CSIlf_ = HR.CSIlf_;
		CSIlr_ = HR.CSIlr_;
		CSI_ = HR.CSI_;
	}
	return *this;
}

real hydrocalc::HydraulicResistanceBase::getLength()
{
	return L_;
}

void hydrocalc::HydraulicResistanceBase::setLength(const real L)
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
}
