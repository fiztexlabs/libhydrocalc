#include <libhydrocalc/c/c_api.h>
#include <libhydrocalc/hydraulic_resistance.h>
#include <libhydrocalc/hydrocalc.h>
#include <vector>
#include <memory>
#include <string>
#include <libhydrocalc/export.h>

std::vector<std::unique_ptr<hydrocalc::HydraulicResistance>> hr_vec;

using namespace hydrocalc;

int LIBHYDROCALC_EXPORT createHydraulicResistance(
	const char* type,
	const real Re,
	const real* G,
	const int G_size,
	const char* name,
	const real vis)
{
	hr_vec.push_back(std::unique_ptr<HydraulicResistance>(createHydraulicResistance(
		std::string(type),
		Re, 
		std::vector<real>(G, G + G_size),
		std::string(name),
		vis)));

	return static_cast<int>(hr_vec.size() - 1);
}

int LIBHYDROCALC_EXPORT createComposite(
	const real Re,
	const real* G,
	const int G_size,
	const int* elements,
	const int elements_size,
	const char* name,
	const real vis)
{
	std::vector<HydraulicResistance*> els;
	for (int i = 0; i < elements_size; ++i)
	{
		els.push_back(hr_vec.at(i).get());
	}

	hr_vec.push_back(std::unique_ptr<HydraulicResistance>(createComposite(
		Re,
		std::vector<real>(G, G + G_size),
		els,
		std::string(name),
		vis)));

	return static_cast<int>(hr_vec.size() - 1);
}
