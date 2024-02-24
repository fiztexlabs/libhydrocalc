#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <src/wrappers/hydraulic_resistance.h>
#include <src/opaque_types.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <libhydrocalc/hydrocalc.h>
#include <libhydrocalc/hydraulic_resistance_base.h>

namespace hr = hydrocalc;

/// @brief Overload of hr::createHydraulicResistance for python
std::unique_ptr<hr::HydraulicResistance> hydraulic_resistance(
	const std::string& type,
	const hr::real Re,
	const std::vector<hr::real>& G,
	const std::string& name = "",
	const hr::real vis = 1.0)
{
    return std::unique_ptr<hr::HydraulicResistance>(hr::createHydraulicResistance(
		type,
		Re,
		G,
		name,
		vis
	));
}

/// @brief Overload of hr::createHydraulicResistance for python
std::unique_ptr<hr::HydraulicResistance> hydraulic_composite(
	const hr::real Re,
	const std::vector<hr::real>& G,
	const std::vector<hr::HydraulicResistance*>& elements,
	const std::string& name = "",
	const hr::real vis = 1.0,
	bool unique = 1)
{
	return std::unique_ptr<hr::HydraulicResistance>(hr::createComposite(
		Re,
		G,
		elements,
		name,
		vis,
		unique
	));
}

namespace py = pybind11;

PYBIND11_MODULE(hydrocalc, m)
{
	m.doc() = R"pbdoc(
        Real substance properties library
        -----------------------

        .. currentmodule:: rsp

        .. autosummary::
           :toctree: _generate

           Substance
           createSubstance
           callProperty
    )pbdoc";

	
	py::bind_vector<std::vector<std::string>>(m, "VectorString", R"pbdoc(
			Lists of strings
		)pbdoc");

	py::class_<hr::HydraulicResistance, py_api::HydraulicResistance>(m, "HydraulicResistance")
		.def(py::init<>(), R"pbdoc(
            Base hydraulic resistance class
            -----------------------
            )pbdoc")
		.def("evaluate", &hr::HydraulicResistance::evaluate, R"pbdoc(
             evaluate element
            )pbdoc")
		.def("setName", &hr::HydraulicResistance::setName, R"pbdoc(
             Set base name of element
             Arguments:
			 	name: Base element name
            )pbdoc",
			py::arg("name"))
		.def("getName", &hr::HydraulicResistance::getName, R"pbdoc(
             Get element name
             Return:
			 	Full element name
            )pbdoc")
		.def("getId", &hr::HydraulicResistance::getId, R"pbdoc(
             Get element Id
             Return:
			 	Element Id
            )pbdoc")
		.def("getType", &hr::HydraulicResistance::getType, R"pbdoc(
             Get element type
             Return:
			 	Type of element
            )pbdoc")
		.def("setViscosity", &hr::HydraulicResistance::setViscosity, R"pbdoc(
             Set kinematic viscosity
             Arguments:
			 	vis: Kinematic viscosity
            )pbdoc",
			py::arg("vis"))
		.def("getViscosity", &hr::HydraulicResistance::getViscosity, R"pbdoc(
             Get element viscosity
             Return:
			 	Kinematic viscosity
            )pbdoc")
		.def("setGeometry", &hr::HydraulicResistance::setGeometry, R"pbdoc(
             Set vector of geometry characteristics for element
             Arguments:
			 	G: Vector of geometry characteristics
            )pbdoc",
			py::arg("G"))
		.def("getGeometry", &hr::HydraulicResistance::getGeometry, R"pbdoc(
             Get vector of element geometry characteristics
             Arguments:
			 	G[out]: Vector of geometry characteristics
            )pbdoc",
			py::arg("G"))
		.def("setRe", &hr::HydraulicResistance::setRe, R"pbdoc(
             Set Reynolds number of hydraulic resistance element. Positive Re corrspond to
			 direct flow, however negative Re - to reversed flow
             Arguments:
			 	Re: Reynolds number
            )pbdoc",
			py::arg("Re"))
		.def("getRe", &hr::HydraulicResistance::getRe, R"pbdoc(
             Get element Reynolds number
             Return:
			 	Element Reynolds number
            )pbdoc")
		.def("setRou", &hr::HydraulicResistance::setRou, R"pbdoc(
             Set roughness of hydraulic resistance element.
             Arguments:
			 	rou: Roughness
            )pbdoc",
			py::arg("rou"))
		.def("getRou", &hr::HydraulicResistance::getRou, R"pbdoc(
             Get roughness
             Return:
			 	Element roughness
            )pbdoc")
		.def("setLength", &hr::HydraulicResistance::setLength, R"pbdoc(
             Set element length.
             Arguments:
			 	L: Element length
            )pbdoc",
			py::arg("L"))
		.def("getLength", &hr::HydraulicResistance::getLength, R"pbdoc(
             Get element length
             Return:
			 	Element length
            )pbdoc")
		.def("getHydraulicDiameter", &hr::HydraulicResistance::getHydraulicDiameter, R"pbdoc(
             Get element hydraulic diameter
             Return:
			 	Element hydraulic diameter
            )pbdoc")
		.def("getFrictionPartCoeff", &hr::HydraulicResistance::getFrictionPartCoeff, R"pbdoc(
             Get friction part of hydraulic resistance coefficient
             Return:
			 	Friction part of hydraulic resistance coefficient
            )pbdoc")
		.def("getGeometryPartCoeff", &hr::HydraulicResistance::getGeometryPartCoeff, R"pbdoc(
             Get geometry part of hydraulic resistance coefficient
             Return:
			 	Geometry part of hydraulic resistance coefficient
            )pbdoc")
		.def("getRelFrictionCoeff", &hr::HydraulicResistance::getRelFrictionCoeff, R"pbdoc(
             Get relative friction coefficient in the elemnt
             Return:
			 	Relative friction coefficient in the elemnt
            )pbdoc")
		.def("getLocalResistanceCoeff", &hr::HydraulicResistance::getLocalResistanceCoeff, R"pbdoc(
             Get local resistance coefficient of element
             Return:
			 	Local resistance coefficient of element
            )pbdoc")
		.def("getCrossSectionArea", &hr::HydraulicResistance::getCrossSectionArea, R"pbdoc(
             Get element cross-section area
             Return:
			 	Element cross-section area
            )pbdoc")
		.def("getDiagram", &hr::HydraulicResistance::getDiagram, R"pbdoc(
             Get number of diagram (or correlation source) for element calculations
             Return:
			 	Calculation diagram
            )pbdoc");

	m.def("createHydraulicResistance", &hydraulic_resistance, R"pbdoc(
             Create hydraulic resistance element
             Arguments:
				 type: Element type
				 Re: Reynolds number
			     G: Vector of geometry characteristics
                 name: Element name
                 vis: Element kinematic viscosity
             )pbdoc",
		  py::arg("type"),
		  py::arg("Re"),
		  py::arg("G"),
		  py::arg("name"),
		  py::arg("vis"),
          py::return_value_policy::reference);

	m.def("createComposite", &hydraulic_composite, R"pbdoc(
             Create hydraulic composite element
             Arguments:
				 Re: Reynolds number
			     G: Vector of geometry characteristics
			     elements: Vector of elements
                 name: Element name
                 vis: Element kinematic viscosity
                 unique: Specifies, whether to store pointer, or independent copies of elements in elements vector
             )pbdoc",
		py::arg("Re"),
		py::arg("G"),
		py::arg("elements"),
		py::arg("name"),
		py::arg("vis"),
		py::arg("unique"),
		py::return_value_policy::reference);

	
	/*auto info = m.def_submodule("info", R"pbdoc(
			Methods for getting library and substances information
		)pbdoc");
	
	py::bind_map<rsp::info::InfoTable>(info, "InfoTable", R"pbdoc(
			Information table. Keys represent evaluations modes.
		)pbdoc");

	py::class_<hr::HydraulicResistanceInfo>(info, "SubstanceInfo")
		.def(py::init<>(), R"pbdoc(
            Container with information about substance. Store available 
			calculation modes (arguments) and list of functions, which is 
			available for each calculation mode.
            -----------------------
            )pbdoc")
		.def(py::init<const hr::HydraulicResistanceInfo &>(), R"pbdoc(
            Copy constructor for SubstanceInfo
            -----------------------
            )pbdoc")
		.def("getInfoTables", &hr::HydraulicResistanceInfo::getInfoTables, R"pbdoc(
            Get information tables. Available calculation modes (info::argument_literals for this 
			substance) are stored in tables keys. Table values - lists of available properties literals, 
			or its aliases (descriptions).
            Arguments:
				functions[out]: Table, in which values - lists of available properties for 
				each calculation mode. This values 
				may be used as property literals, when calling callProperty
				aliases[out]: Table, in which values - lists of available properties aliases for 
				each calculation mode (info::alias for this substance)
            )pbdoc",
			py::arg("functions"),
			py::arg("aliases"))
		.def("getConstantsLists", &hr::HydraulicResistanceInfo::getConstantsLists, R"pbdoc(
            Get list of functions for getting constants and its descriptions (aliases)
            Arguments:
				getters[out]: List of functions names, which may be used as property literal
				aliases[out]: List of corresponding functions description
            )pbdoc",
			py::arg("getters"),
			py::arg("aliases"))
		.def("getCalcModesInfo", &hr::HydraulicResistanceInfo::getCalcModesInfo, R"pbdoc(
            Get list of available calculation modes
            Arguments:
				modes[out]: List of modes. Modes may be used as arguments literals, 
				when calling callProperty
            )pbdoc",
			py::arg("modes"))
		.def("getModeDecomposition", py::overload_cast<rsp::info::InfoTable&>(&hr::HydraulicResistanceInfo::getModeDecomposition, py::const_), R"pbdoc(
            Decomposite mode literals to property literals. E.g. decompose "DT" arguments to "D" and "T".
            Arguments:
				prop_lit[out]:  Decomosition table of property literals, keys - modes
            )pbdoc",
			py::arg("prop_lit"))
		.def("getModeDecomposition", py::overload_cast<const std::string&, std::vector<std::string>&>(&hr::HydraulicResistanceInfo::getModeDecomposition, py::const_), R"pbdoc(
            Get list of available calculation modes
            Arguments:
				mode: Mode literals (property literals)
				prop_lit[out]: Vector of corresponding property literals
            )pbdoc",
			py::arg("mode"),
			py::arg("prop_lit")
			);
	info.def("getSubstanceInfo", &rsp::getSubstanceInfo, R"pbdoc(
            Get info about substance properties. Function try to call all functions, 
			and store names of functions, which isn't raise ExceptionNonExistentFunc
            Arguments:
				substance: Pointer to the substance
				info: Information about available properties and its arguments for this 
				substance
            )pbdoc",
			py::arg("substance"),
			py::arg("info")
			);*/

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}