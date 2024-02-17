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
#include <pch.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <HydraulicResistances/approximations/E523.h>

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

void _E523(/*[in] */ const HSReal* X /* input vector of size 2 */
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

int E523( const int N /* number of input vectors (N >= 0) */
        , const HSReal* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in doubles) between input vectors (ldInput >= {input vector size}) */
        , HSReal* output /* pointer to the output vectors (N == 0 || output != NULL) */
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
    _E523(input + i * ldInput, 1, output + i * ldOutput, 1, output + i * ldOutput + daYDimensionality, daXDimensionality, 0);
  }
  return 0;
}


int E523AE( const int N /* number of input vectors (N >= 0) */
        , const HSReal* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in doubles) between input vectors (ldInput >= {input vector size}) */
        , HSReal* output /* pointer to the output vectors (N == 0 || output != NULL) */
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
    _E523(input + i * ldInput, 1, output + i * ldOutput, 1, output + i * ldOutput + daYDimensionality, daXDimensionality, &options);
  }
  return 0;
}

/* Calculates value and/or gradient of the function E523 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int E523Calc( 
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
    _E523(input, inputInc, value, valueInc, 0, 0, 0);
  } else {
    /* gradient output may be F-major, or X-major, or custom, */
    /* but _E523 function can handle F-major or X-major cases only*/
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
      _E523(input, inputInc, value, valueInc, grad, gradNextDF, &options);
    } else if(1 == daYDimensionality || 1 == gradNextDF) {
      options._gradientMatrixFMajor = 0;
      _E523(input, inputInc, value, valueInc, grad, gradNextDX, &options);
    } else {
      int dx, df;
      HSReal contiguousGrad[2*1];
      options._gradientMatrixFMajor = 1;
      _E523(input, inputInc, value, valueInc, contiguousGrad, 2, &options);
      for(df = 0; df < 1; ++ df) {
        for(dx = 0; dx < 2; ++ dx) {
          grad[gradNextDF*df + gradNextDX*dx] = contiguousGrad[2*df+dx];
        }
      }
    }
  }
  return 0;
}


/* Calculates value and/or gradient of the function AE E523 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int E523CalcAE( 
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
    _E523(input, inputInc, value, valueInc, 0, 0, &options);
  } else {
    /* gradient output may be F-major, or X-major, or custom, */
    /* but _E523 function can handle F-major or X-major cases only*/
    if (daXDimensionality > 1 && 0 == gradNextDX) {
      return 6;
    }
    if (daYDimensionality > 1 && 0 == gradNextDF) {
      return 7;
    }
    if(1 == daXDimensionality || 1 == gradNextDX) {
      options._gradientMatrixFMajor = 1;
      _E523(input, inputInc, value, valueInc, grad, gradNextDF, &options);
    } else if(1 == daYDimensionality || 1 == gradNextDF) {
      options._gradientMatrixFMajor = 0;
      _E523(input, inputInc, value, valueInc, grad, gradNextDX, &options);
    } else {
      int dx, df;
      HSReal contiguousGrad[2*1];
      options._gradientMatrixFMajor = 1;
      _E523(input, inputInc, value, valueInc, contiguousGrad, 2, &options);
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


void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_calculateWeights(/*[in] */ const HSReal* X /* input point */
                   , /*[in] */ int incX /* distance between elements of the vector X */
                   , /*[out]*/ HSReal weights [3] /* weights of the clusters */
                   , /*[out]*/ HSReal weightsGrad [3][2] /* partial derivatives of weights of the clusters with respect to inputs */
                   , /*[in] */ const HSReal dLFdX [1][2] /* partial derivatives of weights of the low fidelity model with respect to inputs */);

void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_localApproximator(/*[in] */ const HSReal* X /* input vector of size 2 */
                    , /*[in] */ int incX /* distance between elements of the vector X */
                    , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
                    , /*[in] */ int incF /* distance between elements of the vector F */
                    , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                              /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                              /* see declaration of struct DACalculationOptions for details */
                    , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                    , /*[in] */ const struct DACalculationOptions* options);

void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_localApproximator1(/*[in] */ const HSReal* X /* input vector of size 2 */
                    , /*[in] */ int incX /* distance between elements of the vector X */
                    , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
                    , /*[in] */ int incF /* distance between elements of the vector F */
                    , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                              /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                              /* see declaration of struct DACalculationOptions for details */
                    , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                    , /*[in] */ const struct DACalculationOptions* options);

void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_localApproximator2(/*[in] */ const HSReal* X /* input vector of size 2 */
                    , /*[in] */ int incX /* distance between elements of the vector X */
                    , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
                    , /*[in] */ int incF /* distance between elements of the vector F */
                    , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                              /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                              /* see declaration of struct DACalculationOptions for details */
                    , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                    , /*[in] */ const struct DACalculationOptions* options);

void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_lowFidelityModel(/*[in] */ const HSReal* X /* input vector of size 2 */
                   , /*[in] */ int incX /* distance between elements of the vector X */
                   , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
                   , /*[in] */ int incF /* distance between elements of the vector F */
                   , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                             /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                             /* see declaration of struct DACalculationOptions for details */
                   , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                   , /*[in] */ const struct DACalculationOptions* options);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_boostedRegression02(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree02(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree101(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree110(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree112(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree121(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree131(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree141(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree151(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree161(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree171(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree181(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree191(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree201(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree212(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree22(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree221(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree32(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree42(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree52(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree62(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree72(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree82(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree91(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree0(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree1(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree2(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree3(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree4(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree5(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree7(/*[in] */ const float X [] /* input vector */);

void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_kernel(/*[in] */ const HSReal* X /* input vector of size 2 */
         , /*[in] */ int incX /* distance between elements of the vector X */
         , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 4 */
         , /*[in] */ int incF /* distance between elements of the vector F */
         , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                   /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                   /* see declaration of struct DACalculationOptions for details */
         , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
         , /*[in] */ const struct DACalculationOptions* options);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_boostedRegression01(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree14(/*[in] */ const float X [] /* input vector */);

float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree17(/*[in] */ const float X [] /* input vector */);


#ifndef DA_CBLAS_DECLARED
#define DA_CBLAS_DECLARED

enum CBLAS_ORDER {CblasRowMajor=101, CblasColMajor=102};
enum CBLAS_TRANSPOSE {CblasNoTrans=111, CblasTrans=112, CblasConjTrans=113};
enum CBLAS_UPLO {CblasUpper=121, CblasLower=122};
enum CBLAS_DIAG {CblasNonUnit=131, CblasUnit=132};

#if DA_CBLAS /* use external cblas */

void cblas_dtrsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO Uplo,
                 const enum CBLAS_TRANSPOSE TransA, const enum CBLAS_DIAG Diag,
                 const int N, const HSReal *A, const int lda, HSReal *X,
                 const int incX);

#else /* use local cblas routines implementation */

#endif /* DA_CBLAS */

#ifndef DA_DOUBLE_QNAN_DECL
#define DA_DOUBLE_QNAN_DECL
#ifdef NAN
static HSReal doubleQNAN() {
  return NAN;
}
#else
# ifdef INFINITY
#  define NAN (HUGE_VAL*HUGE_VAL-INFINITY)
# else
#  define NAN (HUGE_VAL*HUGE_VAL-(HUGE_VAL*HUGE_VAL/HUGE_VAL))
# endif

static HSReal doubleQNAN() {
  static const char* stringNAN = "NAN";
  char* endptr = 0;
  HSReal doubleNAN = strtod(stringNAN, &endptr);
  if (0 == endptr || 0 != *endptr || doubleNAN == doubleNAN) {
    /* Some compilers (e.g. MSVC) does not support NAN as a valid strtod() input, sad but true */
    /* So let's initialize quiet NAN according to the IEEEE 754 standard */
    memset(&doubleNAN, 0xFF, sizeof(doubleNAN));
  }
  return doubleNAN;
}
#endif
#endif

static void aux_fillnan(int sizeF, int sizeX, HSReal* F, int incF, HSReal* dFdX, int nextDF, int nextDX);

#endif /* DA_CBLAS_DECLARED */


void _E523(/*[in] */ const HSReal* X /* input vector of size 2 */
        , /*[in] */ int incX /* distance between elements of the vector X */
        , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
        , /*[in] */ int incF /* distance between elements of the vector F */
        , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                  /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                  /* see declaration of struct DACalculationOptions for details */
        , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
        , /*[in] */ const struct DACalculationOptions* options) {
  /* mixture of approximators */

  void (*clusterModels[3])(const HSReal*, int, HSReal*, int, HSReal*, int, const struct DACalculationOptions*) = {
    _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_localApproximator, /* approximation model fro cluster #1 */
    _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_localApproximator1, /* approximation model fro cluster #2 */
    _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_localApproximator2, /* approximation model fro cluster #3 */
  };
  HSReal clusterWeights[3];
  HSReal clusterWeightsGrad[3][2];
  HSReal currentModelValue[1];
  HSReal currentModelGrad[1][2];
  HSReal XLF[3];
  HSReal lowFidelityModelGrad[1][2];
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
  _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_lowFidelityModel(X, incX, XLF + 2, 1, ((0 == gradF)? 0 : lowFidelityModelGrad[0]), sizeof(lowFidelityModelGrad[0]) / sizeof(lowFidelityModelGrad[0][0]), &localApproximationOptions);

  /* evaluate cluster weights */
  _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_calculateWeights(XLF, 1, clusterWeights, (gradF ? clusterWeightsGrad : 0), (gradF ? lowFidelityModelGrad : 0));

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


void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_localApproximator2(/*[in] */ const HSReal* X /* input vector of size 2 */
                    , /*[in] */ int incX /* distance between elements of the vector X */
                    , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
                    , /*[in] */ int incF /* distance between elements of the vector F */
                    , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
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
    F[incF*0] = _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_boostedRegression02(Z);
    F[0*incF] = 0.5 + F[0*incF];
  }

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_boostedRegression02(/*[in] */ const float X [] /* input vector */) {
  /* boosted regression forest */

  float F = 0.f;
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree02(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree110(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree22(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree32(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree42(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree52(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree62(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree72(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree82(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree91(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree101(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree112(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree121(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree131(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree141(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree151(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree161(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree171(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree181(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree191(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree201(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree212(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree221(X);
  return F;
}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree221(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return -0.000922537467f;

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree212(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.25f            }, /* #0 if x[1] < 0.25f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -7.09873784e-05f  }, /* #1   return -7.09873784e-05f */
    { 0x00000000, -0.000767118181f  }, /* #2   return -0.000767118181f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree181(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.150000006f     }, /* #0 if x[1] < 0.150000006f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.000164398851f  }, /* #1   return -0.000164398851f */
    { 0x00000000, -0.00111050298f   }, /* #2   return -0.00111050298f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree161(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.150000006f     }, /* #0 if x[1] < 0.150000006f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.000421451055f  }, /* #1   return -0.000421451055f */
    { 0x00000000, -0.00173542369f   }, /* #2   return -0.00173542369f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree151(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  0.544999957f     }, /* #0 if x[0] < 0.544999957f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.0500000007f    }, /* #1   if x[1] < 0.0500000007f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000260818022f  }, /* #2     return 0.000260818022f */
    { 0x00000000, -0.00102774962f   }, /* #3     return -0.00102774962f */
    { 0x00000000, -0.00211624755f   }, /* #4   return -0.00211624755f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree141(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000C,  0.150000006f     }, /* #0 if x[1] < 0.150000006f or isnan(x[1]) then #1 else #4 */
    { 0x00000002,  0.544999957f     }, /* #1   if x[0] < 0.544999957f or isnan(x[0]) then #2 else #3 */
    { 0x00000000, -5.48548996e-05f  }, /* #2     return -5.48548996e-05f */
    { 0x00000000, -0.00144809566f   }, /* #3     return -0.00144809566f */
    { 0x00000000, -0.00277987216f   }, /* #4   return -0.00277987216f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree131(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  0.544999957f     }, /* #0 if x[0] < 0.544999957f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.0500000007f    }, /* #1   if x[1] < 0.0500000007f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000297170889f  }, /* #2     return 0.000297170889f */
    { 0x00000000, -0.00186947605f   }, /* #3     return -0.00186947605f */
    { 0x00000000, -0.0034521129f    }, /* #4   return -0.0034521129f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree121(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000C,  0.150000006f     }, /* #0 if x[1] < 0.150000006f or isnan(x[1]) then #1 else #4 */
    { 0x00000002,  0.544999957f     }, /* #1   if x[0] < 0.544999957f or isnan(x[0]) then #2 else #3 */
    { 0x00000000, -0.000265104318f  }, /* #2     return -0.000265104318f */
    { 0x00000000, -0.00267315004f   }, /* #3     return -0.00267315004f */
    { 0x00000000, -0.00449797744f   }, /* #4   return -0.00449797744f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree91(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  0.544999957f     }, /* #0 if x[0] < 0.544999957f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.0500000007f    }, /* #1   if x[1] < 0.0500000007f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000419135409f  }, /* #2     return 0.000419135409f */
    { 0x00000000, -0.0052961302f    }, /* #3     return -0.0052961302f */
    { 0x00000000, -0.00982433744f   }, /* #4   return -0.00982433744f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree82(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000C,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #4 */
    { 0x00000002,  0.544999957f     }, /* #1   if x[0] < 0.544999957f or isnan(x[0]) then #2 else #3 */
    { 0x00000000,  0.000493101776f  }, /* #2     return 0.000493101776f */
    { 0x00000000, -0.00655127363f   }, /* #3     return -0.00655127363f */
    { 0x00000000, -0.0113786571f    }, /* #4   return -0.0113786571f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree51(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000C,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #4 */
    { 0x00000002,  0.290000021f     }, /* #1   if x[0] < 0.290000021f or isnan(x[0]) then #2 else #3 */
    { 0x00000000, -0.0023033293f    }, /* #2     return -0.0023033293f */
    { 0x00000000, -0.00890332926f   }, /* #3     return -0.00890332926f */
    { 0x00000000, -0.0250522438f    }, /* #4   return -0.0250522438f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree31(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.0116736032f    }, /* #1   return -0.0116736032f */
    { 0x00000000, -0.0460598506f    }, /* #2   return -0.0460598506f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree62(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return -0.0184055306f;

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree41(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.00933887716f   }, /* #1   return -0.00933887716f */
    { 0x00000000, -0.0339691415f    }, /* #2   return -0.0339691415f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree11(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.0182400029f    }, /* #1   return -0.0182400029f */
    { 0x00000000, -0.0846834406f    }, /* #2   return -0.0846834406f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree42(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.0124009075f    }, /* #1   return -0.0124009075f */
    { 0x00000000, -0.0363337062f    }, /* #2   return -0.0363337062f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree171(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  0.544999957f     }, /* #0 if x[0] < 0.544999957f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.25f            }, /* #1   if x[1] < 0.25f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  5.03512128e-05f  }, /* #2     return 5.03512128e-05f */
    { 0x00000000, -0.000824949762f  }, /* #3     return -0.000824949762f */
    { 0x00000000, -0.00134952553f   }, /* #4   return -0.00134952553f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree8(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return -0.00101481727f;

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree13(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  0.290000021f     }, /* #0 if x[0] < 0.290000021f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.0500000007f    }, /* #1   if x[1] < 0.0500000007f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000284886366f  }, /* #2     return 0.000284886366f */
    { 0x00000000, -0.0016380304f    }, /* #3     return -0.0016380304f */
    { 0x00000000, -0.00288645318f   }, /* #4   return -0.00288645318f */
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


void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_normalizeInput(/*[in] */ const HSReal* X /* input (unscaled) vector of size 3 */
                 , /*[in] */ int incX /* distance between elements of the vector X */
                 , /*[out]*/ HSReal* Y /* output (normalized) vector of size 3 */
                 , /*[in] */ int incY /* distance between elements of the vector Y */) {
  /* apply standard normalization */

  /* apply standard normalization */
  Y[0 * incY] = (-0.41749999999999998 + X[0 * incX]) * 6.8090654964819546;
  Y[1 * incY] = (-0.69999999999999996 + X[1 * incX]) * 1.4664711502135328;
  Y[2 * incY] = (-0.084652973014651495 + X[2 * incX]) * 20.794675695644088;

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree6(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return -0.000530846009f;

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_boostedRegression0(/*[in] */ const float X [] /* input vector */) {
  /* boosted regression forest */

  float F = 0.f;
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree0(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree1(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree2(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree3(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree4(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree5(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree6(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree7(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree8(X);
  return F;
}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree2(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  0.544999957f     }, /* #0 if x[0] < 0.544999957f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.75f            }, /* #1   if x[1] < 0.75f or isnan(x[1]) then #2 else #3 */
    { 0x00000000, -0.000309133931f  }, /* #2     return -0.000309133931f */
    { 0x00000000, -0.00148628838f   }, /* #3     return -0.00148628838f */
    { 0x00000000, -0.00247096107f   }, /* #4   return -0.00247096107f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree71(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.0053978716f    }, /* #1   return -0.0053978716f */
    { 0x00000000, -0.0136260679f    }, /* #2   return -0.0136260679f */
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


void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_calculateMahalanobisDistance(/*[in] */ const HSReal X [3] /* input point */
                               , /*[in] */ const HSReal mu [3] /* mean value */
                               , /*[in] */ const HSReal sigmaL [3][3] /* lower Cholessky factor of the covariance matrix */
                               , /*[out]*/ HSReal* distance /* distance */
                               , /*[out]*/ HSReal distanceGrad [3] /* partial derivatives of distance with respect to inputs */) {
  /* mixture of approximators: calculate Mahalanobis distance to cluster center */

  HSReal centeredX[3];
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


void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_calculateWeights(/*[in] */ const HSReal* X /* input point */
                   , /*[in] */ int incX /* distance between elements of the vector X */
                   , /*[out]*/ HSReal weights [3] /* weights of the clusters */
                   , /*[out]*/ HSReal weightsGrad [3][2] /* partial derivatives of weights of the clusters with respect to inputs */
                   , /*[in] */ const HSReal dLFdX [1][2] /* partial derivatives of weights of the low fidelity model with respect to inputs */) {
  /* mixture of approximators: clusters weights calculation */
  extern const HSReal _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCenter_000[3];
  extern const HSReal _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCovarianceFactor_000[3][3];
  extern const HSReal _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCenter_001[3];
  extern const HSReal _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCovarianceFactor_001[3][3];
  extern const HSReal _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCenter_002[3];
  extern const HSReal _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCovarianceFactor_002[3][3];
  extern const HSReal _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_extrapolationWeights[3];

  HSReal normalizedX[3];
  HSReal totalWeight = 0.;
  HSReal weightThreshold = 1.;
  HSReal currentDistance;
  HSReal totalWeightGrad[3] = {0., 0., 0.};
  HSReal dWdXnorm[3][3];
  
  _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_normalizeInput(X, incX, normalizedX, 1);
  
  _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_calculateMahalanobisDistance(normalizedX, _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCenter_000, _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCovarianceFactor_000, &currentDistance, (weightsGrad? dWdXnorm[0] : 0));
  
  weights[0] = 0.071981361681815625 * exp(-currentDistance);
  weightThreshold = (weightThreshold < weights[0]) ? weights[0] : weightThreshold;
  
  _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_calculateMahalanobisDistance(normalizedX, _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCenter_001, _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCovarianceFactor_001, &currentDistance, (weightsGrad? dWdXnorm[1] : 0));
  
  weights[1] = 0.42182041832293549 * exp(-currentDistance);
  weightThreshold = (weightThreshold < weights[1]) ? weights[1] : weightThreshold;
  
  _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_calculateMahalanobisDistance(normalizedX, _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCenter_002, _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_clusterCovarianceFactor_002, &currentDistance, (weightsGrad? dWdXnorm[2] : 0));
  
  weights[2] = 0.27816691368316171 * exp(-currentDistance);
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
    const HSReal gradientFactor = -2. * weights[0];
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
    const HSReal gradientFactor = -2. * weights[1];
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
    const HSReal gradientFactor = -2. * weights[2];
    totalWeightGrad[0] += dWdXnorm[2][0] *= gradientFactor;
    totalWeightGrad[1] += dWdXnorm[2][1] *= gradientFactor;
    totalWeightGrad[2] += dWdXnorm[2][2] *= gradientFactor;
  }

  totalWeight += (weights[2] - totalWeight) / (2 + 1);

  totalWeight *= 3;

  if (totalWeight <= 2.2204460492503131e-16) {
    /* we are too far from the known domain */
    memcpy(weights, _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_extrapolationWeights, sizeof(_FS4MX9T39F4951RK9X57WNQ88RF8P9GT_extrapolationWeights));
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
    weightsGrad[0][0] = (dWdXnorm[0][0] - weights[0] * totalWeightGrad[0]) / (totalWeight * 0.14686303142724516);
    weightsGrad[0][1] = (dWdXnorm[0][1] - weights[0] * totalWeightGrad[1]) / (totalWeight * 0.6819090848492928);
    weightsGrad[1][0] = (dWdXnorm[1][0] - weights[1] * totalWeightGrad[0]) / (totalWeight * 0.14686303142724516);
    weightsGrad[1][1] = (dWdXnorm[1][1] - weights[1] * totalWeightGrad[1]) / (totalWeight * 0.6819090848492928);
    weightsGrad[2][0] = (dWdXnorm[2][0] - weights[2] * totalWeightGrad[0]) / (totalWeight * 0.14686303142724516);
    weightsGrad[2][1] = (dWdXnorm[2][1] - weights[2] * totalWeightGrad[1]) / (totalWeight * 0.6819090848492928);
    if (dLFdX) {
      HSReal dWdLF;

      dWdLF = (dWdXnorm[0][2] - weights[0] * totalWeightGrad[2]) / (totalWeight * 0.04808923277459299);
      ((weightsGrad[0][1*0]+=dWdLF*dLFdX[0][1*0]), (weightsGrad[0][1*1]+=dWdLF*dLFdX[0][1*1]));

      dWdLF = (dWdXnorm[1][2] - weights[1] * totalWeightGrad[2]) / (totalWeight * 0.04808923277459299);
      ((weightsGrad[1][1*0]+=dWdLF*dLFdX[0][1*0]), (weightsGrad[1][1*1]+=dWdLF*dLFdX[0][1*1]));

      dWdLF = (dWdXnorm[2][2] - weights[2] * totalWeightGrad[2]) / (totalWeight * 0.04808923277459299);
      ((weightsGrad[2][1*0]+=dWdLF*dLFdX[0][1*0]), (weightsGrad[2][1*1]+=dWdLF*dLFdX[0][1*1]));
    }
  }

}


void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_lowFidelityModel(/*[in] */ const HSReal* X /* input vector of size 2 */
                   , /*[in] */ int incX /* distance between elements of the vector X */
                   , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
                   , /*[in] */ int incF /* distance between elements of the vector F */
                   , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                             /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                             /* see declaration of struct DACalculationOptions for details */
                   , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
                   , /*[in] */ const struct DACalculationOptions* options) {
  /* basic HDA approximation */
  static const HSReal V[1][4] = { 
    { -0.032027254842660322, -0.22556839082726016, -0.053080253726434649, 0.090399994617143459,  }
  };
  static const HSReal b[1] = { 0.17998732532983769,  };

  HSReal psi[4];
  HSReal gradPsi[4 * 2];
  const int gradientFMajor = (0 == options || options->_gradientMatrixFMajor);
  
  _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_kernel(X, incX, ((0 != F)? psi : 0), 1, ((0 != gradF)? gradPsi : 0), (gradientFMajor? 2 : 4), options);
  
  if(0 != F) {
    F[0 * incF] = b[0] + (V[0][0]*psi[0] + V[0][1]*psi[1] + V[0][2]*psi[2] + V[0][3]*psi[3]);
  }
  
  if(0 != gradF) {
    if(gradientFMajor) {
      gradF[0*ldGradF+0] = 0.;
      gradF[0*ldGradF+1] = 0.;
      ((gradF[0*ldGradF+1*0]+=V[0][0]*gradPsi[0*2+1*0]), (gradF[0*ldGradF+1*1]+=V[0][0]*gradPsi[0*2+1*1]));
      ((gradF[0*ldGradF+1*0]+=V[0][1]*gradPsi[1*2+1*0]), (gradF[0*ldGradF+1*1]+=V[0][1]*gradPsi[1*2+1*1]));
      ((gradF[0*ldGradF+1*0]+=V[0][2]*gradPsi[2*2+1*0]), (gradF[0*ldGradF+1*1]+=V[0][2]*gradPsi[2*2+1*1]));
      ((gradF[0*ldGradF+1*0]+=V[0][3]*gradPsi[3*2+1*0]), (gradF[0*ldGradF+1*1]+=V[0][3]*gradPsi[3*2+1*1]));
    } else {
      gradF[0+0*ldGradF] = 0.;
      gradF[0+0*ldGradF] += V[0][0]*gradPsi[4*0+0];
      gradF[0+0*ldGradF] += V[0][1]*gradPsi[4*0+1];
      gradF[0+0*ldGradF] += V[0][2]*gradPsi[4*0+2];
      gradF[0+0*ldGradF] += V[0][3]*gradPsi[4*0+3];
      gradF[0+1*ldGradF] = 0.;
      gradF[0+1*ldGradF] += V[0][0]*gradPsi[4*1+0];
      gradF[0+1*ldGradF] += V[0][1]*gradPsi[4*1+1];
      gradF[0+1*ldGradF] += V[0][2]*gradPsi[4*1+2];
      gradF[0+1*ldGradF] += V[0][3]*gradPsi[4*1+3];
    }
  }
  

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree81(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return -0.00933486875f;

}


void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_localApproximator1(/*[in] */ const HSReal* X /* input vector of size 2 */
                    , /*[in] */ int incX /* distance between elements of the vector X */
                    , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
                    , /*[in] */ int incF /* distance between elements of the vector F */
                    , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
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
    F[incF*0] = _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_boostedRegression01(Z);
    F[0*incF] = 0.5 + F[0*incF];
  }

}


void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_localApproximator(/*[in] */ const HSReal* X /* input vector of size 2 */
                    , /*[in] */ int incX /* distance between elements of the vector X */
                    , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 1 */
                    , /*[in] */ int incF /* distance between elements of the vector F */
                    , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
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
    F[incF*0] = _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_boostedRegression0(Z);
    F[0*incF] = 0.5 + F[0*incF];
  }

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree112(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.544999957f     }, /* #0  if x[0] < 0.544999957f or isnan(x[0]) then #1 else #6 */
    { 0x0000000C,  0.150000006f     }, /* #1    if x[1] < 0.150000006f or isnan(x[1]) then #2 else #5 */
    { 0x0000000A,  0.0500000007f    }, /* #2      if x[1] < 0.0500000007f or isnan(x[1]) then #3 else #4 */
    { 0x00000000,  0.00030282588f   }, /* #3        return 0.00030282588f */
    { 0x00000000, -0.000770657905f  }, /* #4        return -0.000770657905f */
    { 0x00000000, -0.00372754387f   }, /* #5      return -0.00372754387f */
    { 0x00000000, -0.00567453727f   }, /* #6    return -0.00567453727f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree101(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  0.544999957f     }, /* #0 if x[0] < 0.544999957f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.0500000007f    }, /* #1   if x[1] < 0.0500000007f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000356264412f  }, /* #2     return 0.000356264412f */
    { 0x00000000, -0.00410449831f   }, /* #3     return -0.00410449831f */
    { 0x00000000, -0.0074664969f    }, /* #4   return -0.0074664969f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree7(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000002,  0.544999957f     }, /* #0 if x[0] < 0.544999957f or isnan(x[0]) then #1 else #2 */
    { 0x00000000, -0.000193849482f  }, /* #1   return -0.000193849482f */
    { 0x00000000, -0.000755713321f  }, /* #2   return -0.000755713321f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree01(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.0228000022f    }, /* #1   return -0.0228000022f */
    { 0x00000000, -0.114825003f     }, /* #2   return -0.114825003f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree32(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.0155011304f    }, /* #1   return -0.0155011304f */
    { 0x00000000, -0.0489107631f    }, /* #2   return -0.0489107631f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree5(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  0.544999957f     }, /* #0 if x[0] < 0.544999957f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  1.25f            }, /* #1   if x[1] < 1.25f or isnan(x[1]) then #2 else #3 */
    { 0x00000000, -3.25649999e-05f  }, /* #2     return -3.25649999e-05f */
    { 0x00000000, -0.000756039866f  }, /* #3     return -0.000756039866f */
    { 0x00000000, -0.0011619929f    }, /* #4   return -0.0011619929f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree201(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.150000006f     }, /* #0 if x[1] < 0.150000006f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -8.67336985e-06f  }, /* #1   return -8.67336985e-06f */
    { 0x00000000, -0.00072771241f   }, /* #2   return -0.00072771241f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree4(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000002,  0.290000021f     }, /* #0 if x[0] < 0.290000021f or isnan(x[0]) then #1 else #2 */
    { 0x00000000, -0.000293404912f  }, /* #1   return -0.000293404912f */
    { 0x00000000, -0.00110511889f   }, /* #2   return -0.00110511889f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree3(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000002,  0.544999957f     }, /* #0 if x[0] < 0.544999957f or isnan(x[0]) then #1 else #2 */
    { 0x00000000, -0.000965982268f  }, /* #1   return -0.000965982268f */
    { 0x00000000, -0.00187792815f   }, /* #2   return -0.00187792815f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree0(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return -0.442819834f;

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree12(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  0.290000021f     }, /* #0 if x[0] < 0.290000021f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.0500000007f    }, /* #1   if x[1] < 0.0500000007f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000335159915f  }, /* #2     return 0.000335159915f */
    { 0x00000000, -0.00215530349f   }, /* #3     return -0.00215530349f */
    { 0x00000000, -0.00379796093f   }, /* #4   return -0.00379796093f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree61(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000C,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #4 */
    { 0x00000002,  0.290000021f     }, /* #1   if x[0] < 0.290000021f or isnan(x[0]) then #2 else #3 */
    { 0x00000000, -0.00195782934f   }, /* #2     return -0.00195782934f */
    { 0x00000000, -0.00756783085f   }, /* #3     return -0.00756783085f */
    { 0x00000000, -0.018476028f     }, /* #4   return -0.018476028f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree21(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.0145920012f    }, /* #1   return -0.0145920012f */
    { 0x00000000, -0.0624540411f    }, /* #2   return -0.0624540411f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree22(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return -0.0589210168f;

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree72(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000C,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #4 */
    { 0x00000002,  0.544999957f     }, /* #1   if x[0] < 0.544999957f or isnan(x[0]) then #2 else #3 */
    { 0x00000000,  0.000580117106f  }, /* #2     return 0.000580117106f */
    { 0x00000000, -0.00770738162f   }, /* #3     return -0.00770738162f */
    { 0x00000000, -0.0153174279f    }, /* #4   return -0.0153174279f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree9(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000C,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #4 */
    { 0x00000002,  0.290000021f     }, /* #1   if x[0] < 0.290000021f or isnan(x[0]) then #2 else #3 */
    { 0x00000000,  0.000545758056f  }, /* #2     return 0.000545758056f */
    { 0x00000000, -0.00422274042f   }, /* #3     return -0.00422274042f */
    { 0x00000000, -0.00759882294f   }, /* #4   return -0.00759882294f */
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


void _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_kernel(/*[in] */ const HSReal* X /* input vector of size 2 */
         , /*[in] */ int incX /* distance between elements of the vector X */
         , /*[out]*/ HSReal* F /* optional (may be NULL) output vector of size 4 */
         , /*[in] */ int incF /* distance between elements of the vector F */
         , /*[out]*/ HSReal* gradF /* optional (may be NULL) array to store partial derivatives of  */
                                   /* the output vector F with respect to elements of the input vector X (dF_i/dX_j)  */
                                   /* see declaration of struct DACalculationOptions for details */
         , /*[in] */ int ldGradF /* Leading dimension of the matrix gradF */
         , /*[in] */ const struct DACalculationOptions* options) {
  /* response surface model */

  
  if(0 != F) {
    F[0 * incF] = 1. * X[0*incX];
    F[1 * incF] = 1. * X[1*incX];
    F[2 * incF] = 1. * X[0*incX] * X[0*incX];
    F[3 * incF] = 1. * X[1*incX] * X[1*incX];
  }
  
  if(0 != gradF) {
    if((0 == options || options->_gradientMatrixFMajor)) {
      gradF[0*ldGradF + 0] = 1.; /* dF[0]/dX[0] */
      gradF[0*ldGradF + 1] = 0.; /* dF[0]/dX[1] */
      gradF[1*ldGradF + 0] = 0.; /* dF[1]/dX[0] */
      gradF[1*ldGradF + 1] = 1.; /* dF[1]/dX[1] */
      gradF[2*ldGradF + 0] = 2. * X[0*incX]; /* dF[2]/dX[0] */
      gradF[2*ldGradF + 1] = 0.; /* dF[2]/dX[1] */
      gradF[3*ldGradF + 0] = 0.; /* dF[3]/dX[0] */
      gradF[3*ldGradF + 1] = 2. * X[1*incX]; /* dF[3]/dX[1] */
    } else {
      gradF[0 + 0*ldGradF] = 1.; /* dF[0]/dX[0] */
      gradF[1 + 0*ldGradF] = 0.; /* dF[1]/dX[0] */
      gradF[2 + 0*ldGradF] = 2. * X[0*incX]; /* dF[2]/dX[0] */
      gradF[3 + 0*ldGradF] = 0.; /* dF[3]/dX[0] */
      gradF[0 + 1*ldGradF] = 0.; /* dF[0]/dX[1] */
      gradF[1 + 1*ldGradF] = 1.; /* dF[1]/dX[1] */
      gradF[2 + 1*ldGradF] = 0.; /* dF[2]/dX[1] */
      gradF[3 + 1*ldGradF] = 2. * X[1*incX]; /* dF[3]/dX[1] */
    }
  }

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree111(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  0.290000021f     }, /* #0 if x[0] < 0.290000021f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.0500000007f    }, /* #1   if x[1] < 0.0500000007f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000394311559f  }, /* #2     return 0.000394311559f */
    { 0x00000000, -0.0028359266f    }, /* #3     return -0.0028359266f */
    { 0x00000000, -0.00499731768f   }, /* #4   return -0.00499731768f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree1(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000002,  0.290000021f     }, /* #0 if x[0] < 0.290000021f or isnan(x[0]) then #1 else #2 */
    { 0x00000000, -0.00109053729f   }, /* #1   return -0.00109053729f */
    { 0x00000000, -0.0026345076f    }, /* #2   return -0.0026345076f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree19(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return -0.000422808807f;

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree15(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  0.290000021f     }, /* #0 if x[0] < 0.290000021f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.0500000007f    }, /* #1   if x[1] < 0.0500000007f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000243245071f  }, /* #2     return 0.000243245071f */
    { 0x00000000, -0.000863492547f  }, /* #3     return -0.000863492547f */
    { 0x00000000, -0.00178021193f   }, /* #4   return -0.00178021193f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree191(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000002,  0.544999957f     }, /* #0 if x[0] < 0.544999957f or isnan(x[0]) then #1 else #2 */
    { 0x00000000, -9.62776685e-05f  }, /* #1   return -9.62776685e-05f */
    { 0x00000000, -0.000872650242f  }, /* #2   return -0.000872650242f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree18(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000002,  0.290000021f     }, /* #0 if x[0] < 0.290000021f or isnan(x[0]) then #1 else #2 */
    { 0x00000000, -0.000199922928f  }, /* #1   return -0.000199922928f */
    { 0x00000000, -0.000875899743f  }, /* #2   return -0.000875899743f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree16(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.150000006f     }, /* #0 if x[1] < 0.150000006f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.000390688801f  }, /* #1   return -0.000390688801f */
    { 0x00000000, -0.00127985282f   }, /* #2   return -0.00127985282f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree20(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.25f            }, /* #0 if x[1] < 0.25f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -4.47165767e-05f  }, /* #1   return -4.47165767e-05f */
    { 0x00000000, -0.000693371985f  }, /* #2   return -0.000693371985f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree10(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000C,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #4 */
    { 0x00000002,  0.290000021f     }, /* #1   if x[0] < 0.290000021f or isnan(x[0]) then #2 else #3 */
    { 0x00000000,  0.000463892531f  }, /* #2     return 0.000463892531f */
    { 0x00000000, -0.00358933234f   }, /* #3     return -0.00358933234f */
    { 0x00000000, -0.00560413348f   }, /* #4   return -0.00560413348f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree211(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return -0.000882973312f;

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_boostedRegression01(/*[in] */ const float X [] /* input vector */) {
  /* boosted regression forest */

  float F = 0.f;
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree01(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree11(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree21(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree31(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree41(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree51(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree61(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree71(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree81(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree9(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree10(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree111(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree12(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree13(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree14(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree15(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree16(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree17(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree18(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree19(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree20(X);
  F += _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree211(X);
  return F;
}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree02(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* This is degenerated regression tree. It consists of a single leaf only. */
  return -0.106966667f;

}


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree14(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000C,  0.150000006f     }, /* #0 if x[1] < 0.150000006f or isnan(x[1]) then #1 else #4 */
    { 0x00000002,  0.290000021f     }, /* #1   if x[0] < 0.290000021f or isnan(x[0]) then #2 else #3 */
    { 0x00000000, -7.27400175e-06f  }, /* #2     return -7.27400175e-06f */
    { 0x00000000, -0.001329244f     }, /* #3     return -0.001329244f */
    { 0x00000000, -0.00211653067f   }, /* #4   return -0.00211653067f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree17(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000004,  0.290000021f     }, /* #0 if x[0] < 0.290000021f or isnan(x[0]) then #1 else #4 */
    { 0x0000000A,  0.25f            }, /* #1   if x[1] < 0.25f or isnan(x[1]) then #2 else #3 */
    { 0x00000000,  0.000143714438f  }, /* #2     return 0.000143714438f */
    { 0x00000000, -0.000685443752f  }, /* #3     return -0.000685443752f */
    { 0x00000000, -0.00115249632f   }, /* #4   return -0.00115249632f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree110(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000003u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000004u) >> 2) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x00000006,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #2 */
    { 0x00000000, -0.0341066681f    }, /* #1   return -0.0341066681f */
    { 0x00000000, -0.0862371475f    }, /* #2   return -0.0862371475f */
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


float _FS4MX9T39F4951RK9X57WNQ88RF8P9GT_regressionTree52(/*[in] */ const float X [] /* input vector */) {
  /* regression tree */

  /* (NODE::_info & 0x00000007u) is distance (in nodes) to the right child node. */
  /* Left child node is always follows the current one. Zero indicates leaf node. */
  /* ((NODE::_info & 0x00000008u) >> 3) is 0-based index of the variable to test. */
  static const struct NODE {
    uint32_t _info;  /* packed node info */
    float    _value; /* leaf: value; branch: split value. */
  } tree[] = {
    { 0x0000000C,  0.0500000007f    }, /* #0 if x[1] < 0.0500000007f or isnan(x[1]) then #1 else #4 */
    { 0x00000002,  0.544999957f     }, /* #1   if x[0] < 0.544999957f or isnan(x[0]) then #2 else #3 */
    { 0x00000000, -0.002565542f     }, /* #2     return -0.002565542f */
    { 0x00000000, -0.0123155424f    }, /* #3     return -0.0123155424f */
    { 0x00000000, -0.0269907545f    }, /* #4   return -0.0269907545f */
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

static void aux_fillnan(int sizeF, int sizeX, HSReal* F, int incF, HSReal* dFdX, int nextDF, int nextDX) {
#ifdef NAN
  const HSReal NaN = NAN;
#else
  const HSReal NaN = doubleQNAN();
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
