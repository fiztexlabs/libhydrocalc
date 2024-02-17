#pragma once
#include <HydraulicResistances/CylindricalHydraulicResistance.h>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

/**
* @brief Class for calculating hydraulic resistance of friction in 
cylindrical elements.
* @details Calculation based on diagrams (I.E. Idelchik, 1992):
* 2-1
* @image html 2-1.png
* 2-3
* @image html 2-3.png
* 2-4
* @image html 2-4.png
* This elemnt has a direction independent 
* geometry, so Re computse as @f$ Re=|Re| @f$.
* @author Ilya Konovalov
* @date Released 01.08.2022
*/
class CylindricalFriction :
	public CylindricalHydraulicResistance
{
private:
	/// @brief Length of element [m]
	HSReal L_ = 0.0;

protected:
	/**
	* @brief Check cylindrical friction element values and raise exeptions or warnings.
	* @details Error codes:
	*	- 1: invalid size of vector of geometry characteristic
	*	- 2: one of element characteristics have an invalid value
	*/
	void errorHandling();

	/**
	* @brief Check cylindrical friction input values and raise exeptions or warnings
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
	* @brief Default constructor of cylindrical friction element.
	* @details Fields of element must be initialized by setters methods
	and after that function calculateElement() must be called.
	* @see Service
	*/
	CylindricalFriction()
		: CylindricalHydraulicResistance()
	{
		// set default name of element
		name_ = "CylindricalFriction_Id" + std::to_string(id_);
	};

	/**
	* @brief Recommended constructor of cylindrical friction element.
	* @details Automatically check inputs, initialize fields and calculate element
	(if autocalc = 1).
	* @param name: String name of element
	* @param Re: Reynolds number, negative value correspond to negative flow
	* @param G: Vector of geometry characteristics of element:
	*	- G[0]: Roughness [m]
	*	- G[1]: Diameter of cross-section [m]
	*	- G[2]: Length of element [m]
	* @see Service
	*/
	CylindricalFriction(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
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
			name_ = "CylindricalFriction" + std::to_string(id_);
		}

		// check inputs
		errorHandling(Re, G);

		Re_ = Re;
		rou_ = G[0];
		D0_ = G[1];
		L_ = G[2];
		A_ = M_PI * pow(0.5 * G[1], 2.0);
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

