#ifndef DA_KE27_H
#define DA_KE27_H

/* 2-7 */
/* 
Inputs number               : 2
Outputs number              : 1
Input Variables             :
  Input # 0
    name                    : e
    variability             : continuous
  Input # 1
    name                    : dD
    variability             : continuous
Output Variables            :
  Output # 0
    name                    : ke
    variability             : continuous
Accuracy evaluation         : AVAILABLE
Outputs rearrangement       : NOT AVAILABLE
Probability estimation      : NOT AVAILABLE
Additionally smoothed model : NO
Technique used              : TGP
Training points number      : 12
Training options            :
  GTApprox/Accelerator=3
  GTApprox/GPLearningMode=Accurate
  GTApprox/GPPower=2
  GTApprox/InputNanMode=ignore
  GTApprox/InternalValidation=false
  GTApprox/IVSavePredictions=true
  GTApprox/OutputNanMode=ignore
  GTApprox/OutputTransformation=["none"]
  GTApprox/StoreTrainingSample=True
  GTApprox/Technique=TGP
  GTApprox/TensorFactors=[[0,"Auto"],[1,"Auto"]]
Training hints              :
    @GTApprox/TrainingSubsampleRatio=0
Statistics of the input part of the training sample:
  NaN Count: [0, 0]
  Inf Count: [0, 0]
  Count: [12, 12]
  Min: [0, 0.5]
  Max: [1, 0.69999999999999996]
  Range: [1, 0.19999999999999996]
  Mean: [0.5, 0.59999999999999998]
  Std: [0.35675303400633795, 0.10444659357341868]
  Var: [0.12727272727272732, 0.010909090909090903]
  Q1: [0.20000000000000001, 0.5]
  Median: [0.59999999999999998, 0.69999999999999996]
  Q3: [0.80000000000000004, 0.69999999999999996]
  IQR: [0.60000000000000009, 0.19999999999999996]
  Q_0.01: [0, 0.5]
  Q_0.05: [0, 0.5]
  Q_0.95: [1, 0.69999999999999996]
  Q_0.99: [1, 0.69999999999999996]
Statistics of the output part of the training sample:
  NaN Count: [0]
  Inf Count: [0]
  Count: [12]
  Min: [0.69999999999999996]
  Max: [1]
  Range: [0.30000000000000004]
  Mean: [0.87499999999999989]
  Std: [0.112047068031901]
  Var: [0.01255454545454545]
  Q1: [0.80000000000000004]
  Median: [0.90000000000000002]
  Q3: [1]
  IQR: [0.19999999999999996]
  Q_0.01: [0.69999999999999996]
  Q_0.05: [0.69999999999999996]
  Q_0.95: [1]
  Q_0.99: [1]
Training Time               :
  Start                     : 2022-11-02 09:24:00.460690
  Finish                    : 2022-11-02 09:26:53.499994
  Total                     : 0:02:53.039304
 */
#include <libhydrocalc/settings.h>

#define KE27_sizeX 2 /* input dimensionality */
#define KE27_sizeF 1 /* model output dimensionality */
#define KE27_outputVectorSize (1 * (2 + 1)) /* size of the full (model value and partial derivatives) output vector  */
#define KE27_Fi(i) (i) /* 0-based index of i-the output in the full output vector */
#define KE27_dFi_dXj(i, j) (1 + (i)*2+(j)) /* 0-based index of the partial derivative of i-th model output with respect to j-th model input in the full output vector */


#ifdef __cplusplus
extern "C" {
#endif

int KE27( const int N /* number of input vectors (N >= 0) */
        , const hydrocalc::real* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in hydrocalc::reals) between input vectors (ldInput >= {input vector size}) */
        , hydrocalc::real* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in hydrocalc::reals) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
        );

int KE27AE( const int N /* number of input vectors (N >= 0) */
        , const hydrocalc::real* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in hydrocalc::reals) between input vectors (ldInput >= {input vector size}) */
        , hydrocalc::real* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in hydrocalc::reals) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
        );

/* Calculates value and/or gradient of the function KE27 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int KE27Calc( 
          const hydrocalc::real* input  /* [in] pointer to the input vector, requires input != NULL */
        , const int inputInc   /* [in] distance (in hydrocalc::reals) between elements of the input vector) */
        , hydrocalc::real* value        /* [out] optional pointer to the function value. */
                               /* Set this pointer to NULL to avoid calculation of the function value */
        , const int valueInc   /* [in] distance (in hydrocalc::reals) between elements of vector 'value'. */
                               /* Ignored if function has 1-dimensional output or value==NULL */
        , hydrocalc::real* grad         /* [out] optional pointer to the function gradient dF_i/dX_j. */
                               /* Set this pointer to NULL to avoid calculation of the function gradient */
        , const int gradNextDF /* [in] distance (in hydrocalc::reals) between dF_i/dX_k and dF_{i+1}/dX_k */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional */
                               /* output or grad==NULL */
        , const int gradNextDX /* [in] distance (in hydrocalc::reals) between dF_k/dX_j and dF_k/dX_{j+1} */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional input */
                               /* or grad==NULL */
        );

/* Calculates value and/or gradient of the function AE KE27 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int KE27CalcAE( 
          const hydrocalc::real* input  /* [in] pointer to the input vector, requires input != NULL */
        , const int inputInc   /* [in] distance (in hydrocalc::reals) between elements of the input vector) */
        , hydrocalc::real* value        /* [out] optional pointer to the function AE. Set this pointer to NULL */
                               /* to avoid calculation of the function AE */
        , const int valueInc   /* [in] distance (in hydrocalc::reals) between elements of vector 'value'. */
                               /* Ignored if function has 1-dimensional output or value==NULL */
        , hydrocalc::real* grad         /* [out] optional pointer to the gradient of the function AE dAE_i/dX_j. */
                               /* Set this pointer to NULL to avoid calculation of the gradient of */
                               /* the function AE. */
        , const int gradNextDF /* [in] distance (in hydrocalc::reals) between dAE_i/dX_k and dAE_{i+1}/dX_k */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional */
                               /* output or grad==NULL */
        , const int gradNextDX /* [in] distance (in hydrocalc::reals) between dAE_k/dX_j and dAE_k/dX_{j+1} */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional input */
                               /* or grad==NULL */
        );



const hydrocalc::real _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvaluesFactor2_[2] = { 1.6248582586819049, 0.37514174131809519, };

const hydrocalc::real _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvaluesFactor1_[6] = { 4.0015469809623507, 1.5852180327808305, 0.35992856610104823, 0.04919156665774041, 0.0039636602356973201, 0.00015119326233192836, };

const hydrocalc::real _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_cartesianFactor1_[6][1] = {
    { -1.40152977645347,  }, { -0.84091786587208195,  }, { -0.28030595529069391,  }, { 0.28030595529069391,  },
    { 0.84091786587208217,  }, { 1.40152977645347,  }
};

const hydrocalc::real _39VSR563ECQANGU12PUAMTS8T0HVMEBA_alpha[1][12] = {
    { -5.3975771640501593, 22.298430595520276, -42.867691025405776, 51.789580273647381, -36.558109839011934, 11.840245465305786, 6.3322087502801656, -27.735354095693534,
      61.726773618152379, -76.743514480331669, 53.317970923879841, -18.456789022809286,  }
};

const hydrocalc::real _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_cartesianFactor2_[2][1] = {
    { -0.9574271077563381,  }, { 0.9574271077563381,  }
};

const hydrocalc::real _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor2_[2][2] = {
    { 0.70710678118654746, 0.70710678118654746,  }, { -0.70710678118654746, 0.70710678118654746,  }
};

const hydrocalc::real _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor1_[6][6] = {
    { 0.3237407671540346, 0.41642019549453468, 0.47094175485595913, 0.47094175485595935, 0.41642019549453507, 0.32374076715403494,  },
    { -0.53466928517212076, -0.43167388301462517, -0.16669257396959553, 0.16669257396959569, 0.43167388301462484, 0.53466928517212065,  },
    { 0.57047039857848925, 0.027947756107007747, -0.41687221936018032, -0.41687221936018071, 0.027947756107007532, 0.57047039857848958,  },
    { 0.45144441347635955, -0.43065997252422766, -0.3327610698480446, 0.33276106984804138, 0.43065997252423294, -0.45144441347636144,  },
    { 0.26411255181875815, -0.57080044123394658, 0.32315850021142201, 0.32315850021145698, -0.57080044123396145, 0.26411255181875892,  },
    { 0.1016203573823657, -0.35803581774525828, 0.60123510890248855, -0.601235108902471, 0.35803581774522786, -0.10162035738235183,  }
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DA_KE27_H */
