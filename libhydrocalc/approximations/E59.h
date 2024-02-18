#ifndef DA_E59_H
#define DA_E59_H

/* Approximation for CSI, diagram 5-9 */
/* 
Inputs number               : 2
Outputs number              : 1
Input Variables             :
  Input # 0
    name                    : np
    variability             : continuous
  Input # 1
    name                    : LD
    variability             : continuous
Output Variables            :
  Output # 0
    name                    : csi
    variability             : continuous
Accuracy evaluation         : AVAILABLE
Outputs rearrangement       : NOT AVAILABLE
Probability estimation      : NOT AVAILABLE
Additionally smoothed model : NO
Technique used              : TGP
Training points number      : 110
Training options            :
  GTApprox/Accelerator=3
  GTApprox/GPLearningMode=Robust
  GTApprox/GPPower=1.3999999999999999
  GTApprox/InputNanMode=ignore
  GTApprox/InternalValidation=true
  GTApprox/IVSavePredictions=true
  GTApprox/MaxParallel=8
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
  Count: [110, 110]
  Min: [1.5, 0.5]
  Max: [20, 14]
  Range: [18.5, 13.5]
  Mean: [7, 5.954545454545455]
  Std: [5.7926717386331861, 4.3391462476465783]
  Var: [33.555045871559621, 18.828190158465382]
  Q1: [2.5, 2]
  Median: [5, 5]
  Q3: [10, 10]
  IQR: [7.5, 8]
  Q_0.01: [1.5, 0.5]
  Q_0.05: [1.5, 0.5]
  Q_0.95: [20, 14]
  Q_0.99: [20, 14]
Statistics of the output part of the training sample:
  NaN Count: [0]
  Inf Count: [0]
  Count: [110]
  Min: [0.02]
  Max: [0.40999999999999998]
  Range: [0.38999999999999996]
  Mean: [0.12045454545454545]
  Std: [0.07778335431509166]
  Var: [0.0060502502085070884]
  Q1: [0.080000000000000002]
  Median: [0.10000000000000001]
  Q3: [0.14000000000000001]
  IQR: [0.060000000000000012]
  Q_0.01: [0.029999999999999999]
  Q_0.05: [0.040000000000000001]
  Q_0.95: [0.29999999999999999]
  Q_0.99: [0.39000000000000001]
Statistics of the input part of the separate test sample:
  NaN Count: [0, 0]
  Inf Count: [0, 0]
  Count: [20, 20]
  Min: [1.5, 0.5]
  Max: [20, 14]
  Range: [18.5, 13.5]
  Mean: [10.5, 8.6750000000000007]
  Std: [5.5131421931694504, 4.5081067329633475]
  Var: [30.394736842105257, 20.323026315789466]
  Q1: [5, 5]
  Median: [14, 12]
  Q3: [14, 12]
  IQR: [9, 7]
  Q_0.01: [1.5, 0.5]
  Q_0.05: [2, 1]
  Q_0.95: [20, 14]
  Q_0.99: [20, 14]
Statistics of the output part of the separate test sample:
  NaN Count: [0]
  Inf Count: [0]
  Count: [20]
  Min: [0.080000000000000002]
  Max: [0.39000000000000001]
  Range: [0.31]
  Mean: [0.13799999999999998]
  Std: [0.080889788568995785]
  Var: [0.006543157894736841]
  Q1: [0.089999999999999997]
  Median: [0.11]
  Q3: [0.16]
  IQR: [0.070000000000000007]
  Q_0.01: [0.080000000000000002]
  Q_0.05: [0.080000000000000002]
  Q_0.95: [0.39000000000000001]
  Q_0.99: [0.39000000000000001]
Training Time               :
  Start                     : 2022-08-08 13:01:41.405129
  Finish                    : 2022-08-08 13:02:16.783116
  Total                     : 0:00:35.377987
 */
#include <libhydrocalc/settings.h>

#define E59_sizeX 2 /* input dimensionality */
#define E59_sizeF 1 /* model output dimensionality */
#define E59_outputVectorSize (1 * (2 + 1)) /* size of the full (model value and partial derivatives) output vector  */
#define E59_Fi(i) (i) /* 0-based index of i-the output in the full output vector */
#define E59_dFi_dXj(i, j) (1 + (i)*2+(j)) /* 0-based index of the partial derivative of i-th model output with respect to j-th model input in the full output vector */


#ifdef __cplusplus
extern "C" {
#endif

int E59( const int N /* number of input vectors (N >= 0) */
        , const hydrocalc::real* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in doubles) between input vectors (ldInput >= {input vector size}) */
        , hydrocalc::real* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in doubles) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
        );

int E59AE( const int N /* number of input vectors (N >= 0) */
        , const hydrocalc::real* input /* pointer to the input vectors (N == 0 || input != NULL) */
        , const int ldInput /* distance (in doubles) between input vectors (ldInput >= {input vector size}) */
        , hydrocalc::real* output /* pointer to the output vectors (N == 0 || output != NULL) */
        , const int ldOutput /* distance (in doubles) between output vectors (ldOutput >= {output vector size} * ({input vector size} + 1))) */
        );

/* Calculates value and/or gradient of the function E59 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int E59Calc( 
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

/* Calculates value and/or gradient of the function AE E59 at the single point. */
/* Returns 0 on success or 1-based index of the invalid input parameter */
int E59CalcAE( 
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

const hydrocalc::real _5ED102M07W7GS9NWJQHJKCUFP0ML3A50_tensoredGPCalculator1_eigenvaluesFactor2_[9] = { 7.2347480549628234, 1.1234412963882627, 0.44394232157536828, 0.1123781844652387, 0.039760209654051588, 0.025087996276393559, 0.011418341601368941, 0.0060338287005216934, 0.0031897663759680914, };

const hydrocalc::real _5ED102M07W7GS9NWJQHJKCUFP0ML3A50_tensoredGPCalculator1_eigenvaluesFactor1_[10] = { 6.5740275366889431, 1.9231836615320586, 0.77615344493517202, 0.35715524095609719, 0.15851937559657783, 0.087985672320840411, 0.054524804318761597, 0.031437715295838567,
      0.021705111512314156, 0.015307436843394273, };

const hydrocalc::real _5ED102M07W7GS9NWJQHJKCUFP0ML3A50_alpha[1][90] = {
    { -79.212146271425695, -4.1445506633830096, 71.888779132225991, -10.579660780983566, 8.0746647686932551, -15.570632717537483, 6.4924309155783533, 16.01971534933918,
      -7.105736309958214, 17.344619802295774, -21.333193229740068, 74.44370369532696, -36.322912418884734, 9.3527724933787972, -42.466499079909212, 33.206715137176367,
      -16.522919855253743, -20.813039601518511, 22.192938807022017, -19.519855742927724, 39.973961644129261, -10.029677350620943, -77.536643191438074, 31.19127629979123,
      11.970157392832359, 18.257857680815651, 21.083803602973248, -28.534617884460452, -9.710037823593872, 9.7826269802097023, 26.005922030701971, -34.896213466568305,
      50.954146698257823, -36.561658887612161, 25.022510335179824, -29.388835513193097, -24.326621325413974, 40.755888883665605, -10.208628083742136, -7.5136599172038459,
      -10.685264638605325, 5.0354959124519727, -6.9294979308162254, 14.776311269400018, -16.047276191064999, 5.4381691564803116, 4.0013607871331178, 1.1010589329834595,
      -1.8526631213796012, 1.8133124108927534, 58.974040919465722, -47.510640088392236, 5.9144219536284304, -15.650561457155296, 24.132190225847829, -24.010736647827475,
      15.55539957848961, -11.877711650221821, 10.424091509177895, -3.9042331018651915, -2.7685341315897247, 8.1186564846680049, -17.065361003392169, 15.228069140055045,
      -11.328185082156319, 11.702852849615592, -6.1188024657601821, 3.5343104896813147, -5.9829087951345974, 3.7525910836520362, -7.0435622845306369, 4.6933728389094131,
      9.8095801214397333, -9.146912239094652, -0.17104700175668341, 2.2414037717940349, -1.1782386460184677, 0.19996083213036675, 2.2238797444747669, -1.5788701388349371,
      18.705724414980967, -15.078904983195166, -2.0336240908834609, 1.309738129474284, 0.27292319047586122, -1.8813713841200328, 1.3747603331666005, -0.53681974628795037,
      0.12777831691274458, 0.0077194248294869539,  }
};

const hydrocalc::real _5ED102M07W7GS9NWJQHJKCUFP0ML3A50_tensoredGPCalculator1_cartesianFactor1_[10][1] = {
    { -1.1872457305531967,  }, { -1.0648492634858568,  }, { -0.82005632935117712,  }, { -0.57526339521649739,  },
    { -0.3304704610818176,  }, { -0.08567752694713783,  }, { 0.15911540718754194,  }, { 0.64870127545690148,  },
    { 1.1382871437262609,  }, { 2.1174588802649801,  }
};

const hydrocalc::real _5ED102M07W7GS9NWJQHJKCUFP0ML3A50_tensoredGPCalculator1_cartesianFactor2_[9][1] = {
    { -0.84484227152674118,  }, { -0.75538838395332164,  }, { -0.66593449637990199,  }, { -0.57648060880648233,  },
    { -0.39757283365964302,  }, { -0.21866505851280374,  }, { 0.31805826692771411,  }, { 0.67587381722139261,  },
    { 2.4649515686897856,  }
};

const hydrocalc::real _5ED102M07W7GS9NWJQHJKCUFP0ML3A50_tensoredGPCalculator1_eigenvectorsFactor1_[10][10] = {
    { 0.30987704118899928, 0.32575981114903435, 0.34971521550924617, 0.36375982575990096, 0.36736191904598658, 0.36060119170361721, 0.34429220473347444, 0.29491625951144324,
      0.23649363691875513, 0.1296335616181569,  },
    { -0.33238189254340444, -0.32148215770901384, -0.26580543192037426, -0.17526838500965899, -0.060255882353454346, 0.065850408907519392, 0.18882044491020744, 0.39356421107660428,
      0.50477784907104817, 0.48113022362042229,  },
    { 0.34449344665407255, 0.30189749006823047, 0.15296461010038018, -0.033447567895832982, -0.20758641178556428, -0.32309478880930564, -0.3500364215389084, -0.17980152880522474,
      0.14202440158922719, 0.66570104494181026,  },
    { 0.29629332680927561, 0.22288264779535036, -0.0069821357550235571, -0.22670583712459913, -0.32960924695928118, -0.26538454875720008, -0.063411633310843485, 0.40911620010028649,
      0.44396346362105477, -0.51333948916850369,  },
    { 0.3360045364086916, 0.17663680546819024, -0.2566032934845599, -0.45464281329031936, -0.2428082688834465, 0.19066443849231476, 0.46459516014054281, 0.14014459277395858,
      -0.46878023214630327, 0.18111375778335978,  },
    { 0.21979222145186972, 0.0569846494933808, -0.31082047538405144, -0.25074890620214718, 0.1532627439521333, 0.34613968777621162, 0.057041874503688007, -0.63336597178830534,
      0.47909427149548856, -0.10825915410830243,  },
    { 0.27579393749776082, -0.012581135528901933, -0.50828715431859384, -0.017855855103740416, 0.51147705459083226, 0.056192172799863854, -0.50920938761692769, 0.34510886006103653,
      -0.14643927916874142, 0.02235241354587127,  },
    { 0.24358179645443326, -0.13119456058898959, -0.44159846262235192, 0.50851199287871696, 0.020743310671399517, -0.52054569986496702, 0.42572111449790212, -0.12672571520742656,
      0.033987102849143261, -0.0033374610435014389,  },
    { 0.17568798287266016, -0.17195585012991252, -0.18209292215297365, 0.47623104054194204, -0.5985950041480812, 0.50915795714125023, -0.24386670850449302, 0.049720499685215205,
      -0.010471457478754768, 0.00072571866480072367,  },
    { 0.50947492833856478, -0.75387271810300449, 0.36690916363735421, -0.17079555590816795, 0.082944014938438254, -0.035755840114840787, 0.012534278778291963, -0.0015281723407246494,
      0.00036195408695135838, -4.2813283599504806e-05,  }
};

const hydrocalc::real _5ED102M07W7GS9NWJQHJKCUFP0ML3A50_tensoredGPCalculator1_eigenvectorsFactor2_[9][9] = {
    { 0.34869280865398361, 0.35495313813711937, 0.35956322430286269, 0.36246273365999093, 0.36402921400086735, 0.36086707764712739, 0.3339998737338476, 0.30622013388790675, 0.15390791704146517,  },
    { 0.23665356956747069, 0.21980699424976866, 0.19633841315959244, 0.16664725911953648, 0.093821049411709462, 0.010008161683998554, -0.25887407075813662, -0.40794582935127016, -0.76617344970103451,  },
    { 0.25385061216656696, 0.22035323478209645, 0.17296798543157535, 0.11407878263402492, -0.021707297592240282, -0.15796769780193687, -0.46289661290970541, -0.4750534462621297, 0.61538473707575869,  },
    { 0.40794229778950014, 0.28218685439349445, 0.10206158358490999, -0.098639756345338558, -0.44577904786239603, -0.57364676049504082, 0.01139685324155711, 0.44453735438916375, -0.090963616107288481,  },
    { 0.24936696298801836, 0.097749091073544181, -0.094548114642877379, -0.23674106177725085, -0.25269621833080336, 0.032635376299367344, 0.70916791102018117, -0.5414595962484402, 0.047513047843137014,  },
    { 0.46427736510271594, 0.074607596125292053, -0.34805434116201023, -0.50854386635674598, -0.03126989077877014, 0.52873435066097152, -0.30942030392020131, 0.15094016004984045, -0.0077375972213507551,  },
    { 0.30583233408673927, -0.14471188296305224, -0.37725324694544315, -0.082693253289055704, 0.7090592899111009, -0.47409649787346791, 0.091009363408727131, -0.02347650681371077, 0.00067184862838476096,  },
    { 0.40763507235619567, -0.54001720319393565, -0.2744225594156906, 0.60914704193273239, -0.29279878143244614, 0.10013847078159717, -0.008984403072715301, 0.0027602234718175412, 0.00017365803275460777,  },
    { 0.23262467370526363, -0.60813394833100098, 0.66642486492282338, -0.35432217032120639, 0.078490686796387626, -0.015169232458692969, 0.0012896132623039095, 4.661061249175253e-05, 4.7961060264325475e-05,  }
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DA_E59_H */
