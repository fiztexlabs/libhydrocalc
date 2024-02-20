#pragma once
#include <libhydrocalc/complex_resistance.h>
#include <libhydrocalc/cylindrical_friction.h>
#include <string>
#include <math.h>
#include <vector>

namespace hydrocalc
{
	/**
	* @brief 
	* @author Ilya Konovalov
	* @date Released 19.02.2024
	*/
	class Composite :
		public ComplexResistance
	{
	private:
		/// @brief Main viscosity of composite element
		real main_viscosity_{ 1.0 };

		/// @brief Vector of elements viscosities in composite
		std::vector<real> elements_viscosity_;

		/// @brief Indicate, that composite store elements pointers, or elements copies
		bool is_unique_ = 1;

	protected:
		/**
		* @brief Check cylindrical friction input values and raise exeptions or warnings
		* @param G: Input vector of geometry characteristics
		* @throw ExceptionInvalidValue
		*/
		real checkGeometry(const std::vector<real>& G);

		/**
		* @brief Check cylindrical friction input values and raise exeptions or warnings
		* @param V: Input vector of elements viscosity
		* @param v: Main viscosity of composite element
		* @throw ExceptionInvalidValue
		*/
		real checkViscosity(const real v, const std::vector<real>& V);

		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const override;

		/**
		* @brief Check, if Composite contains element.
		* @param Element: Pointer to the element
		* @return True/False
		*/ 
		bool isInComposite(HydraulicResistance* Element);

	public:
		Composite() :
			ComplexResistance()
		{
			this->setName("Composite " + std::to_string(id_));
		};

		/**
		* @brief 
		* @param name: String name of element
		* @param Re: Reynolds number. Negative value correspond to negative flow
		* @param G: Vector of geometry characteristics of the bend element:
		*	- G[0]: Roughness [m]
		*	- G[1]: Hydraulic diameter [m]
		*	- G[2]: Equivalent element length [m]
		* @param elements
		* @param vis: Flow kinematic viscosity in the element [Pa*s]
		* @param unique: Specifies, whether to store pointer, or independent copies of elements in
		* elements vector
		*/
		Composite(
			const real Re, 
			const std::vector<real>& G, 
			const std::vector<HydraulicResistance*>& elements, 
			const std::string& name = "", 
			const real vis = 1.0,
			bool unique = 1)
			: ComplexResistance(name, Re, G.at(1), G.at(0), M_PI* std::pow(0.5 * G.at(1), 2.0), G.at(2), vis, "[Composite]"), is_unique_(unique)
		{
			// set name
			if (name != "")
			{
				// user defined name

				this->setName(name);
			}
			else
			{
				// default name
				this->setName("Composite " + std::to_string(id_));
			}

			// fill internal elements vector with copies of hydraulic resistances
			for (auto& hr : elements)
			{
				if (is_unique_)
				{
					internal_resistances_.push_back(hr->copy());
				}
				else
				{
					internal_resistances_.push_back(hr);
				}
			}
			for (auto& hr : internal_resistances_)
			{
				hr->setExternalElementName(name_base_);
			}

		};

		virtual ~Composite() 
		{
			for (auto& hr : internal_resistances_)
			{
				if (is_unique_)
				{
					delete hr;
				}
				else
				{
					hr->setExternalElementName("");
				}
			}
		};

		/// @see HydraulicResistance::calculateElement()
		virtual void evaluate() override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;

		/// @see HydraulicResistance::getGeometry()
		virtual void getGeometry(std::vector<real>& G) override;

		/// @see HydraulicResistance::setRe()
		virtual void setRe(const real Re) override;

		void push_back(const HydraulicResistance* hr);

		void erase(const size_t idx);

		HydraulicResistance* get(const size_t idx);

		void getAll(std::vector<HydraulicResistance*>& elements);

		size_t size();
	};
}

