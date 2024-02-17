#pragma once
#include <HydraulicResistances/IBaseHydraulicResistance.h>
#include <service/ServiceHS.h>
#include <string>

/**
* @brief abstract class CylindricalHydraulicResistance define the global functions and variables
for all cylindrical local hydraulic resistance elements
* @author Ilya Konovalov
* @date Released 01.08.2022
*/
class CylindricalHydraulicResistance :
	public IBaseHydraulicResistance
{
protected:
	/// @brief Element name
	std::string name_;

	/// @brief Diagram number
	std::string diagram_ = "";

	/// @brief Element id
	unsigned int id_ = 0;

	/// @brief Reynolds number
	HSReal Re_ = 0.0;

	/// @brief Hydraulic diameter [m]
	HSReal D0_ = 0.0;

	/// @brief Cross-section area [m2]
	HSReal A_ = 0.0;

	/// @brief Roughness [m]
	HSReal rou_ = 0.0;

	/// @brief Relative roughness @f$ \bar{\Delta} = \frac{\Delta}{D_0} @f$.
	HSReal relRou_ = 0.0;

	/// @brief Relative friction loss coefficient [-]
	HSReal lf_ = 0.0;

	/// @brief Friction part of local resistance coefficient [-]
	HSReal CSIlf_ = 0.0;

	/// @brief Geometry part of local resistance coefficient [-]
	HSReal CSIlr_ = 0.0;

	/// @brief Local resistance coefficient [-], @f$ \xi = \xi_\lambda+\xi_l @f$
	HSReal CSI_ = 0.0;

	/// @brief type of geometry (cylinrical, rectangular etc.)
	unsigned int type_ = 0;

	/// @brief Enable or disable recalculation element values, when anything is changed (when keys changed = 1 and calculated = 0)
	int autocalc = 1;

	/// @brief flag, shows wether the element values was recalculated after changes (when key changed = 1)
	int calculated = 0;

	/// @brief flag, shows wether the element values was changed by setters
	int changed = 0;

	/// @brief enable or disable warnings (enable by default)
	bool flagHandleWarnings = 1;

protected:
	///**
	//* @brief Check element values and raise exeptions or warnings.
	//*/
	//virtual void errorHandling() = 0;
	//
	///**
	//* @brief Check element input values and raise exeptions or warnings
	//* @param Re: Input Reynolds number
	//* @param G: Input vector of geometry characteristics
	//*/
	//virtual void errorHandling(const HSReal Re, const std::vector<HSReal>& G) = 0;

public:
	/// @see IBaseHydraulicResistance::calculateElement()
	virtual void calculateElement() = 0;

	/// @see IBaseHydraulicResistance::setGeometry()
	virtual void setGeometry(const std::vector<HSReal>& G) = 0;

	/// @see IBaseHydraulicResistance::getGeometry()
	virtual void getGeometry(std::vector<HSReal>& G) = 0;

	/**
	* @brief Default constructor
	* @details Initialize fields by default, turn element counter and set id to element
	*/
	CylindricalHydraulicResistance()
	{
		idHR++;
		id_ = idHR - 1;
	}

	/**
	* @brief Recommended constructor
	* @details Initialize main variables, turn element counter and set id to element
	* @param name: String name of element
	* @param Re: Reynolds number
	* @param D0: Hydraulic diameter [m]
	* @param A: Cross-section area [m2]
	* @param rou: Roughness [m]
	* @param relRou: Relative roughness, @f$ \bar{\Delta} = \frac{\Delta}{D_0} @f$.
	*/
	CylindricalHydraulicResistance(const std::string& name, const HSReal Re, const HSReal D0, const HSReal A, 
		const HSReal rou, const HSReal relRou)
	{
		idHR++;
		id_ = idHR - 1;
		name_ = name;
		Re_ = Re;
		D0_ = D0;
		A_ = A;
		rou_ = rou;
		relRou_ = relRou;
		type_ = 0;
	};

	~CylindricalHydraulicResistance() {};

	/// @see IBaseHydraulicResistance::setName()
	void setName(const std::string& name);

	/// @see IBaseHydraulicResistance::setAutocalc()
	void setAutocalc(const bool flag);

	/// @see IBaseHydraulicResistance::setHandleWarnings()
	void setHandleWarnings(const bool flag);

	/// @see IBaseHydraulicResistance::setRe()
	void setRe(const HSReal Re);

	/// @see IBaseHydraulicResistance::setRou()
	void setRou(const HSReal rou);

	/// @see IBaseHydraulicResistance::getType()
	unsigned int getType();

	/// @see IBaseHydraulicResistance::getHydraulicDiameter()
	HSReal getHydraulicDiameter();

	/// @see IBaseHydraulicResistance::getRe()
	HSReal getRe();

	/// @see IBaseHydraulicResistance::getRou()
	HSReal getRou();

	/// @see IBaseHydraulicResistance::getName()
	void getName(std::string& name);

	/// @see IBaseHydraulicResistance::getId()
	unsigned int getId();

	/// @see IBaseHydraulicResistance::getFrictionPartCoeff()
	HSReal getFrictionPartCoeff();

	/// @see IBaseHydraulicResistance::getGeometryPartCoeff()
	HSReal getGeometryPartCoeff();

	/// @see IBaseHydraulicResistance::getRelFrictionCoeff()
	HSReal getRelFrictionCoeff();

	/// @see IBaseHydraulicResistance::getLocalResistanceCoeff()
	HSReal getLocalResistanceCoeff();

	/// @see IBaseHydraulicResistance::getCrossSectionArea()
	HSReal getCrossSectionArea();

	/// @see IBaseHydraulicResistance::getDiagram()
	void getDiagram(std::string& diagram);

	/// @see IBaseHydraulicResistance::getError()
	HSReal getError();

	/// @see IBaseHydraulicResistance::deleteElement()
	void deleteElement();

	/// @see IBaseHydraulicResistance::getElement()
	IBaseHydraulicResistance* getElement(IBaseHydraulicResistance* Element);

	/// @see IBaseHydraulicResistance::addToComposite()
	void addToComposite(const std::vector< IBaseHydraulicResistance*>& elementsToComposite);

	/// @see IBaseHydraulicResistance::deleteFromComposite()
	void deleteFromComposite(const std::vector< IBaseHydraulicResistance*>& elementsToDelete);
};


