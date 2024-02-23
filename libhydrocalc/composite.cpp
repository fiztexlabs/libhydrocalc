#include <libhydrocalc/composite.h>
#include <libmath/boolean.h>
#include <libhydrocalc/exceptions.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <limits>
#include <string>

using namespace hydrocalc;

real Composite::checkGeometry(const std::vector<real>& G)
{
	real err = 0.0;

	if (CurrentSettings_.checkInputs)
	{
		if (G.at(0) < 0.0)
		{
			err += procInvalidValue("rou (roughness) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set rou (roughness) < 0.0"));
		}
		if (G.at(1) <= 0.0)
		{
			err += procInvalidValue("D0 (hydraulic diameter) <= 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set D0 (hydraulic diameter) <= 0.0"));
		}
	}

	return err;
}

HydraulicResistance* hydrocalc::Composite::copy() const
{
	return new Composite(
		Re_,
		{
			D0_,
			L_
		},
		internal_resistances_,
		name_base_,
		vis_,
		is_unique_
	);
}

bool hydrocalc::Composite::isInComposite(HydraulicResistance* Element)
{
	return (std::find(internal_resistances_.begin(), internal_resistances_.end(), Element) != internal_resistances_.end());
}

real hydrocalc::Composite::procInconsistentReynolds(HydraulicResistance* hr) const
{
	std::string elname;
	hr->getName(elname);

	switch (CurrentSettings_.InconsistentReynoldsMode)
	{
	case settings::InconsistentReynolds::Warn:
		std::cerr << "%%warn Inconsistent reynolds number in " << type_ << " element " << name_ << ": " <<
			"main Re = " << Re_ << ", while, Re of " << hr->getType() << " element " << elname << " = " << hr->getRe() << std::endl;
		break;
	case settings::InconsistentReynolds::QuietNaN:
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::InconsistentReynolds::WarnNaN:
		std::cerr << "%%warn Inconsistent reynolds number in " << type_ << " element " << name_ << ": " <<
			"main Re = " << Re_ << ", while, Re of " << hr->getType() << " element " << elname << " = " << hr->getRe() << std::endl;
		return std::numeric_limits<real>::quiet_NaN();
		break;
	case settings::InconsistentReynolds::Stop:
		throw(ExceptionInconsistentReynolds(
			"Inconsistent reynolds number in " + type_ + " element " + name_ + ": main Re = " +
			std::to_string(Re_) + ", while, Re of " + hr->getType() + " element " + elname + " = " + std::to_string(hr->getRe())
		));
		break;
	default:
		throw(ExceptionInconsistentReynolds(
			"Inconsistent reynolds number in " + type_ + " element " + name_ + ": main Re = " +
			std::to_string(Re_) + ", while, Re of " + hr->getType() + " element " + elname + " = " + std::to_string(hr->getRe())
		));
		break;
	}

	return real();
}

void hydrocalc::Composite::evaluate()
{
	A_ = M_PI * std::pow(0.5 * D0_, 2.0);

	CSI_ = 0.0;
	CSIlr_ = 0.0;

	real reversed = checkReversedFlow("Re < 0.0", ExceptionReversedFlow("reversed flow in the " + type_ + " element " + name_));

	if (std::isnan(reversed))
	{
		lf_ = reversed;
		CSI_ = reversed;
		CSIlr_ = reversed;
		CSIlf_ = reversed;
	}
	else
	{
		if (math::isEqual<real, real>(Re_, static_cast<real>(0.0)))
		{
			CSI_ = CurrentSettings_.MAX_CSI;
			CSIlf_ = 0.0;
			CSIlr_ = CurrentSettings_.MAX_CSI;
			lf_ = 0.0;
		}
		else
		{
			auto correct_Re = elements_Re_.cbegin();

			for (auto& hr : internal_resistances_)
			{
				// check if Mass flow throw elements != const
				if (!math::isEqual(*correct_Re, hr->getRe()))
				{
					real err = procInconsistentReynolds(hr);

					if (std::isnan(err))
					{
						CSI_ = err;
						CSIlf_ = err;
						CSIlr_ = err;
						lf_ = err;

						return void();
					}
				}

				hr->evaluate();

				real csi2 = hr->getLocalResistanceCoeff();
				real d2 = hr->getHydraulicDiameter();

				CSIlr_ += csi2 * std::pow(D0_ / d2, 4.0);

				Lfull_ += hr->getLength();

				++correct_Re;
			}

			CSI_ = CSIlr_ + CSIlf_;
		}
	}
}

void hydrocalc::Composite::setGeometry(const std::vector<real>& G)
{
	real err = checkGeometry(G);

	if (std::isnan(err))
	{
		D0_ = err;
		L_ = err;
	}
	else
	{
		D0_ = G.at(0);
		L_ = G.at(1);
	}
}

void hydrocalc::Composite::getGeometry(std::vector<real>& G)
{
	G =
	{
		rou_,
		D0_,
		L_,
		A_
	};
}

void hydrocalc::Composite::setRe(const real Re)
{
	Re_ = Re;

	elements_Re_.clear();

	for (auto& hr : internal_resistances_)
	{
		real A2 = hr->getCrossSectionArea();
		real D2 = hr->getHydraulicDiameter();
		real vis2 = hr->getViscosity();

		real Re_curr = Re_ * ((A_ / A2) * (D2 / D0_) * (vis_ / vis2));
		elements_Re_.push_back(Re_curr);

		hr->setRe(Re_curr);
	}
}

void hydrocalc::Composite::push_back(HydraulicResistance* hr)
{
	if (is_unique_)
	{
		internal_resistances_.push_back(hr->copy());

		// mark hr, that its included to this composite
		dynamic_cast<HydraulicResistanceBase*>(internal_resistances_.back())->composites_.push_back(this);
	}
	else
	{
		internal_resistances_.push_back(hr);

		// mark hr, that its included to this composite
		dynamic_cast<HydraulicResistanceBase*>(hr)->composites_.push_back(this);
	}

	hr->setExternalElementName(name_base_);
}

void hydrocalc::Composite::push_back(const std::vector<HydraulicResistance*>& elements)
{
	for (auto hr : elements)
	{
		(*this).push_back(hr);
	}
}

void hydrocalc::Composite::erase(const size_t idx)
{
	if (idx >= internal_resistances_.size())
	{
		throw(ExceptionInvalidElementId(type_ + " element: try to get element by id " + std::to_string(idx) + ", which is not in the composite"));
	}
	else
	{
		if (is_unique_)
		{
			delete internal_resistances_.at(idx);
			internal_resistances_.erase(internal_resistances_.begin() + idx);
		}
		else
		{
			internal_resistances_.at(idx)->setExternalElementName("");
			internal_resistances_.erase(internal_resistances_.begin() + idx);
		}
	}
}

void hydrocalc::Composite::erase(HydraulicResistance* hr)
{
	if (isInComposite(hr))
	{
		throw(ExceptionInvalidElementId(type_ + " element: try to get element, which is not in the composite by pointer"));
	}
	else
	{
		auto el = std::find(internal_resistances_.begin(), internal_resistances_.end(), hr);

		if (is_unique_)
		{
			delete* el;
			internal_resistances_.erase(el);
		}
		else
		{
			(*el)->setExternalElementName("");
			internal_resistances_.erase(el);
		}
	}
}

void hydrocalc::Composite::erase(const std::vector<HydraulicResistance*>& elements)
{
	for (auto hr : elements)
	{
		(*this).erase(hr);
	}
}

void hydrocalc::Composite::erase(const std::vector<size_t>& elements)
{
	for (auto hr : elements)
	{
		(*this).erase(hr);
	}
}

HydraulicResistance* hydrocalc::Composite::get(const size_t idx, const bool copy)
{
	if (copy)
	{
		return internal_resistances_.at(idx)->copy();
	}
	else
	{
		return internal_resistances_.at(idx);
	}
}

void hydrocalc::Composite::get(std::vector<HydraulicResistance*>& elements, const bool copy)
{
	if (copy)
	{
		for (auto hr : internal_resistances_)
		{
			elements.push_back(hr->copy());
		}
	}
	else
	{
		elements = internal_resistances_;
	}
}

size_t hydrocalc::Composite::size()
{
	return internal_resistances_.size();
}

bool hydrocalc::Composite::isUnique()
{
	return is_unique_;
}
