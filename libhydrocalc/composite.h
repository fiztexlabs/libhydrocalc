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

		/// @brief Indicate, that composite store elements pointers, or elements copies
		bool is_unique_ = 1;

		/// @brief Correct Reynolds numbers of internal elements
		std::vector<real> elements_Re_;

		/// @brief Real full length of elements in the composite
		real Lfull_ = 0.0;

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

		/**
		* @bpief Proceed FlowOutOfRange accidents
		* @param msg: Error message
		* @param exec: Type of exception to raise
		* @return NaN or 0.0 correspond to CurrentSettings_.OutOfRangeMode
		*/
		real procInconsistentReynolds(HydraulicResistance* hr) const;

	public:
		Composite() :
			ComplexResistance()
		{
			type_ = "[Composite]";

			this->setName("Composite " + std::to_string(id_));
		};

		/**
		* @brief 
		* @param name: String name of element
		* @param Re: Reynolds number. Negative value correspond to negative flow
		* @param G: Vector of geometry characteristics of the bend element:
		*	- G[0]: Hydraulic diameter [m]
		*	- G[1]: Equivalent element length [m]
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
			: ComplexResistance(name, Re, G.at(0), 0.0, M_PI* std::pow(0.5 * G.at(0), 2.0), G.at(1), vis, "[Composite]"), is_unique_(unique)
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

			// check inputs
			real err = checkGeometry(G);

			if (std::isnan(err))
			{
				D0_ = err;
				L_ = err;
			}

			// set Reynolds number
			setRe(Re_);
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

		/// @see HydraulicResistance::evaluate()
		virtual void evaluate() override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;

		/// @see HydraulicResistance::getGeometry()
		virtual void getGeometry(std::vector<real>& G) override;

		/// @see HydraulicResistance::setRe()
		virtual void setRe(const real Re) override;

		/**
		* @brief Add element to the composite
		* @details If is_unique_, then method place to composite copy of hr,
		* else - pointer to hr
		* @param hr: Pointer to hydraulic resistance
		*/
		void push_back(HydraulicResistance* hr);

		/**
		* @brief Add few elements to the composite
		* @details If is_unique_, then method place to composite copies of elements,
		* else - pointer to hr
		* @param elements: Vector of elements
		*/
		void push_back(const std::vector<HydraulicResistance*>& elements);

		/**
		* @brief Erase element from composite by index (in composite)
		* @details If is_unique_, cal delete for destruct element, else
		* only erase element from composite internal elements
		* @param idx: Element index in the composite
		* @throw ExceptionInvalidElementId
		*/
		void erase(const size_t idx);

		/**
		* @brief Erase element from composite by pointer
		* @details If is_unique_, cal delete for destruct element, else
		* only erase element from composite internal elements
		* @param hr: Pointer to the hydraulic resistance element
		* @throw ExceptionInvalidElementId
		*/
		void erase(HydraulicResistance* hr);

		/**
		* @brief Erase elements from composite by index
		* @details If is_unique_, cal delete for destruct element, else
		* only erase element from composite internal elements
		* @param elements: Vector of elements indices to be erased
		* @throw ExceptionInvalidElementId
		*/
		void erase(const std::vector<size_t>& elements);

		/**
		* @brief Erase elements from composite by pointer
		* @details If is_unique_, cal delete for destruct element, else
		* only erase element from composite internal elements
		* @param elements: Vector of elements to be erased
		* @throw ExceptionInvalidElementId
		*/
		void erase(const std::vector<HydraulicResistance*>& elements);

		/**
		* @brief Get element pointer by index in the composite
		* @param idx: Index of element in composite
		* @param copy: If 0, get return pointer to element in the composite, 
		* else get return pointer to the
		*/
		HydraulicResistance* get(const size_t idx, const bool copy = 0);

		/**
		* @brief Return vector of pointers to all hydraulic resistances in the composite
		* @param[out] elements: Vector of composite hydraulic elements
		* @param copy: If 0, get return pointer to element in the composite, 
		* else get return pointer to the
		*/
		void get(std::vector<HydraulicResistance*>& elements, const bool copy = 0);

		/**
		* @brief Count of elements in the composite
		*/
		size_t size();

		/**
		* @brief Check, if composite contains elements pointers, or its copies
		*/
		bool isUnique();
	};
}

