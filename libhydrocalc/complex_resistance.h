#pragma once
#include <libhydrocalc/hydraulic_resistance_base.h>
#include <string>
#include <vector>

namespace hydrocalc
{
	/**
	* @brief Base class for composite resistances, which include friction, or
	* others resistance objects
	* @author Ilya Konovalov
	* @date Released 18.02.2024
	*/
	class ComplexResistance :
		public HydraulicResistanceBase
	{
	protected:
		/// @brief Vector of hydraulic resistance components
		std::vector<HydraulicResistance*> internal_resistances_;

		/// @see HydraulicResistance::setExternalElementName()
		virtual void setExternalElementName(const std::string& name) override;

	public:
		/// @brief Default constructor
		ComplexResistance() :
			HydraulicResistanceBase()
		{};

		/// @brief Constructor with parameters
		ComplexResistance(
			const std::string& name,
			const real Re,
			const real D0,
			const real rou,
			const real A,
			const real L,
			const real vis,
			const std::string& type) :
			HydraulicResistanceBase(
				name,
				Re,
				D0,
				rou,
				A,
				L,
				vis,
				type)
		{};

		virtual ~ComplexResistance() {};

		/// @see HydraulicResistance::setName()
		virtual void setName(const std::string& name) override;

		/// @see HydraulicResistance::setRe()
		virtual void setRe(const real Re) override;

		/// @see HydraulicResistance::setRou()
		virtual void setRou(const real rou) override;

		/// @see HydraulicResistance::setLength()
		virtual void setLength(const real L) override;

		/// @see HydraulicResistance::setViscosity()
		virtual void setViscosity(const real vis) override;

	};
}