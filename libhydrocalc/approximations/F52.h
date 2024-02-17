#ifndef DA_F52_H
#define DA_F52_H

/* Approximation of diagram 5-2 */
/* 
Inputs number               : 2
Outputs number              : 1
Input Variables             :
  Input # 0
    name                    : a, deg
    variability             : continuous
  Input # 1
    name                    : Re
    variability             : continuous
Output Variables            :
  Output # 0
    name                    : Ф
    variability             : continuous
Accuracy evaluation         : NOT AVAILABLE
Outputs rearrangement       : NOT AVAILABLE
Probability estimation      : NOT AVAILABLE
Additionally smoothed model : NO
Technique used              : GBRT
Training points number      : 42
Training options            :
  GTApprox/Accelerator=3
  GTApprox/EnableTensorFeature=false
  GTApprox/GBRTColsampleRatio=1
  GTApprox/GBRTMaxDepth=10
  GTApprox/GBRTMinChildWeight=1
  GTApprox/GBRTMinLossReduction=3.6558002247725074e-06
  GTApprox/GBRTSubsampleRatio=0.147698104238532
  GTApprox/InputNanMode=ignore
  GTApprox/InternalValidation=false
  GTApprox/IVSavePredictions=true
  GTApprox/OutputNanMode=ignore
  GTApprox/OutputTransformation=["none"]
  GTApprox/StoreTrainingSample=True
  GTApprox/Technique=GBRT
  GTApprox/TensorFactors=[]
Training hints              :
    @GTApprox/TrainingSubsampleRatio=0
Statistics of the input part of the training sample:
  NaN Count: [0, 0]
  Inf Count: [0, 0]
  Count: [42, 42]
  Min: [0, 50000]
  Max: [180, 600000]
  Range: [180, 550000]
  Mean: [50, 283333.33333333331]
  Std: [50.894438816426934, 234953.72317228842]
  Var: [2590.2439024390246, 55203252032.52034]
  Q1: [15, 50000]
  Median: [40, 200000]
  Q3: [60, 600000]
  IQR: [45, 550000]
  Q_0.01: [0, 50000]
  Q_0.05: [0, 50000]
  Q_0.95: [180, 600000]
  Q_0.99: [180, 600000]
Statistics of the output part of the training sample:
  NaN Count: [0]
  Inf Count: [0]
  Count: [42]
  Min: [0]
  Max: [1.02]
  Range: [1.02]
  Mean: [0.60476190476190483]
  Std: [0.3700114572730912]
  Var: [0.13690847851335661]
  Q1: [0.25]
  Median: [0.77000000000000002]
  Q3: [0.94999999999999996]
  IQR: [0.69999999999999996]
  Q_0.01: [0]
  Q_0.05: [0]
  Q_0.95: [1]
  Q_0.99: [1.02]
Training Time               :
  Start                     : 2022-08-08 10:14:47.854048
  Finish                    : 2022-08-08 10:18:32.903221
  Total                     : 0:03:45.049173
 */
#include <service/ServiceHS.h>

#define F52_sizeX 2 /* input dimensionality */
#define F52_sizeF 1 /* model output dimensionality */
#define F52_outputVectorSize (1 * (2 + 1)) /* size of the full (model value and partial derivatives) output vector  */
#define F52_Fi(i) (i) /* 0-based index of i-the output in the full output vector */
#define F52_dFi_dXj(i, j) (1 + (i)*2+(j)) /* 0-based index of the partial derivative of i-th model output with respect to j-th model input in the full output vector */


#ifdef __cplusplus
extern "C" {
#endif

int F52( const int N /* number of input vectors (N >= 0) */
        , const HSReal* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in doubles) between input vectors (ldInput >= {input vector size}) */
        , HSReal* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in doubles) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
        );

int F52AE( const int N /* number of input vectors (N >= 0) */
        , const HSReal* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in doubles) between input vectors (ldInput >= {input vector size}) */
        , HSReal* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in doubles) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
        );

/* Calculates value and/or gradient of the function F52 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int F52Calc( 
          const HSReal* input  /* [in] pointer to the input vector, requires input != NULL */
        , const int inputInc   /* [in] distance (in doubles) between elements of the input vector) */
        , HSReal* value        /* [out] optional pointer to the function value. */
                               /* Set this pointer to NULL to avoid calculation of the function value */
        , const int valueInc   /* [in] distance (in doubles) between elements of vector 'value'. */
                               /* Ignored if function has 1-dimensional output or value==NULL */
        , HSReal* grad         /* [out] optional pointer to the function gradient dF_i/dX_j. */
                               /* Set this pointer to NULL to avoid calculation of the function gradient */
        , const int gradNextDF /* [in] distance (in doubles) between dF_i/dX_k and dF_{i+1}/dX_k */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional */
                               /* output or grad==NULL */
        , const int gradNextDX /* [in] distance (in doubles) between dF_k/dX_j and dF_k/dX_{j+1} */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional input */
                               /* or grad==NULL */
        );

/* Calculates value and/or gradient of the function AE F52 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int F52CalcAE( 
          const HSReal* input  /* [in] pointer to the input vector, requires input != NULL */
        , const int inputInc   /* [in] distance (in doubles) between elements of the input vector) */
        , HSReal* value        /* [out] optional pointer to the function AE. Set this pointer to NULL */
                               /* to avoid calculation of the function AE */
        , const int valueInc   /* [in] distance (in doubles) between elements of vector 'value'. */
                               /* Ignored if function has 1-dimensional output or value==NULL */
        , HSReal* grad         /* [out] optional pointer to the gradient of the function AE dAE_i/dX_j. */
                               /* Set this pointer to NULL to avoid calculation of the gradient of */
                               /* the function AE. */
        , const int gradNextDF /* [in] distance (in doubles) between dAE_i/dX_k and dAE_{i+1}/dX_k */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional */
                               /* output or grad==NULL */
        , const int gradNextDX /* [in] distance (in doubles) between dAE_k/dX_j and dAE_k/dX_{j+1} */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional input */
                               /* or grad==NULL */
        );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DA_F52_H */
