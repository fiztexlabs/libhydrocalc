#pragma once
#include <HydraulicResistances/CylindricalHydraulicResistance.h>
#include <service/ServiceHS.h>

#define _USE_MATH_DEFINES
#include <math.h>
/**
* @brief Class for define composite element, contains variable set of elements inside
* @details HydraulicComposite get from elements id and than call it's methods using id and stack of elements.
* HydraulicComposite element must be created in approach of constant volumetric flow in all its own elements.
* This condition satisfied if for all elements @f$ Re = Re_i\frac{D_0}{D_i} = const @f$. Otherwise 
* correspond warning will be raised.
* Example of calling from C++
* @code
* #include <iostream>
* #include "..\HydraulicResistances\IBaseHydraulicResistance.h"
* 
* int main()
* {
* 	// create cylindrical friction element
* 	IBaseHydraulicResistance* CF1 = CylindricalFrictionFab("CF2", 3187.0, { 2.e-5,0.02,1.0 });
* 
* 	// create first bend element
* 	IBaseHydraulicResistance* B1 = CylindricalBendFab("bend1", 51089.0, { 2.e-5,0.05,0.21,90.0, 10.0 });
* 
* 	// create second bend element
* 	IBaseHydraulicResistance* B2 = CylindricalBendFab("bend2", 51089.0, { 2.e-5,0.05,0.21,90.0, 10.0 });
* 
* 	// create HydraulicComposite element
* 	IBaseHydraulicResistance* composite = CompositeFab("branch", { 0.05 }, { B1, CF1, B2 });
* 	if (composite)
* 	{ 
* 		// call method from HydraulicComposite
* 		std::cout << composite->getLocalResistanceCoeff() << " id " << composite->getId() << "\n";
* 	}
* 
* }
* @endcode
* @see Service
*/
class HydraulicComposite :
	public CylindricalHydraulicResistance
{
private:
	/// @brief Vector of pointers to elements, belongs to this composite
	std::vector<IBaseHydraulicResistance*> compositeElements_;

	/// @brief General length of element
	HSReal L_ = 0.0;

protected:
	/**
	* @brief Check cylindrical friction element values and raise exeptions or warnings.
	* @details Error codes: -
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

	/**
	* @brief Check, if HydraulicComposite contains element.
	* @param Element: Pointer to the element
	* @return True/False
	*/
	bool isInComposite(IBaseHydraulicResistance* Element);
public:
	/**
	* @brief Default constructor of composite element.
	* @details Fields of element must be initialized by setters methods
	and after that function calculateElement() must be called.
	* @param name: String name of element
	* @see Service
	*/
	HydraulicComposite()
		: CylindricalHydraulicResistance()
	{
		// set default name of element
		name_ = "HydraulicComposite" + std::to_string(id_);

	}

	/**
	* @brief Recommended constructor of cylindrical friction element.
	* @details Automatically check inputs, initialize fields and calculate element
	(if autocalc = 1).
	* @param name: String name of composite element
	* @param G: Vector of geometry characteristics of element:
	*	- G[0]: Hydraulic diameter [m]. All hydraulic resistances will be reduced
	* to this hydraulic diameter.
	* @param ptrCompositeElements: Vector of objects to include in composite
	* @see IBaseHydraulicResistance::addToComposite()
	* @see IBaseHydraulicResistance::deleteFromComposite()
	* @see Service
	*/
	HydraulicComposite(const std::string& name, const std::vector<HSReal>& G, 
		const std::vector<IBaseHydraulicResistance*>& ptrCompositeElements)
		: CylindricalHydraulicResistance(name, 0.0, 0.0, 0.0, 0.0, 0.0)
	{
		errorHandling(0.0, G);

		compositeElements_ = ptrCompositeElements;
		// delete nullptr elements
		for (auto i = compositeElements_.begin(); i != compositeElements_.end();
			i = (*i == nullptr) ? compositeElements_.erase(i) : i + 1);

		D0_ = G[0];

		errorHandling();

		A_ = M_PI * pow(0.5 * D0_, 2.0);

		if (autocalc)
		{
			calculateElement();
		}


		for (size_t i = 0; i < compositeElements_.size(); i++)
		{
			L_ += compositeElements_[i]->getLength();
		}
	}

	/// @see IBaseHydraulicResistance::copy()
	virtual IBaseHydraulicResistance* copy() const;

	/// @see IBaseHydraulicResistance::getElement()
	IBaseHydraulicResistance* getElement(IBaseHydraulicResistance* Element);

	/// @see IBaseHydraulicResistance::addToComposite()
	void addToComposite(const std::vector< IBaseHydraulicResistance*>& elementsToComposite);

	/// @see IBaseHydraulicResistance::deleteFromComposite()
	void deleteFromComposite(const std::vector< IBaseHydraulicResistance*>& elementsToDelete);

	/// @see IBaseHydraulicResistance::calculateElement()
	void calculateElement();

	/// @see IBaseHydraulicResistance::setGeometry()
	void setGeometry(const std::vector<HSReal>& G);

	/// @see IBaseHydraulicResistance::setRe()
	void setRe(const HSReal Re);

	/// @see IBaseHydraulicResistance::setRou()
	void setRou(const HSReal rou);

	/// @see IBaseHydraulicResistance::getGeometry()
	void getGeometry(std::vector<HSReal>& G);

	/// @see IBaseHydraulicResistance::setAutocalc()
	void setAutocalc(const bool flag);

	/// @see IBaseHydraulicResistance::setHandleWarnings()
	void setHandleWarnings(const bool flag);

	/// @see IBaseHydraulicResistance::getFrictionPartCoeff()
	HSReal getFrictionPartCoeff();

	/// @see IBaseHydraulicResistance::getGeometryPartCoeff()
	HSReal getGeometryPartCoeff();

	/// @see IBaseHydraulicResistance::getRelFrictionCoeff()
	HSReal getRelFrictionCoeff();

	/// @see IBaseHydraulicResistance::getLocalResistanceCoeff()
	HSReal getLocalResistanceCoeff();

	/// @see IBaseHydraulicResistance::getLength()
	HSReal getLength();

	/// @see IBaseHydraulicResistance::setLength()
	virtual void setLength(const HSReal L);
};

