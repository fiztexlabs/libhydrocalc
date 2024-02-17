#pragma once
#include <HydraulicResistances/CylindricalHydraulicResistance.h>
#include <HydraulicResistances/CylindricalFriction.h>

#define _USE_MATH_DEFINES
#include <math.h>

class CurveCylindricalDiffuser;

/**
* @brief Class for calculating hydraulic resistance of cylindrical confusers with
* curve generatrix.
* @details Calculation based on diagrams (I.E. Idelchik, 1992):
* 5-23
* This elemnt has a direction dependent geometry, so in the case of negative flow @f$ (Re < 0) @f$
* element create CurveCylindricalDiffuser in function createDiffuser and calculate it.
* @author Ilya Konovalov
* @date Released 11.08.2022
*/
class CurveCylindricalConfuser :
	public CylindricalHydraulicResistance
{
private:
	/// @brief Friction part of hydraulic resistance of bend
	CylindricalFriction FrictionPart;

	/// @brief If flow through element is negative, then confuser turns to diffuser
	CurveCylindricalDiffuser* InvertConfuser;

	/// @brief Length of outlet section of confuser [m]
	HSReal L0_ = 0.0;

	/// @brief Curve radius [m]
	HSReal R0_ = 0.0;

	/// @brief Length of diffuser [m]
	HSReal Lc_ = 0.0;

	/// @brief Hydraulic diameter of inlet section of confuser [m]
	HSReal D1_ = 0.0;

	/// @brief Cross-section area of inlet section of confuser [m2]
	HSReal A1_ = 0.0;

	/**
	* @brief create diffuser element for negative flow
	* @return Pointer to CurveCylindricalDiffuser
	*/
	CurveCylindricalDiffuser* createDiffuser();

protected:
	/**
	* @brief Check curve cylindrical confuser element values and raise exeptions or warnings.
	* @details Error codes: -
	*/
	void errorHandling();

	/**
	* @brief Check curve cylindrical confuser element input values and raise exeptions
	* or warnings.
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
	* @brief Default constructor of curve cylindrical confuser element.
	* @details Fields of element must be initialized by setters methods
	and after that function calculateElement() must be called.
	* @see Service
	*/
	CurveCylindricalConfuser()
		: CylindricalHydraulicResistance()
	{
		// set default name of element
		name_ = "CurveCylindricalConfuser" + std::to_string(id_);
	}

	/**
	* @brief Recommended constructor of curve cylindrical confuser element.
	* @details Automatically check inputs, initialize fields and calculate element
	(if autocalc = 1).
	* @param name: String name of element
	* @param Re: Reynolds number. Negative value correspond to negative flow
	* @param G: Vector of geometry characteristics of the bend element:
	*	- G[0]: Roughness [m]
	*	- G[1]: Hydraulic diameter of confuser [m]
	*	- G[2]: Length of outlet section of confuser [m]
	*	- G[3]: Length of confuser [m]
	*	- G[4]: Hydraulic diameter of outlet section of confuser [m]
	*	- G[5]: Curve radius [m]
	* @param invertable: Define that element create diffuser obj inside for reversable flow
	* @see Service
	*/
	CurveCylindricalConfuser(const std::string& name, const HSReal Re, const std::vector<HSReal>& G, bool invertable = true)
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
			name_ = "CurveCylindricalConfuser" + std::to_string(id_);
		}

		// check inputs
		errorHandling(Re, G);

		Re_ = Re;
		rou_ = G[0];
		D0_ = G[1];
		L0_ = G[2];
		Lc_ = G[3];
		D1_ = G[4];
		R0_ = G[5];

		// create diffuser element (for negative flow)
		if (invertable)
		{
			InvertConfuser = createDiffuser();
		}

		// initialize friction element
		FrictionPart = CylindricalFriction(name_ + "_friction", Re_, { rou_,D0_,Lc_ });

		A_ = M_PI * pow(0.5 * D0_, 2.0);
		A1_ = M_PI * pow(0.5 * D1_, 2.0);
		relRou_ = rou_ / D0_;

		if (autocalc)
		{
			calculateElement();
		}

	}

	/// @see IBaseHydraulicResistance::setGeometry()
	void setGeometry(const std::vector<HSReal>& G);

	/// @see IBaseHydraulicResistance::getGeometry()
	void getGeometry(std::vector<HSReal>& G);

	/// @see IBaseHydraulicResistance::getLength()
	HSReal getLength();

	/// @see IBaseHydraulicResistance::setLength()
	virtual void setLength(const HSReal L);
};

