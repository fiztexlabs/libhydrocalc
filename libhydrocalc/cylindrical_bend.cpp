#include <libhydrocalc/cylindrical_bend.h>
#include <libmath/boolean.h>
#include <cmath>
#include <libhydrocalc/settings.h>
#include <algorithm>

using namespace hydrocalc;

real CylindricalBend::checkGeometry(const std::vector<real>& G)
{
	real err = 0.0;

	if (CurrentSettings_.checkInputs)
	{
		if (G.at(0) < 0.0)
		{
			err += procInvalidValue("rou (roughness) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set rou (roughness) < 0.0"));
		}
		if (G.at(1) <= 0.0)
		{
			err += procInvalidValue("D0 (hydraulic diameter) <= 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set D0 (hydraulic diameter) <= 0.0"));
		}
		if (G.at(4) < 0.0)
		{
			err += procInvalidValue("R0 (bending radius) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set R0 (bending radius) < 0.0"));
		}
		if (G.at(4) < 0.0)
		{
			err += procInvalidValue("L0 (previous section length) < 0.0", ExceptionInvalidValue(type_ + " element " + name_ + ": try to set L0 (previous section length) < 0.0"));
		}
	}

	return err;
}

void CylindricalBend::evaluate()
{
	A_ = M_PI * std::pow(0.5 * D0_, 2.0);
	relRou_ = rou_ / D0_;

	real reversed = checkReversedFlow("Re < 0.0", ExceptionReversedFlow("reversed flow in the " + type_ + " element " + name_));

	if (std::isnan(reversed))
	{
		lf_ = reversed;
		CSI_ = reversed;
		CSIlr_ = reversed;
		CSIlf_ = reversed;
	}
	else
	{
		// direction independent
		real Re = std::abs(Re_);

		if (math::isEqual<real, real>(Re, static_cast<real>(0.0)))
		{
			CSI_ = CurrentSettings_.MAX_CSI;
			CSIlf_ = 0.0;
			CSIlr_ = CurrentSettings_.MAX_CSI;
			lf_ = 0.0;
		}
		else
		{
			FrictionPart_.evaluate();
			lf_ = FrictionPart_.getRelFrictionCoeff();

			// remember values, calculated for friction part
			real friction_CSIlf = FrictionPart_.CSIlf_;
			real friction_CSIlr = FrictionPart_.CSIlr_;
			real friction_CSI = FrictionPart_.CSI_;

			real RD = R0_ / D0_;

			// from diagram 6-1
			real kRe = 0.0;
			if (RD <= 0.55)
			{
				kRe = 1.0 + 4400.0 / Re;
			}
			if ((RD > 0.55) && (RD <= 0.7))
			{
				kRe = 5.45 / std::pow(Re, 0.131);
			}
			if (RD > 0.7)
			{
				kRe = 1.3 - 0.29 * std::log(Re * 10.e-5);
			}
			//from plot b
			kRe = std::max(kRe, 1.0);

			// from diagram 6-1
			real klf = 0.0;
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
						real lfSmooth_ = 0.0;
						// calculate friction coefficient for smooth wall
						FrictionPart_.setRou(0.0);
						FrictionPart_.evaluate();
						klf = lf_ / FrictionPart_.getRelFrictionCoeff();

						// return real value of lf to FrictionPart object
						FrictionPart_.rou_ = rou_;
						FrictionPart_.lf_ = lf_;
						FrictionPart_.CSIlf_ = friction_CSIlf;
						FrictionPart_.CSIlr_ = friction_CSIlr;
						FrictionPart_.CSI_ = friction_CSI;
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
			real A1 = 0.0;
			// approximation of plot a
			if (delta_ <= 160.0)
			{
				A1 = -0.0000393540143182754 * std::pow(delta_, 2.0) + 0.0133768215757644 * delta_ + 0.0157345210469009;
			}
			else
			{
				A1 = 0.7 + 0.35 * (delta_ / 90.0);
			}

			// diagram 6-1
			if ((RD > 0.5) && (RD < 3.0))
			{
				diagram_ = "6-1";

				real err{ 0.0 };

				if (CurrentSettings_.GeometryOutOfRangeMode != settings::GeometryOutOfRangeBehaviorMode::NoCheck)
				{
					// check bending radius for diagram 6-1
					if (RD < 0.5)
					{
						err += procGeometryOutOfRange("R0/D0 = " + std::to_string(RD) + " < 0.5", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": R0/D0 < 0.5"));
					}
					// check relative length
					if (L0_ / D0_ < 10.0)
					{
						err += procGeometryOutOfRange("L0/D0 = " + std::to_string(L0_ / D0_) + " < 10.0", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": L0/D0 < 10.0"));
					}
					// check angle
					if (delta_ > 180.0)
					{
						err += procGeometryOutOfRange("delta (bending angle) = " + std::to_string(delta_) + " < 180.0 deg", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": delta (bending angle) < 180.0"));
					}

					if (std::isnan(err))
					{
						CSIlf_ = err;
						CSIlr_ = err;
						CSI_ = err;

						return void();
					}
				}

				real B1 = 0.0;
				if (RD < 1.0)
				{
					B1 = 0.21 * std::pow((RD), -2.5);
				}
				// approximation of plots b, v
				else
				{
					B1 = 0.32671971103835 * std::pow((RD), -0.684096233583221);
				}

				CSIlr_ = A1 * B1;
				CSIlf_ = 0.0175 * delta_ * lf_ * (RD);

				// smooth wall
				if (rou_ == 0.0)
				{
					real err{ 0.0 };

					if (CurrentSettings_.FlowOutOfRangeMode != settings::FlowOutOfRangeBehaviorMode::NoCheck)
					{
						// check Re for diagram 6-1
						if (Re < 2.e5)
						{
							err = procFlowOutOfRange("Re = " + std::to_string(Re) + " < 2.e5", ExceptionFlowOutOfRange(type_ + " element " + name_ + ": Re < 2.e5"));
						}

						if (std::isnan(err))
						{
							CSIlf_ = err;
							CSIlr_ = err;
							CSI_ = err;

							return void();
						}
					}

					CSI_ = CSIlr_ + CSIlf_;
				}
				// roughness wall
				else
				{
					real err{ 0.0 };

					if (CurrentSettings_.FlowOutOfRangeMode != settings::FlowOutOfRangeBehaviorMode::NoCheck)
					{
						// check Re for diagram 6-1
						if (Re < 3.3e3)
						{
							err = procFlowOutOfRange("Re = " + std::to_string(Re) + " < 3.3e3", ExceptionFlowOutOfRange(type_ + " element " + name_ + ": Re < 3.3e3"));
						}

						if (std::isnan(err))
						{
							CSIlf_ = err;
							CSIlr_ = err;
							CSI_ = err;

							return void();
						}
					}
					if ((Re >= 3.3e3) && (Re < 1.e4))
					{
						real A2 = 0.0;
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

				return void();
			}

			// diagram 6-2
			if (RD >= 3)
			{
				diagram_ = "6-2";

				real err{ 0.0 };

				if (CurrentSettings_.GeometryOutOfRangeMode != settings::GeometryOutOfRangeBehaviorMode::NoCheck)
				{
					// check relative length
					if (L0_ / D0_ < 10.0)
					{
						err += procGeometryOutOfRange("L0/D0 = " + std::to_string(L0_ / D0_) + " < 10.0", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": L0/D0 < 10.0"));
					}

					if (std::isnan(err))
					{
						CSIlf_ = err;
						CSIlr_ = err;
						CSI_ = err;

						return void();
					}
				}

				real ReRD = Re * std::sqrt(D0_ / (2.0 * R0_));

				if (CurrentSettings_.FlowOutOfRangeMode != settings::FlowOutOfRangeBehaviorMode::NoCheck)
				{
					// check ReRD = f(Re, R, D) complex
					if (ReRD <= 50.0)
					{
						real botReLim = 50.0 / std::sqrt(D0_ / (2.0 * R0_));
						err += procFlowOutOfRange("Re = " + std::to_string(Re) + " < " + std::to_string(botReLim),
							ExceptionFlowOutOfRange(type_ + " element " + name_ + ": Re < " + std::to_string(botReLim)));
					}
					// check Re for diagram 6-2
					if (Re > 8.e4)
					{
						err = procFlowOutOfRange("Re = " + std::to_string(Re) + " > 8.e4", ExceptionFlowOutOfRange(type_ + " element " + name_ + ": Re < 8.e4"));
					}

					if (std::isnan(err))
					{
						CSIlf_ = err;
						CSIlr_ = err;
						CSI_ = err;

						return void();
					}
				}

				if (ReRD <= 5000)
				{
					if (ReRD <= 600.0)
					{
						lf_ = (20.0 / std::pow(Re, 0.65)) * std::pow((D0_ / (2.0 * R0_)), 0.175);
					}
					if ((ReRD > 600.0) && (ReRD <= 1400.0))
					{
						lf_ = (10.4 / std::pow(Re, 0.55)) * std::pow((D0_ / (2.0 * R0_)), 0.225);
					}
					if ((ReRD > 1400.0) && (ReRD <= 5000.0))
					{
						lf_ = (5.0 / std::pow(Re, 0.45)) * std::pow((D0_ / (2.0 * R0_)), 0.275);
					}
				}

				CSIlr_ = 0.0;
				CSIlf_ = 0.0175 * lf_ * delta_ * RD;
				CSI_ = CSIlr_ + CSIlf_;

				return void();
			}

			// diagram 6-7
			if (RD == 0.0)
			{
				diagram_ = "6-7";

				real err{ 0.0 };

				if (CurrentSettings_.GeometryOutOfRangeMode != settings::GeometryOutOfRangeBehaviorMode::NoCheck)
				{
					// check relative length
					if (L0_ / D0_ < 10.0)
					{
						err += procGeometryOutOfRange("L0/D0 = " + std::to_string(L0_ / D0_) + " < 10.0", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": L0/D0 < 10.0"));
					}

					if (std::isnan(err))
					{
						CSIlf_ = err;
						CSIlr_ = err;
						CSI_ = err;

						return void();
					}
				}

				real A = 0.95 + 33.5 / delta_;
				CSIlr_ = 0.95 * std::pow(sin((0.5 * delta_) / (180.0 / M_PI)), 2.0) + 2.05 * std::pow(sin((0.5 * delta_) / (180.0 / M_PI)), 4.0);
				CSIlf_ = 0.0;

				if (rou_ == 0.0)
				{
					real err{ 0.0 };

					if (CurrentSettings_.FlowOutOfRangeMode != settings::FlowOutOfRangeBehaviorMode::NoCheck)
					{
						// check Re for diagram 6-7
						if (Re < 2.e5)
						{
							err += procFlowOutOfRange("Re = " + std::to_string(Re) + " < 2.e5", ExceptionFlowOutOfRange(type_ + " element " + name_ + ": Re < 2.e5"));
						}

						if (std::isnan(err))
						{
							CSIlf_ = err;
							CSIlr_ = err;
							CSI_ = err;

							return void();
						}
					}
					CSI_ = CSIlr_ * A;
				}
				else
				{
					diagram_ = "6-7/6-6";

					real err{ 0.0 };

					if (CurrentSettings_.FlowOutOfRangeMode != settings::FlowOutOfRangeBehaviorMode::NoCheck)
					{
						// check Re for diagram 6-7
						if (Re < 1.e4)
						{
							err += procFlowOutOfRange("Re = " + std::to_string(Re) + " < 1.e4", ExceptionFlowOutOfRange(type_ + " element " + name_ + ": Re < 1.e4"));
						}
						// check Re for diagram 6-6
						if (Re < 3.e3)
						{
							err += procFlowOutOfRange("Re = " + std::to_string(Re) + " < 3.e3", ExceptionFlowOutOfRange(type_ + " element " + name_ + ": Re < 3.e3"));
						}

						if (std::isnan(err))
						{
							CSIlf_ = err;
							CSIlr_ = err;
							CSI_ = err;

							return void();
						}
					}

					real kRe = 0.0;
					kRe = 4.06 / std::pow(Re, 0.118);

					real kf = 0.0;
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

				return void();
			}

			// diagram 6-9
			if (RD <= 0.5)
			{
				diagram_ = "6-9";

				real err{ 0.0 };

				if (CurrentSettings_.GeometryOutOfRangeMode != settings::GeometryOutOfRangeBehaviorMode::NoCheck)
				{
					// check bending radius for diagram 6-9
					if (RD < 0.05)
					{
						err += procGeometryOutOfRange("R0/D0 = " + std::to_string(RD) + " < 0.05", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": R0/D0 < 0.05"));
					}
					// check relative length
					if (L0_ / D0_ < 10.0)
					{
						err += procGeometryOutOfRange("L0/D0 = " + std::to_string(L0_ / D0_) + " < 10.0", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": L0/D0 < 10.0"));
					}
					// check angle
					if (delta_ > 180.0)
					{
						err += procGeometryOutOfRange("delta (bending angle) = " + std::to_string(delta_) + " < 180.0 deg", ExceptionGeometryOutOfRange(type_ + " element " + name_ + ": delta (bending angle) < 180.0"));
					}

					if (std::isnan(err))
					{
						CSIlf_ = err;
						CSIlr_ = err;
						CSI_ = err;

						return void();
					}
				}

				CSIlf_ = (1.0 + 0.0175 * (180.0 - delta_) * RD) * lf_;
				real B1 = 0.155 * std::pow(RD, -0.595);
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
	}
}

HydraulicResistance* CylindricalBend::copy() const
{
	return new CylindricalBend(
		Re_,
		{
			rou_,
			D0_,
			R0_,
			delta_,
			L0_
		},
		name_
	);
}

void CylindricalBend::setGeometry(const std::vector<real>& G)
{
	real err = checkGeometry(G);

	if (std::isnan(err))
	{
		rou_ = err;
		D0_ = err;
		L_ = err;
		L0_ = err;
		R0_ = err;
		delta_ = err;
	}
	else
	{
		rou_ = G.at(0);
		D0_ = G.at(1);
		L0_ = G.at(4);
		R0_ = G.at(2);
		delta_ = G.at(3);
	}

	FrictionPart_.setGeometry({ rou_, D0_, L_ });
}

void CylindricalBend::getGeometry(std::vector<real>& G)
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
