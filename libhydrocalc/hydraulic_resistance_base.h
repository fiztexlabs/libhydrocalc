#pragma once
#include <libhydrocalc/hydraulic_resistance.h>
#include <libhydrocalc/exceptions.h>
#include <string>

namespace hydrocalc
{
	class HydraulicResistanceBase :
		public HydraulicResistance
	{
	private:
		/// @brief Counter of HR elements
		static size_t count;
	protected:
		/// @brief Current settings
		settings::Settings CurrentSettings_;

		/// @brief Element name
		std::string name_;

		/// @brief Diagram number
		std::string diagram_ = "";

		/// @brief Element id
		const size_t id_;

		/// @brief Reynolds number
		real Re_ = 0.0;

		/// @brief Hydraulic diameter [m]
		real D0_ = 0.0;

		/// @brief Cross-section area [m2]
		real A_ = 0.0;

		/// @brief Roughness [m]
		real rou_ = 0.0;

		/// @brief Relative roughness @f$ \bar{\Delta} = \frac{\Delta}{D_0} @f$.
		real relRou_ = 0.0;

		/// @brief Relative friction loss coefficient [-]
		real lf_ = 0.0;

		/// @brief Friction part of local resistance coefficient [-]
		real CSIlf_ = 0.0;

		/// @brief Geometry part of local resistance coefficient [-]
		real CSIlr_ = 0.0;

		/// @brief Local resistance coefficient [-], @f$ \xi = \xi_\lambda+\xi_l @f$
		real CSI_ = 0.0;

		/// @brief type of geometry (cylinrical, rectangular etc.)
		Type type_ = Type::cylindrical;

		/**
		* @bpief Proceed InvalidValue accidents
		* @param msg: Error message
		* @param exec: Type of eception to raise
		* @return NaN or 0.0 correspond to CurrentSettings_.InvalidValuesBehaviorMode 
		*/
		real procInvalidValue(const std::string& msg, const Exception& exec);

		/**
		* @bpief Proceed unphysical value accidents
		* @param val: Calculated value
		* @param true_val: True value
		* @param msg: Error message
		* @param exec: Type of eception to raise
		* @return NaN or 0.0 correspond to CurrentSettings_.InvalidValuesBehaviorMode
		*/
		real procUnphysicalValue(const real val, const real true_val, const std::string& msg, const Exception& exec);

		/**
		* @brief Rise actions corresponding to CurrentSettings_.NonExistentFunc flag
		* @param FuncName: Name of function for report message
		* @param exec: Type of eception to raise
		* @return NaN value if function does not exist and 0.0 value if non-existent function, or ignored.
		* Result dependent on CurrentSettings_.NonExistentFunc
		*/
		real procNonExixtantFunc(const std::string& FuncName, const Exception& exec);

		/**
		* @bpief Check and proceed ReversedFlow accidents
		* @details Flow is reversed for Re < 0.0
		* @param msg: Error message
		* @param exec: Type of exception to raise
		* @return NaN or 0.0 correspond to CurrentSettings_.ReversedFlowMode flag
		*/
		real checkReversedFlow(const std::string& msg, const Exception& exec);

		/**
		* @bpief Proceed OutOfRange accidents
		* @param msg: Error message
		* @param nearest: Nearest valid value
		* @param exec: Type of exception to raise
		* @return NaN or 0.0 correspond to CurrentSettings_.OutOfRangeMode
		*/
		real procOutOfRange(const std::string& msg, const Exception& exec, const real nearest = 0.0);

	public:
		/// @brief Default constructor
		HydraulicResistanceBase() :
			id_(count),
			name_("Undefined element " + std::to_string(id_))
		{
			++count;
		}

		/**
		* @brief Recommended constructor
		* @details Initialize main variables, turn element counter and set id to element
		* @param name: String name of element
		* @param Re: Reynolds number
		* @param D0: Hydraulic diameter [m]
		* @param A: Cross-section area [m2]
		* @param rou: Roughness [m]
		* @param type: Type of geometry (hydrocalc::Type)
		*/
		HydraulicResistanceBase(
			const std::string& name, 
			const real Re, 
			const real D0, 
			const real rou,
			const real A,
			const Type type) :
			id_(count),
			name_(name),
			Re_(Re),
			D0_(D0),
			A_(A),
			rou_(rou),
			relRou_(rou/D0),
			type_(type)
		{
			++count;
		};

		virtual ~HydraulicResistanceBase() {};

		/// @see HydraulicResistance::setName()
		virtual void setName(const std::string& name) override;

		/// @see HydraulicResistance::getName()
		virtual void getName(std::string& name);

		/// @see HydraulicResistance::setRe()
		virtual void setRe(const real Re) override;

		/// @see HydraulicResistance::getRe()
		virtual real getRe() override;

		/// @see HydraulicResistance::setRou()
		virtual void setRou(const real rou) override;

		/// @see HydraulicResistance::getRou()
		virtual real getRou() override;

		/// @see HydraulicResistance::getType()
		virtual Type getType() override;

		/// @see HydraulicResistance::getHydraulicDiameter()
		virtual real getHydraulicDiameter() override;

		/// @see HydraulicResistance::getId()
		virtual size_t getId() override;

		/// @see HydraulicResistance::getFrictionPartCoeff()
		virtual real getFrictionPartCoeff() override;

		/// @see HydraulicResistance::getGeometryPartCoeff()
		virtual real getGeometryPartCoeff() override;

		/// @see HydraulicResistance::getRelFrictionCoeff()
		virtual real getRelFrictionCoeff() override;

		/// @see HydraulicResistance::getLocalResistanceCoeff()
		virtual real getLocalResistanceCoeff() override;

		/// @see HydraulicResistance::getCrossSectionArea()
		virtual real getCrossSectionArea() override;

		/// @see HydraulicResistance::getDiagram()
		virtual void getDiagram(std::string& diagram) override;

		/// @see HydraulicResistance::getElement()
		virtual HydraulicResistance* getElement(HydraulicResistance* Element) override;

		/// @see HydraulicResistance::addToComposite()
		virtual void addToComposite(const std::vector< HydraulicResistance*>& elementsToComposite) override;

		/// @see HydraulicResistance::deleteFromComposite()
		virtual void deleteFromComposite(const std::vector< HydraulicResistance*>& elementsToDelete) override;
	};

	/// @brief Initialize counter of HR elements
	inline size_t HydraulicResistanceBase::count = 0;
}