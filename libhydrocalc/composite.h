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
		real main_viscosity_{ 1.0 };

		std::vector<real> elements_viscosity_;

	protected:
		/**
		* @brief Check cylindrical friction input values and raise exeptions or warnings
		* @param G: Input vector of geometry characteristics
		* @throw ExceptionInvalidValue
		*/
		real checkGeometry(const std::vector<real>& G);

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
		*/
		Composite(const real Re, const std::vector<real>& G, const std::vector<HydraulicResistance*>& elements, const std::string& name = "", const std::vector<real>& elements_viscosity = std::vector<real>())
			: ComplexResistance(name, Re, G.at(1), G.at(0), M_PI* std::pow(0.5 * G.at(1), 2.0), 0.0, "composite")
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

			for (auto& hr : elements)
			{
				internal_resistances_.push_back(hr->copy());
			}
			for (auto& hr : internal_resistances_)
			{
				hr->setExternalElementName(name_base_);
			}

			//if()
		};

		virtual ~Composite() 
		{
			for (auto& hr : internal_resistances_)
			{
				delete hr;
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

