#include <MCADINCL.H>

char* HydrocalcFunctionErrors[] =
{
  "Value must be real",
  "Value must be positive",
  "Value must be integer",
  "Not enougth memory"
};

LRESULT rgpTCRITimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}

	if (static_cast<int>(_Id->real) != _Id->real)
	{
		return MAKELRESULT(3, 1);
	}

	if ((int(_Id->real) <= 0) && (int(_Id->real) > 2))
	{
		return MAKELRESULT(4, 1);
	}
	else
	{
		_result->real = rgpTCRIT(static_cast<const int>(_Id->real));
	}

	_result->imag = 0.0;

	return 0;
}