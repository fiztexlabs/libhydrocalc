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
#include <pch.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <HydraulicResistances/approximations/KE27.h>

#ifdef __TINYC__
#undef NAN
#define NAN (1.e310*1.e310-1.e310*1.e310)
#endif

#ifndef DACalculationOptions_DECLARED
#define DACalculationOptions_DECLARED

struct DACalculationOptions {
  int _gradientMatrixFMajor; /* (boolean) indicates whether gradient matrix should be stored in a F-major mode */
                             /* i.e. partial derivative dF_i/dX_j will be stored in j-th column of i-th row */
  int _estimateError; /* (boolean) indicates whether approximation error should be estimated instead of calculation of function value */
};

#endif /* DACalculationOptions_DECLARED */

#ifdef __cplusplus
extern "C" {
#endif

void _KE27(/*[in] */ const HSReal* X /* input vector of size 2 */
        , /*[in] */ int incX /* distance between elements of the vector X */
        , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
        , /*[in] */ int incF /* distance between elements of the vector F */
        , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                  /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                  /* see declaration of struct DACalculationOptions for details */
        , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
        , /*[in] */ const struct DACalculationOptions* options);

#ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef __cplusplus
extern "C" {
#endif

int KE27( const int N /* number of input vectors (N >= 0) */
        , const HSReal* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in HSReals) between input vectors (ldInput >= {input vector size}) */
        , HSReal* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in HSReals) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
        ) {
  static const int daXDimensionality = 2;
  static const int daYDimensionality = 1;
  int i;
  if (N < 0) {
    return 1;
  }
  if (N != 0 && !input) {
    return 2;
  }
  if (ldInput < daXDimensionality) {
    return 3;
  }
  if (N != 0 && !output) {
    return 4;
  }
  if (ldOutput < (daYDimensionality + daXDimensionality * daYDimensionality)) {
    return 5;
  }
#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (i = 0; i < N; ++i) {
    _KE27(input + i * ldInput, 1, output + i * ldOutput, 1, output + i * ldOutput + daYDimensionality, daXDimensionality, 0);
  }
  return 0;
}


int KE27AE( const int N /* number of input vectors (N >= 0) */
        , const HSReal* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in HSReals) between input vectors (ldInput >= {input vector size}) */
        , HSReal* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in HSReals) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
        ) {
  static const int daXDimensionality = 2;
  static const int daYDimensionality = 1;
  int i;
  struct DACalculationOptions options;
  options._gradientMatrixFMajor = 1;
  options._estimateError = 1;
  if (N < 0) {
    return 1;
  } else if(0 == N) {
    /* quick return if possible */
    return 0;
  }
  if (!input) {
    return 2;
  }
  if (ldInput < daXDimensionality) {
    return 3;
  }
  if (!output) {
    return 4;
  }
  if (ldOutput < (daYDimensionality + daXDimensionality * daYDimensionality)) {
    return 5;
  }
#ifdef _OPENMP
#pragma omp parallel for
#endif
  for (i = 0; i < N; ++i) {
    _KE27(input + i * ldInput, 1, output + i * ldOutput, 1, output + i * ldOutput + daYDimensionality, daXDimensionality, &options);
  }
  return 0;
}

/* Calculates value and/or gradient of the function KE27 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int KE27Calc( 
          const HSReal* input  /* [in] pointer to the input vector, requires input != NULL */
        , const int inputInc   /* [in] distance (in HSReals) between elements of the input vector) */
        , HSReal* value        /* [out] optional pointer to the function value. */
                               /* Set this pointer to NULL to avoid calculation of the function value */
        , const int valueInc   /* [in] distance (in HSReals) between elements of vector 'value'. */
                               /* Ignored if function has 1-dimensional output or value==NULL */
        , HSReal* grad         /* [out] optional pointer to the function gradient dF_i/dX_j. */
                               /* Set this pointer to NULL to avoid calculation of the function gradient */
        , const int gradNextDF /* [in] distance (in HSReals) between dF_i/dX_k and dF_{i+1}/dX_k */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional */
                               /* output or grad==NULL */
        , const int gradNextDX /* [in] distance (in HSReals) between dF_k/dX_j and dF_k/dX_{j+1} */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional input */
                               /* or grad==NULL */
        ) {
  static const int daXDimensionality = 2;
  static const int daYDimensionality = 1;
  if (!input) {
    return 1;
  }
  if(!value && !grad) {
    /* nothing to calculate - quick return */
    return 0;
  }
  if (value && daYDimensionality > 1 && 0 == valueInc) {
    return 4;
  }
  if( !grad ) {
    _KE27(input, inputInc, value, valueInc, 0, 0, 0);
  } else {
    /* gradient output may be F-major, or X-major, or custom, */
    /* but _KE27 function can handle F-major or X-major cases only*/
    struct DACalculationOptions options;
    options._estimateError = 0;
    if (daXDimensionality > 1 && 0 == gradNextDX) {
      return 6;
    }
    if (daYDimensionality > 1 && 0 == gradNextDF) {
      return 7;
    }
    if(1 == daXDimensionality || 1 == gradNextDX) {
      options._gradientMatrixFMajor = 1;
      _KE27(input, inputInc, value, valueInc, grad, gradNextDF, &options);
    } else if(1 == daYDimensionality || 1 == gradNextDF) {
      options._gradientMatrixFMajor = 0;
      _KE27(input, inputInc, value, valueInc, grad, gradNextDX, &options);
    } else {
      int dx, df;
      HSReal contiguousGrad[2*1];
      options._gradientMatrixFMajor = 1;
      _KE27(input, inputInc, value, valueInc, contiguousGrad, 2, &options);
      for(df = 0; df < 1; ++ df) {
        for(dx = 0; dx < 2; ++ dx) {
          grad[gradNextDF*df + gradNextDX*dx] = contiguousGrad[2*df+dx];
        }
      }
    }
  }
  return 0;
}


/* Calculates value and/or gradient of the function AE KE27 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int KE27CalcAE( 
          const HSReal* input  /* [in] pointer to the input vector, requires input != NULL */
        , const int inputInc   /* [in] distance (in HSReals) between elements of the input vector) */
        , HSReal* value        /* [out] optional pointer to the function AE. Set this pointer to NULL */
                               /* to avoid calculation of the function AE */
        , const int valueInc   /* [in] distance (in HSReals) between elements of vector 'value'. */
                               /* Ignored if function has 1-dimensional output or value==NULL */
        , HSReal* grad         /* [out] optional pointer to the gradient of the function AE dAE_i/dX_j. */
                               /* Set this pointer to NULL to avoid calculation of the gradient of */
                               /* the function AE. */
        , const int gradNextDF /* [in] distance (in HSReals) between dAE_i/dX_k and dAE_{i+1}/dX_k */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional */
                               /* output or grad==NULL */
        , const int gradNextDX /* [in] distance (in HSReals) between dAE_k/dX_j and dAE_k/dX_{j+1} */
                               /* elements of the array 'grad'. Ignored if function has 1-dimensional input */
                               /* or grad==NULL */
        ) {
  static const int daXDimensionality = 2;
  static const int daYDimensionality = 1;
  struct DACalculationOptions options;
  options._estimateError = 1;
  if (!input) {
    return 1;
  }
  if(!value && !grad) {
    /* nothing to calculate - quick return */
    return 0;
  }
  if (value && daYDimensionality > 1 && 0 == valueInc) {
    return 4;
  }
  if( !grad ) {
    _KE27(input, inputInc, value, valueInc, 0, 0, &options);
  } else {
    /* gradient output may be F-major, or X-major, or custom, */
    /* but _KE27 function can handle F-major or X-major cases only*/
    if (daXDimensionality > 1 && 0 == gradNextDX) {
      return 6;
    }
    if (daYDimensionality > 1 && 0 == gradNextDF) {
      return 7;
    }
    if(1 == daXDimensionality || 1 == gradNextDX) {
      options._gradientMatrixFMajor = 1;
      _KE27(input, inputInc, value, valueInc, grad, gradNextDF, &options);
    } else if(1 == daYDimensionality || 1 == gradNextDF) {
      options._gradientMatrixFMajor = 0;
      _KE27(input, inputInc, value, valueInc, grad, gradNextDX, &options);
    } else {
      int dx, df;
      HSReal contiguousGrad[2*1];
      options._gradientMatrixFMajor = 1;
      _KE27(input, inputInc, value, valueInc, contiguousGrad, 2, &options);
      for(df = 0; df < 1; ++ df) {
        for(dx = 0; dx < 2; ++ dx) {
          grad[gradNextDF*df + gradNextDX*dx] = contiguousGrad[2*df+dx];
        }
      }
    }
  }
  return 0;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef __cplusplus
extern "C" {
#endif


void _39VSR563ECQANGU12PUAMTS8T0HVMEBA_normalizeInput(/*[in] */ const HSReal* X /* input (unscaled) vector of size 2 */
                 , /*[in] */ int incX /* distance between elements of the vector X */
                 , /*[out]*/ HSReal* Y /* output (normalized) vector of size 2 */
                 , /*[in] */ int incY /* distance between elements of the vector Y */);

void _39VSR563ECQANGU12PUAMTS8T0HVMEBA_reverseOutputGradNormalization1(/*[in] */ const HSReal* gradIn /* input gradient */
                                  , /*[in] */ int ldGradIn /* Leading dimension of the matrix gradIn */
                                  , /*[in] */ const int gradInFMajor /* is input gradient has F-major order */
                                  , /*[out]*/ HSReal* gradOut /* output gradient */
                                  , /*[in] */ int ldGradOut /* Leading dimension of the matrix gradOut */
                                  , /*[in] */ const int gradOutFMajor /* is output gradient has F-major order */);

void _39VSR563ECQANGU12PUAMTS8T0HVMEBA_reverseOutputNormalization1(/*[in] */ const HSReal* X /* input (normalized) vector of size 1 */
                              , /*[in] */ int incX /* distance between elements of the vector X */
                              , /*[out]*/ HSReal* Y /* output (unscaled) vector of size 1 */
                              , /*[in] */ int incY /* distance between elements of the vector Y */);

void _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1(/*[in] */ const HSReal* X /* input vector of size 2 */
                        , /*[in] */ int incX /* distance between elements of the vector X */
                        , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
                        , /*[in] */ int incF /* distance between elements of the vector F */
                        , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                                  /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                                  /* see declaration of struct DACalculationOptions for details */
                        , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                        , /*[in] */ const struct DACalculationOptions* options);


#ifndef DA_CBLAS_DECLARED
#define DA_CBLAS_DECLARED

enum CBLAS_ORDER {CblasRowMajor=101, CblasColMajor=102};
enum CBLAS_TRANSPOSE {CblasNoTrans=111, CblasTrans=112, CblasConjTrans=113};
enum CBLAS_UPLO {CblasUpper=121, CblasLower=122};
enum CBLAS_DIAG {CblasNonUnit=131, CblasUnit=132};

#if DA_CBLAS /* use external cblas */

HSReal cblas_ddot(const int N, const HSReal *X, const int incX,
                  const HSReal *Y, const int incY);

#else /* use local cblas routines implementation */

static HSReal cblas_ddot(const int N, const HSReal *X, const int incX,
                  const HSReal *Y, const int incY);

#endif /* DA_CBLAS */

#endif /* DA_CBLAS_DECLARED */


void _KE27(/*[in] */ const HSReal* X /* input vector of size 2 */
        , /*[in] */ int incX /* distance between elements of the vector X */
        , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
        , /*[in] */ int incF /* distance between elements of the vector F */
        , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                  /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                  /* see declaration of struct DACalculationOptions for details */
        , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
        , /*[in] */ const struct DACalculationOptions* options) {
  /* Normalization wrapper for the Tensored GP approximation */

  HSReal normalizedX[2];
  HSReal normalizedF[1] = {0.};
  HSReal normalizedGradF[4] = {0., 0., 0., 0.};
  const int  isGradientFMajor = (0 == options || options->_gradientMatrixFMajor);
  const int  predictValues = (0 != F) || (0 != options && options->_estimateError);
  struct DACalculationOptions tensoredGPCalculatorOptions;
  
  if(0 == gradF && 0 == F) {
    /* quick return if possible */
    return;
  }
  
  _39VSR563ECQANGU12PUAMTS8T0HVMEBA_normalizeInput(X, incX, normalizedX, 1);
  
  tensoredGPCalculatorOptions._gradientMatrixFMajor = 1;
  tensoredGPCalculatorOptions._estimateError = (options ? options->_estimateError : 0);
  _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1(normalizedX, 1, (predictValues ? normalizedF : 0), 1, ((0 != gradF) ? normalizedGradF : 0), 2, &tensoredGPCalculatorOptions);
  
  if((0 != options && options->_estimateError)) {
    /* reverse normalize error prediction stored in normalizedF and/or normalizedGradF */
    
    normalizedF[0] = (normalizedF[0] <= 0.) ? 0. : sqrt(normalizedF[0]);

    if(0 != F) {
      F[0*incF] = 0.112047068031901 * normalizedF[0];
    }

    if(0 != gradF) {
      const int nextDX = (0 == options || options->_gradientMatrixFMajor)? 1 : ldGradF; /* distance between dF[i]/dX[j+1] and dF[i]/dX[j] elements of derivatives matrix */
      const int nextDF = (0 == options || options->_gradientMatrixFMajor)? ldGradF : 1; /* distance between dF[i+1]/dX[j] and dF[i]/dX[j] elements of derivatives matrix */
      gradF[0*nextDF+0*nextDX] = 0.15703730221101694 * normalizedGradF[2*0+0] / normalizedF[0];
      gradF[0*nextDF+1*nextDX] = 0.53638450139180327 * normalizedGradF[2*0+1] / normalizedF[0];
    }
  } else {
    /* reverse normalize value prediction stored in normalizedF and/or normalizedGradF */
    if (0 != F) {
      _39VSR563ECQANGU12PUAMTS8T0HVMEBA_reverseOutputNormalization1(normalizedF, 1, F, incF);
    }
    
    if (0 != gradF) {
      _39VSR563ECQANGU12PUAMTS8T0HVMEBA_reverseOutputGradNormalization1(normalizedGradF, 2, 1, gradF, ldGradF, isGradientFMajor);
    }
  }

}


void _39VSR563ECQANGU12PUAMTS8T0HVMEBA_reverseOutputGradNormalization1(/*[in] */ const HSReal* gradIn /* input gradient */
                                  , /*[in] */ int ldGradIn /* Leading dimension of the matrix gradIn */
                                  , /*[in] */ const int gradInFMajor /* is input gradient has F-major order */
                                  , /*[out]*/ HSReal* gradOut /* output gradient */
                                  , /*[in] */ int ldGradOut /* Leading dimension of the matrix gradOut */
                                  , /*[in] */ const int gradOutFMajor /* is output gradient has F-major order */) {
  /* consider derivatives of input and output normalization */

  const int inputNextDF = gradInFMajor? ldGradIn : 1;
  const int inputNextDX = gradInFMajor? 1 : ldGradIn;
  const int outputNextDF = gradOutFMajor? ldGradOut : 1;
  const int outputNextDX = gradOutFMajor? 1 : ldGradOut;
  gradOut[0 * outputNextDF + 0 * outputNextDX] = 3.14074604422033887e-01 * gradIn[0 * inputNextDF + 0 * inputNextDX];
  gradOut[0 * outputNextDF + 1 * outputNextDX] = 1.07276900278360632e+00 * gradIn[0 * inputNextDF + 1 * inputNextDX];

}


void _39VSR563ECQANGU12PUAMTS8T0HVMEBA_normalizeInput(/*[in] */ const HSReal* X /* input (unscaled) vector of size 2 */
                 , /*[in] */ int incX /* distance between elements of the vector X */
                 , /*[out]*/ HSReal* Y /* output (normalized) vector of size 2 */
                 , /*[in] */ int incY /* distance between elements of the vector Y */) {
  /* apply standard normalization */

  /* apply standard normalization */
  Y[0 * incY] = (-0.5 + X[0 * incX]) * 2.80305955290694;
  Y[1 * incY] = (-0.59999999999999998 + X[1 * incX]) * 9.5742710775633828;

}


void _39VSR563ECQANGU12PUAMTS8T0HVMEBA_covarianceFunction1(/*[in] */ const HSReal* X /* left vector */
                      , /*[in] */ int incX /* distance between elements of the vector X */
                      , /*[in] */ const HSReal* Y /* right vector */
                      , /*[in] */ int incY /* distance between elements of the vector Y */
                      , /*[out]*/ HSReal* covarianceValue /* calculated covariance value cov(X,Y) */
                      , /*[out]*/ HSReal* covarianceDerivative /* derivative of cov(X,Y) */
                      , /*[in] */ int incCovarianceDerivative /* distance between elements of the vector covarianceDerivative */) {
  /* weighted L_p (p=2) covariance function */
  static const HSReal variance[1] = { 0.33205182484143975,  };
  static const HSReal derivativeScale[1] = { 0.66410364968287949,  };

  HSReal calculatedCovariance;
  HSReal delta[1] = {Y[0] - X[0]};

  calculatedCovariance = exp(-variance[0] * (delta[0] * delta[0]));

  if(0 != covarianceValue) {
    *covarianceValue = calculatedCovariance;
  }

  if(0 != covarianceDerivative) {
    covarianceDerivative[0*incCovarianceDerivative] = derivativeScale[0] * calculatedCovariance * delta[0];
  }

}


void _39VSR563ECQANGU12PUAMTS8T0HVMEBA_covarianceFunction2(/*[in] */ const HSReal* X /* left vector */
                      , /*[in] */ int incX /* distance between elements of the vector X */
                      , /*[in] */ const HSReal* Y /* right vector */
                      , /*[in] */ int incY /* distance between elements of the vector Y */
                      , /*[out]*/ HSReal* covarianceValue /* calculated covariance value cov(X,Y) */
                      , /*[out]*/ HSReal* covarianceDerivative /* derivative of cov(X,Y) */
                      , /*[in] */ int incCovarianceDerivative /* distance between elements of the vector covarianceDerivative */) {
  /* weighted L_p (p=2) covariance function */
  static const HSReal variance[1] = { 0.12824466574760351,  };
  static const HSReal derivativeScale[1] = { 0.25648933149520703,  };

  HSReal calculatedCovariance;
  HSReal delta[1] = {Y[0] - X[0]};

  calculatedCovariance = exp(-variance[0] * (delta[0] * delta[0]));

  if(0 != covarianceValue) {
    *covarianceValue = calculatedCovariance;
  }

  if(0 != covarianceDerivative) {
    covarianceDerivative[0*incCovarianceDerivative] = derivativeScale[0] * calculatedCovariance * delta[0];
  }

}


void _39VSR563ECQANGU12PUAMTS8T0HVMEBA_reverseOutputNormalization1(/*[in] */ const HSReal* X /* input (normalized) vector of size 1 */
                              , /*[in] */ int incX /* distance between elements of the vector X */
                              , /*[out]*/ HSReal* Y /* output (unscaled) vector of size 1 */
                              , /*[in] */ int incY /* distance between elements of the vector Y */) {
  /* reverse standard normalization */

  /* reverse standard normalization */
  Y[0 * incY] = 0.87499999999999989 + X[0 * incX] * 0.112047068031901;

}


void _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1(/*[in] */ const HSReal* X /* input vector of size 2 */
                        , /*[in] */ int incX /* distance between elements of the vector X */
                        , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
                        , /*[in] */ int incF /* distance between elements of the vector F */
                        , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                                  /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                                  /* see declaration of struct DACalculationOptions for details */
                        , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                        , /*[in] */ const struct DACalculationOptions* options) {
  /* Tensored GP approximation */
  extern const HSReal _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_cartesianFactor1_[6][1];
  extern const HSReal _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_cartesianFactor2_[2][1];
  extern const HSReal _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvaluesFactor1_[6];
  extern const HSReal _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor1_[6][6];
  extern const HSReal _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvaluesFactor2_[2];
  extern const HSReal _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor2_[2][2];
  extern const HSReal _39VSR563ECQANGU12PUAMTS8T0HVMEBA_alpha[1][12];

  HSReal crossCovariance1[6];
  HSReal crossCovarianceGrad1[6];
  HSReal crossCovariance2[2];
  HSReal crossCovarianceGrad2[2];
  HSReal testPoint[2];
  int k;
  
  if(0 == gradF && 0 == F) {
    /* quick return if possible */
    return;
  }
  
  /* calculate cross covariances between test point and cartesian factors of the learning dataset */
  
  /* read test point for the factor #1 */
  testPoint[0] = X[incX * 0];
  
  /* calculate cross covariances for the factor #1 */
  for(k = 0; k < 6; ++ k) {
    _39VSR563ECQANGU12PUAMTS8T0HVMEBA_covarianceFunction1(testPoint, 1, _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_cartesianFactor1_[k], 1, crossCovariance1 + k, ((0 == gradF) ? 0 : (crossCovarianceGrad1+k)), 6);
  }
  
  /* read test point for the factor #2 */
  testPoint[0] = X[incX * 1];
  
  /* calculate cross covariances for the factor #2 */
  _39VSR563ECQANGU12PUAMTS8T0HVMEBA_covarianceFunction2(testPoint, 1, _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_cartesianFactor2_[0], 1, crossCovariance2 + 0, ((0 == gradF) ? 0 : (crossCovarianceGrad2+0)), 2);
  _39VSR563ECQANGU12PUAMTS8T0HVMEBA_covarianceFunction2(testPoint, 1, _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_cartesianFactor2_[1], 1, crossCovariance2 + 1, ((0 == gradF) ? 0 : (crossCovarianceGrad2+1)), 2);
  
  if((0 != options && options->_estimateError)) {
    /* error prediction */
    HSReal semiInversedCovariance1[6];
    HSReal semiInversedCovariance2[2];
    HSReal explainedCovariance[1] = {0.};
    HSReal inversedEigenvalues[1];
    HSReal currentCovarianceEigenvalue, currentSemiInversedCovariance;
    int k;
    const int incGradX = (0 == options || options->_gradientMatrixFMajor)? 1 : ldGradF; /* distance between dF[i]/dX[j+1] and dF[i]/dX[j] elements of derivatives matrix */
    const int incGradF = (0 == options || options->_gradientMatrixFMajor)? ldGradF : 1; /* distance between dF[i+1]/dX[j] and dF[i]/dX[j] elements of derivatives matrix */
    
    /* calculate matrix-vector product between transposed matrix of learning sample covariances eigenvectors and test point cross covariances vector */
    for(k = 0; k < 6; ++ k) {
      semiInversedCovariance1[k] = cblas_ddot(6, _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor1_[k], 1, crossCovariance1, 1);
    }
    semiInversedCovariance2[0] = (_39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor2_[0][0]*crossCovariance2[0] + _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor2_[0][1]*crossCovariance2[1]);
    semiInversedCovariance2[1] = (_39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor2_[1][0]*crossCovariance2[0] + _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor2_[1][1]*crossCovariance2[1]);
    
    if (0 != gradF) {
      HSReal semiInversedCovarianceGrad1[1][6];
      HSReal semiInversedCovarianceGrad2[1][2];
      HSReal explainedCovarianceGrad[2][1] = { {0.},
                                               {0.} };
    
      /* calculate matrix-matrix product between transposed matrix of learning sample covariances eigenvectors and test point cross covariances derivatives */
      for(k = 0; k < 6; ++ k) {
        semiInversedCovarianceGrad1[0][k] = cblas_ddot(6, _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor1_[k], 1, crossCovarianceGrad1+0, 1);
      }
      semiInversedCovarianceGrad2[0][0] = (_39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor2_[0][0]*crossCovarianceGrad2[0+0] + _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor2_[0][1]*crossCovarianceGrad2[0+1]);
      semiInversedCovarianceGrad2[0][1] = (_39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor2_[1][0]*crossCovarianceGrad2[0+0] + _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvectorsFactor2_[1][1]*crossCovarianceGrad2[0+1]);

      /* iterate over kroneker product */
      for(k = 0; k < 12; ++ k) {
        currentSemiInversedCovariance = semiInversedCovariance1[k%6]*semiInversedCovariance2[k/6%2];
        currentCovarianceEigenvalue = _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvaluesFactor1_[k%6]*_39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvaluesFactor2_[k/6%2];

        inversedEigenvalues[0] = 1. / (currentCovarianceEigenvalue + 3.4196480547536515e-09);

        if (0 != F) {
          explainedCovariance[0] = hypot(explainedCovariance[0], currentSemiInversedCovariance * sqrt(inversedEigenvalues[0]));
        }

        explainedCovarianceGrad[0][0] += inversedEigenvalues[0]*currentSemiInversedCovariance*semiInversedCovarianceGrad1[0][k%6]*semiInversedCovariance2[k/6%2];
        explainedCovarianceGrad[1][0] += inversedEigenvalues[0]*currentSemiInversedCovariance*semiInversedCovariance1[k%6]*semiInversedCovarianceGrad2[0][k/6%2];
      }
    
      gradF[0*incGradF+0*incGradX] = -2. * 0.55739632293868824 * explainedCovarianceGrad[0][0];
      gradF[0*incGradF+1*incGradX] = -2. * 0.55739632293868824 * explainedCovarianceGrad[1][0];
    } else {
      for(k = 0; k < 12; ++ k) {
        currentSemiInversedCovariance = semiInversedCovariance1[k%6]*semiInversedCovariance2[k/6%2];
        currentCovarianceEigenvalue = _39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvaluesFactor1_[k%6]*_39VSR563ECQANGU12PUAMTS8T0HVMEBA_tensoredGPCalculator1_eigenvaluesFactor2_[k/6%2];

        explainedCovariance[0] = hypot(explainedCovariance[0], currentSemiInversedCovariance / sqrt(currentCovarianceEigenvalue + 3.4196480547536515e-09));
      }
    }
    
    if (0 != F) {
      if(0. > (explainedCovariance[0] = 1. - explainedCovariance[0]*explainedCovariance[0])) {
        explainedCovariance[0] = 0.;
      }
      F[0*incF]=0.55739632293868824*(explainedCovariance[0]+3.4196480547536515e-09);
    }
  } else {
    /* value prediction */
    if(0 != gradF) {
      const int incGradX = (0 == options || options->_gradientMatrixFMajor)? 1 : ldGradF; /* distance between dF[i]/dX[j+1] and dF[i]/dX[j] elements of derivatives matrix */
      const int incGradF = (0 == options || options->_gradientMatrixFMajor)? ldGradF : 1; /* distance between dF[i+1]/dX[j] and dF[i]/dX[j] elements of derivatives matrix */
      {
        const int offset2 = 0;  /* just to make code generation easer */
        HSReal accum2 = 0.;
        HSReal grad2_0 = 0.;
        HSReal grad2_1 = 0.;
        int i1, offset1;
        for(i1 = 0, offset1 = offset2; i1 < 2; ++ i1, offset1 += 6) {
          const HSReal accum1 = cblas_ddot(6, _39VSR563ECQANGU12PUAMTS8T0HVMEBA_alpha[0]+offset1, 1, crossCovariance1, 1);
          const HSReal grad1_0 = cblas_ddot(6, _39VSR563ECQANGU12PUAMTS8T0HVMEBA_alpha[0]+offset1, 1, crossCovarianceGrad1+0, 1);
          accum2 += accum1 * crossCovariance2[i1];
          grad2_0 += grad1_0 * crossCovariance2[i1];
          grad2_1 += accum1 * crossCovarianceGrad2[i1 + 0 * 2];
        }
        if(0 != F) {
          F[0 * incF] = accum2;
        }
        gradF[0*incGradF+0*incGradX] = grad2_0;
        gradF[0*incGradF+1*incGradX] = grad2_1;
      }
    } else if(0 != F) {
      {
        const int offset2 = 0;  /* just to make code generation easer */
        HSReal accum2 = 0.;
        int i1, offset1;
        for(i1 = 0, offset1 = offset2; i1 < 2; ++ i1, offset1 += 6) {
          const HSReal accum1 = cblas_ddot(6, _39VSR563ECQANGU12PUAMTS8T0HVMEBA_alpha[0]+offset1, 1, crossCovariance1, 1);
          accum2 += accum1 * crossCovariance2[i1];
        }
        F[0 * incF] = accum2;
      }
    }
  }

}


#ifdef __cplusplus
} /* extern "C" */
#endif
#ifdef __cplusplus
extern "C" {
#endif


/* internal BLAS and BLAS-like routines */


#if DA_CBLAS /* use external cblas */

#else /* use local cblas routines implementation */

static HSReal cblas_ddot(const int N, const HSReal *X, const int incX,
                  const HSReal *Y, const int incY) {
  HSReal accum = 0.;
  int j;
  
  if(1 == incX && 1 == incY) {
    const int N1 = N & ~3;
    for(j = 0; j < N1; j += 4) {
      accum += X[j]*Y[j]+X[j+1]*Y[j+1]+X[j+2]*Y[j+2]+X[j+3]*Y[j+3];
    }
    switch(N & 3) {
    case 1:
      accum += X[N1]*Y[N1];
      break;
    case 2:
      accum += X[N1]*Y[N1]+X[N1+1]*Y[N1+1];
      break;
    case 3:
      accum += X[N1]*Y[N1]+X[N1+1]*Y[N1+1]+X[N1+2]*Y[N1+2];
      break;
    }
  } else {
    for(j = 0; j < N; ++ j) {
      accum += X[incX*j] * Y[incY*j];
    }
  }
  
  return accum;
}

#endif /* DA_CBLAS */

#ifdef __cplusplus
} /* extern "C" */
#endif

/* Global variables section */

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
