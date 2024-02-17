#pragma once
#include <HydraulicResistances/CylindricalHydraulicResistance.h>
#include <HydraulicResistances/CylindricalFriction.h>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

/**
* @brief Class for calculating hydraulic resistance of cylindrical bends.
* @details Calculation based on diagrams (I.E. Idelchik, 1992): 
* 6-1
* @image html 6-1.png
* 6-2
* @image html 6-2.png
* 6-7
* @image html 6-7.png
* 6-9
* @image html 6-9.png
* This elemnt has a direction independent geometry, so Re computes as @f$ Re=|Re| @f$.
* @author Ilya Konovalov
* @date Released 03.08.2022
*/
class CylindricalBend :
	public CylindricalHydraulicResistance
{
protected:
	/// @brief Friction part of hydraulic resistance of bend
	CylindricalFriction FrictionPart;

	/// @brief Length of element [m]
	HSReal L_ = 0.0;

	/// @brief Length of straight section before bend [m]
	HSReal L0_ = 0.0;

	/// @brief Bending radius [m]
	HSReal R0_ = 0.0;

	/// @brief Bending angle [deg]
	HSReal delta_ = 0.0;

	/**
	* @brief Check cylindrical bend element values and raise exeptions or warnings.
	* @details Error codes: -
	*/
	void errorHandling();

	/**
	* @brief Check cylindrical bend input values and raise exeptions or warnings.
	* @details Error codes:
	*	- 1: Invalid size of vector of geometry characteristic
	*	- 2: One of element characteristics have an invalid value
	* @param Re: input Reynolds number, const HSReal
	* @param G: input vector of geometry characteristics, const std::vector<HSReal>&
	*/
	void errorHandling(const HSReal Re, const std::vector<HSReal>& G);

public:
	/// @see IBaseHydraulicResistance::calculateElement()
	void calculateElement();

	/// @see IBaseHydraulicResistance::copy()
	virtual IBaseHydraulicResistance* copy() const;

	/**
	* @brief Default constructor of cylindrical bend element.
	* @details Fields of element must be initialized by setters methods
	and after that function calculateElement() must be called.
	* @see Service
	*/
	CylindricalBend()
		: CylindricalHydraulicResistance()
	{
		// set default name of element
		name_ = "CylindricalBend" + std::to_string(id_);
	};

	/**
	* @brief Recommended constructor of cylindrical bend element.
	* @details Automatically check inputs, initialize fields and calculate element
	(if autocalc = 1).
	* @param name: String name of element
	* @param Re: Reynolds number. Negative value correspond to negative flow
	* @param G: Vector of geometry characteristics of the bend element:
	*	- G[0]: Roughness [m]
	*	- G[1]: Diameter of cross-section [m]
	*	- G[2]: Bending radius [m]
	*	- G[3]: Bending angle [deg]; in the case, when G[3] < 0, bending angle 
	calculates as 360 - G[3]
	*	- G[4]: Length of section before bend [m]; G[4] = 0 means, that
	bend located after collector, however G[4] > 0 means, that straight section L = G[4]
	located before bend
	* @see Service
	*/
	CylindricalBend(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
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
			name_ = "CylindricalBend" + std::to_string(id_);
		}

		Re_ = Re;
		rou_ = G[0];
		D0_ = G[1];
		L0_ = G[4];
		R0_ = G[2];
		if (G[3] < 0)
		{
			delta_ = 360.0 - G[3];
		}
		else
		{
			delta_ = G[3];
		}

		// check inputs
		errorHandling(Re, G);

		/* 
		initialize friction element (L of friction elemnt is equal to 0, because only relative
		friction loss coefficient is needed
		*/
		FrictionPart = CylindricalFriction(name_ + "_friction", Re_, { rou_,D0_,0.0 });

		A_ = M_PI * pow(0.5 * G[1], 2.0);
		L_ = (2.0 * M_PI * R0_ * delta_) / 360.0;
		relRou_ = rou_ / D0_;

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
