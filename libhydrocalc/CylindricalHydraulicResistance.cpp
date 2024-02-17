#include <pch.h>
#include <HydraulicResistances/CylindricalHydraulicResistance.h>

void CylindricalHydraulicResistance::setName(const std::string& name)
{
	name_ = name;
}

void CylindricalHydraulicResistance::setAutocalc(const bool flag)
{
	autocalc = flag;
}

void CylindricalHydraulicResistance::setHandleWarnings(const bool flag)
{
	flagHandleWarnings = flag;
}

void CylindricalHydraulicResistance::setRe(const HSReal Re)
{
	if (Re_ != Re)
	{
		Re_ = Re;
		changed = 1;
		calculated = 0;
		if (autocalc)
		{
			calculateElement();
		}
	}
}

void CylindricalHydraulicResistance::setRou(const HSReal rou)
{
	if (rou < 0.0)
	{
		std::cerr << "%err invalid value of rou to set, roughness rou must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (rou_ != rou)
	{
		rou_ = rou;
		changed = 1;
		calculated = 0;
		if (autocalc)
		{
			calculateElement();
		}
	}
}

unsigned int CylindricalHydraulicResistance::getType()
{
	return type_;
}

HSReal CylindricalHydraulicResistance::getHydraulicDiameter()
{
	return D0_;
}

HSReal CylindricalHydraulicResistance::getRe()
{
	return Re_;
}

HSReal CylindricalHydraulicResistance::getRou()
{
	return rou_;
}

void CylindricalHydraulicResistance::getName(std::string& name)
{
	name = name_;
}

unsigned int CylindricalHydraulicResistance::getId()
{
	return id_;
}

HSReal CylindricalHydraulicResistance::getFrictionPartCoeff()
{
	return CSIlf_;
}

HSReal CylindricalHydraulicResistance::getGeometryPartCoeff()
{
	return CSIlr_;
}

HSReal CylindricalHydraulicResistance::getRelFrictionCoeff()
{
	return lf_;
}

HSReal CylindricalHydraulicResistance::getLocalResistanceCoeff()
{
	return CSI_;
}

HSReal CylindricalHydraulicResistance::getCrossSectionArea()
{
	return A_;
}

void CylindricalHydraulicResistance::getDiagram(std::string& diagram)
{
	diagram = diagram_;
}

HSReal CylindricalHydraulicResistance::getError()
{
	std::cerr << "%err function getError does not exists yet in the element " << id_ << " (" << name_ << ")\n";
	exit(3);
	return 0.0;
}

void CylindricalHydraulicResistance::deleteElement()
{
	delete this;
}

IBaseHydraulicResistance* CylindricalHydraulicResistance::getElement(IBaseHydraulicResistance* Element)
{
	std::cerr << "%err method ""getElement"", called from element " << id_ << " (" << name_ 
		<< ") valid only for HydraulicComposite elements\n";
	exit(3);

	return nullptr;
}

void CylindricalHydraulicResistance::addToComposite(const std::vector<IBaseHydraulicResistance*>& elementsToComposite)
{
	std::cerr << "%err method ""addToComposite"", called from element " << id_ << " (" << name_
		<< ") valid only for HydraulicComposite elements\n";
	exit(3);
	return void();
}

void CylindricalHydraulicResistance::deleteFromComposite(const std::vector<IBaseHydraulicResistance*>& elementsToDelete)
{
	std::cerr << "%err method ""deleteFromComposite"", called from element " << id_ << " (" << name_
		<< ") valid only for HydraulicComposite elements\n";
	exit(3);
	return void();
}
