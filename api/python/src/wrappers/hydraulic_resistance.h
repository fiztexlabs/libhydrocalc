#pragma once
#include <libhydrocalc/hydraulic_resistance_base.h>
#include <pybind11/pybind11.h>

namespace hr = hydrocalc;

namespace py_api
{
    /// @todo Wrappers for setup and information functions
    class HydraulicResistance : public hr::HydraulicResistanceBase
    {
    protected:

        hr::HydraulicResistance* copy() const override
        {
            PYBIND11_OVERRIDE_PURE(
                hr::HydraulicResistance*,
                hr::HydraulicResistanceBase,
                copy);
        }
    public:
        // Inherit the constructors
        using hr::HydraulicResistanceBase::HydraulicResistanceBase;

        void evaluate() override
        {
            PYBIND11_OVERRIDE_PURE(
                void,
                hr::HydraulicResistanceBase,
                hr::evaluate);
        }

        void setName(const std::string& name) override
        {
            PYBIND11_OVERRIDE_PURE(
                void,
                hr::HydraulicResistanceBase,
                hr::setName,
                name);
        }

        void setGeometry(const std::vector<hr::real>& G) override
        {
            PYBIND11_OVERRIDE_PURE(
                void,
                hr::HydraulicResistanceBase,
                hr::setGeometry,
                G);
        }

        void getGeometry(std::vector<hr::real>& G) override
        {
            PYBIND11_OVERRIDE_PURE(
                void,
                hr::HydraulicResistanceBase,
                hr::getGeometry,
                G);
        }
    };
}