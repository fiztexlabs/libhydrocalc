#pragma once

namespace hydrocalc
{
	/// @brief Precision
#ifdef HR_DOUBLE_PRECISION_DEFINE
	typedef double real;
	const double DEF_MAX_CSI = 1.7e308;
#else
	typedef float real;
	const double DEF_MAX_CSI = 3.4e38;
#endif

	/*/// @brief Geometry types of hydraulic resistances
	enum class Type
	{
		/// @brief cylindrical geometry
		cylindrical = 0,
		/// @brief ring geometry
		ring = 1,
		/// @brief elliptic geometry
		elliptic = 2,
		/// @brief rectangular geometry
		rectangular = 3,
		/// @brief triangulare bundles
		triangular_bundle = 4,
		/// @brief rectangular bundles
		rectangular_bundle = 5
	};*/
}

namespace hydrocalc::settings
{
	/**
	* @defgroup Settings Settings of hydraulic resistance element
	* @{
	* @brief Settings of hydraulic resistance element
	*/

	/// @brief Behavior on unphysical value accidents
	enum class UnphysicalValueBehaviorMode
	{
		/// @brief Return truth (NaN or inf) values without warnings
		QuietTrue = 0,
		/// @brief Return truth (NaN or inf) values and rise warning
		WarnTrue = 1,
		/// @brief Stop execution and rise exception
		Stop = 2,
		/// @brief Compute unphysical value without warnings
		QuitCalc = 3,
		/// @brief Compute unphysical value an rise warning
		WarnCalc = 4
	};

	/// @brief Behavior on InvalidValue accidents
	enum class InvalidValuesBehaviorMode
	{
		/// @brief Return NaN value without warnings
		QuitNaN = 0,
		/// @brief Return NaN value and rise warning
		WarnNan = 1,
		/// @brief Stop execution and rise exception
		Stop = 2,
		/// @brief Do nothing
		NoCheck = 3
	};

	/// @brief Behavior on GeometryOutOfRange accidents
	enum class GeometryOutOfRangeBehaviorMode
	{
		/// @brief Return quiet NaN value
		QuietNaN = 0,
		/// @brief Return NaN value and rise warning
		WarnNaN= 1,
		/// @brief Do nothing
		NoCheck = 2,
		/// @brief Generate warning without stop execution
		Warn = 3,
		/// @brief Stop code execution
		Stop = 4,
		/// @brief Nearest neigboor valid value without warning
		NearestValidWithNoWarn = 5,
		/// @brief Nearest neigboor valid with warning
		NearestValidWithWarn = 6
	};

	/// @brief Behavior on FlowOutOfRange accidents
	enum class FlowOutOfRangeBehaviorMode
	{
		/// @brief Return quiet NaN value
		QuietNaN = 0,
		/// @brief Return NaN value and rise warning
		WarnNaN = 1,
		/// @brief Do nothing
		NoCheck = 2,
		/// @brief Generate warning without stop execution
		Warn = 3,
		/// @brief Stop code execution
		Stop = 4,
		/// @brief Nearest neigboor valid value without warning
		NearestValidWithNoWarn = 5,
		/// @brief Nearest neigboor valid with warning
		NearestValidWithWarn = 6
	};

	/// @brief Behavior on NonExistentFunction accidents
	enum class NonExistentFuncBehaviorMode
	{
		/// @brief Return quiet NaN value
		QuietNaN = 0,
		/// @brief Return NaN value and rise warning
		WarnNaN = 1,
		/// @brief Stop code execution
		Stop = 2
	};

	/// @brief Behavior on ReversedFlow accidents
	enum class ReversedFlowBehaviorMode
	{
		/// @brief Do nothing
		Quiet = 0,
		/// @brief Print warning message
		Warn = 1,
		/// @brief Return quiet NaN value
		QuietNaN = 2,
		/// @brief Return NaN value and rise warning
		WarnNaN = 3,
		/// @brief Stop code execution
		Stop = 4
	};

	/// @brief Behavior on InconsistentReynolds accidents in composite
	enum class InconsistentReynolds
	{
		/// @brief Do nothing
		Quiet = 0,
		/// @brief Print warning message
		Warn = 1,
		/// @brief Return quiet NaN value
		QuietNaN = 2,
		/// @brief Return NaN value and rise warning
		WarnNaN = 3,
		/// @brief Stop code execution
		Stop = 4
	};

	/// @brief Global librsp settings
	struct Settings
	{
		/// @brief Target tolerance for numerical methods
		real TargetTolerance = 1.e-3;

		/// @brief Behavior on InvalidValue accidents
		InvalidValuesBehaviorMode InvalidValueMode = InvalidValuesBehaviorMode::Stop;

		/// @brief Behavior on UnphysicalValue accidents
		UnphysicalValueBehaviorMode UnphysicalMode = UnphysicalValueBehaviorMode::Stop;

		/// @brief Behavior on GeometryOutOfRange accidents
		GeometryOutOfRangeBehaviorMode GeometryOutOfRangeMode = GeometryOutOfRangeBehaviorMode::Warn;

		/// @brief Behavior on FlowOutOfRange accidents
		FlowOutOfRangeBehaviorMode FlowOutOfRangeMode = FlowOutOfRangeBehaviorMode::Warn;

		/// @brief Behavior on NonExistentFunction accidents
		NonExistentFuncBehaviorMode NonExistentFunc = NonExistentFuncBehaviorMode::Stop;

		/// @brief Behavior on ReversedFlows accidents
		ReversedFlowBehaviorMode ReversedFlowMode = ReversedFlowBehaviorMode::Quiet;

		/// @brief Behavior on InconsistentReynolds accidents in composite
		InconsistentReynolds InconsistentReynoldsMode = InconsistentReynolds::Warn;

		/// @brief Enable or disable check inputs
		bool checkInputs = 1;

		/// @brief Maximum CSI, ocurred in specific points (such as Re = 0.0)
		real MAX_CSI = DEF_MAX_CSI;
	};

	/**
	* @}
	*/
}