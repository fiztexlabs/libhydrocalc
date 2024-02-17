#pragma once
#include <libhydrocalc/hydraulic_resistance_base.h>
#include <string>

namespace hydrocalc
{
	/**
	* @brief Friction base class
	* @author Ilya Konovalov
	* @date Released 17.02.2024
	*/
	class Friction :
		public HydraulicResistanceBase
	{
	protected:
		/// @brief Length of element [m]
		real L_ = 0.0;
	public:
		/**
		* @brief Default constructor
		*/
		Friction() :
			HydraulicResistanceBase()
		{};

		/**
		* @brief Recommended constructor
		* @details Initialize main variables, turn element counter and set id to element
		* @param name: String name of element
		* @param Re: Reynolds number
		* @param D0: Hydraulic diameter [m]
		* @param A: Cross-section area [m2]
		* @param rou: Roughness [m]
		*/
		Friction(
			const std::string& name,
			const real Re,
			const real D0,
			const real rou,
			const real A,
			const real L,
			const Type type) :
			HydraulicResistanceBase(name, Re, D0, rou, A, type),
			L_(L)
		{};

		virtual ~Friction() {};
	};
}


