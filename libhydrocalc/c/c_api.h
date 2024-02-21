#pragma once
#include <libhydrocalc/export.h>

/// @brief Precisions
#ifdef HR_DOUBLE_PRECISION_DEFINE
typedef double real;
#else
typedef float real;
#endif

/**
* @defgroup CAPI C application user interface
* @{
* @brief Wrappers for library methods
*/

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	/**
	* @brief Create hydraulic resistance with defined parameters
	* @details Wrapper for hydrocalc::createHydraulicResistance()
	* @param type: Type of element (from hydrocalc::info::elementsTypes)
	* @param Re: Reynolds number
	* @pram G: Vector of geometry parameters, correspond to specified element
	* @param G_size: Size of G
	* @param name: Element name
	* @param vis: Flow kinematic viscosity in the element [Pa*s]
	*/
	int LIBHYDROCALC_EXPORT createHydraulicResistance(
		const char* type,
		const real Re,
		const real* G,
		const int G_size,
		const char* name,
		const real vis
	);

	/**
	* @brief Create composite hydraulic resistance with defined parameters
	* @details Wrapper for hydrocalc::createComposite()
	* @param Re: Reynolds number
	* @pram G: Vector of geometry parameters, correspond to specified element
	* @param G_size: Size of G
	* @param elements: Elements to be added to composite
	* @param elements_size: Size of elements
	* @param name: Element name
	* @param vis: Flow kinematic viscosity in the element [Pa*s]
	* @param unique: Specifies, whether to store pointer, or independent copies of elements in
	* elements vector
	*/
	int LIBHYDROCALC_EXPORT createComposite(
		const real Re,
		const real* G,
		const int G_size,
		const int* elements,
		const int elements_size,
		const char* name,
		const real vis
	);

#ifdef __cplusplus
}
#endif // __cplusplus


/**
* @}
*/