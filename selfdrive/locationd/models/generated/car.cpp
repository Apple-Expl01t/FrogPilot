#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_7430062589862895583) {
   out_7430062589862895583[0] = delta_x[0] + nom_x[0];
   out_7430062589862895583[1] = delta_x[1] + nom_x[1];
   out_7430062589862895583[2] = delta_x[2] + nom_x[2];
   out_7430062589862895583[3] = delta_x[3] + nom_x[3];
   out_7430062589862895583[4] = delta_x[4] + nom_x[4];
   out_7430062589862895583[5] = delta_x[5] + nom_x[5];
   out_7430062589862895583[6] = delta_x[6] + nom_x[6];
   out_7430062589862895583[7] = delta_x[7] + nom_x[7];
   out_7430062589862895583[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3062673581371571051) {
   out_3062673581371571051[0] = -nom_x[0] + true_x[0];
   out_3062673581371571051[1] = -nom_x[1] + true_x[1];
   out_3062673581371571051[2] = -nom_x[2] + true_x[2];
   out_3062673581371571051[3] = -nom_x[3] + true_x[3];
   out_3062673581371571051[4] = -nom_x[4] + true_x[4];
   out_3062673581371571051[5] = -nom_x[5] + true_x[5];
   out_3062673581371571051[6] = -nom_x[6] + true_x[6];
   out_3062673581371571051[7] = -nom_x[7] + true_x[7];
   out_3062673581371571051[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8338450128735048996) {
   out_8338450128735048996[0] = 1.0;
   out_8338450128735048996[1] = 0;
   out_8338450128735048996[2] = 0;
   out_8338450128735048996[3] = 0;
   out_8338450128735048996[4] = 0;
   out_8338450128735048996[5] = 0;
   out_8338450128735048996[6] = 0;
   out_8338450128735048996[7] = 0;
   out_8338450128735048996[8] = 0;
   out_8338450128735048996[9] = 0;
   out_8338450128735048996[10] = 1.0;
   out_8338450128735048996[11] = 0;
   out_8338450128735048996[12] = 0;
   out_8338450128735048996[13] = 0;
   out_8338450128735048996[14] = 0;
   out_8338450128735048996[15] = 0;
   out_8338450128735048996[16] = 0;
   out_8338450128735048996[17] = 0;
   out_8338450128735048996[18] = 0;
   out_8338450128735048996[19] = 0;
   out_8338450128735048996[20] = 1.0;
   out_8338450128735048996[21] = 0;
   out_8338450128735048996[22] = 0;
   out_8338450128735048996[23] = 0;
   out_8338450128735048996[24] = 0;
   out_8338450128735048996[25] = 0;
   out_8338450128735048996[26] = 0;
   out_8338450128735048996[27] = 0;
   out_8338450128735048996[28] = 0;
   out_8338450128735048996[29] = 0;
   out_8338450128735048996[30] = 1.0;
   out_8338450128735048996[31] = 0;
   out_8338450128735048996[32] = 0;
   out_8338450128735048996[33] = 0;
   out_8338450128735048996[34] = 0;
   out_8338450128735048996[35] = 0;
   out_8338450128735048996[36] = 0;
   out_8338450128735048996[37] = 0;
   out_8338450128735048996[38] = 0;
   out_8338450128735048996[39] = 0;
   out_8338450128735048996[40] = 1.0;
   out_8338450128735048996[41] = 0;
   out_8338450128735048996[42] = 0;
   out_8338450128735048996[43] = 0;
   out_8338450128735048996[44] = 0;
   out_8338450128735048996[45] = 0;
   out_8338450128735048996[46] = 0;
   out_8338450128735048996[47] = 0;
   out_8338450128735048996[48] = 0;
   out_8338450128735048996[49] = 0;
   out_8338450128735048996[50] = 1.0;
   out_8338450128735048996[51] = 0;
   out_8338450128735048996[52] = 0;
   out_8338450128735048996[53] = 0;
   out_8338450128735048996[54] = 0;
   out_8338450128735048996[55] = 0;
   out_8338450128735048996[56] = 0;
   out_8338450128735048996[57] = 0;
   out_8338450128735048996[58] = 0;
   out_8338450128735048996[59] = 0;
   out_8338450128735048996[60] = 1.0;
   out_8338450128735048996[61] = 0;
   out_8338450128735048996[62] = 0;
   out_8338450128735048996[63] = 0;
   out_8338450128735048996[64] = 0;
   out_8338450128735048996[65] = 0;
   out_8338450128735048996[66] = 0;
   out_8338450128735048996[67] = 0;
   out_8338450128735048996[68] = 0;
   out_8338450128735048996[69] = 0;
   out_8338450128735048996[70] = 1.0;
   out_8338450128735048996[71] = 0;
   out_8338450128735048996[72] = 0;
   out_8338450128735048996[73] = 0;
   out_8338450128735048996[74] = 0;
   out_8338450128735048996[75] = 0;
   out_8338450128735048996[76] = 0;
   out_8338450128735048996[77] = 0;
   out_8338450128735048996[78] = 0;
   out_8338450128735048996[79] = 0;
   out_8338450128735048996[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3507057343060404379) {
   out_3507057343060404379[0] = state[0];
   out_3507057343060404379[1] = state[1];
   out_3507057343060404379[2] = state[2];
   out_3507057343060404379[3] = state[3];
   out_3507057343060404379[4] = state[4];
   out_3507057343060404379[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3507057343060404379[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3507057343060404379[7] = state[7];
   out_3507057343060404379[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6251704956922705200) {
   out_6251704956922705200[0] = 1;
   out_6251704956922705200[1] = 0;
   out_6251704956922705200[2] = 0;
   out_6251704956922705200[3] = 0;
   out_6251704956922705200[4] = 0;
   out_6251704956922705200[5] = 0;
   out_6251704956922705200[6] = 0;
   out_6251704956922705200[7] = 0;
   out_6251704956922705200[8] = 0;
   out_6251704956922705200[9] = 0;
   out_6251704956922705200[10] = 1;
   out_6251704956922705200[11] = 0;
   out_6251704956922705200[12] = 0;
   out_6251704956922705200[13] = 0;
   out_6251704956922705200[14] = 0;
   out_6251704956922705200[15] = 0;
   out_6251704956922705200[16] = 0;
   out_6251704956922705200[17] = 0;
   out_6251704956922705200[18] = 0;
   out_6251704956922705200[19] = 0;
   out_6251704956922705200[20] = 1;
   out_6251704956922705200[21] = 0;
   out_6251704956922705200[22] = 0;
   out_6251704956922705200[23] = 0;
   out_6251704956922705200[24] = 0;
   out_6251704956922705200[25] = 0;
   out_6251704956922705200[26] = 0;
   out_6251704956922705200[27] = 0;
   out_6251704956922705200[28] = 0;
   out_6251704956922705200[29] = 0;
   out_6251704956922705200[30] = 1;
   out_6251704956922705200[31] = 0;
   out_6251704956922705200[32] = 0;
   out_6251704956922705200[33] = 0;
   out_6251704956922705200[34] = 0;
   out_6251704956922705200[35] = 0;
   out_6251704956922705200[36] = 0;
   out_6251704956922705200[37] = 0;
   out_6251704956922705200[38] = 0;
   out_6251704956922705200[39] = 0;
   out_6251704956922705200[40] = 1;
   out_6251704956922705200[41] = 0;
   out_6251704956922705200[42] = 0;
   out_6251704956922705200[43] = 0;
   out_6251704956922705200[44] = 0;
   out_6251704956922705200[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6251704956922705200[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6251704956922705200[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6251704956922705200[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6251704956922705200[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6251704956922705200[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6251704956922705200[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6251704956922705200[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6251704956922705200[53] = -9.8000000000000007*dt;
   out_6251704956922705200[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6251704956922705200[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6251704956922705200[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6251704956922705200[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6251704956922705200[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6251704956922705200[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6251704956922705200[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6251704956922705200[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6251704956922705200[62] = 0;
   out_6251704956922705200[63] = 0;
   out_6251704956922705200[64] = 0;
   out_6251704956922705200[65] = 0;
   out_6251704956922705200[66] = 0;
   out_6251704956922705200[67] = 0;
   out_6251704956922705200[68] = 0;
   out_6251704956922705200[69] = 0;
   out_6251704956922705200[70] = 1;
   out_6251704956922705200[71] = 0;
   out_6251704956922705200[72] = 0;
   out_6251704956922705200[73] = 0;
   out_6251704956922705200[74] = 0;
   out_6251704956922705200[75] = 0;
   out_6251704956922705200[76] = 0;
   out_6251704956922705200[77] = 0;
   out_6251704956922705200[78] = 0;
   out_6251704956922705200[79] = 0;
   out_6251704956922705200[80] = 1;
}
void h_25(double *state, double *unused, double *out_672568371399758073) {
   out_672568371399758073[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8355043907258562396) {
   out_8355043907258562396[0] = 0;
   out_8355043907258562396[1] = 0;
   out_8355043907258562396[2] = 0;
   out_8355043907258562396[3] = 0;
   out_8355043907258562396[4] = 0;
   out_8355043907258562396[5] = 0;
   out_8355043907258562396[6] = 1;
   out_8355043907258562396[7] = 0;
   out_8355043907258562396[8] = 0;
}
void h_24(double *state, double *unused, double *out_8821153942059904067) {
   out_8821153942059904067[0] = state[4];
   out_8821153942059904067[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7865992382472120658) {
   out_7865992382472120658[0] = 0;
   out_7865992382472120658[1] = 0;
   out_7865992382472120658[2] = 0;
   out_7865992382472120658[3] = 0;
   out_7865992382472120658[4] = 1;
   out_7865992382472120658[5] = 0;
   out_7865992382472120658[6] = 0;
   out_7865992382472120658[7] = 0;
   out_7865992382472120658[8] = 0;
   out_7865992382472120658[9] = 0;
   out_7865992382472120658[10] = 0;
   out_7865992382472120658[11] = 0;
   out_7865992382472120658[12] = 0;
   out_7865992382472120658[13] = 0;
   out_7865992382472120658[14] = 1;
   out_7865992382472120658[15] = 0;
   out_7865992382472120658[16] = 0;
   out_7865992382472120658[17] = 0;
}
void h_30(double *state, double *unused, double *out_3878838642927280968) {
   out_3878838642927280968[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3175009824959372465) {
   out_3175009824959372465[0] = 0;
   out_3175009824959372465[1] = 0;
   out_3175009824959372465[2] = 0;
   out_3175009824959372465[3] = 0;
   out_3175009824959372465[4] = 1;
   out_3175009824959372465[5] = 0;
   out_3175009824959372465[6] = 0;
   out_3175009824959372465[7] = 0;
   out_3175009824959372465[8] = 0;
}
void h_26(double *state, double *unused, double *out_1460093029859426942) {
   out_1460093029859426942[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4613540588384506172) {
   out_4613540588384506172[0] = 0;
   out_4613540588384506172[1] = 0;
   out_4613540588384506172[2] = 0;
   out_4613540588384506172[3] = 0;
   out_4613540588384506172[4] = 0;
   out_4613540588384506172[5] = 0;
   out_4613540588384506172[6] = 0;
   out_4613540588384506172[7] = 1;
   out_4613540588384506172[8] = 0;
}
void h_27(double *state, double *unused, double *out_5243062382334104263) {
   out_5243062382334104263[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6050941648314897415) {
   out_6050941648314897415[0] = 0;
   out_6050941648314897415[1] = 0;
   out_6050941648314897415[2] = 0;
   out_6050941648314897415[3] = 1;
   out_6050941648314897415[4] = 0;
   out_6050941648314897415[5] = 0;
   out_6050941648314897415[6] = 0;
   out_6050941648314897415[7] = 0;
   out_6050941648314897415[8] = 0;
}
void h_29(double *state, double *unused, double *out_2520202874486568178) {
   out_2520202874486568178[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8735936304429714510) {
   out_8735936304429714510[0] = 0;
   out_8735936304429714510[1] = 1;
   out_8735936304429714510[2] = 0;
   out_8735936304429714510[3] = 0;
   out_8735936304429714510[4] = 0;
   out_8735936304429714510[5] = 0;
   out_8735936304429714510[6] = 0;
   out_8735936304429714510[7] = 0;
   out_8735936304429714510[8] = 0;
}
void h_28(double *state, double *unused, double *out_8648584433145411770) {
   out_8648584433145411770[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7747177497714510855) {
   out_7747177497714510855[0] = 1;
   out_7747177497714510855[1] = 0;
   out_7747177497714510855[2] = 0;
   out_7747177497714510855[3] = 0;
   out_7747177497714510855[4] = 0;
   out_7747177497714510855[5] = 0;
   out_7747177497714510855[6] = 0;
   out_7747177497714510855[7] = 0;
   out_7747177497714510855[8] = 0;
}
void h_31(double *state, double *unused, double *out_7012224341023609554) {
   out_7012224341023609554[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8385689869135522824) {
   out_8385689869135522824[0] = 0;
   out_8385689869135522824[1] = 0;
   out_8385689869135522824[2] = 0;
   out_8385689869135522824[3] = 0;
   out_8385689869135522824[4] = 0;
   out_8385689869135522824[5] = 0;
   out_8385689869135522824[6] = 0;
   out_8385689869135522824[7] = 0;
   out_8385689869135522824[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_7430062589862895583) {
  err_fun(nom_x, delta_x, out_7430062589862895583);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3062673581371571051) {
  inv_err_fun(nom_x, true_x, out_3062673581371571051);
}
void car_H_mod_fun(double *state, double *out_8338450128735048996) {
  H_mod_fun(state, out_8338450128735048996);
}
void car_f_fun(double *state, double dt, double *out_3507057343060404379) {
  f_fun(state,  dt, out_3507057343060404379);
}
void car_F_fun(double *state, double dt, double *out_6251704956922705200) {
  F_fun(state,  dt, out_6251704956922705200);
}
void car_h_25(double *state, double *unused, double *out_672568371399758073) {
  h_25(state, unused, out_672568371399758073);
}
void car_H_25(double *state, double *unused, double *out_8355043907258562396) {
  H_25(state, unused, out_8355043907258562396);
}
void car_h_24(double *state, double *unused, double *out_8821153942059904067) {
  h_24(state, unused, out_8821153942059904067);
}
void car_H_24(double *state, double *unused, double *out_7865992382472120658) {
  H_24(state, unused, out_7865992382472120658);
}
void car_h_30(double *state, double *unused, double *out_3878838642927280968) {
  h_30(state, unused, out_3878838642927280968);
}
void car_H_30(double *state, double *unused, double *out_3175009824959372465) {
  H_30(state, unused, out_3175009824959372465);
}
void car_h_26(double *state, double *unused, double *out_1460093029859426942) {
  h_26(state, unused, out_1460093029859426942);
}
void car_H_26(double *state, double *unused, double *out_4613540588384506172) {
  H_26(state, unused, out_4613540588384506172);
}
void car_h_27(double *state, double *unused, double *out_5243062382334104263) {
  h_27(state, unused, out_5243062382334104263);
}
void car_H_27(double *state, double *unused, double *out_6050941648314897415) {
  H_27(state, unused, out_6050941648314897415);
}
void car_h_29(double *state, double *unused, double *out_2520202874486568178) {
  h_29(state, unused, out_2520202874486568178);
}
void car_H_29(double *state, double *unused, double *out_8735936304429714510) {
  H_29(state, unused, out_8735936304429714510);
}
void car_h_28(double *state, double *unused, double *out_8648584433145411770) {
  h_28(state, unused, out_8648584433145411770);
}
void car_H_28(double *state, double *unused, double *out_7747177497714510855) {
  H_28(state, unused, out_7747177497714510855);
}
void car_h_31(double *state, double *unused, double *out_7012224341023609554) {
  h_31(state, unused, out_7012224341023609554);
}
void car_H_31(double *state, double *unused, double *out_8385689869135522824) {
  H_31(state, unused, out_8385689869135522824);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
