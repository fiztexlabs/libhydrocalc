/*  */
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
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <libhydrocalc/approximations/kn27.h>

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

void _KN27(/*[in] */ const hydrocalc::real* X /* input vector of size 2 */
        , /*[in] */ int incX /* distance between elements of the vector X */
        , /*[out]*/ hydrocalc::real* F /* optional (may be NULL) output vector of size 1 */
        , /*[in] */ int incF /* distance between elements of the vector F */
        , /*[out]*/ hydrocalc::real* gradF /* optional (may be NULL) array to store partial derivatives of  */
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

int KN27( const int N /* number of input vectors (N >= 0) */
        , const hydrocalc::real* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in doubles) between input vectors (ldInput >= {input vector size}) */
        , hydrocalc::real* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in doubles) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
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
    _KN27(input + i * ldInput, 1, output + i * ldOutput, 1, output + i * ldOutput + daYDimensionality, daXDimensionality, 0);
  }
  return 0;
}


int KN27AE( const int N /* number of input vectors (N >= 0) */
        , const hydrocalc::real* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in doubles) between input vectors (ldInput >= {input vector size}) */
        , hydrocalc::real* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in doubles) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
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
    _KN27(input + i * ldInput, 1, output + i * ldOutput, 1, output + i * ldOutput + daYDimensionality, daXDimensionality, &options);
  }
  return 0;
}

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
    _KN27(input, inputInc, value, valueInc, 0, 0, 0);
  } else {
    /* gradient output may be F-major, or X-major, or custom, */
    /* but _KN27 function can handle F-major or X-major cases only*/
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
      _KN27(input, inputInc, value, valueInc, grad, gradNextDF, &options);
    } else if(1 == daYDimensionality || 1 == gradNextDF) {
      options._gradientMatrixFMajor = 0;
      _KN27(input, inputInc, value, valueInc, grad, gradNextDX, &options);
    } else {
      int dx, df;
      hydrocalc::real contiguousGrad[2*1];
      options._gradientMatrixFMajor = 1;
      _KN27(input, inputInc, value, valueInc, contiguousGrad, 2, &options);
      for(df = 0; df < 1; ++ df) {
        for(dx = 0; dx < 2; ++ dx) {
          grad[gradNextDF*df + gradNextDX*dx] = contiguousGrad[2*df+dx];
        }
      }
    }
  }
  return 0;
}


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
    _KN27(input, inputInc, value, valueInc, 0, 0, &options);
  } else {
    /* gradient output may be F-major, or X-major, or custom, */
    /* but _KN27 function can handle F-major or X-major cases only*/
    if (daXDimensionality > 1 && 0 == gradNextDX) {
      return 6;
    }
    if (daYDimensionality > 1 && 0 == gradNextDF) {
      return 7;
    }
    if(1 == daXDimensionality || 1 == gradNextDX) {
      options._gradientMatrixFMajor = 1;
      _KN27(input, inputInc, value, valueInc, grad, gradNextDF, &options);
    } else if(1 == daYDimensionality || 1 == gradNextDF) {
      options._gradientMatrixFMajor = 0;
      _KN27(input, inputInc, value, valueInc, grad, gradNextDX, &options);
    } else {
      int dx, df;
      hydrocalc::real contiguousGrad[2*1];
      options._gradientMatrixFMajor = 1;
      _KN27(input, inputInc, value, valueInc, contiguousGrad, 2, &options);
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

#if _MSC_VER > 0 && _MSC_VER < 1600
  typedef __int32 int32_t;
  typedef unsigned __int32 uint32_t;
  typedef __int64 int64_t;
  typedef unsigned __int64 uint64_t;
#else
#  include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_calculateWeights(/*[in] */ const hydrocalc::real* X /* input point */
                   , /*[in] */ int incX /* distance between elements of the vector X */
                   , /*[out]*/ hydrocalc::real weights [3] /* weights of the clusters */
                   , /*[out]*/ hydrocalc::real weightsGrad [3][2] /* partial derivatives of weights of the clusters with respect to inputs */
                   , /*[in] */ const hydrocalc::real dLFdX [1][2] /* partial derivatives of weights of the low fidelity model with respect to inputs */);

void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_localApproximator(/*[in] */ const hydrocalc::real* X /* input vector of size 2 */
                    , /*[in] */ int incX /* distance between elements of the vector X */
                    , /*[out]*/ hydrocalc::real* F /* optional (may be NULL) output vector of size 1 */
                    , /*[in] */ int incF /* distance between elements of the vector F */
                    , /*[out]*/ hydrocalc::real* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                              /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                              /* see declaration of struct DACalculationOptions for details */
                    , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                    , /*[in] */ const struct DACalculationOptions* options);

void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_localApproximator1(/*[in] */ const hydrocalc::real* X /* input vector of size 2 */
                    , /*[in] */ int incX /* distance between elements of the vector X */
                    , /*[out]*/ hydrocalc::real* F /* optional (may be NULL) output vector of size 1 */
                    , /*[in] */ int incF /* distance between elements of the vector F */
                    , /*[out]*/ hydrocalc::real* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                              /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                              /* see declaration of struct DACalculationOptions for details */
                    , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                    , /*[in] */ const struct DACalculationOptions* options);

void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_localApproximator2(/*[in] */ const hydrocalc::real* X /* input vector of size 2 */
                    , /*[in] */ int incX /* distance between elements of the vector X */
                    , /*[out]*/ hydrocalc::real* F /* optional (may be NULL) output vector of size 1 */
                    , /*[in] */ int incF /* distance between elements of the vector F */
                    , /*[out]*/ hydrocalc::real* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                              /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                              /* see declaration of struct DACalculationOptions for details */
                    , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                    , /*[in] */ const struct DACalculationOptions* options);

void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_lowFidelityModel(/*[in] */ const hydrocalc::real* X /* input vector of size 2 */
                   , /*[in] */ int incX /* distance between elements of the vector X */
                   , /*[out]*/ hydrocalc::real* F /* optional (may be NULL) output vector of size 1 */
                   , /*[in] */ int incF /* distance between elements of the vector F */
                   , /*[out]*/ hydrocalc::real* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                             /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                             /* see declaration of struct DACalculationOptions for details */
                   , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                   , /*[in] */ const struct DACalculationOptions* options);

void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_calculateMahalanobisDistance(/*[in] */ const hydrocalc::real X [3] /* input point */
                               , /*[in] */ const hydrocalc::real mu [3] /* mean value */
                               , /*[in] */ const hydrocalc::real sigmaL [3][3] /* lower Cholessky factor of the covariance matrix */
                               , /*[out]*/ hydrocalc::real* distance /* distance */
                               , /*[out]*/ hydrocalc::real distanceGrad [3] /* partial derivatives of distance with respect to inputs */);

void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_normalizeInput(/*[in] */ const hydrocalc::real* X /* input (unscaled) vector of size 3 */
                 , /*[in] */ int incX /* distance between elements of the vector X */
                 , /*[out]*/ hydrocalc::real* Y /* output (normalized) vector of size 3 */
                 , /*[in] */ int incY /* distance between elements of the vector Y */);

float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree0(/*[in] */ const float X [] /* input vector */);

float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree7(/*[in] */ const float X [] /* input vector */);

float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_boostedRegression02(/*[in] */ const float X [] /* input vector */);

float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree32(/*[in] */ const float X [] /* input vector */);


#ifndef DA_CBLAS_DECLARED
#define DA_CBLAS_DECLARED

enum CBLAS_ORDER {CblasRowMajor=101, CblasColMajor=102};
enum CBLAS_TRANSPOSE {CblasNoTrans=111, CblasTrans=112, CblasConjTrans=113};
enum CBLAS_UPLO {CblasUpper=121, CblasLower=122};
enum CBLAS_DIAG {CblasNonUnit=131, CblasUnit=132};

#if DA_CBLAS /* use external cblas */

void cblas_dtrsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const hydrocalc::real *A, const int lda, hydrocalc::real *X,
                 const int incX);

#else /* use local cblas routines implementation */

#endif /* DA_CBLAS */

#ifndef DA_DOUBLE_QNAN_DECL
#define DA_DOUBLE_QNAN_DECL
#ifdef NAN
static hydrocalc::real doubleQNAN() {
  return NAN;
}
#else
# ifdef INFINITY
#  define NAN (HUGE_VAL*HUGE_VAL-INFINITY)
# else
#  define NAN (HUGE_VAL*HUGE_VAL-(HUGE_VAL*HUGE_VAL/HUGE_VAL))
# endif

static hydrocalc::real doubleQNAN() {
  static const char* stringNAN = "NAN";
  char* endptr = 0;
  hydrocalc::real doubleNAN = strtod(stringNAN, &endptr);
  if (0 == endptr || 0 != *endptr || doubleNAN == doubleNAN) {
    /* Some compilers (e.g. MSVC) does not support NAN as a valid strtod() input, sad but true */
    /* So let's initialize quiet NAN according to the IEEEE 754 standard */
    memset(&doubleNAN, 0xFF, sizeof(doubleNAN));
  }
  return doubleNAN;
}
#endif
#endif

static void aux_fillnan(int sizeF, int sizeX, hydrocalc::real* F, int incF, hydrocalc::real* dFdX, int nextDF, int nextDX);

#endif /* DA_CBLAS_DECLARED */


void _KN27(/*[in] */ const hydrocalc::real* X /* input vector of size 2 */
        , /*[in] */ int incX /* distance between elements of the vector X */
        , /*[out]*/ hydrocalc::real* F /* optional (may be NULL) output vector of size 1 */
        , /*[in] */ int incF /* distance between elements of the vector F */
        , /*[out]*/ hydrocalc::real* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                  /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                  /* see declaration of struct DACalculationOptions for details */
        , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
        , /*[in] */ const struct DACalculationOptions* options) {
  /* mixture of approximators */

  void (*clusterModels[3])(const hydrocalc::real*, int, hydrocalc::real*, int, hydrocalc::real*, int, const struct DACalculationOptions*) = {
    _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_localApproximator, /* approximation model fro cluster #1 */
    _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_localApproximator1, /* approximation model fro cluster #2 */
    _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_localApproximator2, /* approximation model fro cluster #3 */
  };
  hydrocalc::real clusterWeights[3];
  hydrocalc::real clusterWeightsGrad[3][2];
  hydrocalc::real currentModelValue[1];
  hydrocalc::real currentModelGrad[1][2];
  hydrocalc::real XLF[3];
  hydrocalc::real lowFidelityModelGrad[1][2];
  struct DACalculationOptions localApproximationOptions;
  int clusterIndex;
  const int nextGradDF = (0 == options || options->_gradientMatrixFMajor)? ldGradF : 1; /* distance between dF[i+1]/dX[j] and dF[i]/dX[j] elements of derivatives matrix */
  const int nextGradDX = (0 == options || options->_gradientMatrixFMajor)? 1 : ldGradF; /* distance between dF[i]/dX[j+1] and dF[i]/dX[j] elements of derivatives matrix */
  
  if(0 == X || (0 == F && 0 == gradF)) {
    /* quick return if possible */
    return;
  }
  
  localApproximationOptions._gradientMatrixFMajor = 1;
  localApproximationOptions._estimateError = 0;

  /* copy input vector to the extended [X, LF(X)] one */
  if (incX == 1) {
    memcpy(XLF, X, sizeof(X[0])*2);
  } else {
    XLF[0] = X[incX*0];
    XLF[1] = X[incX*1];
  }

  /* evaluate low fidelity model */
  _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_lowFidelityModel(X, incX, XLF + 2, 1, ((0 == gradF)? 0 : lowFidelityModelGrad[0]), sizeof(lowFidelityModelGrad[0]) / sizeof(lowFidelityModelGrad[0][0]), &localApproximationOptions);

  /* evaluate cluster weights */
  _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_calculateWeights(XLF, 1, clusterWeights, (gradF ? clusterWeightsGrad : 0), (gradF ? lowFidelityModelGrad : 0));

  if (F) {
    /* zero initialize predictions */
    F[incF*0] = 0.;
  }

  if (gradF) {
    /* zero initialize gradient */
    gradF[nextGradDF*0+nextGradDX*0] = 0.;
    gradF[nextGradDF*0+nextGradDX*1] = 0.;
  }

  if((0 != options && options->_estimateError)) {
    /* This function doesn't support error prediction - fill output with nans */
    aux_fillnan(1, 2, F, incF, gradF, ((0 == options || options->_gradientMatrixFMajor) ? ldGradF : 1), ((0 == options || options->_gradientMatrixFMajor) ? 1 : ldGradF));
    return;
  }


  for(clusterIndex = 0; clusterIndex < 3; ++ clusterIndex) {
    if (clusterWeights[clusterIndex]) {
      /* Evaluate cluster model */
      (*clusterModels[clusterIndex])(X, incX, currentModelValue, 1, ((0 == gradF)? 0 : currentModelGrad[0]), sizeof(currentModelGrad[0])/sizeof(currentModelGrad[0][0]), &localApproximationOptions);

      if (0 != F) {
        F[0*incF] += clusterWeights[clusterIndex] * currentModelValue[0];
      }

      if (0 != gradF) {
        gradF[0*nextGradDF+0*nextGradDX] += clusterWeights[clusterIndex] * currentModelGrad[0][0] + clusterWeightsGrad[clusterIndex][0] * currentModelValue[0];
        gradF[0*nextGradDF+1*nextGradDX] += clusterWeights[clusterIndex] * currentModelGrad[0][1] + clusterWeightsGrad[clusterIndex][1] * currentModelValue[0];
      }
    }
  }

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree132(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return 0.000440752396f;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree72(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000002,  550000.f         }, /* #0 if x[0] < 550000.f or isnan(x[0]) then #1 else #2 */
    { 0x00000000,  0.00155699265f   }, /* #1   return 0.00155699265f */
    { 0x00000006,  0.550000012f     }, /* #2   if x[1] < 0.550000012f or isnan(x[1]) then #3 else #4 */
    { 0x00000000, -1.99556362e-05f  }, /* #3     return -1.99556362e-05f */
    { 0x00000000,  0.000739236653f  }, /* #4     return 0.000739236653f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree62(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  550000.f         }, /* #0  if x[0] < 550000.f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.649999976f     }, /* #1    if x[1] < 0.649999976f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000790464925f  }, /* #2      return 0.000790464925f */
    { 0x00000000,  0.00240156963f   }, /* #3      return 0.00240156963f */
    { 0x0000000A,  0.899999976f     }, /* #4    if x[1] < 0.899999976f or isnan(x[1]) then #5 else #6 */
    { 0x00000000,  0.000505852746f  }, /* #5      return 0.000505852746f */
    { 0x00000000,  0.00135608914f   }, /* #6      return 0.00135608914f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000007u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000008u) >> 3)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree102(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000002,  550000.f         }, /* #0 if x[0] < 550000.f or isnan(x[0]) then #1 else #2 */
    { 0x00000000,  0.000753045082f  }, /* #1   return 0.000753045082f */
    { 0x00000000,  0.000209352118f  }, /* #2   return 0.000209352118f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree52(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  550000.f         }, /* #0 if x[0] < 550000.f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.649999976f     }, /* #1   if x[1] < 0.649999976f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000988078187f  }, /* #2     return 0.000988078187f */
    { 0x00000000,  0.00309878308f   }, /* #3     return 0.00309878308f */
    { 0x00000000,  0.00107762706f   }, /* #4   return 0.00107762706f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000007u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000008u) >> 3)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree42(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  5500000.f        }, /* #0  if x[0] < 5500000.f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.550000012f     }, /* #1    if x[1] < 0.550000012f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000746226346f  }, /* #2      return 0.000746226346f */
    { 0x00000000,  0.00308242277f   }, /* #3      return 0.00308242277f */
    { 0x0000000A,  0.899999976f     }, /* #4    if x[1] < 0.899999976f or isnan(x[1]) then #5 else #6 */
    { 0x00000000,  0.000544152281f  }, /* #5      return 0.000544152281f */
    { 0x00000000,  0.00177093747f   }, /* #6      return 0.00177093747f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000007u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000008u) >> 3)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree82(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.649999976f     }, /* #0 if x[1] < 0.649999976f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.000229183279f  }, /* #1   return 0.000229183279f */
    { 0x00000002,  550000.f         }, /* #2   if x[0] < 550000.f or isnan(x[0]) then #3 else #4 */
    { 0x00000000,  0.00151088845f   }, /* #3     return 0.00151088845f */
    { 0x00000000,  0.00059851585f   }, /* #4     return 0.00059851585f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree22(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return 0.00423413748f;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree112(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000002,  5500000.f        }, /* #0 if x[0] < 5500000.f or isnan(x[0]) then #1 else #2 */
    { 0x00000000,  0.00651518395f   }, /* #1   return 0.00651518395f */
    { 0x00000000,  0.00347224483f   }, /* #2   return 0.00347224483f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree17(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.899999976f     }, /* #0 if x[1] < 0.899999976f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  3.8963557e-05f   }, /* #1   return 3.8963557e-05f */
    { 0x00000000,  0.00095275644f   }, /* #2   return 0.00095275644f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree5(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.449999988f     }, /* #0 if x[1] < 0.449999988f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00265207305f   }, /* #1   return 0.00265207305f */
    { 0x00000000,  0.00603895215f   }, /* #2   return 0.00603895215f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree16(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.25f            }, /* #0 if x[1] < 0.25f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.000232762104f  }, /* #1   return -0.000232762104f */
    { 0x00000000,  0.000511336373f  }, /* #2   return 0.000511336373f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree8(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.649999976f     }, /* #0 if x[1] < 0.649999976f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00124483113f   }, /* #1   return 0.00124483113f */
    { 0x00000000,  0.00306683802f   }, /* #2   return 0.00306683802f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree14(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.899999976f     }, /* #0 if x[1] < 0.899999976f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.000206565863f  }, /* #1   return 0.000206565863f */
    { 0x00000000,  0.00142486102f   }, /* #2   return 0.00142486102f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_lowFidelityModel(/*[in] */ const hydrocalc::real* X /* input vector of size 2 */
                   , /*[in] */ int incX /* distance between elements of the vector X */
                   , /*[out]*/ hydrocalc::real* F /* optional (may be NULL) output vector of size 1 */
                   , /*[in] */ int incF /* distance between elements of the vector F */
                   , /*[out]*/ hydrocalc::real* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                             /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                             /* see declaration of struct DACalculationOptions for details */
                   , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                   , /*[in] */ const struct DACalculationOptions* options) {
  /* constant function F=[1.041] */

  if ((0 != options && options->_estimateError)) {
    if (F) {
      F[incF*0] = 0.020102302457742617;
    }

    if (gradF) {
      const int nextDF = (0 == options || options->_gradientMatrixFMajor)? ldGradF : 1; /* distance between dF[i+1]/dX[j] and dF[i]/dX[j] elements of derivatives matrix */
      const int nextDX = (0 == options || options->_gradientMatrixFMajor)? 1 : ldGradF; /* distance between dF[i]/dX[j+1] and dF[i]/dX[j] elements of derivatives matrix */
      gradF[nextDF*0+nextDX*0] = 0.;
      gradF[nextDF*0+nextDX*1] = 0.;
    }

    return;
  }

  if(F) {
    F[0 * incF] = 1.0410000000000001;
  }
  
  if(gradF) {
    if((0 == options || options->_gradientMatrixFMajor)) {
      /* gradient matrix is F-major 1-by-2 */
      gradF[0 * ldGradF + 0] = 0.;
      gradF[0 * ldGradF + 1] = 0.;
    } else {
      /* gradient matrix is X-major 2-by-1 */
      gradF[0 * ldGradF + 0] = 0.;
      gradF[1 * ldGradF + 0] = 0.;
    }
  }

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree92(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.649999976f     }, /* #0  if x[1] < 0.649999976f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.000170246203f  }, /* #1    return 0.000170246203f */
    { 0x00000002,  5500000.f        }, /* #2    if x[0] < 5500000.f or isnan(x[0]) then #3 else #4 */
    { 0x00000000,  0.000987477018f  }, /* #3      return 0.000987477018f */
    { 0x00000006,  0.899999976f     }, /* #4      if x[1] < 0.899999976f or isnan(x[1]) then #5 else #6 */
    { 0x00000000, -0.00033183099f   }, /* #5        return -0.00033183099f */
    { 0x00000000,  0.000939595746f  }, /* #6        return 0.000939595746f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree15(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.899999976f     }, /* #0 if x[1] < 0.899999976f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.000150775915f  }, /* #1   return 0.000150775915f */
    { 0x00000000,  0.00121112471f   }, /* #2   return 0.00121112471f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree13(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.899999976f     }, /* #0 if x[1] < 0.899999976f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.000282962341f  }, /* #1   return 0.000282962341f */
    { 0x00000000,  0.00167630916f   }, /* #2   return 0.00167630916f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree131(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return 0.000594784331f;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree11(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.899999976f     }, /* #0 if x[1] < 0.899999976f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.000588834286f  }, /* #1   return 0.000588834286f */
    { 0x00000000,  0.00222857599f   }, /* #2   return 0.00222857599f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree6(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.449999988f     }, /* #0 if x[1] < 0.449999988f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00198905473f   }, /* #1   return 0.00198905473f */
    { 0x00000000,  0.00452922611f   }, /* #2   return 0.00452922611f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_calculateWeights(/*[in] */ const hydrocalc::real* X /* input point */
                   , /*[in] */ int incX /* distance between elements of the vector X */
                   , /*[out]*/ hydrocalc::real weights [3] /* weights of the clusters */
                   , /*[out]*/ hydrocalc::real weightsGrad [3][2] /* partial derivatives of weights of the clusters with respect to inputs */
                   , /*[in] */ const hydrocalc::real dLFdX [1][2] /* partial derivatives of weights of the low fidelity model with respect to inputs */) {
  /* mixture of approximators: clusters weights calculation */
  extern const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCenter_000[3];
  extern const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCovarianceFactor_000[3][3];
  extern const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCenter_001[3];
  extern const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCovarianceFactor_001[3][3];
  extern const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCenter_002[3];
  extern const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCovarianceFactor_002[3][3];
  extern const hydrocalc::real _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_extrapolationWeights[3];

  hydrocalc::real normalizedX[3];
  hydrocalc::real totalWeight = 0.;
  hydrocalc::real weightThreshold = 1.;
  hydrocalc::real currentDistance;
  hydrocalc::real totalWeightGrad[3] = {0., 0., 0.};
  hydrocalc::real dWdXnorm[3][3];
  
  _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_normalizeInput(X, incX, normalizedX, 1);
  
  _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_calculateMahalanobisDistance(normalizedX, _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCenter_000, _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCovarianceFactor_000, &currentDistance, (weightsGrad? dWdXnorm[0] : 0));
  
  weights[0] = 15.865478226640747 * exp(-currentDistance);
  weightThreshold = (weightThreshold < weights[0]) ? weights[0] : weightThreshold;
  
  _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_calculateMahalanobisDistance(normalizedX, _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCenter_001, _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCovarianceFactor_001, &currentDistance, (weightsGrad? dWdXnorm[1] : 0));
  
  weights[1] = 12.458929112925606 * exp(-currentDistance);
  weightThreshold = (weightThreshold < weights[1]) ? weights[1] : weightThreshold;
  
  _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_calculateMahalanobisDistance(normalizedX, _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCenter_002, _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_clusterCovarianceFactor_002, &currentDistance, (weightsGrad? dWdXnorm[2] : 0));
  
  weights[2] = 10.842472914538952 * exp(-currentDistance);
  weightThreshold = (weightThreshold < weights[2]) ? weights[2] : weightThreshold;
  
  weightThreshold *= 2.2204460492503131e-16;

  if (weights[0] < weightThreshold) {
    weights[0] = 0.;
    if (weightsGrad) {
      dWdXnorm[0][0] = 0.;
      dWdXnorm[0][1] = 0.;
      dWdXnorm[0][2] = 0.;
    }
  } else if (weightsGrad) {
    const hydrocalc::real gradientFactor = -2. * weights[0];
    totalWeightGrad[0] += dWdXnorm[0][0] *= gradientFactor;
    totalWeightGrad[1] += dWdXnorm[0][1] *= gradientFactor;
    totalWeightGrad[2] += dWdXnorm[0][2] *= gradientFactor;
  }

  totalWeight += (weights[0] - totalWeight) / (0 + 1);

  if (weights[1] < weightThreshold) {
    weights[1] = 0.;
    if (weightsGrad) {
      dWdXnorm[1][0] = 0.;
      dWdXnorm[1][1] = 0.;
      dWdXnorm[1][2] = 0.;
    }
  } else if (weightsGrad) {
    const hydrocalc::real gradientFactor = -2. * weights[1];
    totalWeightGrad[0] += dWdXnorm[1][0] *= gradientFactor;
    totalWeightGrad[1] += dWdXnorm[1][1] *= gradientFactor;
    totalWeightGrad[2] += dWdXnorm[1][2] *= gradientFactor;
  }

  totalWeight += (weights[1] - totalWeight) / (1 + 1);

  if (weights[2] < weightThreshold) {
    weights[2] = 0.;
    if (weightsGrad) {
      dWdXnorm[2][0] = 0.;
      dWdXnorm[2][1] = 0.;
      dWdXnorm[2][2] = 0.;
    }
  } else if (weightsGrad) {
    const hydrocalc::real gradientFactor = -2. * weights[2];
    totalWeightGrad[0] += dWdXnorm[2][0] *= gradientFactor;
    totalWeightGrad[1] += dWdXnorm[2][1] *= gradientFactor;
    totalWeightGrad[2] += dWdXnorm[2][2] *= gradientFactor;
  }

  totalWeight += (weights[2] - totalWeight) / (2 + 1);

  totalWeight *= 3;

  if (totalWeight <= 2.2204460492503131e-16) {
    /* we are too far from the known domain */
    memcpy(weights, _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_extrapolationWeights, sizeof(_W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_extrapolationWeights));
    if(0 != weightsGrad) {
      weightsGrad[0][0] = 0.;
      weightsGrad[0][1] = 0.;
      weightsGrad[1][0] = 0.;
      weightsGrad[1][1] = 0.;
      weightsGrad[2][0] = 0.;
      weightsGrad[2][1] = 0.;
    }
    return;
  }
  
  weights[0] /= totalWeight;
  weights[1] /= totalWeight;
  weights[2] /= totalWeight;
  
  if (weightsGrad) {
    weightsGrad[0][0] = (dWdXnorm[0][0] - weights[0] * totalWeightGrad[0]) / (totalWeight * 41878417.770971246);
    weightsGrad[0][1] = (dWdXnorm[0][1] - weights[0] * totalWeightGrad[1]) / (totalWeight * 0.30397368307141326);
    weightsGrad[1][0] = (dWdXnorm[1][0] - weights[1] * totalWeightGrad[0]) / (totalWeight * 41878417.770971246);
    weightsGrad[1][1] = (dWdXnorm[1][1] - weights[1] * totalWeightGrad[1]) / (totalWeight * 0.30397368307141326);
    weightsGrad[2][0] = (dWdXnorm[2][0] - weights[2] * totalWeightGrad[0]) / (totalWeight * 41878417.770971246);
    weightsGrad[2][1] = (dWdXnorm[2][1] - weights[2] * totalWeightGrad[1]) / (totalWeight * 0.30397368307141326);
    if (dLFdX) {
      hydrocalc::real dWdLF;

      dWdLF = (dWdXnorm[0][2] - weights[0] * totalWeightGrad[2]) / (totalWeight * 1.);
      ((weightsGrad[0][1*0]+=dWdLF*dLFdX[0][1*0]), (weightsGrad[0][1*1]+=dWdLF*dLFdX[0][1*1]));

      dWdLF = (dWdXnorm[1][2] - weights[1] * totalWeightGrad[2]) / (totalWeight * 1.);
      ((weightsGrad[1][1*0]+=dWdLF*dLFdX[0][1*0]), (weightsGrad[1][1*1]+=dWdLF*dLFdX[0][1*1]));

      dWdLF = (dWdXnorm[2][2] - weights[2] * totalWeightGrad[2]) / (totalWeight * 1.);
      ((weightsGrad[2][1*0]+=dWdLF*dLFdX[0][1*0]), (weightsGrad[2][1*1]+=dWdLF*dLFdX[0][1*1]));
    }
  }

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree2(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00288027246f   }, /* #1   return 0.00288027246f */
    { 0x00000000,  0.0121404529f    }, /* #2   return 0.0121404529f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree9(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000E,  0.899999976f     }, /* #0  if x[1] < 0.899999976f or isnan(x[1]) then #1 else #6 */
    { 0x0000000A,  0.25f            }, /* #1    if x[1] < 0.25f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000373215997f  }, /* #2      return 0.000373215997f */
    { 0x0000000A,  0.75f            }, /* #3      if x[1] < 0.75f or isnan(x[1]) then #4 else #5 */
    { 0x00000000,  0.0015034558f    }, /* #4        return 0.0015034558f */
    { 0x00000000,  8.45432296e-05f  }, /* #5        return 8.45432296e-05f */
    { 0x00000000,  0.0030845406f    }, /* #6    return 0.0030845406f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000007u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000008u) >> 3)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_calculateMahalanobisDistance(/*[in] */ const hydrocalc::real X [3] /* input point */
                               , /*[in] */ const hydrocalc::real mu [3] /* mean value */
                               , /*[in] */ const hydrocalc::real sigmaL [3][3] /* lower Cholessky factor of the covariance matrix */
                               , /*[out]*/ hydrocalc::real* distance /* distance */
                               , /*[out]*/ hydrocalc::real distanceGrad [3] /* partial derivatives of distance with respect to inputs */) {
  /* mixture of approximators: calculate Mahalanobis distance to cluster center */

  hydrocalc::real centeredX[3];
  centeredX[0] = X[0] - mu[0];
  centeredX[1] = X[1] - mu[1];
  centeredX[2] = X[2] - mu[2];
  
#if DA_CBLAS
  cblas_dtrsv(CblasRowMajor, CblasLower, CblasNoTrans, CblasNonUnit, 3, sigmaL, 3, centeredX, 1);
#else
  { /* inline implementation of cblas_dtrsv(CblasRowMajor, CblasLower, CblasNoTrans, CblasNonUnit, 3, sigmaL, 3, centeredX, 1) */
    centeredX[0] /= sigmaL[0][0];
    centeredX[1] = (centeredX[1] - (sigmaL[1][0]*centeredX[0])) / sigmaL[1][1];
    centeredX[2] = (centeredX[2] - (sigmaL[2][0]*centeredX[0] + sigmaL[2][1]*centeredX[1])) / sigmaL[2][2];
  }
#endif
  
  if(0 != distance) {
    *distance = (centeredX[0]*centeredX[0] + centeredX[1]*centeredX[1] + centeredX[2]*centeredX[2]);
  }
  
  if(0 != distanceGrad) {
#if DA_CBLAS
    cblas_dtrsv(CblasRowMajor, CblasLower, CblasTrans, CblasNonUnit, 3, sigmaL, 3, centeredX, 1);
#else
    { /* inline implementation of cblas_dtrsv(CblasRowMajor, CblasLower, CblasTrans, CblasNonUnit, 3, sigmaL, 3, centeredX, 1) */
      centeredX[2] /= sigmaL[2][2];
      ((centeredX[1*0]+=-centeredX[2]*sigmaL[2][1*0]), (centeredX[1*1]+=-centeredX[2]*sigmaL[2][1*1]));
      centeredX[1] /= sigmaL[1][1];
      ((centeredX[1*0]+=-centeredX[1]*sigmaL[1][1*0]));
      centeredX[0] /= sigmaL[0][0];
      ;
    }
#endif
    distanceGrad[0] = centeredX[0];
    distanceGrad[1] = centeredX[1];
    distanceGrad[2] = centeredX[2];
  }

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree1(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.150000006f     }, /* #0 if x[1] < 0.150000006f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00605045585f   }, /* #1   return 0.00605045585f */
    { 0x00000000,  0.0170672666f    }, /* #2   return 0.0170672666f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree12(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.649999976f     }, /* #0 if x[1] < 0.649999976f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.000284251582f  }, /* #1   return 0.000284251582f */
    { 0x00000000,  0.00145326555f   }, /* #2   return 0.00145326555f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree10(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.899999976f     }, /* #0 if x[1] < 0.899999976f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.000806626107f  }, /* #1   return 0.000806626107f */
    { 0x00000000,  0.00262185931f   }, /* #2   return 0.00262185931f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree122(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000C,  0.899999976f     }, /* #0 if x[1] < 0.899999976f or isnan(x[1]) then #1 else #4 */
    { 0x00000002,  5500000.f        }, /* #1   if x[0] < 5500000.f or isnan(x[0]) then #2 else #3 */
    { 0x00000000,  0.000234822452f  }, /* #2     return 0.000234822452f */
    { 0x00000000, -0.00035905838f   }, /* #3     return -0.00035905838f */
    { 0x00000000,  0.000574457692f  }, /* #4   return 0.000574457692f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000007u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000008u) >> 3)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree3(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.25f            }, /* #0 if x[1] < 0.25f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00370706338f   }, /* #1   return 0.00370706338f */
    { 0x00000000,  0.00983670726f   }, /* #2   return 0.00983670726f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree71(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.25f            }, /* #0 if x[1] < 0.25f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00226603751f   }, /* #1   return 0.00226603751f */
    { 0x00000000,  0.00406319415f   }, /* #2   return 0.00406319415f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree4(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.449999988f     }, /* #0 if x[1] < 0.449999988f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00353609351f   }, /* #1   return 0.00353609351f */
    { 0x00000000,  0.00805194955f   }, /* #2   return 0.00805194955f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree121(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  550000.f         }, /* #0  if x[0] < 550000.f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.0500000007f    }, /* #1    if x[1] < 0.0500000007f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  7.9384452e-05f   }, /* #2      return 7.9384452e-05f */
    { 0x00000000,  0.00135513779f   }, /* #3      return 0.00135513779f */
    { 0x0000000A,  0.350000024f     }, /* #4    if x[1] < 0.350000024f or isnan(x[1]) then #5 else #6 */
    { 0x00000000,  0.000266291725f  }, /* #5      return 0.000266291725f */
    { 0x00000000,  0.0010310174f    }, /* #6      return 0.0010310174f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000007u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000008u) >> 3)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree18(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.899999976f     }, /* #0 if x[1] < 0.899999976f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  2.84528742e-05f  }, /* #1   return 2.84528742e-05f */
    { 0x00000000,  0.000809848367f  }, /* #2   return 0.000809848367f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree31(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.150000006f     }, /* #0 if x[1] < 0.150000006f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00705492264f   }, /* #1   return 0.00705492264f */
    { 0x00000000,  0.0125374077f    }, /* #2   return 0.0125374077f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree19(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return 0.000529586105f;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_boostedRegression0(/*[in] */ const float X [] /* input vector */) {
  /* boosted regression forest */

  float F = 0.f;
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree0(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree1(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree2(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree3(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree4(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree5(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree6(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree7(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree8(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree9(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree10(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree11(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree12(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree13(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree14(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree15(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree16(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree17(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree18(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree19(X);
  return F;
}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree0(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return 0.474747717f;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree101(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  5500000.f        }, /* #0 if x[0] < 5500000.f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.25f            }, /* #1   if x[1] < 0.25f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.00103389961f   }, /* #2     return 0.00103389961f */
    { 0x00000000,  0.0021772529f    }, /* #3     return 0.0021772529f */
    { 0x00000000,  0.000606790243f  }, /* #4   return 0.000606790243f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000007u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000008u) >> 3)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_localApproximator(/*[in] */ const hydrocalc::real* X /* input vector of size 2 */
                    , /*[in] */ int incX /* distance between elements of the vector X */
                    , /*[out]*/ hydrocalc::real* F /* optional (may be NULL) output vector of size 1 */
                    , /*[in] */ int incF /* distance between elements of the vector F */
                    , /*[out]*/ hydrocalc::real* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                              /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                              /* see declaration of struct DACalculationOptions for details */
                    , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                    , /*[in] */ const struct DACalculationOptions* options) {
  /* GBRT approximation */

  if (gradF) {
    /* no gradient */
    const int nextDF = (0 == options || options->_gradientMatrixFMajor)? ldGradF : 1;
    const int nextDX = (0 == options || options->_gradientMatrixFMajor)? 1 : ldGradF;
    aux_fillnan(1, 2, 0, 0, gradF, nextDF, nextDX);
  }

  if (F) {
    float Z[2] = { (float)X[0], (float)X[incX * 1] };
    /* predict value */
    F[incF*0] = _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_boostedRegression0(Z);
    F[0*incF] = 0.5 + F[0*incF];
  }

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree01(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return 0.456354558f;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree161(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000C,  0.350000024f     }, /* #0  if x[1] < 0.350000024f or isnan(x[1]) then #1 else #4 */
    { 0x00000002,  550000.f         }, /* #1    if x[0] < 550000.f or isnan(x[0]) then #2 else #3 */
    { 0x00000000,  0.000431106106f  }, /* #2      return 0.000431106106f */
    { 0x00000000, -0.000119247044f  }, /* #3      return -0.000119247044f */
    { 0x00000002,  5500000.f        }, /* #4    if x[0] < 5500000.f or isnan(x[0]) then #5 else #6 */
    { 0x00000000,  0.000976538693f  }, /* #5      return 0.000976538693f */
    { 0x00000000, -0.000155872112f  }, /* #6      return -0.000155872112f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000007u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000008u) >> 3)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree110(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00982022472f   }, /* #1   return 0.00982022472f */
    { 0x00000000,  0.0222402681f    }, /* #2   return 0.0222402681f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree21(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00761067448f   }, /* #1   return 0.00761067448f */
    { 0x00000000,  0.0160814188f    }, /* #2   return 0.0160814188f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree61(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.25f            }, /* #0 if x[1] < 0.25f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00310416357f   }, /* #1   return 0.00310416357f */
    { 0x00000000,  0.00546968309f   }, /* #2   return 0.00546968309f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree02(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return 0.538110971f;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree81(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  550000.f         }, /* #0  if x[0] < 550000.f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.0500000007f    }, /* #1    if x[1] < 0.0500000007f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000644445419f  }, /* #2      return 0.000644445419f */
    { 0x00000000,  0.00365361222f   }, /* #3      return 0.00365361222f */
    { 0x0000000A,  0.25f            }, /* #4    if x[1] < 0.25f or isnan(x[1]) then #5 else #6 */
    { 0x00000000,  0.00100401475f   }, /* #5      return 0.00100401475f */
    { 0x00000000,  0.00221716403f   }, /* #6      return 0.00221716403f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000007u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000008u) >> 3)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree41(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.150000006f     }, /* #0 if x[1] < 0.150000006f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00524079893f   }, /* #1   return 0.00524079893f */
    { 0x00000000,  0.00915232021f   }, /* #2   return 0.00915232021f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_localApproximator2(/*[in] */ const hydrocalc::real* X /* input vector of size 2 */
                    , /*[in] */ int incX /* distance between elements of the vector X */
                    , /*[out]*/ hydrocalc::real* F /* optional (may be NULL) output vector of size 1 */
                    , /*[in] */ int incF /* distance between elements of the vector F */
                    , /*[out]*/ hydrocalc::real* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                              /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                              /* see declaration of struct DACalculationOptions for details */
                    , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                    , /*[in] */ const struct DACalculationOptions* options) {
  /* GBRT approximation */

  if (gradF) {
    /* no gradient */
    const int nextDF = (0 == options || options->_gradientMatrixFMajor)? ldGradF : 1;
    const int nextDX = (0 == options || options->_gradientMatrixFMajor)? 1 : ldGradF;
    aux_fillnan(1, 2, 0, 0, gradF, nextDF, nextDX);
  }

  if (F) {
    float Z[2] = { (float)X[0], (float)X[incX * 1] };
    /* predict value */
    F[incF*0] = _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_boostedRegression02(Z);
    F[0*incF] = 0.5 + F[0*incF];
  }

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree51(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.25f            }, /* #0 if x[1] < 0.25f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00425227219f   }, /* #1   return 0.00425227219f */
    { 0x00000000,  0.00736301672f   }, /* #2   return 0.00736301672f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree113(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return 0.000543940812f;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree91(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  550000.f         }, /* #0  if x[0] < 550000.f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.0500000007f    }, /* #1    if x[1] < 0.0500000007f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000547778618f  }, /* #2      return 0.000547778618f */
    { 0x00000000,  0.00277674431f   }, /* #3      return 0.00277674431f */
    { 0x0000000A,  0.25f            }, /* #4    if x[1] < 0.25f or isnan(x[1]) then #5 else #6 */
    { 0x00000000,  0.000745838042f  }, /* #5      return 0.000745838042f */
    { 0x00000000,  0.00168501376f   }, /* #6      return 0.00168501376f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000007u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000008u) >> 3)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree111(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000002,  550000.f         }, /* #0 if x[0] < 550000.f or isnan(x[0]) then #1 else #2 */
    { 0x00000000,  0.00154100067f   }, /* #1   return 0.00154100067f */
    { 0x00000006,  0.350000024f     }, /* #2   if x[1] < 0.350000024f or isnan(x[1]) then #3 else #4 */
    { 0x00000000,  0.000363121449f  }, /* #3     return 0.000363121449f */
    { 0x00000000,  0.00128879549f   }, /* #4     return 0.00128879549f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_boostedRegression02(/*[in] */ const float X [] /* input vector */) {
  /* boosted regression forest */

  float F = 0.f;
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree02(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree112(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree22(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree32(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree42(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree52(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree62(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree72(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree82(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree92(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree102(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree113(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree122(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree132(X);
  return F;
}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree141(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.25f            }, /* #0 if x[1] < 0.25f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.000180670031f  }, /* #1   return 0.000180670031f */
    { 0x00000002,  5500000.f        }, /* #2   if x[0] < 5500000.f or isnan(x[0]) then #3 else #4 */
    { 0x00000000,  0.000987467822f  }, /* #3     return 0.000987467822f */
    { 0x00000000,  3.19480896e-05f  }, /* #4     return 3.19480896e-05f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree151(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return 0.000321743282f;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree171(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return 0.000654902076f;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree32(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000002,  550000.f         }, /* #0 if x[0] < 550000.f or isnan(x[0]) then #1 else #2 */
    { 0x00000000,  0.00428492436f   }, /* #1   return 0.00428492436f */
    { 0x00000006,  0.550000012f     }, /* #2   if x[1] < 0.550000012f or isnan(x[1]) then #3 else #4 */
    { 0x00000000,  0.000532221806f  }, /* #3     return 0.000532221806f */
    { 0x00000000,  0.00237629423f   }, /* #4     return 0.00237629423f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_boostedRegression01(/*[in] */ const float X [] /* input vector */) {
  /* boosted regression forest */

  float F = 0.f;
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree01(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree110(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree21(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree31(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree41(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree51(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree61(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree71(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree81(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree91(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree101(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree111(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree121(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree131(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree141(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree151(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree161(X);
  F += _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree171(X);
  return F;
}


float _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_regressionTree7(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.649999976f     }, /* #0 if x[1] < 0.649999976f or isnan(x[1]) then #1 else #2 */
    { 0x00000000,  0.00168791867f   }, /* #1   return 0.00168791867f */
    { 0x00000000,  0.00395722408f   }, /* #2   return 0.00395722408f */
  };
  uint32_t nodeIndex = 0u;
  uint32_t rightChildLeapDistance;
  
  /* iterate until first leaf node */
  while (0u != (rightChildLeapDistance = (tree[nodeIndex]._info & 0x00000003u))) {
        /* default is a left child node, so if test value is NaN then (test >= _value) is false and left child will be selected */
        nodeIndex += (X[((tree[nodeIndex]._info & 0x00000004u) >> 2)] >= tree[nodeIndex]._value) ? rightChildLeapDistance : 1u;
  }
  
  return tree[nodeIndex]._value;

}


void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_normalizeInput(/*[in] */ const hydrocalc::real* X /* input (unscaled) vector of size 3 */
                 , /*[in] */ int incX /* distance between elements of the vector X */
                 , /*[out]*/ hydrocalc::real* Y /* output (normalized) vector of size 3 */
                 , /*[in] */ int incY /* distance between elements of the vector Y */) {
  /* apply standard normalization */

  /* apply standard normalization */
  Y[0 * incY] = (-27775000. + X[0 * incX]) * 2.3878648077606395e-08;
  Y[1 * incY] = (-0.45999999999999996 + X[1 * incX]) * 3.2897584747988451;
  Y[2 * incY] = (-1.0410000000000001 + X[2 * incX]) * 1.;

}


void _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_localApproximator1(/*[in] */ const hydrocalc::real* X /* input vector of size 2 */
                    , /*[in] */ int incX /* distance between elements of the vector X */
                    , /*[out]*/ hydrocalc::real* F /* optional (may be NULL) output vector of size 1 */
                    , /*[in] */ int incF /* distance between elements of the vector F */
                    , /*[out]*/ hydrocalc::real* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                              /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                              /* see declaration of struct DACalculationOptions for details */
                    , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                    , /*[in] */ const struct DACalculationOptions* options) {
  /* GBRT approximation */

  if (gradF) {
    /* no gradient */
    const int nextDF = (0 == options || options->_gradientMatrixFMajor)? ldGradF : 1;
    const int nextDX = (0 == options || options->_gradientMatrixFMajor)? 1 : ldGradF;
    aux_fillnan(1, 2, 0, 0, gradF, nextDF, nextDX);
  }

  if (F) {
    float Z[2] = { (float)X[0], (float)X[incX * 1] };
    /* predict value */
    F[incF*0] = _W1G22XLMTP1A2QRFNERF9WXSXF5PDNQC_boostedRegression01(Z);
    F[0*incF] = 0.5 + F[0*incF];
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

#endif /* DA_CBLAS */

static void aux_fillnan(int sizeF, int sizeX, hydrocalc::real* F, int incF, hydrocalc::real* dFdX, int nextDF, int nextDX) {
#ifdef NAN
  const hydrocalc::real NaN = NAN;
#else
  const hydrocalc::real NaN = doubleQNAN();
#endif

  if (F) {
    int i;
    if (1 == incF) {
      for (i = 0; i < sizeF; ++ i) {
        F[i] = NaN;
      }
    } else {
      for (i = 0; i < sizeF; ++ i) {
        F[i * incF] = NaN;
      }
    }
  }

  if (dFdX) {
    int i, j;
    if ((nextDX == 1 && nextDF == sizeX) || (nextDF == 1 && nextDX == sizeF)) {
      for (i = 0; i < sizeF * sizeX; ++ i) {
        dFdX[i] = NaN;
      }
    } else if (1 == nextDX) {
      for (i = 0; i < sizeF; ++ i) {
        for (j = 0; j < sizeX; ++ j) {
          dFdX[j] = NaN;
        }
        dFdX += nextDF;
      }
    } else if (1 == nextDF) {
      for (j = 0; j < sizeX; ++ j) {
        for (i = 0; i < sizeF; ++ i) {
          dFdX[i] = NaN;
        }
        dFdX += nextDX;
      }
    } else {
      for (i = 0; i < sizeF; ++ i) {
        for (j = 0; j < sizeX; ++ j) {
          dFdX[j * nextDX] = NaN;
        }
        dFdX += nextDF;
      }
    }
  }
}

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
