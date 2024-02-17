#pragma once
#include <HydraulicResistances/CylindricalHydraulicResistance.h>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

/**
* @brief Class for calculating unexpected size changes with sharp edges.
* @details Calculation based on diagrams (I.E. Idelchik, 1992):
* 4-1
* 4-9
* This elemnt has a direction dependent geometry, so in the case of negative flow @f$ (Re < 0) @f$ 
* if element is expansion, than it turns to constriction and vice versa. Also if @f$ D_0 < D_1 @f$
* element is expansion, othervise - constriction.
* @author Ilya Konovalov
* @date Released 12.08.2022
*/
class SharpUnexpectedSizeChange :
	public CylindricalHydraulicResistance
{
private:
	/// @brief Cross-section area of additional section (inlet if constriction or outlet if expansion) [m2]
	HSReal A2_ = 0.0;

	/// @brief Diameter 1 [m]
	HSReal D1_ = 0.0;

	/// @brief Diameter 2 [m]
	HSReal D2_ = 0.0;

protected:
	/**
	* @brief Check element values and raise exeptions or warnings.
	* @details Error codes:
	*	- 1: invalid size of vector of geometry characteristic
	*	- 2: one of element characteristics have an invalid value
	*/
	void errorHandling();

	/**
	* @brief Check element input values and raise exeptions or warnings
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
	* @brief Default constructor of unexpected size changes with sharp edges.
	* @details Fields of element must be initialized by setters methods
	and after that function calculateElement() must be called.
	* @see Service
	*/
	SharpUnexpectedSizeChange()
		: CylindricalHydraulicResistance()
	{
		// set default name of element
		name_ = "UnexpectedSizeChange_constriction" + std::to_string(id_);
	};

	/**
	* @brief Recommended constructor of unexpected size changes with sharp edges.
	* @details Automatically check inputs, initialize fields and calculate element
	(if autocalc = 1).
	* @param name: String name of element
	* @param Re: Reynolds number, negative value correspond to negative flow
	* @param G: Vector of geometry characteristics of element:
	*	- G[0]: Roughness [m]
	*	- G[1]: Diameter 1 [m]
	*	- G[2]: Diameter 2 [m]
	* @see Service
	*/
	SharpUnexpectedSizeChange(const std::string& name, const HSReal Re, const std::vector<HSReal>& G)
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
			if (G[1] > G[0])
			{
				name_ = "UnexpectedSizeChange_constriction" + std::to_string(id_);
			}
			else
			{
				name_ = "UnexpectedSizeChange_expansion" + std::to_string(id_);
			}
		}

		// check inputs
		errorHandling(Re, G);


		Re_ = Re;
		rou_ = G[0];
		D1_ = G[1];
		D2_ = G[2];
		D0_ = min(D1_, D2_);

		A_ = M_PI * pow(0.5 * D0_, 2.0);
		A2_ = M_PI * pow(0.5 * max(D1_, D2_), 2.0);
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

