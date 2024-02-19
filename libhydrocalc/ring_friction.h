#pragma once
#include <libhydrocalc/complex_resistance.h>
#include <libhydrocalc/cylindrical_friction.h>
#include <string>
#include <vector>
#include <cmath>
#include <math.h>

namespace hydrocalc
{
	/**
	* @brief Class for calculating hydraulic resistance of
	* ring channels
	* @details Calculation based on diagrams (I.E. Idelchik, 1992):
	* 2-7
	* @author Ilya Konovalov
	* @date Released 18.04.2023
	*/
	class RingFriction :
		public ComplexResistance
	{
	private:
		/// @brief Friction part of hydraulic resistance of ring channel
		CylindricalFriction FrictionPart_;

		/// @brief External diameter [m]
		real d_ext_ = 0.0;

		/// @brief Internal diameter [m]
		real d_int_ = 0.0;

		/// @brief Excentric [m]
		real exc_ = 0.0;

	protected:
		/**
		* @brief Check ring friction input values and raise exeptions or warnings
		* @param G: Input vector of geometry characteristics
		* @throw ExceptionInvalidValue
		*/
		real checkGeometry(const std::vector<real>& G);

		/// @see HydraulicResistance::copy()
		virtual HydraulicResistance* copy() const override;

		/// @brief Evaluate hydraulic resisance with respect to diagram 2-7
		void diagram27();

	public:
		/**
		* @brief Default constructor of ring friction element.
		*/
		RingFriction()
			: ComplexResistance()
		{
			internal_resistances_.push_back(&FrictionPart_);

			// set default name of element
			this->setName("RingFriction " + std::to_string(id_));

			FrictionPart_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		};

		/**
		* @brief Recommended constructor of ring friction element.
		* @param name: String name of element
		* @param Re: Reynolds number, negative value correspond to negative flow
		* @param G: Vector of geometry characteristics of element:
		*	- G[0]: Roughness [m]
		*	- G[1]: External diameter [m]
		*	- G[2]: Internal diameter [m]
		*	- G[3]: Excentric		  [m]
		*	- G[4]: Length of element [m]
		* @throw ExceptionInvalidValue
		*/
		RingFriction(const real Re, const std::vector<real>& G, const std::string& name = "")
			: ComplexResistance(
				name, 
				Re, 
				G.at(1) - G.at(2), 
				G.at(0), 
				M_PI * (std::pow(0.5 * G.at(1), 2.0) - std::pow(0.5 * G.at(2), 2.0)),
				G.at(4), 
				"ring friction")
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
				this->setName("RingFriction " + std::to_string(id_));
			}

			// check inputs
			real err = checkGeometry(G);

			if (std::isnan(err))
			{
				rou_ = err;
				D0_ = err;
				d_ext_ = err;
				d_int_ = err;
				exc_ = err;
				L_ = err;
			}
			else
			{
				d_ext_ = G.at(1);
				d_int_ = G.at(2);
				exc_ = G.at(3);
				L_ = G.at(4);
			}

			FrictionPart_ = CylindricalFriction(Re_, { rou_,D0_,L_ }, "friction");
			FrictionPart_.setExternalElementName(name_base_);

			// disable check parameters for internal part
			FrictionPart_.CurrentSettings_.checkInputs = 0;
			FrictionPart_.CurrentSettings_.GeometryOutOfRangeMode = settings::GeometryOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.FlowOutOfRangeMode = settings::FlowOutOfRangeBehaviorMode::NoCheck;
			FrictionPart_.CurrentSettings_.ReversedFlowMode = settings::ReversedFlowBehaviorMode::Quiet;
		};

		virtual ~RingFriction() {};

		/// @see HydraulicResistance::calculateElement()
		virtual void evaluate() override;

		/// @see HydraulicResistance::setGeometry()
		virtual void setGeometry(const std::vector<real>& G) override;

		/// @see HydraulicResistance::getGeometry()
		virtual void getGeometry(std::vector<real>& G) override;
	};
}