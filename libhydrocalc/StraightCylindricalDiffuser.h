#pragma once
#include <HydraulicResistances/CylindricalHydraulicResistance.h>
#include <HydraulicResistances/CylindricalFriction.h>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

class StraightCylindricalConfuser;

/**
* @brief Class for calculating hydraulic resistance of cylindrical diffusers with 
* straight generatrix.
* @todo Add approximation of @f$ k_d @f$ with diagram 5-2 for
* straight cylindrical diffuser element
* @details Calculation based on diagrams (I.E. Idelchik, 1992):
* 5-2
* 5-7
* 5-9
* This elemnt has a direction dependent geometry, so in the case of negative flow @f$ (Re < 0) @f$, 
* if diagram 5-9 used for calculation, element create StraightCylindricalConfuser and 
* SharpUnexpectedSizeChange elements and calculate it. Othervise for @f$ (Re < 0) @f$ created only
* StraightCylindricalConfuser.
* @author Ilya Konovalov
* @date Released 05.08.2022
*/
class StraightCylindricalDiffuser :
	public CylindricalHydraulicResistance
{
private:
	/// @brief Friction part of hydraulic resistance of bend
	CylindricalFriction FrictionPart;

	/// @brief If flow through element is negative, then diffuser turns to confuser
	StraightCylindricalConfuser* InvertDiffuser;

	/// @brief Length of inlet section of diffuser [m]
	HSReal L0_ = 0.0;
	
	/// @brief Length of diffuser [m]
	HSReal Ld_ = 0.0;

	/// @brief Length of outlet section of diffuser [m]
	HSReal L1_ = 0.0;

	/// @brief Hydraulic diameter of outlet section of diffuser [m]
	HSReal D1_ = 0.0;

	/// @brief Diameter of outlet of diffuser [m]
	HSReal Dout_ = 0.0;

	/// @brief Cross-section area of outlet section of diffuser [m2]
	HSReal A1_ = 0.0;
	
	/// @brief Angle of diffuser [deg]
	HSReal alpha_ = 0.0;

	/// @brief Turbulence intensity, @f$ I=\frac{w_0}{w_max} @f$
	HSReal I_ = 0.0;

	/**
	* @brief create confuser element for negative flow
	* @return Pointer to StraightCylindricalDiffuser
	*/
	StraightCylindricalConfuser* createConfuser();

protected:
	/**
	* @brief Check straight cylindrical diffusers element values and raise exeptions or warnings.
	* @details Error codes: -
	*/
	void errorHandling();

	/**
	* @brief Check straight cylindrical diffuser element input values and raise exeptions 
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
	* @brief Default constructor of straight cylindrical diffuser element.
	* @details Fields of element must be initialized by setters methods
	and after that function calculateElement() must be called.
	* @see Service
	*/
	StraightCylindricalDiffuser()
		: CylindricalHydraulicResistance()
	{
		// set default name of element
		name_ = "StraightCylindricalDiffuser" + std::to_string(id_);
	}

	/**
	* @brief Recommended constructor of straight cylindrical diffuser element.
	* @details Automatically check inputs, initialize fields and calculate element
	(if autocalc = 1).
	* @param name: String name of element
	* @param Re: Reynolds number. Negative value correspond to negative flow
	* @param G: Vector of geometry characteristics of the bend element:
	*	- G[0]: Roughness [m]
	*	- G[1]: Hydraulic diameter of diffuser [m]
	*	- G[2]: Turbulence intensity, @f$ I=\frac{w_0}{w_max} @f$. If @f$ I=1 @f$
	* velocity profile before diffuser is straight and influece of hit coefficient @f$ k_d @f$
	doesn't matter. Otherwise @f$ k_d @f$ should be taken into account with diagram 5-2
	*	- G[3]: Length of inlet section of diffuser [m]
	*	- G[4]: Length of diffuser [m]
	*	- G[5]: Length of outlet section of diffuser [m]
	*	- G[6]: Diameter of the outlet of diffuser[m]
	*	- G[7]: Hydraulic diameter of outlet section of diffuser [m]
	*	- G[8]: Angle of diffuser [deg]
	* @param invertable: Define that element create confuser obj inside for reversable flow
	* @see Service
	*/
	StraightCylindricalDiffuser(const std::string& name, const HSReal Re, const std::vector<HSReal>& G, bool invertable = true)
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
			name_ = "StraightCylindricalDiffuser" + std::to_string(id_);
		}

		// check inputs
		errorHandling(Re, G);

		Re_ = Re;
		rou_ = G[0];
		D0_ = G[1];
		I_ = G[2];
		L0_ = G[3];
		Ld_ = G[4];
		L1_ = G[5];
		Dout_ = G[6];
		D1_ = G[7];
		alpha_ = G[8];

		// create confuser element (for negative flow)
		if (invertable)
		{
			InvertDiffuser = createConfuser();
		}

		// initialize friction element
		FrictionPart = CylindricalFriction(name_ + "_friction", Re_, { rou_,D0_,Ld_ });

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

