#pragma once
#include "CylindricalHydraulicResistance.h"
#include "CylindricalFriction.h"
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

class RingFriction :
	public CylindricalHydraulicResistance
{
private:
	/// @brief Friction part of hydraulic resistance of ring channel
	CylindricalFriction FrictionPart;

	/// @brief Length of element [m]
	HSReal L_ = 0.0;

	/// @brief External diameter [m]
	HSReal d_ext_ = 0.0;

	/// @brief Internal diameter [m]
	HSReal d_int_ = 0.0;

	/// @brief Excentric [m]
	HSReal exc_ = 0.0;

protected:
	/**
	* @brief Check ring friction element values and raise exeptions or warnings.
	* @details Error codes:
	*	- 1: invalid size of vector of geometry characteristic
	*	- 2: one of element characteristics have an invalid value
	*/
	void errorHandling();

	/**
	* @brief Check ring friction input values and raise exeptions or warnings
	* @details Error codes:
	*	- 1: Invalid size of vector of geometry characteristic
	*	- 2: One of element characteristics have an invalid value
	* @param Re: Input Reynolds number
	* @param G: Input vector of geometry characteristics
	*/
	void errorHandling(const HSReal Re, const std::vector<HSReal>& G);

public:
	/// @see IBaseHydraulicResistance::calculateElement()
	void calculateElement();

	/// @see IBaseHydraulicResistance::copy()
	virtual IBaseHydraulicResistance* copy() const;

	/**
	* @brief Default constructor of ring friction element.
	* @details Fields of element must be initialized by setters methods
	and after that function calculateElement() must be called.
	* @see Service
	*/
	RingFriction()
		: CylindricalHydraulicResistance()
	{
		// set default name of element
		name_ = "RingFriction_Id" + std::to_string(id_);
	};

	/**
	* @brief Recommended constructor of ring friction element.
	* @details Automatically check inputs, initialize fields and calculate element
	(if autocalc = 1).
	* @param name: String name of element
	* @param Re: Reynolds number, negative value correspond to negative flow
	* @param G: Vector of geometry characteristics of element:
	*	- G[0]: Roughness [m]
	*	- G[1]: External diameter [m]
	*	- G[2]: Internal diameter [m]
	*	- G[3]: Excentric		  [m]
	*	- G[4]: Length of element [m]
	* @see Service
	*/
	RingFriction(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
		: CylindricalHydraulicResistance(name, Re, 0.0, 0.0, 0.0, 0.0)
	{
		// set name
		if (name != "")
		{
			// user defined name
			name_ = name;
		}
		else
		{
			// default name
			name_ = "RingFriction" + std::to_string(id_);
		}

		// check inputs
		errorHandling(Re, G);

		Re_ = Re;
		rou_ = G[0];
		d_ext_ = G[1];
		d_int_ = G[2];
		exc_ = G[3];
		L_ = G[4];
		A_ = M_PI * (pow(0.5 * G[1], 2.0) - pow(0.5 * G[2], 2.0));

		D0_ = d_ext_ - d_int_;
		relRou_ = rou_ / D0_;

		/*
		initialize friction element (L of friction elemnt is equal to 0, because only relative
		friction loss coefficient is needed
		*/
		FrictionPart = CylindricalFriction(name_ + "_friction", Re_, { rou_,D0_,0.0 });

		if (autocalc)
		{
			calculateElement();
		}

	};

	/// @see IBaseHydraulicResistance::setGeometry()
	void setGeometry(const std::vector<HSReal>& G);

	/// @see IBaseHydraulicResistance::getGeometry()
	void getGeometry(std::vector<HSReal>& G);

	/// @see IBaseHydraulicResistance::getLength()
	HSReal getLength();

	/// @see IBaseHydraulicResistance::setLength()
	virtual void setLength(const HSReal L);
};
