#include <pch.h>
#include <HydraulicResistances/HydraulicComposite.h>

void HydraulicComposite::errorHandling()
{
	if (flagHandleWarnings)
	{
		if (Re_ < 0.0)
		{
			std::cerr << "%inf reversed flow in the element " << id_ << " (" << name_ << ")\n";
		}

		HSReal ReCheck = (compositeElements_[0]->getRe()) * (D0_ / (compositeElements_[0]->getHydraulicDiameter()));

		for (size_t i = 1; i < compositeElements_.size(); i++)
		{
			if (ReCheck != compositeElements_[i]->getRe() * ((compositeElements_[i]->getHydraulicDiameter()) / D0_))
			{
				std::cerr << "%warn elements have different volumetric flows in the composite element " << id_ << " (" << name_ << ")\n";
			}
		}
	}
}

void HydraulicComposite::errorHandling(const HSReal Re, const std::vector<HSReal>& G)
{
	if (flagHandleWarnings)
	{
		if (G.size() > 1)
		{
			std::cerr << "%warn size of vector of geometry characteristics more than 1 in the composite element " << id_ << " (" << name_ << ")\n";
		}
	}
	if (G.size() < 1)
	{
		std::cerr << "%err size of input vector of geometry characteristics less than 1 in the composite element " << id_ << " (" << name_ << ")\n";
		exit(1);
	}
	if (G[0] <= 0.0)
	{
		std::cerr << "%err invalid value of G, hydraulic diameter D0 (G[1]) must be > 0.0 in the composite element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
}

bool HydraulicComposite::isInComposite(IBaseHydraulicResistance* Element)
{
	return (std::find(compositeElements_.begin(), compositeElements_.end(), Element) != compositeElements_.end());
}

IBaseHydraulicResistance* HydraulicComposite::copy() const
{
	std::vector<IBaseHydraulicResistance*> clones;
	for (auto i = compositeElements_.begin(); i != compositeElements_.end(); ++i)
	{
		clones.push_back((*i)->copy());
	}
	return new HydraulicComposite(name_, { D0_ }, clones);
}

IBaseHydraulicResistance* HydraulicComposite::getElement(IBaseHydraulicResistance* Element)
{
	if (!isInComposite(Element))
	{
		std::string elName;
		Element->getName(elName);
		std::cerr << "%err Element " << elName << " does not belong to composite element " << id_ << " (" << name_ << ")\n";
		exit(5);
	}
	return nullptr;
}

void HydraulicComposite::addToComposite(const std::vector<IBaseHydraulicResistance*>& elementsToComposite)
{
	for (size_t i = 0; i < elementsToComposite.size(); i++)
	{
		compositeElements_.push_back(elementsToComposite[i]);
	}

	if (autocalc)
	{
		calculateElement();
	}
}

void HydraulicComposite::deleteFromComposite(const std::vector<IBaseHydraulicResistance*>& elementsToDelete)
{
	for (size_t i = 0; i < elementsToDelete.size(); i++)
	{
		compositeElements_.erase(std::find(compositeElements_.begin(), compositeElements_.end(), elementsToDelete[i]));
	}

	if (autocalc)
	{
		calculateElement();
	}
}

void HydraulicComposite::calculateElement()
{
	errorHandling();

	for (size_t i = 0; i < compositeElements_.size(); i++)
	{
		compositeElements_[i]->calculateElement();
	}

	CSI_ = 0.0;
	CSIlf_ = 0.0;
	CSIlr_ = 0.0;
	rou_ = 0.0;
	lf_ = 0.0;
	std::string currDiagramName;

	for (size_t i = 0; i < compositeElements_.size(); i++)
	{
		// calculate CSI as summ of CSI of elements, reduced to D0
		CSI_ += (compositeElements_[i]->getLocalResistanceCoeff()) *
			(pow(compositeElements_[i]->getHydraulicDiameter(), 4.0) / pow(D0_, 4.0));
		CSIlf_ += (compositeElements_[i]->getFrictionPartCoeff()) *
			(pow(compositeElements_[i]->getHydraulicDiameter(), 4.0) / pow(D0_, 4.0));
		CSIlr_ += (compositeElements_[i]->getGeometryPartCoeff()) *
			(pow(compositeElements_[i]->getHydraulicDiameter(), 4.0) / pow(D0_, 4.0));

		// calculate average rou
		rou_ += compositeElements_[i]->getRou();

		// calculate average lf
		lf_ += (compositeElements_[i]->getRelFrictionCoeff()) *
			(pow(compositeElements_[i]->getHydraulicDiameter(), 3.0) / pow(D0_, 3.0));

		// fill diagram numbers
		compositeElements_[i]->getDiagram(currDiagramName);
		if (i == 0)
		{
			diagram_ = currDiagramName;
		}
		else
		{
			diagram_ += " " + currDiagramName;
		}
	}

	// calculate rou of composite as average rou for all elements in composite
	rou_ = rou_ / compositeElements_.size();

	// calculate lf of composite as average lf for all elements in composite
	lf_ = lf_ / compositeElements_.size();

	relRou_ = rou_ / D0_;

	changed = 0;
	calculated = 1;

}

void HydraulicComposite::setGeometry(const std::vector<HSReal>& G)
{
	errorHandling(Re_, G);

	if (G[0] != D0_)
	{
		D0_ = G[0];

		changed = 1;
		calculated = 0;
		if (autocalc)
		{
			CSI_ = 0.0;
			CSIlf_ = 0.0;
			CSIlr_ = 0.0;
			for (size_t i = 0; i < compositeElements_.size(); i++)
			{
				CSI_ += (compositeElements_[i]->getLocalResistanceCoeff()) *
					(pow(compositeElements_[i]->getHydraulicDiameter(), 4.0) / pow(D0_, 4.0));
				CSIlf_ += (compositeElements_[i]->getFrictionPartCoeff()) *
					(pow(compositeElements_[i]->getHydraulicDiameter(), 4.0) / pow(D0_, 4.0));
				CSIlr_ += (compositeElements_[i]->getGeometryPartCoeff()) *
					(pow(compositeElements_[i]->getHydraulicDiameter(), 4.0) / pow(D0_, 4.0));
			}
			changed = 0;
			calculated = 1;
		}
	}
}

void HydraulicComposite::setRe(const HSReal Re)
{
	Re_ = Re;

	for (size_t i = 0; i < compositeElements_.size(); i++)
	{
		compositeElements_[i]->setRe(Re_ * ((compositeElements_[i]->getHydraulicDiameter()) / D0_));
	}

	changed = 1;
	calculated = 0;

	if (autocalc)
	{
		calculateElement();
	}
}

void HydraulicComposite::setRou(const HSReal rou)
{
	if (flagHandleWarnings)
	{
		std::cerr << "%inf roughness for all elements in composite " << id_ << " (" << name_ << ") was set to " << rou_ << "\n";
	}
	if (rou < 0.0)
	{
		std::cerr << "%err invalid value of rou to set, roughness rou must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	rou_ = rou;

	for (size_t i = 0; i < compositeElements_.size(); i++)
	{
		compositeElements_[i]->setRou(rou_);
	}
}

void HydraulicComposite::getGeometry(std::vector<HSReal>& G)
{
	G =
	{
		rou_,
		D0_
	};
}

void HydraulicComposite::setAutocalc(const bool flag)
{
	for (size_t i = 0; i < compositeElements_.size(); i++)
	{
		compositeElements_[i]->setAutocalc(flag);
	}
}

void HydraulicComposite::setHandleWarnings(const bool flag)
{
	for (size_t i = 0; i < compositeElements_.size(); i++)
	{
		compositeElements_[i]->setHandleWarnings(flag);
	}
}

HSReal HydraulicComposite::getFrictionPartCoeff()
{
	calculateElement();
	return CSIlf_;
}

HSReal HydraulicComposite::getGeometryPartCoeff()
{
	calculateElement();
	return CSIlr_;
}

HSReal HydraulicComposite::getRelFrictionCoeff()
{
	calculateElement();
	return lf_;
}

HSReal HydraulicComposite::getLocalResistanceCoeff()
{
	calculateElement();
	return CSI_;
}

HSReal HydraulicComposite::getLength()
{
	if (L_ > 0.0)
	{
		return L_;
	}
	else
	{
		return 1.e-6;
	}
}

void HydraulicComposite::setLength(const HSReal L)
{
	HSReal dL = L / compositeElements_.size();

	for (size_t i = 0; i < compositeElements_.size(); i++)
	{
		compositeElements_[i]->setLength(dL);
	}

	changed = 1;
	calculated = 0;
	if (autocalc)
	{
		calculateElement();
	}
}
