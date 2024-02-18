#ifndef DA_E523_H
#define DA_E523_H

/* Approximation of diagram 5-23 */
/* 
Inputs number               : 2
Outputs number              : 1
Input Variables             :
  Input # 0
    name                    : n0
    variability             : continuous
  Input # 1
    name                    : R0D0
    variability             : continuous
Output Variables            :
  Output # 0
    name                    : CSI
    variability             : continuous
Accuracy evaluation         : NOT AVAILABLE
Outputs rearrangement       : NOT AVAILABLE
Probability estimation      : NOT AVAILABLE
Additionally smoothed model : NO
Technique used              : MoA
Training points number      : 32
Training options            :
  /GTApprox/MoALowFidelityModel=[]
  GTApprox/Accelerator=3
  GTApprox/EnableTensorFeature=false
  GTApprox/InputNanMode=ignore
  GTApprox/InternalValidation=false
  GTApprox/IVSavePredictions=true
  GTApprox/MoACovarianceType=Diag
  GTApprox/MoANumberOfClusters=[3]
  GTApprox/MoATechnique=GBRT
  GTApprox/OutputNanMode=ignore
  GTApprox/OutputTransformation=["none"]
  GTApprox/StoreTrainingSample=True
  GTApprox/Technique=MoA
  GTApprox/TensorFactors=[]
Training hints              :
    @GTApprox/TrainingSubsampleRatio=0
Statistics of the input part of the training sample:
  NaN Count: [0, 0]
  Inf Count: [0, 0]
  Count: [32, 32]
  Min: [0.25, 0]
  Max: [0.64000000000000001, 2]
  Range: [0.39000000000000001, 2]
  Mean: [0.41750000000000004, 0.69999999999999996]
  Std: [0.14921298914314488, 0.69282032302755092]
  Var: [0.022264516129032269, 0.47999999999999998]
  Q1: [0.33000000000000002, 0.20000000000000001]
  Median: [0.45000000000000001, 0.5]
  Q3: [0.64000000000000001, 1.5]
  IQR: [0.31, 1.3]
  Q_0.01: [0.25, 0]
  Q_0.05: [0.25, 0]
  Q_0.95: [0.64000000000000001, 2]
  Q_0.99: [0.64000000000000001, 2]
Statistics of the output part of the training sample:
  NaN Count: [0]
  Inf Count: [0]
  Count: [32]
  Min: [0.043999999999999997]
  Max: [0.40799999999999997]
  Range: [0.36399999999999999]
  Mean: [0.085312500000000013]
  Std: [0.089999439962415245]
  Var: [0.0080998991935483863]
  Q1: [0.048000000000000001]
  Median: [0.053999999999999999]
  Q3: [0.066000000000000003]
  IQR: [0.018000000000000002]
  Q_0.01: [0.043999999999999997]
  Q_0.05: [0.043999999999999997]
  Q_0.95: [0.36399999999999999]
  Q_0.99: [0.40799999999999997]
Training Time               :
  Start                     : 2022-08-12 08:16:30.769164
  Finish                    : 2022-08-12 08:19:59.438471
  Total                     : 0:03:28.669307
 */
#include <libhydrocalc/settings.h>

#define E523_sizeX 2 /* input dimensionality */
#define E523_sizeF 1 /* model output dimensionality */
#define E523_outputVectorSize (1 * (2 + 1)) /* size of the full (model value and partial derivatives) output vector  */
#define E523_Fi(i) (i) /* 0-based index of i-the output in the full output vector */
#define E523_dFi_dXj(i, j) (1 + (i)*2+(j)) /* 0-based index of the partial derivative of i-th model output with respect to j-th model input in the full output vector */


#ifdef __cplusplus
extern "C" {
#endif

int E523( const int N /* number of input vectors (N >= 0) */
        , const hydrocalc::real* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in doubles) between input vectors (ldInput >= {input vector size}) */
        , hydrocalc::real* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in doubles) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
        );

int E523AE( const int N /* number of input vectors (N >= 0) */
        , const hydrocalc::real* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in doubles) between input vectors (ldInput >= {input vector size}) */
        , hydrocalc::real* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in doubles) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
        );

/* Calculates value and/or gradient of the function E523 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int E523Calc( 
          const hydrocalc::real* input  /* [in] pointer to the input vector, requires input != NULL */
        , const int inputInc   /* [in] distance (in doubles) between elements of the input vector) */
        , hydrocalc::real* value        /* [out] optional pointer to the function value. */
                               /* Set this pointer to NULL to avoid calculation of the function value */
        , const int valueInc   /* [in] distance (in doubles) between elements of vector 'value'. */
                               /* Ignored if function has 1-dimensional output or value==NULL */
        , hydrocalc::real* grad         /* [out] optional pointer to the function gradient dF_i/dX_j. */
                               /* Set this pointer to NULL to avoid calculation of the function gradient */
        , const int gradNextDF /* [in] distance (in doubles) between dF_i/dX_k and dF_{i+1}/dX_k */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional */
                               /* output or grad==NULL */
        , const int gradNextDX /* [in] distance (in doubles) between dF_k/dX_j and dF_k/dX_{j+1} */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional input */
                               /* or grad==NULL */
        );

/* Calculates value and/or gradient of the function AE E523 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int E523CalcAE( 
          const hydrocalc::real* input  /* [in] pointer to the input vector, requires input != NULL */
        , const int inputInc   /* [in] distance (in doubles) between elements of the input vector) */
        , hydrocalc::real* value        /* [out] optional pointer to the function AE. Set this pointer to NULL */
                               /* to avoid calculation of the function AE */
        , const int valueInc   /* [in] distance (in doubles) between elements of vector 'value'. */
                               /* Ignored if function has 1-dimensional output or value==NULL */
        , hydrocalc::real* grad         /* [out] optional pointer to the gradient of the function AE dAE_i/dX_j. */
                               /* Set this pointer to NULL to avoid calculation of the gradient of */
                               /* the function AE. */
        , const int gradNextDF /* [in] distance (in doubles) between dAE_i/dX_k and dAE_{i+1}/dX_k */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional */
                               /* output or grad==NULL */
        , const int gradNextDX /* [in] distance (in doubles) between dAE_k/dX_j and dAE_k/dX_{j+1} */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional input */
                               /* or grad==NULL */
        );


const hydrocalc::real _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCenter_002[3] = { 0.77648975781822105, -0.80512394158157796, 0.6624686229866158, };

const hydrocalc::real _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_extrapolationWeights[3] = { 0.093243887051870325, 0.54642166420995653, 0.36033444873817311, };

const hydrocalc::real _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCenter_001[3] = { -0.8846288369761075, -0.7237007607517244, 0.86126188676998461, };

const hydrocalc::real _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCenter_000[3] = { 0.098810676037750969, 0.91316450011173445, -0.91586874813876762, };

const hydrocalc::real _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCovarianceFactor_002[3][3] = {
    { 0.72390884029141822, 0., 0.,  },
    { 0., 0.16754985317924651, 0.,  },
    { 0., 0., 0.49503306108229117,  }
};

const hydrocalc::real _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCovarianceFactor_001[3][3] = {
    { 0.27466659089284151, 0., 0.,  },
    { 0., 0.24562014589890344, 0.,  },
    { 0., 0., 0.62860896516646392,  }
};

const hydrocalc::real _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCovarianceFactor_000[3][3] = {
    { 1.0034623231067623, 0., 0.,  },
    { 0., 0.78282143946857174, 0.,  },
    { 0., 0., 0.511162649420142,  }
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DA_E523_H */
