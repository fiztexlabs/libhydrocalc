#include <pch.h>
#include <HydraulicResistances/CylindricalBend.h>
#include <math/mathlib.h>

void CylindricalBend::errorHandling()
{
	if (flagHandleWarnings)
	{
		if (Re_ < 0.0)
		{
			std::cerr << "%inf reversed flow in the element " << id_ << " (" << name_ << ")\n";
		}
	}
}

void CylindricalBend::errorHandling(const HSReal Re, const std::vector<HSReal>& G)
{
	if (flagHandleWarnings)
	{
		if (G.size() > 5)
		{
			std::cerr << "%warn size of vector of geometry characteristics more than 5 in the element " << id_ << " (" << name_ << ")\n";
		}
	}
	if (G.size() < 5)
	{
		std::cerr << "%err size of input vector of geometry characteristics less than 5 in the element " << id_ << " (" << name_ << ")\n";
		exit(1);
	}
	if (G[0] < 0.0)
	{
		std::cerr << "%err invalid value of G, roughness rou (G[0]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[1] <= 0.0)
	{
		std::cerr << "%err invalid value of G, diameter of channel D0 (G[1]) must be > 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[2] < 0.0)
	{
		std::cerr << "%err invalid value of G, bending radius R0 (G[2]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
	if (G[4] < 0.0)
	{
		std::cerr << "%err invalid value of G, length of straght section L0 before bend (G[4]) must be >= 0.0 in the element " << id_ << " (" << name_ << ")\n";
		exit(2);
	}
}

void CylindricalBend::calculateElement()
{
	if (calculated)
	{
		return void();
	}

	// chek values
	errorHandling();
	// direction independent
	HSReal Re = abs(Re_);

	A_ = M_PI * pow(0.5 * D0_, 2.0);
	relRou_ = rou_ / D0_;

	if (math::isEqual<HSReal, HSReal>(Re, static_cast<HSReal>(0.0)))
	{
		CSI_ = 0.0;
		CSIlf_ = 0.0;
		CSIlr_ = 0.0;
		lf_ = 0.0;
	}
	else
	{
		FrictionPart.setGeometry({ rou_,D0_,0.0 });
		FrictionPart.setRe(Re);
		if (!autocalc)
		{
			FrictionPart.calculateElement();
		}
		lf_ = FrictionPart.getRelFrictionCoeff();

		HSReal RD = R0_ / D0_;

		// from diagram 6-1
		HSReal kRe = 0.0;
		if (RD <= 0.55)
		{
			kRe = 1.0 + 4400.0 / Re;
		}
		if ((RD > 0.55) && (RD <= 0.7))
		{
			kRe = 5.45 / pow(Re, 0.131);
		}
		if (RD > 0.7)
		{
			kRe = 1.3 - 0.29 * log(Re * 10.e-5);
		}
		//from blot b
		kRe = max(kRe, 1.0);

		// from diagram 6-1
		HSReal klf = 0.0;
		if (relRou_ == 0.0)
		{
			klf = 1.0;
		}
		if (RD > 0.55)
		{
			if ((relRou_ > 0.0) && (relRou_ <= 0.001))
			{
				if (Re <= 4.e4)
				{
					klf = 1.0;
				}
				if ((Re > 4.e4) && (Re <= 2.e5))
				{
					HSReal lfSmooth_ = 0.0;
					// calculate friction coefficient for smooth wall
					FrictionPart.setRou(0.0);
					if (!autocalc)
					{
						FrictionPart.calculateElement();
					}
					klf = lf_ / FrictionPart.getRelFrictionCoeff();

					// return real value of lf to FrictionPart object
					FrictionPart.setRou(rou_);
					if (!autocalc)
					{
						FrictionPart.calculateElement();
					}
				}
				if (Re > 2.e5)
				{
					klf = 1.0 + relRou_ * 1.e3;
				}
			}
			if (relRou_ > 0.001)
			{
				if (Re <= 4.e4)
				{
					klf = 1.0;
				}
				if ((Re > 4.e4) && (Re <= 2.e5))
				{
					klf = 2.0;
				}
				if (Re > 2.e5)
				{
					klf = 2.0;
				}
			}
		}
		else
		{
			// 0.5 <= Re <= 0.55
			if ((relRou_ > 0.0) && (relRou_ <= 0.001))
			{
				if (Re <= 4.e4)
				{
					klf = 1.0;
				}
				if (Re > 4.e4)
				{
					klf = 1.0 + relRou_ * 0.5e3;
				}
			}
			if (relRou_ > 0.001)
			{
				if (Re <= 4.e4)
				{
					klf = 1.0;
				}
				if (Re > 4.e4)
				{
					klf = 1.5;
				}
			}

		}
		// from diagram 6-1
		HSReal A1 = 0.0;
		// approximation of plot a
		if (delta_ <= 160.0)
		{
			A1 = -0.0000393540143182754 * pow(delta_, 2.0) + 0.0133768215757644 * delta_ + 0.0157345210469009;
		}
		else
		{
			A1 = 0.7 + 0.35 * (delta_ / 90.0);
		}

		// diagram 6-1
		if ((RD > 0.5) && (RD < 3.0))
		{
			diagram_ = "6-1";
			if (flagHandleWarnings)
			{
				// check bending radius for diagram 6-1
				if (RD < 0.5)
				{
					std::cerr << "%warn R0/D0 = " << RD << " less than 0.5 in the element " << id_ << " (" << name_ << ") (diagram 6-1)\n";
				}
				// check relative length
				if (L0_ / D0_ < 10.0)
				{
					std::cerr << "%warn L0/D0 = " << L0_ / D0_ << " less than 10.0 in the element " << id_ << " (" << name_ << ") (diagram 6-1)\n";
				}
				// check angle
				if (delta_ > 180.0)
				{
					std::cerr << "%warn bending angle = " << delta_ << " more than 180.0 degree in the element " << id_ << " (" << name_ << ") (diagram 6-1)\n";
				}
			}

			HSReal B1 = 0.0;
			if (RD < 1.0)
			{
				B1 = 0.21 * pow((RD), -2.5);
			}
			// approximation of plots b, v
			else
			{
				B1 = 0.32671971103835 * pow((RD), -0.684096233583221);
			}

			CSIlr_ = A1 * B1;
			CSIlf_ = 0.0175 * delta_ * lf_ * (RD);

			// smooth wall
			if (rou_ == 0.0)
			{
				if (flagHandleWarnings)
				{
					// check Re for diagram 6-1
					if (Re < 2.e5)
					{
						std::cerr << "%warn Re = " << Re << " less than 2.e5 in the element " << id_ << " (" << name_ << ") (diagram 6-1)\n";
					}
				}

				CSI_ = CSIlr_ + CSIlf_;
			}
			// roughness wall
			else
			{
				if (flagHandleWarnings)
				{
					// check Re for diagram 6-1
					if (Re < 3.3e3)
					{
						std::cerr << "%warn Re = " << Re << " less than 3.3e3 in the element " << id_ << " (" << name_ << ") (diagram 6-1)\n";
					}
				}
				if ((Re >= 3.3e3) && (Re < 1.e4))
				{
					HSReal A2 = 0.0;
					if (RD <= 0.55)
					{
						A2 = 4.e3;
					}
					if ((RD > 0.55) && (RD <= 0.7))
					{
						A2 = 6.e3;
					}
					if ((RD > 0.7) && (RD <= 1.0))
					{
						A2 = -2.e3 * ((RD - 0.2) / 0.3) + 4.e3;
					}
					if ((RD > 1.0) && (RD <= 2.0))
					{
						A2 = 1.e3;
					}
					if (RD > 2.0)
					{
						A2 = 0.6e3;
					}
					CSI_ = (A2 / Re) + CSIlr_ + CSIlf_;
				}
				if (Re >= 1.e4)
				{
					CSI_ = klf * kRe * CSIlr_ + CSIlf_;
				}
			}

		}

		// diagram 6-2
		if (RD >= 3)
		{
			diagram_ = "6-2";
			if (flagHandleWarnings)
			{
				// check relative length
				if (L0_ / D0_ < 10.0)
				{
					std::cerr << "%warn L0/D0 = " << L0_ / D0_ << " less than 10.0 in the element " << id_ << " (" << name_ << ") (diagram 6-2)\n";
				}
			}
			
			HSReal ReRD = Re * sqrt(D0_ / (2.0 * R0_));
			if (flagHandleWarnings)
			{
				// check ReRD = f(Re, R, D) complex
				if (ReRD <= 50.0)
				{
					HSReal botReLim = 50.0 / sqrt(D0_ / (2.0 * R0_));
					std::cerr << "%warn Re = " << Re << " less than " << botReLim << ", that leads to Re*sqrt(D0/(2*R0)) = " 
						<< ReRD << " less than 50.0 in the element " << id_ << " (" << name_ << ") (diagram 6-2)\n";
				}
				// check Re for diagram 6-2
				if (Re > 8.e4)
				{
					std::cerr << "%warn Re = " << Re << " more than 8e4 in the element " << id_ << " (" << name_ << ") (diagram 6-2)\n";
				}
			}

			if (ReRD <= 5000)
			{
				if (ReRD <= 600.0)
				{
					lf_ = (20.0 / pow(Re, 0.65)) * pow((D0_ / (2.0 * R0_)), 0.175);
				}
				if ((ReRD > 600.0) && (ReRD <= 1400.0))
				{
					lf_ = (10.4 / pow(Re, 0.55)) * pow((D0_ / (2.0 * R0_)), 0.225);
				}
				if ((ReRD > 1400.0) && (ReRD <= 5000.0))
				{
					lf_ = (5.0 / pow(Re, 0.45)) * pow((D0_ / (2.0 * R0_)), 0.275);
				}
			}

			CSIlr_ = 0.0;
			CSIlf_ = 0.0175 * lf_ * delta_ * RD;
			CSI_ = CSIlr_ + CSIlf_;
		}

		// diagram 6-7
		if (RD == 0.0)
		{
			diagram_ = "6-7";
			if (flagHandleWarnings)
			{
				// check relative length for diagram 6-7
				if (L0_ / D0_ < 10.0)
				{
					std::cerr << "%warn L0/D0 = " << L0_ / D0_ << " less than 10.0 in the element " << id_ << " (" << name_ << ") (diagram 6-7)\n";
				}
			}

			HSReal A = 0.95 + 33.5 / delta_;
			CSIlr_ = 0.95 * pow(sin((0.5 * delta_) / (180.0 / M_PI)), 2.0) + 2.05 * pow(sin((0.5 * delta_) / (180.0 / M_PI)), 4.0);
			CSIlf_ = 0.0;
			if (rou_ == 0.0)
			{
				if (flagHandleWarnings)
				{
					// check Re for diagram 6-7
					if (Re < 2.e5)
					{
						std::cerr << "%warn Re = " << Re << " less than 2.e5 in the element " << id_ << " (" << name_ << ") (diagram 6-7)\n";
					}
				}
				CSI_ = CSIlr_ * A;
			}
			else
			{
				if (flagHandleWarnings)
				{
					// check Re for diagram 6-7
					if (Re < 1.e4)
					{
						std::cerr << "%warn Re = " << Re << " less than 1.e4 in the element " << id_ << " (" << name_ << ") (diagram 6-7)\n";
					}
					// check Re for diagram 6-6
					if (Re < 3.e3)
					{
						std::cerr << "%warn Re = " << Re << " less than 3.e3 in the element " << id_ << " (" << name_ << ") (diagram 6-6)\n";
					}
				}

				diagram_ = "6-7/6-6";

				HSReal kRe = 0.0;
				kRe = 4.06 / pow(Re, 0.118);

				HSReal kf = 0.0;
				if (Re < 40.e3)
				{
					kf = 1.0;
				}
				else
				{
					if (relRou_ == 0.0)
					{
						kf = 1.0;
					}
					if ((relRou_ > 0.0) && (relRou_ <= 0.001))
					{
						kf = 1.0 + 0.5e3 * relRou_;
					}
					if (relRou_ > 0.001)
					{
						kf = 1.5;
					}
				}
				CSI_ = kRe * kf * A * CSIlr_;

			}
		}

		// diagram 6-9
		if (RD <= 0.5)
		{
			diagram_ = "6-9";
			if (flagHandleWarnings)
			{
				// check bending radius for diagram 6-1
				if (RD < 0.05)
				{
					std::cerr << "%warn R0/D0 = " << RD << " less than 0.05 in the element " << id_ << " (" << name_ << ") (diagram 6-9)\n";
				}
				// check relative length
				if (L0_ / D0_ < 10.0)
				{
					std::cerr << "%warn L0/D0 = " << L0_ / D0_ << " less than 10.0 in the element " << id_ << " (" << name_ << ") (diagram 6-9)\n";
				}
				// check angle
				if (delta_ > 180.0)
				{
					std::cerr << "%warn bending angle = " << delta_ << " more than 180.0 degree in the element " << id_ << " (" << name_ << ") (diagram 6-9)\n";
				}
			}

			CSIlf_ = (1.0 + 0.0175 * (180.0 - delta_) * RD) * lf_;
			HSReal B1 = 0.155 * pow(RD, -0.595);
			CSIlr_ = A1 * B1;

			// smooth wall
			if (relRou_ == 0.0)
			{
				CSI_ = CSIlr_ + CSIlf_;
			}
			//rougth wall
			else
			{
				CSI_ = klf * kRe * CSIlr_ + CSIlf_;
			}


		}
	}

	calculated = 1;
	changed = 0;
}

IBaseHydraulicResistance* CylindricalBend::copy() const
{
	return new CylindricalBend(name_, Re_,
		{
			rou_,
			D0_,
			R0_,
			delta_,
			L0_
		}
	);
}

void CylindricalBend::setGeometry(const std::vector<HSReal>& G)
{
	errorHandling(Re_, G);

	if ((G[0] != rou_) || (G[1] != D0_) || (G[2] != R0_) || (G[3] != delta_) || (G[4] != L0_))
	{
		rou_ = G[0];
		D0_ = G[1];
		L0_ = G[4];
		R0_ = G[2];
		delta_ = G[3];

		changed = 1;
		calculated = 0;
		if (autocalc)
		{
			calculateElement();
		}
	}
}

void CylindricalBend::getGeometry(std::vector<HSReal>& G)
{
	G =
	{
		rou_,
		D0_,
		R0_,
		delta_,
		L0_,
		A_
	};
}

HSReal CylindricalBend::getLength()
{
	if (L_ > 0.0)
	{
		return L_;
	}
	else
	{
		return 1.e-6;
	}
}

void CylindricalBend::setLength(const HSReal L)
{
	L_ = L;
	changed = 1;
	calculated = 0;
	if (autocalc)
	{
		calculateElement();
	}
}
