//		**********************************************************
//		* Общие функции RGP. Оболочка для Mathcad				 *
//		* Автор: Коновалов И.А. 16-04-2021                       *
//		**********************************************************

#include "stdafx.h"
#include "math.h"
#include "RGP.h"

char* RGPFunctionErrors[] =
{
  "Value must be real",
  "Value must be positive",
  "Value must be integer",
  "Invalid substance id",
  "Not enougth memory"
};

// ============================== ПАРАМЕТРЫ В КРИТИЧЕСКОЙ ТОЧКЕ ==============================

// температура в критической точке [К]
	// Входные параметры:
	//			id - идентификатор вещества
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

FUNCTIONINFO firgpTCRIT =
{
	"rgpTCRIT",
	"",
	"",
	(LPCFUNCTION)rgpTCRITimpl,
	COMPLEX_SCALAR,
	1,
	{COMPLEX_SCALAR}
};

// плотность в критической точке [кг/м3]
	// Входные параметры:
	//			id - идентификатор вещества
LRESULT rgpDCRITimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id)
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
		_result->real = rgpDCRIT(static_cast<const int>(_Id->real));
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDCRIT =
{
	"rgpDCRIT",
	"",
	"",
	(LPCFUNCTION)rgpDCRITimpl,
	COMPLEX_SCALAR,
	1,
	{COMPLEX_SCALAR}
};

// давление в критической точке [Па]
	// Входные параметры:
	//			id - идентификатор вещества
LRESULT rgpPCRITimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id)
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
		_result->real = rgpPCRIT(static_cast<const int>(_Id->real));
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPCRIT =
{
	"rgpPCRIT",
	"",
	"",
	(LPCFUNCTION)rgpPCRITimpl,
	COMPLEX_SCALAR,
	1,
	{COMPLEX_SCALAR}
};


// ============================== ПАРАМЕТРЫ В ТРОЙНОЙ ТОЧКЕ ==============================

// температура в тройной точке [К]
	// Входные параметры:
	//			id - идентификатор вещества
LRESULT rgpTTRIPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id)
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
		_result->real = rgpTTRIP(static_cast<const int>(_Id->real));
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTTRIP =
{
	"rgpTTRIP",
	"",
	"",
	(LPCFUNCTION)rgpTTRIPimpl,
	COMPLEX_SCALAR,
	1,
	{COMPLEX_SCALAR}
};

// давление в тройнй точке [Па]
// Входные параметры:
//			id - идентификатор вещества
LRESULT rgpPTRIPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id)
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
		_result->real = rgpPTRIP(static_cast<const int>(_Id->real));
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPTRIP =
{
	"rgpPTRIP",
	"",
	"",
	(LPCFUNCTION)rgpPTRIPimpl,
	COMPLEX_SCALAR,
	1,
	{COMPLEX_SCALAR}
};


// ============================== f(P, T) ОДНОФАЗНАЯ ОБЛАСТЬ ==============================

// номер области на диаграмме состояния
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
	// Выходные параметры:
	//			1 - жидкая фаза,
	//			2 - газовая фаза, 
	//			3 - жидкая фаза, 
	//			!! 4 - двухфазная область, при попадании параметров в двухфазную область возвращает 2
	//			5 - сверхкритическая область
	//			6 - твердая фаза
LRESULT rgpSTATEAREAPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpSTATEAREAPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSTATEAREAPT =
{
	"rgpSTATEAREAPT",
	"",
	"",
	(LPCFUNCTION)rgpSTATEAREAPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// плотность в однофазной области [кг/м3]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpDPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;
		
	return 0;
}

FUNCTIONINFO firgpDPT =
{
	"rgpDPT",
	"",
	"",
	(LPCFUNCTION)rgpDPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельный объём в однофазной области [м3/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpVPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpVPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpVPT =
{
	"rgpVPT",
	"",
	"",
	(LPCFUNCTION)rgpVPTimpl,
	COMPLEX_SCALAR,
	3, 
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная внутренняя энергия в однофазной области [Дж/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpUPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpUPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpUPT =
{
	"rgpUPT",
	"",
	"",
	(LPCFUNCTION)rgpUPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтальпия в однофазной области [Дж/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpHPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpHPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpHPT =
{
	"rgpHPT",
	"",
	"",
	(LPCFUNCTION)rgpHPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтропия в однофазной области [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpSPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpSPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSPT =
{
	"rgpSPT",
	"",
	"",
	(LPCFUNCTION)rgpSPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость в однофазной области [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpCPPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpCPPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCPPT =
{
	"rgpCPPT",
	"",
	"",
	(LPCFUNCTION)rgpCPPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость в однофазной области [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpCVPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpCVPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCVPT =
{
	"rgpCVPT",
	"",
	"",
	(LPCFUNCTION)rgpCVPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// скорость звука в однофазной области [м/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpWPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpWPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpWPT =
{
	"rgpWPT",
	"",
	"",
	(LPCFUNCTION)rgpWPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// показатель изоэнтропы в однофазной области [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpKPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpKPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKPT =
{
	"rgpKPT",
	"",
	"",
	(LPCFUNCTION)rgpKPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// динамическая вязкость в однофазной области [Па*с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpDYNVISPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDYNVISPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDYNVISPT =
{
	"rgpDYNVISPT",
	"",
	"",
	(LPCFUNCTION)rgpDYNVISPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// кинематическая вязкость в однофазной области [м2/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpKINVISPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpKINVISPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKINVISPT =
{
	"rgpKINVISPT",
	"",
	"",
	(LPCFUNCTION)rgpKINVISPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// теплопроводность в однофазной области [Вт/(м*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpTHERMCONDPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpTHERMCONDPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTHERMCONDPT =
{
	"rgpTHERMCONDPT",
	"",
	"",
	(LPCFUNCTION)rgpTHERMCONDPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// число Прандтля в однофазной области [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpPRANDTLEPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpPRANDTLEPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPRANDTLEPT =
{
	"rgpPRANDTLEPT",
	"",
	"",
	(LPCFUNCTION)rgpPRANDTLEPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной температуре в однофазной области [м3 / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpDVDPTPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDVDPTPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPTPT =
{
	"rgpDVDPTPT",
	"",
	"",
	(LPCFUNCTION)rgpDVDPTPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по температуре при постоянном давлении в однофазной области [м3/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpDVDTPPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDVDTPPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDTPPT =
{
	"rgpDVDTPPT",
	"",
	"",
	(LPCFUNCTION)rgpDVDTPPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной температуре в однофазной области [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpDDDPTPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDDDPTPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPTPT =
{
	"rgpDDDPTPT",
	"",
	"",
	(LPCFUNCTION)rgpDDDPTPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по температуре при постоянном давлении в однофазной области [кг/(К*м3)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpDDDTPPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDDDTPPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDTPPT =
{
	"rgpDDDTPPT",
	"",
	"",
	(LPCFUNCTION)rgpDDDTPPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по энтальпии при постоянном давлении в однофазной области [1/Па]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpDVDHPPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDVDHPPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDHPPT =
{
	"rgpDVDHPPT",
	"",
	"",
	(LPCFUNCTION)rgpDVDHPPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной энтальпии в однофазной области [(с2*м4)/кг2]
	// входные параметры:
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpDVDPHPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDVDPHPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPHPT =
{
	"rgpDVDPHPT",
	"",
	"",
	(LPCFUNCTION)rgpDVDPHPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по энтальпии при постоянном давлении в однофазной области [кг*с2/м5]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpDDDHPPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDDDHPPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDHPPT =
{
	"rgpDDDHPPT",
	"",
	"",
	(LPCFUNCTION)rgpDDDHPPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной энтальпии в однофазной области [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpDDDPHPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDDDPHPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPHPT =
{
	"rgpDDDPHPT",
	"",
	"",
	(LPCFUNCTION)rgpDDDPHPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по давлению при постоянной температуре в однофазной области [Дж/(кг*Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpDHDPTPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDHDPTPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDPTPT =
{
	"rgpDHDPTPT",
	"",
	"",
	(LPCFUNCTION)rgpDHDPTPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по температуре при постоянном давлении в однофазной области [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
LRESULT rgpDHDTPPTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDHDTPPT(static_cast<const int>(_Id->real), _P->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDTPPT =
{
	"rgpDHDTPPT",
	"",
	"",
	(LPCFUNCTION)rgpDHDTPPTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// результат вычисления свойств в однофазной области
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			T - температура [K]
	// выходные параметры:
	//			V - удельный объем [м3/кг]
	//			U - удельная внутренняя энергия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
	//			h - удельная энтальпия [Дж/кг]
	//			Cv - удельная изохорная теплоемкость [Дж/(кг*К)]
	//			dVdTp - производная удельного объема по температуре при постоянном давлении [м3/(кг*К)]
	//			dDdTp - производная плотности по температуре при постоянном давлении [кг/(К*м3)]
	//			dVdPt - производная удельного объема по давлению при постоянной температуре [м3/(кг*Па)]
	//			dDdPt - производная плотности по давлению при постоянной температуре [с2/м2]
	//			dUdTp - производная удельной внутренней энергии по температуре при постоянном давлении [Дж/(кг*К)]
	//			dUdPt - производная удельной внутренней энергии по давлению при постоянной температуре [Дж/(кг*Па)]
	//			dSdTp - производная удельной энтропии по температуре при постоянном давлении [Дж/(кг*К*К)]
	//			dSdPt - производная удельнойэнтропиипо давлению при постоянной температуре [Дж/(кг*К*Па)]
	//			dHdTp - производная удельной энтальпии по температуре при постоянном давлении [Дж/(кг*К)]
	//			dHdPt - производная удельной энтальпии по давлению при постоянной температуре [Дж/(кг*Па)]
LRESULT rgpVUSHCVCPWDERPTPTimpl(COMPLEXARRAY* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
	}

	if (static_cast<int>(_Id->real) != _Id->real)
	{
		return MAKELRESULT(3, 1);
	}

	double V = 0.0;
	double U = 0.0;
	double s = 0.0;
	double h = 0.0;
	double Cv = 0.0;
	double Cp = 0.0;
	double w = 0.0;
	double dVdTp = 0.0;
	double dDdTp = 0.0;
	double dVdPt = 0.0;
	double dDdPt = 0.0;
	double dUdTp = 0.0;
	double dUdPt = 0.0;
	double dSdTp = 0.0;
	double dSdPt = 0.0;
	double dHdTp = 0.0;
	double dHdPt = 0.0;

	if ((int(_Id->real) <= 0) && (int(_Id->real) > 2))
	{
		return MAKELRESULT(4, 1);
	}
	else
	{
		rgpVUSHCVCPWDERPTPT(static_cast<const int>(_Id->real), _P->real, _T->real, &V, &U, &s, &h, &Cv, &Cp, &w, &dVdTp, &dDdTp, &dVdPt, &dDdPt, &dUdTp, &dUdPt, &dSdTp, &dSdPt, &dHdTp, &dHdPt);
			
	}

	_result->cols = 1;
	_result->rows = 17;

	// Выделение памяти под возвращаемый массив
	if (!MathcadArrayAllocate(_result, _result->rows, _result->cols, TRUE, TRUE))
	{
		// При неудачном выделении возвращаем код ошибки
		return MAKELRESULT(4, 0);
	}

	_result->hReal[0][0] = V;
	_result->hReal[0][1] = U;
	_result->hReal[0][2] = s;
	_result->hReal[0][3] = h;
	_result->hReal[0][4] = Cv;
	_result->hReal[0][5] = Cp;
	_result->hReal[0][6] = w;
	_result->hReal[0][7] = dVdTp;
	_result->hReal[0][8] = dDdTp;
	_result->hReal[0][9] = dVdPt;
	_result->hReal[0][10] = dDdPt;
	_result->hReal[0][11] = dUdTp;
	_result->hReal[0][12] = dUdPt;
	_result->hReal[0][13] = dSdTp;
	_result->hReal[0][14] = dSdPt;
	_result->hReal[0][15] = dHdTp;
	_result->hReal[0][16] = dHdPt;

	_result->hImag[0][0] = 0.0;
	_result->hImag[0][1] = 0.0;
	_result->hImag[0][2] = 0.0;
	_result->hImag[0][3] = 0.0;
	_result->hImag[0][4] = 0.0;
	_result->hImag[0][5] = 0.0;
	_result->hImag[0][6] = 0.0;
	_result->hImag[0][7] = 0.0;
	_result->hImag[0][8] = 0.0;
	_result->hImag[0][9] = 0.0;
	_result->hImag[0][10] = 0.0;
	_result->hImag[0][11] = 0.0;
	_result->hImag[0][12] = 0.0;
	_result->hImag[0][13] = 0.0;
	_result->hImag[0][14] = 0.0;
	_result->hImag[0][15] = 0.0;
	_result->hImag[0][16] = 0.0;

	return 0;
}

FUNCTIONINFO firgpVUSHCVCPWDERPTPT =
{
	"rgpVUSHCVCPWDERPTPT",
	"",
	"",
	(LPCFUNCTION)rgpVUSHCVCPWDERPTPTimpl,
	COMPLEX_ARRAY,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// поверхностное натяжение [Н/м]
	// Входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpSURFTENTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpSURFTENT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSURFTENT =
{
	"rgpSURFTENT",
	"",
	"",
	(LPCFUNCTION)rgpSURFTENTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// ============================== f(D, T) ==============================

// давление [Па]
	// Входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpPDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpPDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPDT =
{
	"rgpPDT",
	"",
	"",
	(LPCFUNCTION)rgpPDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная внутренняя энергия [Дж/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpUDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpUDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpUDT =
{
	"rgpUDT",
	"",
	"",
	(LPCFUNCTION)rgpUDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтальпия [Дж/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpHDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpHDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpHDT =
{
	"rgpHDT",
	"",
	"",
	(LPCFUNCTION)rgpHDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтропия [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpSDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpSDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSDT =
{
	"rgpSDT",
	"",
	"",
	(LPCFUNCTION)rgpSDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpCPDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpCPDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCPDT =
{
	"rgpCPDT",
	"",
	"",
	(LPCFUNCTION)rgpCPDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpCVDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpCVDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCVDT =
{
	"rgpCVDT",
	"",
	"",
	(LPCFUNCTION)rgpCVDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// скорость звука [м/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpWDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpWDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpWDT =
{
	"rgpWDT",
	"",
	"",
	(LPCFUNCTION)rgpWDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// показатель изоэнтропы [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpKDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpKDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKDT =
{
	"rgpKDT",
	"",
	"",
	(LPCFUNCTION)rgpKDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// динамическая вязкость [Па*с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpDYNVISDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDYNVISDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDYNVISDT =
{
	"rgpDYNVISDT",
	"",
	"",
	(LPCFUNCTION)rgpDYNVISDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// кинематическая вязкость [м2/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpKINVISDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpKINVISDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKINVISDT =
{
	"rgpKINVISDT",
	"",
	"",
	(LPCFUNCTION)rgpKINVISDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// теплопроводность [Вт/(м*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpTHERMCONDDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpTHERMCONDDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTHERMCONDDT =
{
	"rgpTHERMCONDDT",
	"",
	"",
	(LPCFUNCTION)rgpTHERMCONDDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// число Прандтля [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpPRANDTLEDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpPRANDTLEDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPRANDTLEDT =
{
	"rgpPRANDTLEDT",
	"",
	"",
	(LPCFUNCTION)rgpPRANDTLEDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной температуре [м3 / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpDVDPTDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDVDPTDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPTDT =
{
	"rgpDVDPTDT",
	"",
	"",
	(LPCFUNCTION)rgpDVDPTDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по температуре при постоянном давлении [м3/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpDVDTPDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDVDTPDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDTPDT =
{
	"rgpDVDTPDT",
	"",
	"",
	(LPCFUNCTION)rgpDVDTPDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной температуре [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpDDDPTDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDDDPTDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPTDT =
{
	"rgpDDDPTDT",
	"",
	"",
	(LPCFUNCTION)rgpDDDPTDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по температуре при постоянном давлении [кг/(К*м3)]
	// входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpDDDTPDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDDDTPDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDTPDT =
{
	"rgpDDDTPDT",
	"",
	"",
	(LPCFUNCTION)rgpDDDTPDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по энтальпии при постоянном давлении [1/Па]
	// входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpDVDHPDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDVDHPDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDHPDT =
{
	"rgpDVDHPDT",
	"",
	"",
	(LPCFUNCTION)rgpDVDHPDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной энтальпии [(с2*м4)/кг2]
	// входные параметры:
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpDVDPHDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDVDPHDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPHDT =
{
	"rgpDVDPHDT",
	"",
	"",
	(LPCFUNCTION)rgpDVDPHDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по энтальпии при постоянном давлении [кг*с2/м5]
	// входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpDDDHPDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDDDHPDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDHPDT =
{
	"rgpDDDHPDT",
	"",
	"",
	(LPCFUNCTION)rgpDDDHPDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной энтальпии [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpDDDPHDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDDDPHDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPHDT =
{
	"rgpDDDPHDT",
	"",
	"",
	(LPCFUNCTION)rgpDDDPHDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по давлению при постоянной температуре [Дж/(кг*Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpDHDPTDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDHDPTDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDPTDT =
{
	"rgpDHDPTDT",
	"",
	"",
	(LPCFUNCTION)rgpDHDPTDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по температуре при постоянном давлении [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			D - плотность [кг/м3]
	//			T - температура [K]
LRESULT rgpDHDTPDTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _D, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_D->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_D->real < 0.0)
	{
		return MAKELRESULT(2, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
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
		_result->real = rgpDHDTPDT(static_cast<const int>(_Id->real), _D->real, _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDTPDT =
{
	"rgpDHDTPDT",
	"",
	"",
	(LPCFUNCTION)rgpDHDTPDTimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// ============================== f(P, h) ==============================

// номер области на диаграмме состояния
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
	// Выходные параметры:
	//			1 - жидкая фаза,
	//			2 - газовая фаза, 
	//			3 - жидкая фаза, 
	//			4 - двухфазная область,
	//			5 - сверхкритическая область
	//			6 - твердая фаза
LRESULT rgpSTATEAREAPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpSTATEAREAPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSTATEAREAPH =
{
	"rgpSTATEAREAPH",
	"",
	"",
	(LPCFUNCTION)rgpSTATEAREAPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// температура [К]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpTPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpTPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTPH =
{
	"rgpTPH",
	"",
	"",
	(LPCFUNCTION)rgpTPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// степень сухости пара [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpXPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpXPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpXPH =
{
	"rgpXPH",
	"",
	"",
	(LPCFUNCTION)rgpXPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// плотность [кг/м3]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpDPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDPH =
{
	"rgpDPH",
	"",
	"",
	(LPCFUNCTION)rgpDPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельный объём [м3/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpVPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpVPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpVPH =
{
	"rgpVPH",
	"",
	"",
	(LPCFUNCTION)rgpVPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная внутренняя энергия [Дж/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpUPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpUPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpUPH =
{
	"rgpUPH",
	"",
	"",
	(LPCFUNCTION)rgpUPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтропия [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpSPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpSPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSPH =
{
	"rgpSPH",
	"",
	"",
	(LPCFUNCTION)rgpSPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpCPPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCPPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCPPH =
{
	"rgpCPPH",
	"",
	"",
	(LPCFUNCTION)rgpCPPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpCVPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCVPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCVPH =
{
	"rgpCVPH",
	"",
	"",
	(LPCFUNCTION)rgpCVPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// скорость звука [м/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpWPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpWPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpWPH =
{
	"rgpWPH",
	"",
	"",
	(LPCFUNCTION)rgpWPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// показатель изоэнтропы [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpKPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKPH =
{
	"rgpKPH",
	"",
	"",
	(LPCFUNCTION)rgpKPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// динамическая вязкость [Па*с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpDYNVISPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDYNVISPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDYNVISPH =
{
	"rgpDYNVISPH",
	"",
	"",
	(LPCFUNCTION)rgpDYNVISPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// кинематическая вязкость [м2/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpKINVISPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKINVISPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKINVISPH =
{
	"rgpKINVISPH",
	"",
	"",
	(LPCFUNCTION)rgpKINVISPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// теплопроводность [Вт/(м*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpTHERMCONDPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpTHERMCONDPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTHERMCONDPH =
{
	"rgpTHERMCONDPH",
	"",
	"",
	(LPCFUNCTION)rgpTHERMCONDPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// число Прандтля [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpPRANDTLEPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpPRANDTLEPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPRANDTLEPH =
{
	"rgpPRANDTLEPH",
	"",
	"",
	(LPCFUNCTION)rgpPRANDTLEPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной температуре [м3 / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpDVDPTPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPTPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPTPH =
{
	"rgpDVDPTPH",
	"",
	"",
	(LPCFUNCTION)rgpDVDPTPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по температуре при постоянном давлении [м3/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpDVDTPPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDTPPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDTPPH =
{
	"rgpDVDTPPH",
	"",
	"",
	(LPCFUNCTION)rgpDVDTPPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной температуре [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpDDDPTPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPTPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPTPH =
{
	"rgpDDDPTPH",
	"",
	"",
	(LPCFUNCTION)rgpDDDPTPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по температуре при постоянном давлении [кг/(К*м3)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpDDDTPPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDTPPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDTPPH =
{
	"rgpDDDTPPH",
	"",
	"",
	(LPCFUNCTION)rgpDDDTPPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по энтальпии при постоянном давлении [1/Па]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpDVDHPPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDHPPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDHPPH =
{
	"rgpDVDHPPH",
	"",
	"",
	(LPCFUNCTION)rgpDVDHPPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной энтальпии [(с2*м4)/кг2]
	// входные параметры:
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpDVDPHPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPHPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPHPH =
{
	"rgpDVDPHPH",
	"",
	"",
	(LPCFUNCTION)rgpDVDPHPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по энтальпии при постоянном давлении [кг*с2/м5]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpDDDHPPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDHPPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDHPPH =
{
	"rgpDDDHPPH",
	"",
	"",
	(LPCFUNCTION)rgpDDDHPPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной энтальпии [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpDDDPHPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPHPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPHPH =
{
	"rgpDDDPHPH",
	"",
	"",
	(LPCFUNCTION)rgpDDDPHPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по давлению при постоянной температуре [Дж/(кг*Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpDHDPTPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDHDPTPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDPTPH =
{
	"rgpDHDPTPH",
	"",
	"",
	(LPCFUNCTION)rgpDHDPTPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по температуре при постоянном давлении [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			h - удельная энтальпия [Дж/кг]
LRESULT rgpDHDTPPHimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _h)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDHDTPPH(static_cast<const int>(_Id->real), _P->real, _h->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDTPPH =
{
	"rgpDHDTPPH",
	"",
	"",
	(LPCFUNCTION)rgpDHDTPPHimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};



// ============================== f(P, s) ==============================

// номер области на диаграмме состояния
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
	// Выходные параметры:
	//			1 - жидкая фаза,
	//			2 - газовая фаза, 
	//			3 - жидкая фаза, 
	//			4 - двухфазная область,
	//			5 - сверхкритическая область
	//			6 - твердая фаза
LRESULT rgpSTATEAREAPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpSTATEAREAPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSTATEAREAPS =
{
	"rgpSTATEAREAPS",
	"",
	"",
	(LPCFUNCTION)rgpSTATEAREAPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// температура [К]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpTPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpTPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTPS =
{
	"rgpTPS",
	"",
	"",
	(LPCFUNCTION)rgpTPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// степень сухости пара [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpXPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpXPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpXPS =
{
	"rgpXPS",
	"",
	"",
	(LPCFUNCTION)rgpXPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// плотность [кг/м3]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDPS =
{
	"rgpDPS",
	"",
	"",
	(LPCFUNCTION)rgpDPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельный объём [м3/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpVPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpVPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpVPS =
{
	"rgpVPS",
	"",
	"",
	(LPCFUNCTION)rgpVPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная внутренняя энергия [Дж/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpUPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpUPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpUPS =
{
	"rgpUPS",
	"",
	"",
	(LPCFUNCTION)rgpUPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтальпия [Дж/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpHPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpHPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpHPS =
{
	"rgpHPS",
	"",
	"",
	(LPCFUNCTION)rgpHPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpCPPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCPPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCPPS =
{
	"rgpCPPS",
	"",
	"",
	(LPCFUNCTION)rgpCPPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpCVPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCVPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCVPS =
{
	"rgpCVPS",
	"",
	"",
	(LPCFUNCTION)rgpCVPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// скорость звука [м/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpWPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpWPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpWPS =
{
	"rgpWPS",
	"",
	"",
	(LPCFUNCTION)rgpWPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};



// показатель изоэнтропы [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpKPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKPS =
{
	"rgpKPS",
	"",
	"",
	(LPCFUNCTION)rgpKPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// динамическая вязкость [Па*с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDYNVISPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDYNVISPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDYNVISPS =
{
	"rgpDYNVISPS",
	"",
	"",
	(LPCFUNCTION)rgpDYNVISPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// кинематическая вязкость [м2/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpKINVISPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKINVISPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKINVISPS =
{
	"rgpKINVISPS",
	"",
	"",
	(LPCFUNCTION)rgpKINVISPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// теплопроводность [Вт/(м*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpTHERMCONDPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpTHERMCONDPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTHERMCONDPS =
{
	"rgpTHERMCONDPS",
	"",
	"",
	(LPCFUNCTION)rgpTHERMCONDPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// число Прандтля [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpPRANDTLEPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpPRANDTLEPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPRANDTLEPS =
{
	"rgpPRANDTLEPS",
	"",
	"",
	(LPCFUNCTION)rgpPRANDTLEPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной температуре [м3 / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDVDPTPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPTPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPTPS =
{
	"rgpDVDPTPS",
	"",
	"",
	(LPCFUNCTION)rgpDVDPTPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по температуре при постоянном давлении [м3/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDVDTPPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDTPPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDTPPS =
{
	"rgpDVDTPPS",
	"",
	"",
	(LPCFUNCTION)rgpDVDTPPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной температуре [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDDDPTPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPTPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPTPS =
{
	"rgpDDDPTPS",
	"",
	"",
	(LPCFUNCTION)rgpDDDPTPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по температуре при постоянном давлении [кг/(К*м3)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDDDTPPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDTPPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDTPPS =
{
	"rgpDDDTPPS",
	"",
	"",
	(LPCFUNCTION)rgpDDDTPPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по энтальпии при постоянном давлении [1/Па]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDVDHPPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDHPPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDHPPS =
{
	"rgpDVDHPPS",
	"",
	"",
	(LPCFUNCTION)rgpDVDHPPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной энтальпии [(с2*м4)/кг2]
	// входные параметры:
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDVDPHPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPHPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPHPS =
{
	"rgpDVDPHPS",
	"",
	"",
	(LPCFUNCTION)rgpDVDPHPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по энтальпии при постоянном давлении [кг*с2/м5]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDDDHPPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDHPPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDHPPS =
{
	"rgpDDDHPPS",
	"",
	"",
	(LPCFUNCTION)rgpDDDHPPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной энтальпии [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDDDPHPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPHPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPHPS =
{
	"rgpDDDPHPS",
	"",
	"",
	(LPCFUNCTION)rgpDDDPHPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по давлению при постоянной температуре [Дж/(кг*Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDHDPTPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDHDPTPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDPTPS =
{
	"rgpDHDPTPS",
	"",
	"",
	(LPCFUNCTION)rgpDHDPTPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по температуре при постоянном давлении [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDHDTPPSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDHDTPPS(static_cast<const int>(_Id->real), _P->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDTPPS =
{
	"rgpDHDTPPS",
	"",
	"",
	(LPCFUNCTION)rgpDHDTPPSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};



// ============================== f(h, s) ==============================

// номер области на диаграмме состояния
	// входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
	// Выходные параметры:
	//			1 - жидкая фаза,
	//			2 - газовая фаза, 
	//			3 - жидкая фаза, 
	//			4 - двухфазная область,
	//			5 - сверхкритическая область
	//			6 - твердая фаза
LRESULT rgpSTATEAREAHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpSTATEAREAHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSTATEAREAHS =
{
	"rgpSTATEAREAHS",
	"",
	"",
	(LPCFUNCTION)rgpSTATEAREAHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// давление [Па]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpPHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpPHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPHS =
{
	"rgpPHS",
	"",
	"",
	(LPCFUNCTION)rgpPHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// температура [К]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpTHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpTHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTHS =
{
	"rgpTHS",
	"",
	"",
	(LPCFUNCTION)rgpTHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// степень сухости пара [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpXHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpXHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpXHS =
{
	"rgpXHS",
	"",
	"",
	(LPCFUNCTION)rgpXHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// плотность [кг/м3]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpDHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHS =
{
	"rgpDHS",
	"",
	"",
	(LPCFUNCTION)rgpDHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельный объём [м3/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpVHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpVHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpVHS =
{
	"rgpVHS",
	"",
	"",
	(LPCFUNCTION)rgpVHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная внутренняя энергия [Дж/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpUHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpUHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpUHS =
{
	"rgpUHS",
	"",
	"",
	(LPCFUNCTION)rgpUHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpCPHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpCPHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCPHS =
{
	"rgpCPHS",
	"",
	"",
	(LPCFUNCTION)rgpCPHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpCVHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpCVHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCVHS =
{
	"rgpCVHS",
	"",
	"",
	(LPCFUNCTION)rgpCVHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// скорость звука [м/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpWHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpWHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpWHS =
{
	"rgpWHS",
	"",
	"",
	(LPCFUNCTION)rgpWHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};



// показатель изоэнтропы [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpKHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpKHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKHS =
{
	"rgpKHS",
	"",
	"",
	(LPCFUNCTION)rgpKHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// динамическая вязкость [Па*с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDYNVISHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpDYNVISHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDYNVISHS =
{
	"rgpDYNVISHS",
	"",
	"",
	(LPCFUNCTION)rgpDYNVISHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// кинематическая вязкость [м2/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpKINVISHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpKINVISHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKINVISHS =
{
	"rgpKINVISHS",
	"",
	"",
	(LPCFUNCTION)rgpKINVISHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// теплопроводность [Вт/(м*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpTHERMCONDHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpTHERMCONDHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTHERMCONDHS =
{
	"rgpTHERMCONDHS",
	"",
	"",
	(LPCFUNCTION)rgpTHERMCONDHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// число Прандтля [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpPRANDTLEHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpPRANDTLEHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPRANDTLEHS =
{
	"rgpPRANDTLEHS",
	"",
	"",
	(LPCFUNCTION)rgpPRANDTLEHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной температуре [м3 / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDVDPTHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpDVDPTHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPTHS =
{
	"rgpDVDPTHS",
	"",
	"",
	(LPCFUNCTION)rgpDVDPTHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по температуре при постоянном давлении [м3/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDVDTPHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpDVDTPHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDTPHS =
{
	"rgpDVDTPHS",
	"",
	"",
	(LPCFUNCTION)rgpDVDTPHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной температуре [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDDDPTHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpDDDPTHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPTHS =
{
	"rgpDDDPTHS",
	"",
	"",
	(LPCFUNCTION)rgpDDDPTHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по температуре при постоянном давлении [кг/(К*м3)]
	// входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDDDTPHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpDDDTPHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDTPHS =
{
	"rgpDDDTPHS",
	"",
	"",
	(LPCFUNCTION)rgpDDDTPHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по энтальпии при постоянном давлении [1/Па]
	// входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDVDHPHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpDVDHPHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDHPHS =
{
	"rgpDVDHPHS",
	"",
	"",
	(LPCFUNCTION)rgpDVDHPHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной энтальпии [(с2*м4)/кг2]
	// входные параметры:
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDVDPHHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpDVDPHHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPHHS =
{
	"rgpDVDPHHS",
	"",
	"",
	(LPCFUNCTION)rgpDVDPHHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по энтальпии при постоянном давлении [кг*с2/м5]
	// входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDDDHPHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpDDDHPHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDHPHS =
{
	"rgpDDDHPHS",
	"",
	"",
	(LPCFUNCTION)rgpDDDHPHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной энтальпии [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDDDPHHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpDDDPHHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPHHS =
{
	"rgpDDDPHHS",
	"",
	"",
	(LPCFUNCTION)rgpDDDPHHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по давлению при постоянной температуре [Дж/(кг*Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDHDPTHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpDHDPTHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDPTHS =
{
	"rgpDHDPTHS",
	"",
	"",
	(LPCFUNCTION)rgpDHDPTHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по температуре при постоянном давлении [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			h - удельная энтальпия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
LRESULT rgpDHDTPHSimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _h, const COMPLEXSCALAR* const _s)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_h->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_s->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
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
		_result->real = rgpDHDTPHS(static_cast<const int>(_Id->real), _h->real, _s->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDTPHS =
{
	"rgpDHDTPHS",
	"",
	"",
	(LPCFUNCTION)rgpDHDTPHSimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// ============================== fs(T) ==============================

// давление жидкой фазы на линии насыщения [Па]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpPSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpPST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPST =
{
	"rgpPST",
	"",
	"",
	(LPCFUNCTION)rgpPSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// плотность жидкой фазы на линии насыщения [кг/м3]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDSWT =
{
	"rgpDSWT",
	"",
	"",
	(LPCFUNCTION)rgpDSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельный объем жидкой фазы на линии насыщения [м3/кг]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpVSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpVSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpVSWT =
{
	"rgpVSWT",
	"",
	"",
	(LPCFUNCTION)rgpVSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная внутренняя энергия жидкой фазы на линии насыщения [Дж/кг]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpUSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpUSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpUSWT =
{
	"rgpUSWT",
	"",
	"",
	(LPCFUNCTION)rgpUSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтропия жидкой фазы на линии насыщения [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpSSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpSSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSSWT =
{
	"rgpSSWT",
	"",
	"",
	(LPCFUNCTION)rgpSSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтальпия жидкой фазы на линии насыщения [Дж/кг]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpHSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpHSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpHSWT =
{
	"rgpHSWT",
	"",
	"",
	(LPCFUNCTION)rgpHSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость жидкой фазы на линии насыщения [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpCPSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCPSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCPSWT =
{
	"rgpCPSWT",
	"",
	"",
	(LPCFUNCTION)rgpCPSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изохорная теплоемкость жидкой фазы на линии насыщения [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpCVSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCVSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCVSWT =
{
	"rgpCVSWT",
	"",
	"",
	(LPCFUNCTION)rgpCVSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// скорость звука в жидкой фазе на линии насыщения [м/с]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpWSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpWSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpWSWT =
{
	"rgpWSWT",
	"",
	"",
	(LPCFUNCTION)rgpWSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// показатель изоэнтропы в жидкой фазе на линии насыщения [-]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpKSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKSWT =
{
	"rgpKSWT",
	"",
	"",
	(LPCFUNCTION)rgpKSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// динамическая вязкость жидкой фазы на линии насыщения [Па*с]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDYNVISSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDYNVISSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDYNVISSWT =
{
	"rgpDYNVISSWT",
	"",
	"",
	(LPCFUNCTION)rgpDYNVISSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// кинематическая вязкость жидкой фазы на линии насыщения [м2/с]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpKINVISSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKINVISSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKINVISSWT =
{
	"rgpKINVISSWT",
	"",
	"",
	(LPCFUNCTION)rgpKINVISSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// теплопроводность жидкой фазы на линии насыщения [Вт/(м*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpTHERMCONDSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpTHERMCONDSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTHERMCONDSWT =
{
	"rgpTHERMCONDSWT",
	"",
	"",
	(LPCFUNCTION)rgpTHERMCONDSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// число Прандтля жидкой фазы на линии насыщения [-]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpPRANDTLESWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpPRANDTLESWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPRANDTLESWT =
{
	"rgpPRANDTLESWT",
	"",
	"",
	(LPCFUNCTION)rgpPRANDTLESWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной температуре жидкой фазы на линии насыщения [м3 / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDVDPTSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPTSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPTSWT =
{
	"rgpDVDPTSWT",
	"",
	"",
	(LPCFUNCTION)rgpDVDPTSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по температуре при постоянном давлении жидкой фазы на линии насыщения [м3/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDVDTPSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDTPSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDTPSWT =
{
	"rgpDVDTPSWT",
	"",
	"",
	(LPCFUNCTION)rgpDVDTPSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной температуре жидкой фазы на линии насыщения [2/(кг*Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDDDPTSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPTSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPTSWT =
{
	"rgpDDDPTSWT",
	"",
	"",
	(LPCFUNCTION)rgpDDDPTSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по температуре при постоянном давлении жидкой фазы на линии насыщения [2/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDDDTPSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDTPSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDTPSWT =
{
	"rgpDDDTPSWT",
	"",
	"",
	(LPCFUNCTION)rgpDDDTPSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по энтальпии при постоянном давлении жидкой фазы на линии насыщения [2/Па]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDVDHPSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDHPSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDHPSWT =
{
	"rgpDVDHPSWT",
	"",
	"",
	(LPCFUNCTION)rgpDVDHPSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной энтальпии жидкой фазы на линии насыщения [(с2*м4)/кг2]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDVDPHSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPHSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPHSWT =
{
	"rgpDVDPHSWT",
	"",
	"",
	(LPCFUNCTION)rgpDVDPHSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по энтальпии при постоянном давлении жидкой фазы на линии насыщения [кг*с2/м5]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDDDHPSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDHPSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDHPSWT =
{
	"rgpDDDHPSWT",
	"",
	"",
	(LPCFUNCTION)rgpDDDHPSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной энтальпии жидкой фазы на линии насыщения [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDDDPHSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPHSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPHSWT =
{
	"rgpDDDPHSWT",
	"",
	"",
	(LPCFUNCTION)rgpDDDPHSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по давлению при постоянной температуре жидкой фазы на линии насыщения [Дж / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDHDPTSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDHDPTSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDPTSWT =
{
	"rgpDHDPTSWT",
	"",
	"",
	(LPCFUNCTION)rgpDHDPTSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по температуре при постоянном давлении жидкой фазы на линии насыщения [Дж / (кг * К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDHDTPSWTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDHDTPSWT(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDTPSWT =
{
	"rgpDHDTPSWT",
	"",
	"",
	(LPCFUNCTION)rgpDHDTPSWTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// результат вычисления свойств жидкой фазы на линии насыщения
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	// выходные параметры:
	//			V - удельный объем [м3/кг]
	//			U - удельная внутренняя энергия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
	//			h - удельная энтальпия [Дж/кг]
	//			Cv - удельная изохорная теплоемкость [Дж/(кг*К)]
	//			Cp - удельная изобарная теплоемкость [Дж/(кг*К)]
	//			w - скорость звука [м/c]
	//			dVdTp - производная удельного объема по температуре при постоянном давлении [м3/(кг*К)]
	//			dDdTp - производная плотности по температуре при постоянном давлении [кг/(К*м3)]
	//			dVdPt - производная удельного объема по давлению при постоянной температуре [м3/(кг*Па)]
	//			dDdPt - производная плотности по давлению при постоянной температуре [с2/м2]
	//			dUdTp - производная удельной внутренней энергии по температуре при постоянном давлении [Дж/(кг*К)]
	//			dUdPt - производная удельной внутренней энергии по давлению при постоянной температуре [Дж/(кг*Па)]
	//			dSdTp - производная удельной энтропии по температуре при постоянном давлении [Дж/(кг*К*К)]
	//			dSdPt - производная удельнойэнтропиипо давлению при постоянной температуре [Дж/(кг*К*Па)]
	//			dHdTp - производная удельной энтальпии по температуре при постоянном давлении [Дж/(кг*К)]
	//			dHdPt - производная удельной энтальпии по давлению при постоянной температуре [Дж/(кг*Па)]
LRESULT rgpVUSHCVCPWDERPTSWTimpl(COMPLEXARRAY* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
	}

	if (static_cast<int>(_Id->real) != _Id->real)
	{
		return MAKELRESULT(3, 1);
	}

	double V = 0.0;
	double U = 0.0;
	double s = 0.0;
	double h = 0.0;
	double Cv = 0.0;
	double Cp = 0.0;
	double w = 0.0;
	double dVdTp = 0.0;
	double dDdTp = 0.0;
	double dVdPt = 0.0;
	double dDdPt = 0.0;
	double dUdTp = 0.0;
	double dUdPt = 0.0;
	double dSdTp = 0.0;
	double dSdPt = 0.0;
	double dHdTp = 0.0;
	double dHdPt = 0.0;

	if ((int(_Id->real) <= 0) && (int(_Id->real) > 2))
	{
		return MAKELRESULT(4, 1);
	}
	else
	{
		rgpVUSHCVCPWDERPTSWT(static_cast<const int>(_Id->real),  _T->real, &V, &U, &s, &h, &Cv, &Cp, &w, &dVdTp, &dDdTp, &dVdPt, &dDdPt, &dUdTp, &dUdPt, &dSdTp, &dSdPt, &dHdTp, &dHdPt);

	}

	_result->cols = 1;
	_result->rows = 17;

	// Выделение памяти под возвращаемый массив
	if (!MathcadArrayAllocate(_result, _result->rows, _result->cols, TRUE, TRUE))
	{
		// При неудачном выделении возвращаем код ошибки
		return MAKELRESULT(4, 0);
	}

	_result->hReal[0][0] = V;
	_result->hReal[0][1] = U;
	_result->hReal[0][2] = s;
	_result->hReal[0][3] = h;
	_result->hReal[0][4] = Cv;
	_result->hReal[0][5] = Cp;
	_result->hReal[0][6] = w;
	_result->hReal[0][7] = dVdTp;
	_result->hReal[0][8] = dDdTp;
	_result->hReal[0][9] = dVdPt;
	_result->hReal[0][10] = dDdPt;
	_result->hReal[0][11] = dUdTp;
	_result->hReal[0][12] = dUdPt;
	_result->hReal[0][13] = dSdTp;
	_result->hReal[0][14] = dSdPt;
	_result->hReal[0][15] = dHdTp;
	_result->hReal[0][16] = dHdPt;

	_result->hImag[0][0] = 0.0;
	_result->hImag[0][1] = 0.0;
	_result->hImag[0][2] = 0.0;
	_result->hImag[0][3] = 0.0;
	_result->hImag[0][4] = 0.0;
	_result->hImag[0][5] = 0.0;
	_result->hImag[0][6] = 0.0;
	_result->hImag[0][7] = 0.0;
	_result->hImag[0][8] = 0.0;
	_result->hImag[0][9] = 0.0;
	_result->hImag[0][10] = 0.0;
	_result->hImag[0][11] = 0.0;
	_result->hImag[0][12] = 0.0;
	_result->hImag[0][13] = 0.0;
	_result->hImag[0][14] = 0.0;
	_result->hImag[0][15] = 0.0;
	_result->hImag[0][16] = 0.0;

	return 0;
}

FUNCTIONINFO firgpVUSHCVCPWDERPTSWT =
{
	"rgpVUSHCVCPWDERPTSWT",
	"",
	"",
	(LPCFUNCTION)rgpVUSHCVCPWDERPTSWTimpl,
	COMPLEX_ARRAY,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// плотность газообразной фазы на линии насыщения [кг/м3]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDSST =
{
	"rgpDSST",
	"",
	"",
	(LPCFUNCTION)rgpDSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельный объем газообразной фазы на линии насыщения [м3/кг]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpVSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpVSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpVSST =
{
	"rgpVSST",
	"",
	"",
	(LPCFUNCTION)rgpVSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная внутренняя энергия газообразной фазы на линии насыщения [Дж/кг]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpUSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpUSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpUSST =
{
	"rgpUSST",
	"",
	"",
	(LPCFUNCTION)rgpUSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтропия газообразной фазы на линии насыщения [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpSSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpSSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSSST =
{
	"rgpSSST",
	"",
	"",
	(LPCFUNCTION)rgpSSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтальпия газообразной фазы на линии насыщения [Дж/кг]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpHSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpHSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpHSST =
{
	"rgpHSST",
	"",
	"",
	(LPCFUNCTION)rgpHSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость газообразной фазы на линии насыщения [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpCPSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCPSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCPSST =
{
	"rgpCPSST",
	"",
	"",
	(LPCFUNCTION)rgpCPSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изохорная теплоемкость газообразной фазы на линии насыщения [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpCVSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCVSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCVSST =
{
	"rgpCVSST",
	"",
	"",
	(LPCFUNCTION)rgpCVSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// скорость звука в жидкой фазе на линии насыщения [м/с]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpWSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpWSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpWSST =
{
	"rgpWSST",
	"",
	"",
	(LPCFUNCTION)rgpWSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};



// показатель изоэнтропы в газовой фазе на линии насыщения [-]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpKSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKSST =
{
	"rgpKSST",
	"",
	"",
	(LPCFUNCTION)rgpKSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// динамическая вязкость газообразной фазы на линии насыщения [Па*с]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDYNVISSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDYNVISSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDYNVISSST =
{
	"rgpDYNVISSST",
	"",
	"",
	(LPCFUNCTION)rgpDYNVISSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// кинематрическая вязкость газообразной фазы на линии насыщения [м2/с]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpKINVISSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKINVISSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKINVISSST =
{
	"rgpKINVISSST",
	"",
	"",
	(LPCFUNCTION)rgpKINVISSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// теплопроводность газообразной фазы на линии насыщения [Вт/(м*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpTHERMCONDSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpTHERMCONDSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTHERMCONDSST =
{
	"rgpTHERMCONDSST",
	"",
	"",
	(LPCFUNCTION)rgpTHERMCONDSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// число Прандтля газообразной фазы на линии насыщения [-]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpPRANDTLESSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpPRANDTLESST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPRANDTLESST =
{
	"rgpPRANDTLESST",
	"",
	"",
	(LPCFUNCTION)rgpPRANDTLESSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной температуре газообразной фазы на линии насыщения [м3 / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDVDPTSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPTSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPTSST =
{
	"rgpDVDPTSST",
	"",
	"",
	(LPCFUNCTION)rgpDVDPTSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по температуре при постоянном давлении газообразной фазы на линии насыщения [м3/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDVDTPSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDTPSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDTPSST =
{
	"rgpDVDTPSST",
	"",
	"",
	(LPCFUNCTION)rgpDVDTPSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной температуре газообразной фазы на линии насыщения [2/(кг*Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDDDPTSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPTSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPTSST =
{
	"rgpDDDPTSST",
	"",
	"",
	(LPCFUNCTION)rgpDDDPTSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по температуре при постоянном давлении газообразной фазы на линии насыщения [2/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDDDTPSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDTPSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDTPSST =
{
	"rgpDDDTPSST",
	"",
	"",
	(LPCFUNCTION)rgpDDDTPSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по энтальпии при постоянном давлении газообразной фазы на линии насыщения [2/Па]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDVDHPSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDHPSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDHPSST =
{
	"rgpDVDHPSST",
	"",
	"",
	(LPCFUNCTION)rgpDVDHPSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной энтальпии газообразной фазы на линии насыщения [(с2*м4)/кг2]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDVDPHSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPHSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPHSST =
{
	"rgpDVDPHSST",
	"",
	"",
	(LPCFUNCTION)rgpDVDPHSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по энтальпии при постоянном давлении газообразной фазы на линии насыщения [кг*с2/м5]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDDDHPSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDHPSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDHPSST =
{
	"rgpDDDHPSST",
	"",
	"",
	(LPCFUNCTION)rgpDDDHPSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной энтальпии газообразной фазы на линии насыщения [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDDDPHSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPHSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPHSST =
{
	"rgpDDDPHSST",
	"",
	"",
	(LPCFUNCTION)rgpDDDPHSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по давлению при постоянной температуре газообразной фазы на линии насыщения [Дж / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDHDPTSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDHDPTSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDPTSST =
{
	"rgpDHDPTSST",
	"",
	"",
	(LPCFUNCTION)rgpDHDPTSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по температуре при постоянном давлении газообразной фазы на линии насыщения [Дж / (кг * К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
LRESULT rgpDHDTPSSTimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDHDTPSST(static_cast<const int>(_Id->real), _T->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDTPSST =
{
	"rgpDHDTPSST",
	"",
	"",
	(LPCFUNCTION)rgpDHDTPSSTimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// результат вычисления свойств газообразной фазы на линии насыщения
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	// выходные параметры:
	//			V - удельный объем [м3/кг]
	//			U - удельная внутренняя энергия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
	//			h - удельная энтальпия [Дж/кг]
	//			Cv - удельная изохорная теплоемкость [Дж/(кг*К)]
	//			Cp - удельная изобарная теплоемкость [Дж/(кг*К)]
	//			w - скорость звука [м/c]
	//			dVdTp - производная удельного объема по температуре при постоянном давлении [м3/(кг*К)]
	//			dDdTp - производная плотности по температуре при постоянном давлении [кг/(К*м3)]
	//			dVdPt - производная удельного объема по давлению при постоянной температуре [м3/(кг*Па)]
	//			dDdPt - производная плотности по давлению при постоянной температуре [с2/м2]
	//			dUdTp - производная удельной внутренней энергии по температуре при постоянном давлении [Дж/(кг*К)]
	//			dUdPt - производная удельной внутренней энергии по давлению при постоянной температуре [Дж/(кг*Па)]
	//			dSdTp - производная удельной энтропии по температуре при постоянном давлении [Дж/(кг*К*К)]
	//			dSdPt - производная удельнойэнтропиипо давлению при постоянной температуре [Дж/(кг*К*Па)]
	//			dHdTp - производная удельной энтальпии по температуре при постоянном давлении [Дж/(кг*К)]
	//			dHdPt - производная удельной энтальпии по давлению при постоянной температуре [Дж/(кг*Па)]
LRESULT rgpVUSHCVCPWDERPTSSTimpl(COMPLEXARRAY* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 3);
	}

	if (static_cast<int>(_Id->real) != _Id->real)
	{
		return MAKELRESULT(3, 1);
	}

	double V = 0.0;
	double U = 0.0;
	double s = 0.0;
	double h = 0.0;
	double Cv = 0.0;
	double Cp = 0.0;
	double w = 0.0;
	double dVdTp = 0.0;
	double dDdTp = 0.0;
	double dVdPt = 0.0;
	double dDdPt = 0.0;
	double dUdTp = 0.0;
	double dUdPt = 0.0;
	double dSdTp = 0.0;
	double dSdPt = 0.0;
	double dHdTp = 0.0;
	double dHdPt = 0.0;

	if ((int(_Id->real) <= 0) && (int(_Id->real) > 2))
	{
		return MAKELRESULT(4, 1);
	}
	else
	{
		rgpVUSHCVCPWDERPTSST(static_cast<const int>(_Id->real), _T->real, &V, &U, &s, &h, &Cv, &Cp, &w, &dVdTp, &dDdTp, &dVdPt, &dDdPt, &dUdTp, &dUdPt, &dSdTp, &dSdPt, &dHdTp, &dHdPt);

	}

	_result->cols = 1;
	_result->rows = 17;

	// Выделение памяти под возвращаемый массив
	if (!MathcadArrayAllocate(_result, _result->rows, _result->cols, TRUE, TRUE))
	{
		// При неудачном выделении возвращаем код ошибки
		return MAKELRESULT(4, 0);
	}

	_result->hReal[0][0] = V;
	_result->hReal[0][1] = U;
	_result->hReal[0][2] = s;
	_result->hReal[0][3] = h;
	_result->hReal[0][4] = Cv;
	_result->hReal[0][5] = Cp;
	_result->hReal[0][6] = w;
	_result->hReal[0][7] = dVdTp;
	_result->hReal[0][8] = dDdTp;
	_result->hReal[0][9] = dVdPt;
	_result->hReal[0][10] = dDdPt;
	_result->hReal[0][11] = dUdTp;
	_result->hReal[0][12] = dUdPt;
	_result->hReal[0][13] = dSdTp;
	_result->hReal[0][14] = dSdPt;
	_result->hReal[0][15] = dHdTp;
	_result->hReal[0][16] = dHdPt;

	_result->hImag[0][0] = 0.0;
	_result->hImag[0][1] = 0.0;
	_result->hImag[0][2] = 0.0;
	_result->hImag[0][3] = 0.0;
	_result->hImag[0][4] = 0.0;
	_result->hImag[0][5] = 0.0;
	_result->hImag[0][6] = 0.0;
	_result->hImag[0][7] = 0.0;
	_result->hImag[0][8] = 0.0;
	_result->hImag[0][9] = 0.0;
	_result->hImag[0][10] = 0.0;
	_result->hImag[0][11] = 0.0;
	_result->hImag[0][12] = 0.0;
	_result->hImag[0][13] = 0.0;
	_result->hImag[0][14] = 0.0;
	_result->hImag[0][15] = 0.0;
	_result->hImag[0][16] = 0.0;

	return 0;
}

FUNCTIONINFO firgpVUSHCVCPWDERPTSST =
{
	"rgpVUSHCVCPWDERPTSST",
	"",
	"",
	(LPCFUNCTION)rgpVUSHCVCPWDERPTSSTimpl,
	COMPLEX_ARRAY,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};




// ============================== fs(P) ==============================

// температура жидкой фазы на линии насыщения [K]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpTSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpTSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTSP =
{
	"rgpTSP",
	"",
	"",
	(LPCFUNCTION)rgpTSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// плотность жидкой фазы на линии насыщения [кг/м3]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDSWP =
{
	"rgpDSWP",
	"",
	"",
	(LPCFUNCTION)rgpDSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельный объем жидкой фазы на линии насыщения [м3/кг]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpVSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpVSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpVSWP =
{
	"rgpVSWP",
	"",
	"",
	(LPCFUNCTION)rgpVSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная внутренняя энергия жидкой фазы на линии насыщения [Дж/кг]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpUSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpUSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpUSWP =
{
	"rgpUSWP",
	"",
	"",
	(LPCFUNCTION)rgpUSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтропия жидкой фазы на линии насыщения [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpSSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpSSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSSWP =
{
	"rgpSSWP",
	"",
	"",
	(LPCFUNCTION)rgpSSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтальпия жидкой фазы на линии насыщения [Дж/кг]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpHSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpHSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpHSWP =
{
	"rgpHSWP",
	"",
	"",
	(LPCFUNCTION)rgpHSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость жидкой фазы на линии насыщения [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpCPSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCPSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCPSWP =
{
	"rgpCPSWP",
	"",
	"",
	(LPCFUNCTION)rgpCPSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изохорная теплоемкость жидкой фазы на линии насыщения [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpCVSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCVSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCVSWP =
{
	"rgpCVSWP",
	"",
	"",
	(LPCFUNCTION)rgpCVSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// скорость звука в жидкой фазе на линии насыщения [м/с]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpWSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpWSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpWSWP =
{
	"rgpWSWP",
	"",
	"",
	(LPCFUNCTION)rgpWSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};



// показатель изоэнтропы в жидкой фазе на линии насыщения [-]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpKSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKSWP =
{
	"rgpKSWP",
	"",
	"",
	(LPCFUNCTION)rgpKSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// динамическая вязкость жидкой фазы на линии насыщения [Па*с]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDYNVISSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDYNVISSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDYNVISSWP =
{
	"rgpDYNVISSWP",
	"",
	"",
	(LPCFUNCTION)rgpDYNVISSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// кинематическая вязкость жидкой фазы на линии насыщения [м2/с]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpKINVISSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKINVISSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKINVISSWP =
{
	"rgpKINVISSWP",
	"",
	"",
	(LPCFUNCTION)rgpKINVISSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// теплопроводность жидкой фазы на линии насыщения [Вт/(м*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpTHERMCONDSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpTHERMCONDSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTHERMCONDSWP =
{
	"rgpTHERMCONDSWP",
	"",
	"",
	(LPCFUNCTION)rgpTHERMCONDSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// число Прандтля жидкой фазы на линии насыщения [-]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpPRANDTLESWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpPRANDTLESWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPRANDTLESWP =
{
	"rgpPRANDTLESWP",
	"",
	"",
	(LPCFUNCTION)rgpPRANDTLESWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной температуре жидкой фазы на линии насыщения [м3 / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDVDPTSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPTSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPTSWP =
{
	"rgpDVDPTSWP",
	"",
	"",
	(LPCFUNCTION)rgpDVDPTSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по температуре при постоянном давлении жидкой фазы на линии насыщения [м3/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDVDTPSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDTPSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDTPSWP =
{
	"rgpDVDTPSWP",
	"",
	"",
	(LPCFUNCTION)rgpDVDTPSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной температуре жидкой фазы на линии насыщения [2/(кг*Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDDDPTSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPTSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPTSWP =
{
	"rgpDDDPTSWP",
	"",
	"",
	(LPCFUNCTION)rgpDDDPTSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по температуре при постоянном давлении жидкой фазы на линии насыщения [2/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDDDTPSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDTPSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDTPSWP =
{
	"rgpDDDTPSWP",
	"",
	"",
	(LPCFUNCTION)rgpDDDTPSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по энтальпии при постоянном давлении жидкой фазы на линии насыщения [2/Па]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDVDHPSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDHPSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDHPSWP =
{
	"rgpDVDHPSWP",
	"",
	"",
	(LPCFUNCTION)rgpDVDHPSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной энтальпии жидкой фазы на линии насыщения [(с2*м4)/кг2]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDVDPHSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPHSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPHSWP =
{
	"rgpDVDPHSWP",
	"",
	"",
	(LPCFUNCTION)rgpDVDPHSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по энтальпии при постоянном давлении жидкой фазы на линии насыщения [кг*с2/м5]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDDDHPSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDHPSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDHPSWP =
{
	"rgpDDDHPSWP",
	"",
	"",
	(LPCFUNCTION)rgpDDDHPSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной энтальпии жидкой фазы на линии насыщения [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDDDPHSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPHSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPHSWP =
{
	"rgpDDDPHSWP",
	"",
	"",
	(LPCFUNCTION)rgpDDDPHSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по давлению при постоянной температуре жидкой фазы на линии насыщения [Дж / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDHDPTSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDHDPTSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDPTSWP =
{
	"rgpDHDPTSWP",
	"",
	"",
	(LPCFUNCTION)rgpDHDPTSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по температуре при постоянном давлении жидкой фазы на линии насыщения [Дж / (кг * К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDHDTPSWPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDHDTPSWP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDTPSWP =
{
	"rgpDHDTPSWP",
	"",
	"",
	(LPCFUNCTION)rgpDHDTPSWPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// результат вычисления свойств жидкой фазы на линии насыщения
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	// выходные параметры:
	//			V - удельный объем [м3/кг]
	//			U - удельная внутренняя энергия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
	//			h - удельная энтальпия [Дж/кг]
	//			Cv - удельная изохорная теплоемкость [Дж/(кг*К)]
	//			Cp - удельная изобарная теплоемкость [Дж/(кг*К)]
	//			w - скорость звука [м/c]
	//			dVdTp - производная удельного объема по температуре при постоянном давлении [м3/(кг*К)]
	//			dDdTp - производная плотности по температуре при постоянном давлении [кг/(К*м3)]
	//			dVdPt - производная удельного объема по давлению при постоянной температуре [м3/(кг*Па)]
	//			dDdPt - производная плотности по давлению при постоянной температуре [с2/м2]
	//			dUdTp - производная удельной внутренней энергии по температуре при постоянном давлении [Дж/(кг*К)]
	//			dUdPt - производная удельной внутренней энергии по давлению при постоянной температуре [Дж/(кг*Па)]
	//			dSdTp - производная удельной энтропии по температуре при постоянном давлении [Дж/(кг*К*К)]
	//			dSdPt - производная удельнойэнтропиипо давлению при постоянной температуре [Дж/(кг*К*Па)]
	//			dHdTp - производная удельной энтальпии по температуре при постоянном давлении [Дж/(кг*К)]
	//			dHdPt - производная удельной энтальпии по давлению при постоянной температуре [Дж/(кг*Па)]
LRESULT rgpVUSHCVCPWDERPTSWPimpl(COMPLEXARRAY* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 3);
	}

	if (static_cast<int>(_Id->real) != _Id->real)
	{
		return MAKELRESULT(3, 1);
	}

	double V = 0.0;
	double U = 0.0;
	double s = 0.0;
	double h = 0.0;
	double Cv = 0.0;
	double Cp = 0.0;
	double w = 0.0;
	double dVdTp = 0.0;
	double dDdTp = 0.0;
	double dVdPt = 0.0;
	double dDdPt = 0.0;
	double dUdTp = 0.0;
	double dUdPt = 0.0;
	double dSdTp = 0.0;
	double dSdPt = 0.0;
	double dHdTp = 0.0;
	double dHdPt = 0.0;

	if ((int(_Id->real) <= 0) && (int(_Id->real) > 2))
	{
		return MAKELRESULT(4, 1);
	}
	else
	{
		rgpVUSHCVCPWDERPTSWP(static_cast<const int>(_Id->real), _P->real, &V, &U, &s, &h, &Cv, &Cp, &w, &dVdTp, &dDdTp, &dVdPt, &dDdPt, &dUdTp, &dUdPt, &dSdTp, &dSdPt, &dHdTp, &dHdPt);

	}

	_result->cols = 1;
	_result->rows = 17;

	// Выделение памяти под возвращаемый массив
	if (!MathcadArrayAllocate(_result, _result->rows, _result->cols, TRUE, TRUE))
	{
		// При неудачном выделении возвращаем код ошибки
		return MAKELRESULT(4, 0);
	}

	_result->hReal[0][0] = V;
	_result->hReal[0][1] = U;
	_result->hReal[0][2] = s;
	_result->hReal[0][3] = h;
	_result->hReal[0][4] = Cv;
	_result->hReal[0][5] = Cp;
	_result->hReal[0][6] = w;
	_result->hReal[0][7] = dVdTp;
	_result->hReal[0][8] = dDdTp;
	_result->hReal[0][9] = dVdPt;
	_result->hReal[0][10] = dDdPt;
	_result->hReal[0][11] = dUdTp;
	_result->hReal[0][12] = dUdPt;
	_result->hReal[0][13] = dSdTp;
	_result->hReal[0][14] = dSdPt;
	_result->hReal[0][15] = dHdTp;
	_result->hReal[0][16] = dHdPt;

	_result->hImag[0][0] = 0.0;
	_result->hImag[0][1] = 0.0;
	_result->hImag[0][2] = 0.0;
	_result->hImag[0][3] = 0.0;
	_result->hImag[0][4] = 0.0;
	_result->hImag[0][5] = 0.0;
	_result->hImag[0][6] = 0.0;
	_result->hImag[0][7] = 0.0;
	_result->hImag[0][8] = 0.0;
	_result->hImag[0][9] = 0.0;
	_result->hImag[0][10] = 0.0;
	_result->hImag[0][11] = 0.0;
	_result->hImag[0][12] = 0.0;
	_result->hImag[0][13] = 0.0;
	_result->hImag[0][14] = 0.0;
	_result->hImag[0][15] = 0.0;
	_result->hImag[0][16] = 0.0;

	return 0;
}

FUNCTIONINFO firgpVUSHCVCPWDERPTSWP =
{
	"rgpVUSHCVCPWDERPTSWP",
	"",
	"",
	(LPCFUNCTION)rgpVUSHCVCPWDERPTSWPimpl,
	COMPLEX_ARRAY,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// плотность газообразной фазы на линии насыщения [кг/м3]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDSSP =
{
	"rgpDSSP",
	"",
	"",
	(LPCFUNCTION)rgpDSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельный объем газообразной фазы на линии насыщения [м3/кг]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpVSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpVSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpVSSP =
{
	"rgpVSSP",
	"",
	"",
	(LPCFUNCTION)rgpVSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная внутренняя энергия газообразной фазы на линии насыщения [Дж/кг]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpUSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpUSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpUSSP =
{
	"rgpUSSP",
	"",
	"",
	(LPCFUNCTION)rgpUSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтропия газообразной фазы на линии насыщения [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpSSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpSSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSSSP =
{
	"rgpSSSP",
	"",
	"",
	(LPCFUNCTION)rgpSSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтальпия газообразной фазы на линии насыщения [Дж/кг]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpHSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpHSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpHSSP =
{
	"rgpHSSP",
	"",
	"",
	(LPCFUNCTION)rgpHSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость газообразной фазы на линии насыщения [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpCPSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCPSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCPSSP =
{
	"rgpCPSSP",
	"",
	"",
	(LPCFUNCTION)rgpCPSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изохорная теплоемкость газообразной фазы на линии насыщения [Дж/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpCVSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCVSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCVSSP =
{
	"rgpCVSSP",
	"",
	"",
	(LPCFUNCTION)rgpCVSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// скорость звука в жидкой фазе на линии насыщения [м/с]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpWSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpWSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpWSSP =
{
	"rgpWSSP",
	"",
	"",
	(LPCFUNCTION)rgpWSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};



// показатель изоэнтропы в газовой фазе на линии насыщения [-]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpKSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKSSP =
{
	"rgpKSSP",
	"",
	"",
	(LPCFUNCTION)rgpKSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// динамическая вязкость газообразной фазы на линии насыщения [Па*с]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDYNVISSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDYNVISSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDYNVISSSP =
{
	"rgpDYNVISSSP",
	"",
	"",
	(LPCFUNCTION)rgpDYNVISSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// кинематическая вязкость газообразной фазы на линии насыщения [м2/с]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpKINVISSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKINVISSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKINVISSSP =
{
	"rgpKINVISSSP",
	"",
	"",
	(LPCFUNCTION)rgpKINVISSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// теплопроводность газообразной фазы на линии насыщения [Вт/(м*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpTHERMCONDSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpTHERMCONDSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTHERMCONDSSP =
{
	"rgpTHERMCONDSSP",
	"",
	"",
	(LPCFUNCTION)rgpTHERMCONDSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// число Прандтля газообразной фазы на линии насыщения [-]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpPRANDTLESSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpPRANDTLESSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPRANDTLESSP =
{
	"rgpPRANDTLESSP",
	"",
	"",
	(LPCFUNCTION)rgpPRANDTLESSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной температуре газообразной фазы на линии насыщения [м3 / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDVDPTSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPTSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPTSSP =
{
	"rgpDVDPTSSP",
	"",
	"",
	(LPCFUNCTION)rgpDVDPTSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по температуре при постоянном давлении газообразной фазы на линии насыщения [м3/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDVDTPSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDTPSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDTPSSP =
{
	"rgpDVDTPSSP",
	"",
	"",
	(LPCFUNCTION)rgpDVDTPSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной температуре газообразной фазы на линии насыщения [2/(кг*Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDDDPTSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPTSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPTSSP =
{
	"rgpDDDPTSSP",
	"",
	"",
	(LPCFUNCTION)rgpDDDPTSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по температуре при постоянном давлении газообразной фазы на линии насыщения [2/(кг*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDDDTPSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDTPSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDTPSSP =
{
	"rgpDDDTPSSP",
	"",
	"",
	(LPCFUNCTION)rgpDDDTPSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по энтальпии при постоянном давлении газообразной фазы на линии насыщения [2/Па]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDVDHPSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDHPSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDHPSSP =
{
	"rgpDVDHPSSP",
	"",
	"",
	(LPCFUNCTION)rgpDVDHPSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной энтальпии газообразной фазы на линии насыщения [(с2*м4)/кг2]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDVDPHSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPHSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPHSSP =
{
	"rgpDVDPHSSP",
	"",
	"",
	(LPCFUNCTION)rgpDVDPHSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по энтальпии при постоянном давлении газообразной фазы на линии насыщения [кг*с2/м5]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDDDHPSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDHPSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDHPSSP =
{
	"rgpDDDHPSSP",
	"",
	"",
	(LPCFUNCTION)rgpDDDHPSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной энтальпии газообразной фазы на линии насыщения [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDDDPHSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPHSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPHSSP =
{
	"rgpDDDPHSSP",
	"",
	"",
	(LPCFUNCTION)rgpDDDPHSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по давлению при постоянной температуре газообразной фазы на линии насыщения [Дж / (кг * Па)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDHDPTSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDHDPTSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDPTSSP =
{
	"rgpDHDPTSSP",
	"",
	"",
	(LPCFUNCTION)rgpDHDPTSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельной энтальпии по температуре при постоянном давлении газообразной фазы на линии насыщения [Дж / (кг * К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
LRESULT rgpDHDTPSSPimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDHDTPSSP(static_cast<const int>(_Id->real), _P->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDHDTPSSP =
{
	"rgpDHDTPSSP",
	"",
	"",
	(LPCFUNCTION)rgpDHDTPSSPimpl,
	COMPLEX_SCALAR,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// результат вычисления свойств газообразной фазы на линии насыщения
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	// выходные параметры:
	//			V - удельный объем [м3/кг]
	//			U - удельная внутренняя энергия [Дж/кг]
	//			s - удельная энтропия [Дж/(кг*К)]
	//			h - удельная энтальпия [Дж/кг]
	//			Cv - удельная изохорная теплоемкость [Дж/(кг*К)]
	//			Cp - удельная изобарная теплоемкость [Дж/(кг*К)]
	//			w - скорость звука [м/c]
	//			dVdTp - производная удельного объема по температуре при постоянном давлении [м3/(кг*К)]
	//			dDdTp - производная плотности по температуре при постоянном давлении [кг/(К*м3)]
	//			dVdPt - производная удельного объема по давлению при постоянной температуре [м3/(кг*Па)]
	//			dDdPt - производная плотности по давлению при постоянной температуре [с2/м2]
	//			dUdTp - производная удельной внутренней энергии по температуре при постоянном давлении [Дж/(кг*К)]
	//			dUdPt - производная удельной внутренней энергии по давлению при постоянной температуре [Дж/(кг*Па)]
	//			dSdTp - производная удельной энтропии по температуре при постоянном давлении [Дж/(кг*К*К)]
	//			dSdPt - производная удельнойэнтропиипо давлению при постоянной температуре [Дж/(кг*К*Па)]
	//			dHdTp - производная удельной энтальпии по температуре при постоянном давлении [Дж/(кг*К)]
	//			dHdPt - производная удельной энтальпии по давлению при постоянной температуре [Дж/(кг*Па)]
LRESULT rgpVUSHCVCPWDERPTSSPimpl(COMPLEXARRAY* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 3);
	}

	if (static_cast<int>(_Id->real) != _Id->real)
	{
		return MAKELRESULT(3, 1);
	}

	double V = 0.0;
	double U = 0.0;
	double s = 0.0;
	double h = 0.0;
	double Cv = 0.0;
	double Cp = 0.0;
	double w = 0.0;
	double dVdTp = 0.0;
	double dDdTp = 0.0;
	double dVdPt = 0.0;
	double dDdPt = 0.0;
	double dUdTp = 0.0;
	double dUdPt = 0.0;
	double dSdTp = 0.0;
	double dSdPt = 0.0;
	double dHdTp = 0.0;
	double dHdPt = 0.0;

	if ((int(_Id->real) <= 0) && (int(_Id->real) > 2))
	{
		return MAKELRESULT(4, 1);
	}
	else
	{
		rgpVUSHCVCPWDERPTSSP(static_cast<const int>(_Id->real), _P->real, &V, &U, &s, &h, &Cv, &Cp, &w, &dVdTp, &dDdTp, &dVdPt, &dDdPt, &dUdTp, &dUdPt, &dSdTp, &dSdPt, &dHdTp, &dHdPt);

	}

	_result->cols = 1;
	_result->rows = 17;

	// Выделение памяти под возвращаемый массив
	if (!MathcadArrayAllocate(_result, _result->rows, _result->cols, TRUE, TRUE))
	{
		// При неудачном выделении возвращаем код ошибки
		return MAKELRESULT(4, 0);
	}

	_result->hReal[0][0] = V;
	_result->hReal[0][1] = U;
	_result->hReal[0][2] = s;
	_result->hReal[0][3] = h;
	_result->hReal[0][4] = Cv;
	_result->hReal[0][5] = Cp;
	_result->hReal[0][6] = w;
	_result->hReal[0][7] = dVdTp;
	_result->hReal[0][8] = dDdTp;
	_result->hReal[0][9] = dVdPt;
	_result->hReal[0][10] = dDdPt;
	_result->hReal[0][11] = dUdTp;
	_result->hReal[0][12] = dUdPt;
	_result->hReal[0][13] = dSdTp;
	_result->hReal[0][14] = dSdPt;
	_result->hReal[0][15] = dHdTp;
	_result->hReal[0][16] = dHdPt;

	_result->hImag[0][0] = 0.0;
	_result->hImag[0][1] = 0.0;
	_result->hImag[0][2] = 0.0;
	_result->hImag[0][3] = 0.0;
	_result->hImag[0][4] = 0.0;
	_result->hImag[0][5] = 0.0;
	_result->hImag[0][6] = 0.0;
	_result->hImag[0][7] = 0.0;
	_result->hImag[0][8] = 0.0;
	_result->hImag[0][9] = 0.0;
	_result->hImag[0][10] = 0.0;
	_result->hImag[0][11] = 0.0;
	_result->hImag[0][12] = 0.0;
	_result->hImag[0][13] = 0.0;
	_result->hImag[0][14] = 0.0;
	_result->hImag[0][15] = 0.0;
	_result->hImag[0][16] = 0.0;

	return 0;
}

FUNCTIONINFO firgpVUSHCVCPWDERPTSSP =
{
	"rgpVUSHCVCPWDERPTSSP",
	"",
	"",
	(LPCFUNCTION)rgpVUSHCVCPWDERPTSSPimpl,
	COMPLEX_ARRAY,
	2,
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// ============================== fs(T, x) ==============================

// плотность в двухфазной области [кг/м3]
	// Входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpDSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDSTX =
{
	"rgpDSTX",
	"",
	"",
	(LPCFUNCTION)rgpDSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельный объём в двухфазной области [м3/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpVSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpVSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpVSTX =
{
	"rgpVSTX",
	"",
	"",
	(LPCFUNCTION)rgpVSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная внутренняя энергия в двухфазной области [Дж/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpUSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpUSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpUSTX =
{
	"rgpUSTX",
	"",
	"",
	(LPCFUNCTION)rgpUSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтропия в двухфазной области [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpSSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpSSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSSTX =
{
	"rgpSSTX",
	"",
	"",
	(LPCFUNCTION)rgpSSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтаьпия в двухфазной области [Дж/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpHSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpHSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpHSTX =
{
	"rgpHSTX",
	"",
	"",
	(LPCFUNCTION)rgpHSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость в двухфазной области [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpCPSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCPSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCPSTX =
{
	"rgpCPSTX",
	"",
	"",
	(LPCFUNCTION)rgpCPSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость в двухфазной области [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpCVSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCVSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCVSTX =
{
	"rgpCVSTX",
	"",
	"",
	(LPCFUNCTION)rgpCVSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// скорость звука в двухфазной области [м/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpWSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpWSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpWSTX =
{
	"rgpWSTX",
	"",
	"",
	(LPCFUNCTION)rgpWSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// показатель изоэнтропы в двухфазной области [м/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpKSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKSTX =
{
	"rgpKSTX",
	"",
	"",
	(LPCFUNCTION)rgpKSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// динамическая вязкость в двухфазной области [Па*с]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpDYNVISSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDYNVISSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDYNVISSTX =
{
	"rgpDYNVISSTX",
	"",
	"",
	(LPCFUNCTION)rgpDYNVISSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// кинематическая вязкость в двухфазной области [м2/с]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpKINVISSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKINVISSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKINVISSTX =
{
	"rgpKINVISSTX",
	"",
	"",
	(LPCFUNCTION)rgpKINVISSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// теплопроводность в двухфазной области [Вт/(м*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpTHERMCONDSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpTHERMCONDSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTHERMCONDSTX =
{
	"rgpTHERMCONDSTX",
	"",
	"",
	(LPCFUNCTION)rgpTHERMCONDSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// число Прандтля в двухфазной области [-]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpPRANDTLESTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpPRANDTLESTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPRANDTLESTX =
{
	"rgpPRANDTLESTX",
	"",
	"",
	(LPCFUNCTION)rgpPRANDTLESTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по энтальпии при постоянном давлении в двухфазной области [1/Па]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpDVDHPSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDHPSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDHPSTX =
{
	"rgpDVDHPSTX",
	"",
	"",
	(LPCFUNCTION)rgpDVDHPSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной энтальпии в двухфазной области [(с2*м4)/кг2]
	// входные параметры:
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpDVDPHSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPHSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPHSTX =
{
	"rgpDVDPHSTX",
	"",
	"",
	(LPCFUNCTION)rgpDVDPHSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по энтальпии при постоянном давлении в двухфазной области [кг*с2/м5]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpDDDHPSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDHPSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDHPSTX =
{
	"rgpDDDHPSTX",
	"",
	"",
	(LPCFUNCTION)rgpDDDHPSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной энтальпии в двухфазной области [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			T - температура [K]
	//			x - степень сухости пара [-]
LRESULT rgpDDDPHSTXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _T, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_T->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_T->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPHSTX(static_cast<const int>(_Id->real), _T->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPHSTX =
{
	"rgpDDDPHSTX",
	"",
	"",
	(LPCFUNCTION)rgpDDDPHSTXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};



// ============================== fs(P, x) ==============================

// плотность в двухфазной области [кг/м3]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpDSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDSPX =
{
	"rgpDSPX",
	"",
	"",
	(LPCFUNCTION)rgpDSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельный объём в двухфазной области [м3/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpVSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpVSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpVSPX =
{
	"rgpVSPX",
	"",
	"",
	(LPCFUNCTION)rgpVSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная внутренняя энергия в двухфазной области [Дж/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpUSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpUSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpUSPX =
{
	"rgpUSPX",
	"",
	"",
	(LPCFUNCTION)rgpUSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтропия в двухфазной области [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpSSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpSSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpSSPX =
{
	"rgpSSPX",
	"",
	"",
	(LPCFUNCTION)rgpSSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная энтаьпия в двухфазной области [Дж/кг]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpHSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpHSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpHSPX =
{
	"rgpHSPX",
	"",
	"",
	(LPCFUNCTION)rgpHSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость в двухфазной области [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpCPSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCPSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCPSPX =
{
	"rgpCPSPX",
	"",
	"",
	(LPCFUNCTION)rgpCPSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// удельная изобарная теплоемкость в двухфазной области [Дж/(кг*К)]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpCVSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpCVSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpCVSPX =
{
	"rgpCVSPX",
	"",
	"",
	(LPCFUNCTION)rgpCVSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// скорость звука в двухфазной области [м/с]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpWSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpWSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpWSPX =
{
	"rgpWSPX",
	"",
	"",
	(LPCFUNCTION)rgpWSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};




// показатель изоэнтропы в двухфазной области [-]
	// Входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpKSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKSPX =
{
	"rgpKSPX",
	"",
	"",
	(LPCFUNCTION)rgpKSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};


// динамическая вязкость в двухфазной области [Па*с]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpDYNVISSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDYNVISSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDYNVISSPX =
{
	"rgpDYNVISSPX",
	"",
	"",
	(LPCFUNCTION)rgpDYNVISSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// кинематическая вязкость в двухфазной области [м2/с]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpKINVISSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpKINVISSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpKINVISSPX =
{
	"rgpKINVISSPX",
	"",
	"",
	(LPCFUNCTION)rgpKINVISSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// теплопроводность в двухфазной области [Вт/(м*К)]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpTHERMCONDSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpTHERMCONDSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpTHERMCONDSPX =
{
	"rgpTHERMCONDSPX",
	"",
	"",
	(LPCFUNCTION)rgpTHERMCONDSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// число Прандтля в двухфазной области [-]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpPRANDTLESPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpPRANDTLESPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpPRANDTLESPX =
{
	"rgpPRANDTLESPX",
	"",
	"",
	(LPCFUNCTION)rgpPRANDTLESPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по энтальпии при постоянном давлении в двухфазной области [1/Па]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpDVDHPSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDHPSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDHPSPX =
{
	"rgpDVDHPSPX",
	"",
	"",
	(LPCFUNCTION)rgpDVDHPSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная удельного объема по давлению при постоянной энтальпии в двухфазной области [(с2*м4)/кг2]
	// входные параметры:
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpDVDPHSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDVDPHSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDVDPHSPX =
{
	"rgpDVDPHSPX",
	"",
	"",
	(LPCFUNCTION)rgpDVDPHSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по энтальпии при постоянном давлении в двухфазной области [кг*с2/м5]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpDDDHPSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDHPSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDHPSPX =
{
	"rgpDDDHPSPX",
	"",
	"",
	(LPCFUNCTION)rgpDDDHPSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};

// производная плотности по давлению при постоянной энтальпии в двухфазной области [с2/м2]
	// входные параметры:
	//			id - идентификатор вещества
	//			P - давление [Па]
	//			x - степень сухости пара [-]
LRESULT rgpDDDPHSPXimpl(COMPLEXSCALAR* const _result, const COMPLEXSCALAR* const _Id, const COMPLEXSCALAR* const _P, const COMPLEXSCALAR* const _x)
{
	if (_Id->imag != 0.0)
	{
		return MAKELRESULT(1, 1);
	}
	if (_P->imag != 0.0)
	{
		return MAKELRESULT(1, 2);
	}
	if (_x->imag != 0.0)
	{
		return MAKELRESULT(1, 3);
	}

	if (_Id->real < 0.0)
	{
		return MAKELRESULT(2, 1);
	}
	if (_P->real < 0.0)
	{
		return MAKELRESULT(2, 2);
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
		_result->real = rgpDDDPHSPX(static_cast<const int>(_Id->real), _P->real, _x->real);
	}

	_result->imag = 0.0;

	return 0;
}

FUNCTIONINFO firgpDDDPHSPX =
{
	"rgpDDDPHSPX",
	"",
	"",
	(LPCFUNCTION)rgpDDDPHSPXimpl,
	COMPLEX_SCALAR,
	3,
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};



BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		if (CreateUserErrorMessageTable(hModule, 5, RGPFunctionErrors))
		{
			// SOURCE
			CreateUserFunction(hModule, &firgpTCRIT);
			CreateUserFunction(hModule, &firgpPCRIT);
			CreateUserFunction(hModule, &firgpDCRIT);

			CreateUserFunction(hModule, &firgpTTRIP);
			CreateUserFunction(hModule, &firgpPTRIP);

			// f(P,T)
			CreateUserFunction(hModule, &firgpSTATEAREAPT);
			CreateUserFunction(hModule, &firgpDPT);
			CreateUserFunction(hModule, &firgpVPT);
			CreateUserFunction(hModule, &firgpUPT);
			CreateUserFunction(hModule, &firgpHPT);
			CreateUserFunction(hModule, &firgpSPT);
			CreateUserFunction(hModule, &firgpCPPT);
			CreateUserFunction(hModule, &firgpCVPT);
			CreateUserFunction(hModule, &firgpWPT);
			CreateUserFunction(hModule, &firgpKPT);
			CreateUserFunction(hModule, &firgpDYNVISPT);
			CreateUserFunction(hModule, &firgpKINVISPT);
			CreateUserFunction(hModule, &firgpTHERMCONDPT);
			CreateUserFunction(hModule, &firgpPRANDTLEPT);
			CreateUserFunction(hModule, &firgpDVDPTPT);
			CreateUserFunction(hModule, &firgpDVDTPPT);
			CreateUserFunction(hModule, &firgpDDDPTPT);
			CreateUserFunction(hModule, &firgpDDDTPPT);
			CreateUserFunction(hModule, &firgpDVDHPPT);
			CreateUserFunction(hModule, &firgpDVDPHPT);
			CreateUserFunction(hModule, &firgpDDDHPPT);
			CreateUserFunction(hModule, &firgpDDDPHPT);
			CreateUserFunction(hModule, &firgpDHDPTPT);
			CreateUserFunction(hModule, &firgpDHDTPPT);
			CreateUserFunction(hModule, &firgpVUSHCVCPWDERPTPT);

			// f(D,T)
			CreateUserFunction(hModule, &firgpPDT);
			CreateUserFunction(hModule, &firgpUDT);
			CreateUserFunction(hModule, &firgpHDT);
			CreateUserFunction(hModule, &firgpSDT);
			CreateUserFunction(hModule, &firgpCPDT);
			CreateUserFunction(hModule, &firgpCVDT);
			CreateUserFunction(hModule, &firgpWDT);
			CreateUserFunction(hModule, &firgpKDT);
			CreateUserFunction(hModule, &firgpDYNVISDT);
			CreateUserFunction(hModule, &firgpKINVISDT);
			CreateUserFunction(hModule, &firgpTHERMCONDDT);
			CreateUserFunction(hModule, &firgpPRANDTLEDT);
			CreateUserFunction(hModule, &firgpDVDPTDT);
			CreateUserFunction(hModule, &firgpDVDTPDT);
			CreateUserFunction(hModule, &firgpDDDPTDT);
			CreateUserFunction(hModule, &firgpDDDTPDT);
			CreateUserFunction(hModule, &firgpDVDHPDT);
			CreateUserFunction(hModule, &firgpDVDPHDT);
			CreateUserFunction(hModule, &firgpDDDHPDT);
			CreateUserFunction(hModule, &firgpDDDPHDT);
			CreateUserFunction(hModule, &firgpDHDPTDT);
			CreateUserFunction(hModule, &firgpDHDTPDT);

			// f(P,h)
			CreateUserFunction(hModule, &firgpSTATEAREAPH);
			CreateUserFunction(hModule, &firgpTPH);
			CreateUserFunction(hModule, &firgpXPH);
			CreateUserFunction(hModule, &firgpDPH);
			CreateUserFunction(hModule, &firgpVPH);
			CreateUserFunction(hModule, &firgpUPH);
			CreateUserFunction(hModule, &firgpSPH);
			CreateUserFunction(hModule, &firgpCPPH);
			CreateUserFunction(hModule, &firgpCVPH);
			CreateUserFunction(hModule, &firgpWPH);
			CreateUserFunction(hModule, &firgpKPH);
			CreateUserFunction(hModule, &firgpDYNVISPH);
			CreateUserFunction(hModule, &firgpKINVISPH);
			CreateUserFunction(hModule, &firgpTHERMCONDPH);
			CreateUserFunction(hModule, &firgpPRANDTLEPH);
			CreateUserFunction(hModule, &firgpDVDPTPH);
			CreateUserFunction(hModule, &firgpDVDTPPH);
			CreateUserFunction(hModule, &firgpDDDPTPH);
			CreateUserFunction(hModule, &firgpDDDTPPH);
			CreateUserFunction(hModule, &firgpDVDHPPH);
			CreateUserFunction(hModule, &firgpDVDPHPH);
			CreateUserFunction(hModule, &firgpDDDHPPH);
			CreateUserFunction(hModule, &firgpDDDPHPH);
			CreateUserFunction(hModule, &firgpDHDPTPH);
			CreateUserFunction(hModule, &firgpDHDTPPH);

			// f(P,s)
			CreateUserFunction(hModule, &firgpSTATEAREAPS);
			CreateUserFunction(hModule, &firgpTPS);
			CreateUserFunction(hModule, &firgpXPS);
			CreateUserFunction(hModule, &firgpDPS);
			CreateUserFunction(hModule, &firgpVPS);
			CreateUserFunction(hModule, &firgpUPS);
			CreateUserFunction(hModule, &firgpHPS);
			CreateUserFunction(hModule, &firgpCPPS);
			CreateUserFunction(hModule, &firgpCVPS);
			CreateUserFunction(hModule, &firgpWPS);
			CreateUserFunction(hModule, &firgpKPS);
			CreateUserFunction(hModule, &firgpDYNVISPS);
			CreateUserFunction(hModule, &firgpKINVISPS);
			CreateUserFunction(hModule, &firgpTHERMCONDPS);
			CreateUserFunction(hModule, &firgpPRANDTLEPS);
			CreateUserFunction(hModule, &firgpDVDPTPS);
			CreateUserFunction(hModule, &firgpDVDTPPS);
			CreateUserFunction(hModule, &firgpDDDPTPS);
			CreateUserFunction(hModule, &firgpDDDTPPS);
			CreateUserFunction(hModule, &firgpDVDHPPS);
			CreateUserFunction(hModule, &firgpDVDPHPS);
			CreateUserFunction(hModule, &firgpDDDHPPS);
			CreateUserFunction(hModule, &firgpDDDPHPS);
			CreateUserFunction(hModule, &firgpDHDPTPS);
			CreateUserFunction(hModule, &firgpDHDTPPS);

			// f(h,s)
			CreateUserFunction(hModule, &firgpSTATEAREAHS);
			CreateUserFunction(hModule, &firgpPHS);
			CreateUserFunction(hModule, &firgpXHS);
			CreateUserFunction(hModule, &firgpTHS);
			CreateUserFunction(hModule, &firgpDHS);
			CreateUserFunction(hModule, &firgpVHS);
			CreateUserFunction(hModule, &firgpUHS);
			CreateUserFunction(hModule, &firgpCPHS);
			CreateUserFunction(hModule, &firgpCVHS);
			CreateUserFunction(hModule, &firgpWHS);
			CreateUserFunction(hModule, &firgpKHS);
			CreateUserFunction(hModule, &firgpDYNVISHS);
			CreateUserFunction(hModule, &firgpKINVISHS);
			CreateUserFunction(hModule, &firgpTHERMCONDHS);
			CreateUserFunction(hModule, &firgpPRANDTLEHS);
			CreateUserFunction(hModule, &firgpDVDPTHS);
			CreateUserFunction(hModule, &firgpDVDTPHS);
			CreateUserFunction(hModule, &firgpDDDPTHS);
			CreateUserFunction(hModule, &firgpDDDTPHS);
			CreateUserFunction(hModule, &firgpDVDHPHS);
			CreateUserFunction(hModule, &firgpDVDPHHS);
			CreateUserFunction(hModule, &firgpDDDHPHS);
			CreateUserFunction(hModule, &firgpDDDPHHS);
			CreateUserFunction(hModule, &firgpDHDPTHS);
			CreateUserFunction(hModule, &firgpDHDTPHS);

			// fs(T)
			CreateUserFunction(hModule, &firgpPST);

			CreateUserFunction(hModule, &firgpDSWT);
			CreateUserFunction(hModule, &firgpVSWT);
			CreateUserFunction(hModule, &firgpUSWT);
			CreateUserFunction(hModule, &firgpSSWT);
			CreateUserFunction(hModule, &firgpHSWT);
			CreateUserFunction(hModule, &firgpCPSWT);
			CreateUserFunction(hModule, &firgpCVSWT);
			CreateUserFunction(hModule, &firgpWSWT);
			CreateUserFunction(hModule, &firgpKSWT);
			CreateUserFunction(hModule, &firgpDYNVISSWT);
			CreateUserFunction(hModule, &firgpKINVISSWT);
			CreateUserFunction(hModule, &firgpTHERMCONDSWT);
			CreateUserFunction(hModule, &firgpPRANDTLESWT);
			CreateUserFunction(hModule, &firgpDVDPTSWT);
			CreateUserFunction(hModule, &firgpDVDTPSWT);
			CreateUserFunction(hModule, &firgpDDDPTSWT);
			CreateUserFunction(hModule, &firgpDDDTPSWT);
			CreateUserFunction(hModule, &firgpDVDHPSWT);
			CreateUserFunction(hModule, &firgpDVDPHSWT);
			CreateUserFunction(hModule, &firgpDDDHPSWT);
			CreateUserFunction(hModule, &firgpDDDPHSWT);
			CreateUserFunction(hModule, &firgpDHDPTSWT);
			CreateUserFunction(hModule, &firgpDHDTPSWT);
			CreateUserFunction(hModule, &firgpVUSHCVCPWDERPTSWT);
			CreateUserFunction(hModule, &firgpSURFTENT);

			CreateUserFunction(hModule, &firgpDSST);
			CreateUserFunction(hModule, &firgpVSST);
			CreateUserFunction(hModule, &firgpUSST);
			CreateUserFunction(hModule, &firgpSSST);
			CreateUserFunction(hModule, &firgpHSST);
			CreateUserFunction(hModule, &firgpCPSST);
			CreateUserFunction(hModule, &firgpCVSST);
			CreateUserFunction(hModule, &firgpWSST);
			CreateUserFunction(hModule, &firgpKSST);
			CreateUserFunction(hModule, &firgpDYNVISSST);
			CreateUserFunction(hModule, &firgpKINVISSST);
			CreateUserFunction(hModule, &firgpTHERMCONDSST);
			CreateUserFunction(hModule, &firgpPRANDTLESST);
			CreateUserFunction(hModule, &firgpDVDPTSST);
			CreateUserFunction(hModule, &firgpDVDTPSST);
			CreateUserFunction(hModule, &firgpDDDPTSST);
			CreateUserFunction(hModule, &firgpDDDTPSST);
			CreateUserFunction(hModule, &firgpDVDHPSST);
			CreateUserFunction(hModule, &firgpDVDPHSST);
			CreateUserFunction(hModule, &firgpDDDHPSST);
			CreateUserFunction(hModule, &firgpDDDPHSST);
			CreateUserFunction(hModule, &firgpDHDPTSST);
			CreateUserFunction(hModule, &firgpDHDTPSST);
			CreateUserFunction(hModule, &firgpVUSHCVCPWDERPTSST);

			// fs(P)
			CreateUserFunction(hModule, &firgpTSP);

			CreateUserFunction(hModule, &firgpDSWP);
			CreateUserFunction(hModule, &firgpVSWP);
			CreateUserFunction(hModule, &firgpUSWP);
			CreateUserFunction(hModule, &firgpSSWP);
			CreateUserFunction(hModule, &firgpHSWP);
			CreateUserFunction(hModule, &firgpCPSWP);
			CreateUserFunction(hModule, &firgpCVSWP);
			CreateUserFunction(hModule, &firgpWSWP);
			CreateUserFunction(hModule, &firgpKSWP);
			CreateUserFunction(hModule, &firgpDYNVISSWP);
			CreateUserFunction(hModule, &firgpKINVISSWP);
			CreateUserFunction(hModule, &firgpTHERMCONDSWP);
			CreateUserFunction(hModule, &firgpPRANDTLESWP);
			CreateUserFunction(hModule, &firgpDVDPTSWP);
			CreateUserFunction(hModule, &firgpDVDTPSWP);
			CreateUserFunction(hModule, &firgpDDDPTSWP);
			CreateUserFunction(hModule, &firgpDDDTPSWP);
			CreateUserFunction(hModule, &firgpDVDHPSWP);
			CreateUserFunction(hModule, &firgpDVDPHSWP);
			CreateUserFunction(hModule, &firgpDDDHPSWP);
			CreateUserFunction(hModule, &firgpDDDPHSWP);
			CreateUserFunction(hModule, &firgpDHDPTSWP);
			CreateUserFunction(hModule, &firgpDHDTPSWP);
			CreateUserFunction(hModule, &firgpVUSHCVCPWDERPTSWP);

			CreateUserFunction(hModule, &firgpDSSP);
			CreateUserFunction(hModule, &firgpVSSP);
			CreateUserFunction(hModule, &firgpUSSP);
			CreateUserFunction(hModule, &firgpSSSP);
			CreateUserFunction(hModule, &firgpHSSP);
			CreateUserFunction(hModule, &firgpCPSSP);
			CreateUserFunction(hModule, &firgpCVSSP);
			CreateUserFunction(hModule, &firgpWSSP);
			CreateUserFunction(hModule, &firgpKSSP);
			CreateUserFunction(hModule, &firgpDYNVISSSP);
			CreateUserFunction(hModule, &firgpKINVISSSP);
			CreateUserFunction(hModule, &firgpTHERMCONDSSP);
			CreateUserFunction(hModule, &firgpPRANDTLESSP);
			CreateUserFunction(hModule, &firgpDVDPTSSP);
			CreateUserFunction(hModule, &firgpDVDTPSSP);
			CreateUserFunction(hModule, &firgpDDDPTSSP);
			CreateUserFunction(hModule, &firgpDDDTPSSP);
			CreateUserFunction(hModule, &firgpDVDHPSSP);
			CreateUserFunction(hModule, &firgpDVDPHSSP);
			CreateUserFunction(hModule, &firgpDDDHPSSP);
			CreateUserFunction(hModule, &firgpDDDPHSSP);
			CreateUserFunction(hModule, &firgpDHDPTSSP);
			CreateUserFunction(hModule, &firgpDHDTPSSP);
			CreateUserFunction(hModule, &firgpVUSHCVCPWDERPTSSP);

			// f(T,x)
			CreateUserFunction(hModule, &firgpDSTX);
			CreateUserFunction(hModule, &firgpVSTX);
			CreateUserFunction(hModule, &firgpUSTX);
			CreateUserFunction(hModule, &firgpSSTX);
			CreateUserFunction(hModule, &firgpHSTX);
			CreateUserFunction(hModule, &firgpCPSTX);
			CreateUserFunction(hModule, &firgpCVSTX);
			CreateUserFunction(hModule, &firgpWSTX);
			CreateUserFunction(hModule, &firgpKSTX);
			CreateUserFunction(hModule, &firgpDYNVISSTX);
			CreateUserFunction(hModule, &firgpKINVISSTX);
			CreateUserFunction(hModule, &firgpTHERMCONDSTX);
			CreateUserFunction(hModule, &firgpPRANDTLESTX);
			CreateUserFunction(hModule, &firgpDVDHPSTX);
			CreateUserFunction(hModule, &firgpDVDPHSTX);
			CreateUserFunction(hModule, &firgpDDDHPSTX);
			CreateUserFunction(hModule, &firgpDDDPHSTX);

			// f(P,x)
			CreateUserFunction(hModule, &firgpDSPX);
			CreateUserFunction(hModule, &firgpVSPX);
			CreateUserFunction(hModule, &firgpUSPX);
			CreateUserFunction(hModule, &firgpSSPX);
			CreateUserFunction(hModule, &firgpHSPX);
			CreateUserFunction(hModule, &firgpCPSPX);
			CreateUserFunction(hModule, &firgpCVSPX);
			CreateUserFunction(hModule, &firgpWSPX);
			CreateUserFunction(hModule, &firgpKSPX);
			CreateUserFunction(hModule, &firgpDYNVISSPX);
			CreateUserFunction(hModule, &firgpKINVISSPX);
			CreateUserFunction(hModule, &firgpTHERMCONDSPX);
			CreateUserFunction(hModule, &firgpPRANDTLESPX);
			CreateUserFunction(hModule, &firgpDVDHPSPX);
			CreateUserFunction(hModule, &firgpDVDPHSPX);
			CreateUserFunction(hModule, &firgpDDDHPSPX);
			CreateUserFunction(hModule, &firgpDDDPHSPX);
		};
	}
	break;
	}
	return TRUE;
}

