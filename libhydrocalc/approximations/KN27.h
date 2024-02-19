#ifndef DA_KN27_H
#define DA_KN27_H

/* 2-7 */
/* 
Inputs number               : 2
Outputs number              : 1
Input Variables             :
  Input # 0
    name                    : Re
    variability             : continuous
  Input # 1
    name                    : dD0
    variability             : continuous
Output Variables            :
  Output # 0
    name                    : kn
    variability             : continuous
Accuracy evaluation         : NOT AVAILABLE
Outputs rearrangement       : NOT AVAILABLE
Probability estimation      : NOT AVAILABLE
Additionally smoothed model : NO
Technique used              : MoA
Training points number      : 40
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
  Count: [40, 40]
  Min: [100000, 0]
  Max: [100000000, 1]
  Range: [99900000, 1]
  Mean: [27775000, 0.46000000000000008]
  Std: [42411922.307838798, 0.30784611540383411]
  Var: [1798771153846154.2, 0.094769230769230745]
  Q1: [1000000, 0.20000000000000001]
  Median: [10000000, 0.5]
  Q3: [100000000, 0.69999999999999996]
  IQR: [99000000, 0.49999999999999994]
  Q_0.01: [100000, 0]
  Q_0.05: [100000, 0]
  Q_0.95: [100000000, 1]
  Q_0.99: [100000000, 1]
Statistics of the output part of the training sample:
  NaN Count: [0]
  Inf Count: [0]
  Count: [40]
  Min: [1]
  Max: [1.0700000000000001]
  Range: [0.070000000000000062]
  Mean: [1.0410000000000001]
  Std: [0.020102302457742607]
  Var: [0.00040410256410256445]
  Q1: [1.03]
  Median: [1.05]
  Q3: [1.0600000000000001]
  IQR: [0.030000000000000027]
  Q_0.01: [1]
  Q_0.05: [1]
  Q_0.95: [1.0700000000000001]
  Q_0.99: [1.0700000000000001]
Training Time               :
  Start                     : 2022-11-02 08:30:53.224064
  Finish                    : 2022-11-02 08:33:45.907752
  Total                     : 0:02:52.683688
 */
#include <libhydrocalc/settings.h>

#define KN27_sizeX 2 /* input dimensionality */
#define KN27_sizeF 1 /* model output dimensionality */
#define KN27_outputVectorSize (1 * (2 + 1)) /* size of the full (model value and partial derivatives) output vector  */
#define KN27_Fi(i) (i) /* 0-based index of i-the output in the full output vector */
#define KN27_dFi_dXj(i, j) (1 + (i)*2+(j)) /* 0-based index of the partial derivative of i-th model output with respect to j-th model input in the full output vector */


#ifdef __cplusplus
extern "C" {
#endif

int KN27( const int N /* number of input vectors (N >= 0) */
        , const hydrocalc::real* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in doubles) between input vectors (ldInput >= {input vector size}) */
        , hydrocalc::real* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in doubles) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
        );

int KN27AE( const int N /* number of input vectors (N >= 0) */
        , const hydrocalc::real* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in doubles) between input vectors (ldInput >= {input vector size}) */
        , hydrocalc::real* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in doubles) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
        );

/* Calculates value and/or gradient of the function KN27 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int KN27Calc( 
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

/* Calculates value and/or gradient of the function AE KN27 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int KN27CalcAE( 
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


const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_extrapolationWeights[3] = { 0.40507383084150017, 0.31809858309099598, 0.27682758606750379, };

const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCenter_002[3] = { -0.57487845246837366, 0.76006680133725479, 0., };

const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCenter_001[3] = { -0.57487845246837432, -0.85207627257584451, 0., };

const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCenter_000[3] = { 1.7246353574051216, 8.8817841970012504e-17, 0., };

const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCovarianceFactor_002[3][3] = {
    { 0.11132112505541444, 0., 0.,  },
    { 0., 0.65941742353859867, 0.,  },
    { 0., 0., 0.031622776601683791,  }
};

const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCovarianceFactor_001[3][3] = {
    { 0.11132112505541344, 0., 0.,  },
    { 0., 0.51189553441125657, 0.,  },
    { 0., 0., 0.031622776601683791,  }
};

const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCovarianceFactor_000[3][3] = {
    { 0.031622776601683791, 0., 0.,  },
    { 0., 1.000499875062461, 0.,  },
    { 0., 0., 0.031622776601683791,  }
};


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DA_KN27_H */
