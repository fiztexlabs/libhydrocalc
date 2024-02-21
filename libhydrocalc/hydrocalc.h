#pragma once
#include <libhydrocalc/hydraulic_resistance.h>
#include <libhydrocalc/settings.h>
#include <string>
#include <vector>

namespace hydrocalc
{
    /**
    * @defgroup Factories Factory methods
    * @{
    * @brief Methods for building hydraulic resistance elements
    */

    /**
    * @brief Create hydraulic resistance with defined parameters
    * @param type: Type of element (from hydrocalc::info::elementsTypes)
    * @param Re: Reynolds number
    * @pram G: Vector of geometry parameters, correspond to specified element
    * @param name: Element name
    * @param vis: Flow kinematic viscosity in the element [Pa*s]
    */
    HydraulicResistance *createHydraulicResistance(
        const std::string &type,
        const real Re,
        const std::vector<real> &G,
        const std::string &name = "",
        const real vis = 1.0);

    /**
    * @brief Create hydraulic resistance element with default elements
    * @param type: Type of element (from hydrocalc::info::elementsTypes)
    */
    HydraulicResistance* createHydraulicResistance(const std::string& type);

    /**
    * @brief Create composite hydraulic resistance with defined parameters
    * @param Re: Reynolds number
    * @pram G: Vector of geometry parameters, correspond to specified element
    * @param elements: Elements to be added to composite
    * @param name: Element name
    * @param vis: Flow kinematic viscosity in the element [Pa*s]
	* @param unique: Specifies, whether to store pointer, or independent copies of elements in
	* elements vector
    */
    HydraulicResistance* createComposite(
        const real Re,
        const std::vector<real>& G,
        const std::vector<HydraulicResistance*>& elements,
        const std::string& name = "",
        const real vis = 1.0,
        bool unique = 1);

    /**
    * @brief Create composite hydraulic resistance with default parameters
    */
    HydraulicResistance* createComposite();

    /**
    * @}
    */
}