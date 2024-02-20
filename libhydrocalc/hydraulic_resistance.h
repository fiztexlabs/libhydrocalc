#pragma once
#include <vector>
#include <string>
#include <libhydrocalc/settings.h>

namespace hydrocalc
{
	class ComplexResistance;
	class Composite;

	/**
	* @brief Interface HydraulicResistance define the C++ interface for calculation
	* of local hydraulic resistance element for C++.
	* @details Correlation from diagrams (I.E. Idelchik, 1992) were used
	* @author Ilya Konovalov
	* @date Released 17.02.2024
	* @todo Correct naming of internal objects
	*/
	class HydraulicResistance
	{
	protected:
		/**
		 * @brief Clone hydraulic resistance object
		 * @details For Composite elements also clone each element in composite
		 * @return HR: Pointer to clone of hydraulic resistance
		 */
		virtual HydraulicResistance *copy() const = 0;

		virtual void setExternalElementName(const std::string& name) = 0;

		friend ComplexResistance;
		friend Composite;

	public:
		virtual ~HydraulicResistance(){};

		/**
		* @brief Calculate hydraulic resistance element.
		* @details For HydraulicComposite element call evaluate() 
		* for each element in HydraulicComposite.
		* @throw ExceptionReversedFlow
		* @throw ExceptionGeometryOutOfRange
		* @throw ExceptionFlowOutOfRange
		*/
		virtual void evaluate() = 0;

		/**
		* @brief Set name to element.
		* @details By default element name generated as
		* ClassName + number.
		* @param name: Name of element
		*/
		virtual void setName(const std::string& name) = 0;

		/**
		 * @brief Get name of element.
		 * @details Each element name contains two parts:
		 *	- base part, which is the main name of element
		 *	- external part, which is define name of element, which contain THIS
		 * element as internal part
		 * So, the full element name defined as "[external part]{base part}".
		 * For example, default name for cylindrical friction element is
		 * "[]{CylindricalFriction 0}", because it's doesnt belong to any complex elements.
		 * @param[out] name: String name of element
		 */
		virtual void getName(std::string& name) = 0;

		/**
		 * @brief Get unique id of element
		 * @return id: Id of element
		 */
		virtual size_t getId() = 0;

		/**
		 * @brief Get number of element geometry type.
		 * @return Geometry type [-]:
		 *	- 0: Cylindrical channels
		 *	- 1: Ring channels
		 *	- 2: Elliptic channels
		 *	- 3: Triangular tube bundles
		 *	- 4: Rectangular tube bundles
		 *	- 5: Rectangular channels
		 * @todo actualize elements types
		 */
		virtual std::string getType() = 0;

		/**
		* @brief Set kinematic viscosity for hydraulic element.
		* @details Flow viscosity in the element is used for calculation
		* general hydraulic resistance coefficient, when some elements
		* combined into Composite. In this case calling setRe for composite must call
		* setRe for all elements in Composite with corresponding Re number for each element
		* @param vis: Flow kinematic viscosity in the element [Pa*s]
		*/
		virtual void setViscosity(const real vis) = 0;

		/**
		* @brief Get flow kinematic viscosity of element.
		* @return Kinematic viscosity [Pa*s]
		*/
		virtual real getViscosity() = 0;

		/**
		* @brief Set geometry characteristics to element.
		* @details Vector G may have variable size for each element.
		* @param G: Vector of geometry characteristics of the hydraulic resistance element:
		*	- for composite elment:
		*		- G[0]: Hydraulic diameter [m]. All hydraulic resistances will be reduced
		* to this hydraulic diameter
		*	- for cylindrical friction element:
		*		- G[0]: Roughness [m]
		*		- G[1]: Diameter of cross-section [m]
		*		- G[2]: Length of element [m]
		*	- for ring cylindrical friction element:
		*		- G[0]: Roughness [m]
		*		- G[1]: External diameter [m]
		*		- G[2]: Internal diameter [m]
		*		- G[3]: Excentric		  [m]
		*		- G[4]: Length of element [m]
		*	- for cylindrical bend element:
		*		- G[0]: Roughness [m]
		*		- G[1]: Diameter of cross-section [m]
		*		- G[2]: Bending radius [m]
		*		- G[3]: Bending angle [deg]; in the case, when G[3] < 0, bending angle
		* calculates as 360 - G[3]
		*		- G[4]: length of section before bend [m]; G[4] = 0 means, that
		* bend located after collector, however G[4] > 0 means, that straight section L = G[4]
		* located before bend.
		*	- for straight cylindrical diffuser element:
		*		- G[0]: Roughness [m]
		*		- G[1]: Hydraulic diameter of diffuser [m]
		*		- G[2]: Length of inlet section of diffuser [m]
		*		- G[3]: Length of diffuser [m]
		*		- G[4]: Length of outlet section of diffuser [m]
		*		- G[5]: Diameter of the outlet of diffuser[m]
		*		- G[6]: Hydraulic diameter of outlet section of diffuser [m]
		*		- G[7]: Angle of diffuser [deg]
		*	- for curve cylindrical diffuser element:
		*		- G[0]: Roughness [m]
		*		- G[1]: Hydraulic diameter of diffuser [m]
		*		- G[2]: Length of diffuser [m]
		*		- G[3]: Length of outlet section of diffuser [m]
		*		- G[4]: Hydraulic diameter of outlet section of diffuser [m]
		*	- for straight cylindrical confuser element:
		*		- G[0]: Roughness [m]
		*		- G[1]: Hydraulic diameter of confuser [m]
		*		- G[2]: Length of outlet section of confuser [m]
		*		- G[3]: Length of confuser [m]
		*		- G[4]: Hydraulic diameter of inlet section of confuser [m]
		*		- G[5]: Angle of confuser [deg]
		*	- for curve cylindrical confuser element:
		*		- G[0]: Roughness [m]
		*		- G[1]: Hydraulic diameter of confuser [m]
		*		- G[2]: Length of outlet section of confuser [m]
		*		- G[3]: Length of confuser [m]
		*		- G[4]: Hydraulic diameter of outlet section of confuser [m]
		*		- G[5]: Curve radius [m]
		*	- for unexpected size changes with sharp edges:
		*		- G[0]: Roughness [m]
		*		- G[1]: Diameter 1 [m]
		*		- G[2]: Diameter 2 [m]
		* @throw ExceptionInvalidValue
		* @throw ExceptionGeometryOutOfRange
		*/
		virtual void setGeometry(const std::vector<real> &G) = 0;

		/**
		* @brief Put vector, contains geometry characteristics of element to G.
		* @param[out] G: vector of geometry characteristics:
		*	- for composite elment:
		*		- G[0]: Roughness [m]
		*		- G[1]: Hydraulic diameter [m]
		*	- for cylindrical friction element:
		*		- G[0]: Roughness [m]
		*		- G[1]: Diameter of cross-section [m]
		*		- G[2]: Length of element [m]
		*		- G[3]: Cross-section area, [m2]
		*	- for ring cylindrical friction element:
		*		- G[0]: Roughness [m]
		*		- G[1]: External diameter [m]
		*		- G[2]: Internal diameter [m]
		*		- G[3]: Excentric		  [m]
		*		- G[4]: Length of element [m]
		*		- G[5]: Cross-section area, [m2]
		*	- for cylindrical bend element:
		*		- G[0]: Roughness [m]
		*		- G[1]: Diameter of cross-section [m]
		*		- G[2]: Bending radius [m]
		*		- G[3]: Bending angle [deg]; in the case, when G[3] < 0, bending angle
		* calculates as 360 - G[3]
		*		- G[4]: Length of section before bend [m]; G[4] = 0 means, that
		* bend located after collector, however G[4] > 0 means, that straight section L = G[4]
		* located before bend
		*		- G[5]: Cross-section area, [m2]
		*	- for straight cylindrical diffuser element:
		*		- G[0]: Roughness [m]
		*		- G[1]: Hydraulic diameter of diffuser [m]
		*		- G[2]: Length of inlet section of diffuser [m]
		*		- G[3]: Length of diffuser [m]
		*		- G[4]: Length of outlet section of diffuser [m]
		*		- G[5]: Diameter of the outlet of diffuser[m]
		*		- G[6]: Hydraulic diameter of outlet section of diffuser [m]
		*		- G[7]: Angle of diffuser [deg]
		*		- G[8]: Cross-section area of diffuser inlet, [m2]
		*		- G[9]: Cross-section area of diffuser outlet, [m2]
		*	- for curve cylindrical diffuser element:
		*		- G[0]: Roughness [m]
		*		- G[1]: Hydraulic diameter of diffuser [m]
		*		- G[2]: Length of diffuser [m]
		*		- G[3]: Length of outlet section of diffuser [m]
		*		- G[4]: Hydraulic diameter of outlet section of diffuser [m]
		*		- G[5]: Cross-section area of diffuser inlet, [m2]
		*		- G[6]: Cross-section area of diffuser outlet, [m2]
		*	- for straight cylindrical confuser element:
		*		- G[0]: Roughness [m]
		*		- G[1]: Hydraulic diameter of confuser [m]
		*		- G[2]: Length of outlet section of confuser [m]
		*		- G[3]: Length of diffuser [m]
		*		- G[4]: Hydraulic diameter of inlet section of confuser [m]
		*		- G[5]: Cross-section area of confuser inlet, [m2]
		*		- G[6]: Cross-section area of confuser outlet, [m2]
		*	- for curve cylindrical confuser element:
		*		- G[0]: Roughness [m]
		*		- G[1]: Hydraulic diameter of confuser [m]
		*		- G[2]: Length of outlet section of confuser [m]
		*		- G[3]: Length of diffuser [m]
		*		- G[4]: Hydraulic diameter of outlet section of confuser [m]
		*		- G[5]: Curve radius of confuser [m]
		*		- G[6]: Cross-section area of confuser inlet, [m2]
		*		- G[7]: Cross-section area of confuser outlet, [m2]
		*	- forunexpected size changes with sharp edges:
		*		- G[0]: Roughness [m]
		*		- G[1]: Hydraulic diameter [m]
		*		- G[2]: Diameter 1 [m]
		*		- G[3]: Diameter 2 [m]
		*		- G[4]: Cross-section area 1 [m2]
		*		- G[5]: Cross-section area 2 [m2]
		*/
		virtual void getGeometry(std::vector<real>& G) = 0;

		/**
		* @brief Set Reynolds number of hydraulic resistance element.
		* @details Negative Re correspond to negative flow, in elements with direction
		* independent geometry Re computse as @f$ Re = |Re| @f$. Otherwise element create correspond
		* element (or set of elements) for negative flow and calculate it.
		* In HydraulicComposite element for each element in HydraulicComposite Re
		* calculated as @f$ Re_i=Re\frac{(D_0)_i}{D_0}@f$, where @f$i@f$ - index of element.
		* @param Re: Reynolds number
		* @see HydraulicComposite
		*/
		virtual void setRe(const real Re) = 0;

		/**
		 * @brief Get Reynolds number for hydraulic resistance element.
		 * @return Reynolds number [-]
		 */
		virtual real getRe() = 0;

		/**
		 * @brief Set roughness of hydraulic resistance element.
		 * @details In HydraulicComposite element set roughness for all elements in composite.
		 * @param rou: Roughness [m]
		 * @see HydraulicComposite
		 */
		virtual void setRou(const real rou) = 0;

		/**
		 * @brief Get roughness.
		 * @return Roughness [m]
		 */
		virtual real getRou() = 0;

		/**
		 * @brief Set legth of element
		 * @details Length of element use in network calculations. If length = 0
		 * (e.a. for friction elements), return value 1e-6 [m]. For HydraulicComposite
		 * return summ of length of components.
		 *	- for CylindricalFriction set length of channel;
		 *	- for CylindricalBend set length of bend section;
		 *	- for CurveCylindricalConfuser set length of confuser;
		 *	- for CurveCylindricalDiffuser set length of diffuser;
		 *	- for StraightCylindricalConfuser set length of confuser;
		 *	- for StraightCylindricalDiffuser set length of diffuser;
		 *	- for SharpUnexpectedSizeChange set 1e-6 m;
		 * @param L: Length of element [m]
		 */
		virtual void setLength(const real L) = 0;

		/**
		 * @brief Get legth of element
		 * @details Length of element use in network calculations. If length = 0
		 * (e.a. for friction elements), return value 1e-6 [m]. For HydraulicComposite
		 * return summ of length of components.
		 *	- for CylindricalFriction return length of channel;
		 *	- for CylindricalBend return length of bend section;
		 *	- for CurveCylindricalConfuser return length of confuser;
		 *	- for CurveCylindricalDiffuser return length of diffuser;
		 *	- for StraightCylindricalConfuser return length of confuser;
		 *	- for StraightCylindricalDiffuser return length of diffuser;
		 *	- for SharpUnexpectedSizeChange return 1e-6 m;
		 * @return L: Length of element [m]
		 */
		virtual real getLength() = 0;

		/**
		 * @brief Get hydraulic diameter of hydraulic resistance element.
		 * @return Hydraulic diameter D0 [m]
		 */
		virtual real getHydraulicDiameter() = 0;

		/**
		* @brief Get the friction part of loss coefficient of element.
		* @details Function return friction part of the loss coefficient
		* of the element, so friction part of loss for this element calculated as
		* @f$\Delta P=\xi_\lambda\big(\frac{\rho w^2}{2}\big)@f$.
		* For HydraulicComposite element this function return reduced friction part of loss coefficient calculated as
		* @f$ \xi_\lambda=\displaystyle\sum_{i=0}^{n} \bigg[(\xi_\lambda)_i\bigg(\frac{(D_0)_i}{D_0}\bigg)^4\bigg] @f$,
		* where @f$n@f$ - number of elements in HydraulicComposite. With each calling from HydraulicComposite function also call
		* evaluate() to check actual state of each element in composit, for example,
		* if anything parameter in element in composite was changed like this:
		* @code
		* //C++
		* element->setRe(1.e6);
		* @endcode
		* @return Friction part of loss coefficient @f$ \xi_\lambda @f$ [-]
		* @see getHydraulicDiameter()
		* @see getGeometry()
		* @see HydraulicComposite
		*/
		virtual real getFrictionPartCoeff() = 0;

		/**
		* @brief Get the geometry part of loss coefficient of element.
		* @details Function return geometry part of th loss coefficient
		* of the element. For friction elements @f$ \xi_l = 0.0 @f$.
		* For HydraulicComposite element this function return reduced geometry part of loss coefficient calculated as
		* @f$ \xi_l=\displaystyle\sum_{i=0}^{n} \bigg[(\xi_l)_i\bigg(\frac{(D_0)_i}{D_0}\bigg)^4\bigg] @f$
		* where @f$n@f$ - number of elements in HydraulicComposite. With each calling from HydraulicComposite function also call evaluate()
		* to check actual state of each element in composit, for example, if anything parameter in element in
		* composite was changed like this:
		* @code
		* //C++
		* element->setRe(1.e6);
		* @endcode
		* @return Geometry part of loss coefficient @f$ \xi_l @f$ [-]
		* @see HydraulicComposite
		*/
		virtual real getGeometryPartCoeff() = 0;

		/**
		* @brief Get relative friction loss coefficient of element.
		* @details Function return relative friction loss coefficient,
		* so friction part of loss for this element calculated as
		* @f$ \Delta P =\lambda\big(\frac{L}{D_0}\big)\big(\frac{\rho w^2}{2}\big) @f$,
		* where @f$ D_0 @f$ is hydraulic diameter and @f$ L @f$ - is length of element.
		* For HydraulicComposite element this function return averaged friction loss coefficient calculated as
		* @f$\lambda=\frac{1}{n}\displaystyle\sum_{i=0}^{n} \lambda_i\bigg(\frac{(D_0)_i}{D_0}\bigg)^3 @f$,
		* where @f$ n @f$ - number of	elements in HydraulicComposite. With each calling from HydraulicComposite function also call
		* evaluate() to check actual state of each element in composit, for example, if anything
		* parameter in element in composite was changed like this:
		* @code
		* //C++
		* element->setRe(1.e6);
		* @endcode
		* @return Relative friction loss coefficient [-]
		* @see getHydraulicDiameter()
		* @see getGeometry()
		* @see HydraulicComposite
		*/
		virtual real getRelFrictionCoeff() = 0;

		/**
		* @brief Get value of local resistance coefficient.
		* @details For lonley friction defined as @f$ \xi = \xi_\lambda = \lambda\big(\frac{L}{D_0}\big) @f$,
		* @f$ L @f$ - length of element, so for friction element getFrictionPartCoeff() = getLocalResistanceCoeff().
		* Othervise @f$ \xi = \xi_l + \xi_\lambda + excess @f$, @f$ \xi_l @f$ - local resistance part,
		* @f$ \xi_\lambda @f$ - local friction part, @f$ excess @f$ - part of other effects.
		* For HydraulicComposite element this function return reduced local resistance coefficient	calculated as
		* @f$ \xi=\displaystyle\sum_{i=0}^{n} \bigg[(\xi)_i\bigg(\frac{(D_0)_i}{D_0}\bigg)^4\bigg] @f$
		* where @f$ n @f$ - number of elements in HydraulicComposite. With each calling from HydraulicComposite function also call
		* evaluate() to check actual state of each element in composit, for example, if anything parameter
		* in element in HydraulicComposite was changed like this:
		* @code
		* //C++
		* element->setRe(1.e6);
		* @endcode
		* @return Local resistance coefficient CSI [-]
		* @see HydraulicComposite
		*/
		virtual real getLocalResistanceCoeff() = 0;

		/**
		 * @brief Get value of cross-section area of the element.
		 * @return A [m2]
		 */
		virtual real getCrossSectionArea() = 0;

		/**
		* @brief Get name of correlations diagram.
		* @details For HydraulicComposite element return string, contains diagrams, wich was used
		* for calculation each of element in HydraulicComposite.
		* @param[out] diagram: String number of diagram, which was used for calculations
		* @see HydraulicComposite
		*/
		virtual void getDiagram(std::string &diagram) = 0;
	};
}

// #ifdef __cplusplus
// extern "C"
// {
// #endif

// 	/**
// 	* @brief Fabrication method for cylindrical friction element
// 	* @details Automatically check inputs, initialize fields and calculate element
// 	(if autocalc = 1).
// 	* This elemnt has a direction independent
// 	* geometry, so Re computse as @f$ Re=|Re| @f$.
// 	* @param name: Name of element
// 	* @param Re: Reynolds number, negative value correspond to negative flow
// 	* @param G: Vector of geometry characteristics of friction element:
// 	*	- G[0]: Roughness [m]
// 	*	- G[1]: Diameter of cross-section [m]
// 	*	- G[2]: Length of element [m]
// 	* @return Pointer to hydraulic resistance (HydraulicResistance) object
// 	* @see CylindricalFriction
// 	*/
// 	__HSAPI HydraulicResistance *__HSAPIENTRY CylindricalFrictionFab(const std::string &name, const real Re, const std::vector<real> &G);

// 	/**
// 	* @brief Fabrication method for ring cylindrical friction element
// 	* @details Automatically check inputs, initialize fields and calculate element
// 	(if autocalc = 1).
// 	* This elemnt has a direction independent
// 	* geometry, so Re computse as @f$ Re=|Re| @f$.
// 	* @param name: Name of element
// 	* @param Re: Reynolds number, negative value correspond to negative flow
// 	* @param G: Vector of geometry characteristics of friction element:
// 	*		- G[0]: Roughness [m]
// 	*		- G[1]: External diameter [m]
// 	*		- G[2]: Internal diameter [m]
// 	*		- G[3]: Excentric		  [m]
// 	*		- G[4]: Length of element [m]
// 	* @return Pointer to hydraulic resistance (HydraulicResistance) object
// 	* @see CylindricalFriction
// 	*/
// 	__HSAPI HydraulicResistance *__HSAPIENTRY RingFrictionFab(const std::string &name, const real Re, const std::vector<real> &G);

// 	/**
// 	* @brief Fabrication method for cylindrical bend element
// 	* @details Automatically check inputs, initialize fields and calculate element
// 	(if autocalc = 1).
// 	* This elemnt has a direction independent geometry, so Re computes as @f$ Re=|Re| @f$.
// 	* @param name: Name of element
// 	* @param Re: Reynolds number, negative value correspond to negative flow
// 	* @param G: Vector of geometry characteristics of bend element:
// 	*	- G[0]: Roughness [m]
// 	*	- G[1]: Diameter of cross-section [m]
// 	*	- G[2]: Bending radius [m]
// 	*	- G[3]: Bending angle [deg]; in the case, when G[3] < 0, bending angle
// 	calculates as 360 - G[3]
// 	*	- G[4]: Length of section before bend [m]; G[4] = 0 means, that
// 	bend located after collector, however G[4] > 0 means, that straight section L = G[4]
// 	located before bend
// 	* @return Pointer to hydraulic resistance (HydraulicResistance) object
// 	* @see CylindricalBend
// 	*/
// 	__HSAPI HydraulicResistance *__HSAPIENTRY CylindricalBendFab(const std::string &name, const real Re, const std::vector<real> &G);

// 	/**
// 	* @brief Fabrication method for cylindrical bend with niche element
// 	* @details Automatically check inputs, initialize fields and calculate element
// 	(if autocalc = 1).
// 	* This elemnt has a direction independent geometry, so Re computes as @f$ Re=|Re| @f$.
// 	* @param name: Name of element
// 	* @param Re: Reynolds number, negative value correspond to negative flow
// 	* @param G: Vector of geometry characteristics of bend element:
// 	*	- G[0]: Roughness [m]
// 	*	- G[1]: Diameter of cross-section [m]
// 	*	- G[2]: Bending radius [m]
// 	*	- G[3]: Bending angle [deg]; in the case, when G[3] < 0, bending angle
// 	calculates as 360 - G[3]
// 	*	- G[4]: Length of section before bend [m]; G[4] = 0 means, that
// 	bend located after collector, however G[4] > 0 means, that straight section L = G[4]
// 	located before bend
// 	* @return Pointer to hydraulic resistance (HydraulicResistance) object
// 	* @see CylindricalBendNiche
// 	*/
// 	__HSAPI HydraulicResistance *__HSAPIENTRY CylindricalBendNicheFab(const std::string &name, const real Re, const std::vector<real> &G);

// 	/**
// 	 * @brief Fabrication method for straight cylindrical diffuser element
// 	 * @details Automatically check inputs, initialize fields and calculate element
// 	 * (if autocalc = 1).
// 	 * This elemnt has a direction dependent geometry, so in the case of negative flow @f$ (Re < 0) @f$,
// 	 * if diagram 5-9 used for calculation, element create StraightCylindricalConfuser and
// 	 * SharpUnexpectedSizeChange elements and calculate it. Othervise for @f$ (Re < 0) @f$ created only
// 	 * StraightCylindricalConfuser.
// 	 * @param name: String name of element
// 	 * @param Re: Reynolds number. Negative value correspond to negative flow
// 	 * @param G: Vector of geometry characteristics of the bend element:
// 	 *	- G[0]: Roughness [m]
// 	 *	- G[1]: Hydraulic diameter of diffuser [m]
// 	 *	- G[2]: Turbulence intensity, @f$ I=\frac{w_0}{w_max} @f$. If @f$ I=1 @f$
// 	 * velocity profile before diffuser is straight and influece of hit coefficient @f$ k_d @f$
// 	 * doesn't matter. Otherwise @f$ k_d @f$ should be taken into account with diagram 5-2
// 	 *	- G[3]: Length of inlet section of diffuser [m]
// 	 *	- G[4]: Length of diffuser [m]
// 	 *	- G[5]: Length of outlet section of diffuser [m]
// 	 *	- G[6]: Diameter of the outlet of diffuser[m]
// 	 *	- G[7]: Hydraulic diameter of outlet section of diffuser [m]
// 	 *	- G[8]: Angle of diffuser [deg]
// 	 * @return Pointer to hydraulic resistance (HydraulicResistance) object
// 	 * @see StraightCylindricalDiffuser
// 	 */
// 	__HSAPI HydraulicResistance *__HSAPIENTRY StraightCylindricalDiffuserFab(const std::string &name, const real Re, const std::vector<real> &G);

// 	/**
// 	* @brief Fabrication method for straight cylindrical confuser element
// 	* @details Automatically check inputs, initialize fields and calculate element
// 	(if autocalc = 1).
// 	* This elemnt has a direction dependent geometry, so in the case of negative flow @f$ (Re < 0) @f$
// 	* element create StraightCylindricalDiffuser in function createDiffuser and calculate it.
// 	* @param name: String name of element
// 	* @param Re: Reynolds number. Negative value correspond to negative flow
// 	* @param G: Vector of geometry characteristics of the bend element:
// 	*	- G[0]: Roughness [m]
// 	*	- G[1]: Hydraulic diameter of confuser [m]
// 	*	- G[2]: Length of outlet section of confuser [m]
// 	*	- G[3]: Length of confuser [m]
// 	*	- G[4]: Hydraulic diameter of outlet section of confuser [m]
// 	*	- G[5]: Angle of confuser [deg]
// 	* @return Pointer to hydraulic resistance (HydraulicResistance) object
// 	* @see StraightCylindricalConfuser
// 	*/
// 	__HSAPI HydraulicResistance *__HSAPIENTRY StraightCylindricalConfuserFab(const std::string &name, const real Re, const std::vector<real> &G);

// 	/**
// 	* @brief Fabrication method for curve cylindrical diffuser element
// 	* @details Automatically check inputs, initialize fields and calculate element
// 	(if autocalc = 1).
// 	* This elemnt has a direction dependent geometry, so in the case of negative flow @f$ (Re < 0) @f$
// 	* element create StraightCylindricalConfuser with createConfuser() and calculate it.
// 	* @param name: String name of element
// 	* @param Re: Reynolds number. Negative value correspond to negative flow
// 	* @param G: Vector of geometry characteristics of the bend element:
// 	*	- G[0]: Roughness [m]
// 	*	- G[1]: Hydraulic diameter of diffuser [m]
// 	*	- G[2]: Length of diffuser [m]
// 	*	- G[3]: Length of outlet section of diffuser [m]
// 	*	- G[4]: Hydraulic diameter of outlet section of diffuser [m]
// 	*	- G[5]: Curve radius [m]
// 	* @return Pointer to hydraulic resistance (HydraulicResistance) object
// 	* @see CurveCylindricalDiffuser
// 	*/
// 	__HSAPI HydraulicResistance *__HSAPIENTRY CurveCylindricalDiffuserFab(const std::string &name, const real Re, const std::vector<real> &G);

// 	/**
// 	* @brief Fabrication method for curve cylindrical confuser element
// 	* @details Automatically check inputs, initialize fields and calculate element
// 	(if autocalc = 1).
// 	* This elemnt has a direction dependent geometry, so in the case of negative flow @f$ (Re < 0) @f$
// 	* element create CurveCylindricalDiffuser in function createDiffuser and calculate it.
// 	* @param name: String name of element
// 	* @param Re: Reynolds number. Negative value correspond to negative flow
// 	* @param G: Vector of geometry characteristics of the bend element:
// 	*	- G[0]: Roughness [m]
// 	*	- G[1]: Hydraulic diameter of confuser [m]
// 	*	- G[2]: Length of outlet section of confuser [m]
// 	*	- G[3]: Length of confuser [m]
// 	*	- G[4]: Hydraulic diameter of outlet section of confuser [m]
// 	*	- G[5]: Curve radius [m]
// 	* @return Pointer to hydraulic resistance (HydraulicResistance) object
// 	* @see CurveCylindricalConfuser
// 	*/
// 	__HSAPI HydraulicResistance *__HSAPIENTRY CurveCylindricalConfuserFab(const std::string &name, const real Re, const std::vector<real> &G);

// 	/**
// 	* @brief Fabrication method for unexpected size change with sharp edges
// 	* @details Automatically check inputs, initialize fields and calculate element
// 	(if autocalc = 1).
// 	* This elemnt has a direction dependent geometry, so in the case of negative flow @f$ (Re < 0) @f$
// 	* if element is expansion, than it turns to constriction and vice versa. Also if @f$ D_0 < D_1 @f$
// 	* @param name: String name of element
// 	* @param Re: Reynolds number, negative value correspond to negative flow
// 	* @param G: Vector of geometry characteristics of element:
// 	*	- G[0]: Roughness [m]
// 	*	- G[1]: Diameter 1 [m] (expansion: smaller diameter, constriction: bigger diameter)
// 	*	- G[2]: Diameter 2 [m] (expansion: bigger diameter, constriction: smaller diameter)
// 	* @return Pointer to hydraulic resistance (HydraulicResistance) object
// 	* @see SharpUnexpectedSizeChange
// 	*/
// 	__HSAPI HydraulicResistance *__HSAPIENTRY SharpUnexpectedSizeChangeFab(const std::string &name, const real Re, const std::vector<real> &G);

// 	/**
// 	* @brief Fabrication method for composite element
// 	* @details Automatically check inputs, initialize fields and calculate element
// 	(if autocalc = 1)
// 	* @param name: Name of element
// 	* @param G: Vector of geometry characteristics of element:
// 	*	- G[0]: Hydraulic diameter [m]. All hydraulic resistances will be reduced
// 	* to this hydraulic diameter.
// 	* @param ptrCompositeElements: Vector of objects to include in composite
// 	* @return Pointer to hydraulic resistance (HydraulicResistance) object
// 	* @see HydraulicComposite
// 	*/
// 	__HSAPI HydraulicResistance *__HSAPIENTRY CompositeFab(const std::string &name, const std::vector<real> &G, const std::vector<HydraulicResistance *> &ptrCompositeElements);

// #ifdef __cplusplus
// }
// #endif
