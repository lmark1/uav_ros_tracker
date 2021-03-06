/* Produced by CVXGEN, 2021-02-16 11:21:46 -0500.  */
/* CVXGEN is Copyright (C) 2006-2017 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2017 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: csolve.c. */
/* Description: mex-able file for running cvxgen solver. */
#include "mex.h"
#include "solver.h"
Vars vars;
Params params;
Workspace work;
Settings settings;
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  int i, j;
  mxArray *xm, *cell, *xm_cell;
  double *src;
  double *dest;
  double *dest_cell;
  int valid_vars;
  int steps;
  int this_var_errors;
  int warned_diags;
  int prepare_for_c = 0;
  int extra_solves;
  const char *status_names[] = {"optval", "gap", "steps", "converged"};
  mwSize dims1x1of1[1] = {1};
  mwSize dims[1];
  const char *var_names[] = {"u_0", "u_1", "u_2", "u_3", "u_4", "u_5", "u_6", "u_7", "u_8", "u_9", "u_10", "u_11", "u_12", "u_13", "u_14", "u_15", "u_16", "u_17", "u_18", "u_19", "u_20", "u_21", "u_22", "u_23", "u_24", "u_25", "u_26", "u_27", "u_28", "u_29", "u_30", "u_31", "u_32", "u_33", "u_34", "u_35", "u_36", "u_37", "u_38", "u_39", "u_40", "u_41", "u_42", "u_43", "u_44", "u_45", "u_46", "u_47", "u_48", "u_49", "u_50", "u_51", "u_52", "u_53", "u_54", "u_55", "u_56", "u_57", "u_58", "u_59", "x_1", "x_2", "x_3", "x_4", "x_5", "x_6", "x_7", "x_8", "x_9", "x_10", "x_11", "x_12", "x_13", "x_14", "x_15", "x_16", "x_17", "x_18", "x_19", "x_20", "x_21", "x_22", "x_23", "x_24", "x_25", "x_26", "x_27", "x_28", "x_29", "x_30", "x_31", "x_32", "x_33", "x_34", "x_35", "x_36", "x_37", "x_38", "x_39", "x_40", "x_41", "x_42", "x_43", "x_44", "x_45", "x_46", "x_47", "x_48", "x_49", "x_50", "x_51", "x_52", "x_53", "x_54", "x_55", "x_56", "x_57", "x_58", "x_59", "x_60", "u", "x"};
  const int num_var_names = 122;
  /* Avoid compiler warnings of unused variables by using a dummy assignment. */
  warned_diags = j = 0;
  extra_solves = 0;
  set_defaults();
  /* Check we got the right number of arguments. */
  if (nrhs == 0)
    mexErrMsgTxt("Not enough arguments: You need to specify at least the parameters.\n");
  if (nrhs > 1) {
    /* Assume that the second argument is the settings. */
    if (mxGetField(prhs[1], 0, "eps") != NULL)
      settings.eps = *mxGetPr(mxGetField(prhs[1], 0, "eps"));
    if (mxGetField(prhs[1], 0, "max_iters") != NULL)
      settings.max_iters = *mxGetPr(mxGetField(prhs[1], 0, "max_iters"));
    if (mxGetField(prhs[1], 0, "refine_steps") != NULL)
      settings.refine_steps = *mxGetPr(mxGetField(prhs[1], 0, "refine_steps"));
    if (mxGetField(prhs[1], 0, "verbose") != NULL)
      settings.verbose = *mxGetPr(mxGetField(prhs[1], 0, "verbose"));
    if (mxGetField(prhs[1], 0, "better_start") != NULL)
      settings.better_start = *mxGetPr(mxGetField(prhs[1], 0, "better_start"));
    if (mxGetField(prhs[1], 0, "verbose_refinement") != NULL)
      settings.verbose_refinement = *mxGetPr(mxGetField(prhs[1], 0,
            "verbose_refinement"));
    if (mxGetField(prhs[1], 0, "debug") != NULL)
      settings.debug = *mxGetPr(mxGetField(prhs[1], 0, "debug"));
    if (mxGetField(prhs[1], 0, "kkt_reg") != NULL)
      settings.kkt_reg = *mxGetPr(mxGetField(prhs[1], 0, "kkt_reg"));
    if (mxGetField(prhs[1], 0, "s_init") != NULL)
      settings.s_init = *mxGetPr(mxGetField(prhs[1], 0, "s_init"));
    if (mxGetField(prhs[1], 0, "z_init") != NULL)
      settings.z_init = *mxGetPr(mxGetField(prhs[1], 0, "z_init"));
    if (mxGetField(prhs[1], 0, "resid_tol") != NULL)
      settings.resid_tol = *mxGetPr(mxGetField(prhs[1], 0, "resid_tol"));
    if (mxGetField(prhs[1], 0, "extra_solves") != NULL)
      extra_solves = *mxGetPr(mxGetField(prhs[1], 0, "extra_solves"));
    else
      extra_solves = 0;
    if (mxGetField(prhs[1], 0, "prepare_for_c") != NULL)
      prepare_for_c = *mxGetPr(mxGetField(prhs[1], 0, "prepare_for_c"));
  }
  valid_vars = 0;
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "A");
  if (xm == NULL) {
    printf("could not find params.A.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 4))) {
      printf("A must be size (4,4), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter A must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter A must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter A must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.A;
      src = mxGetPr(xm);
      dest[0] = src[0];  /* (1,1) entry. */
      dest[1] = src[5];  /* (2,2) entry. */
      dest[2] = src[10];  /* (3,3) entry. */
      dest[3] = src[15];  /* (4,4) entry. */
      dest[4] = src[4];  /* (1,2) entry. */
      dest[5] = src[9];  /* (2,3) entry. */
      dest[6] = src[14];  /* (3,4) entry. */
      dest[7] = src[8];  /* (1,3) entry. */
      dest[8] = src[13];  /* (2,4) entry. */
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Af");
  if (xm == NULL) {
    printf("could not find params.Af.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 4))) {
      printf("Af must be size (4,4), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Af must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Af must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Af must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Af;
      src = mxGetPr(xm);
      dest[0] = src[0];  /* (1,1) entry. */
      dest[1] = src[5];  /* (2,2) entry. */
      dest[2] = src[10];  /* (3,3) entry. */
      dest[3] = src[15];  /* (4,4) entry. */
      dest[4] = src[4];  /* (1,2) entry. */
      dest[5] = src[9];  /* (2,3) entry. */
      dest[6] = src[14];  /* (3,4) entry. */
      dest[7] = src[8];  /* (1,3) entry. */
      dest[8] = src[13];  /* (2,4) entry. */
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "B");
  if (xm == NULL) {
    printf("could not find params.B.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("B must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter B must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter B must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter B must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.B;
      src = mxGetPr(xm);
      dest[0] = src[3];  /* (4,1) entry. */
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Bf");
  if (xm == NULL) {
    printf("could not find params.Bf.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("Bf must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Bf must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Bf must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Bf must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Bf;
      src = mxGetPr(xm);
      dest[0] = src[3];  /* (4,1) entry. */
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "Q");
  if (xm == NULL) {
    printf("could not find params.Q.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 4))) {
      printf("Q must be size (4,4), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter Q must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter Q must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter Q must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.Q;
      src = mxGetPr(xm);
      warned_diags = 0;
      for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
          if (i == j) {
            *dest++ = *src;
          } else if (!warned_diags && (*src != 0)) {
            printf("\n!!! Warning: ignoring off-diagonal elements in Q !!!\n\n");
            warned_diags = 1;
          }
          src++;
        }
      }
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "u_max");
  if (xm == NULL) {
    printf("could not find params.u_max.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("u_max must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter u_max must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter u_max must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter u_max must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.u_max;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "u_min");
  if (xm == NULL) {
    printf("could not find params.u_min.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("u_min must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter u_min must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter u_min must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter u_min must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.u_min;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_0");
  if (xm == NULL) {
    printf("could not find params.x_0.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_0 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_0 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_0 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_0 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_0;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_max_2");
  if (xm == NULL) {
    printf("could not find params.x_max_2.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("x_max_2 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_max_2 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_max_2 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_max_2 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_max_2;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_max_3");
  if (xm == NULL) {
    printf("could not find params.x_max_3.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("x_max_3 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_max_3 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_max_3 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_max_3 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_max_3;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_max_4");
  if (xm == NULL) {
    printf("could not find params.x_max_4.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("x_max_4 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_max_4 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_max_4 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_max_4 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_max_4;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_min_2");
  if (xm == NULL) {
    printf("could not find params.x_min_2.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("x_min_2 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_min_2 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_min_2 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_min_2 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_min_2;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_min_3");
  if (xm == NULL) {
    printf("could not find params.x_min_3.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("x_min_3 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_min_3 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_min_3 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_min_3 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_min_3;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_min_4");
  if (xm == NULL) {
    printf("could not find params.x_min_4.\n");
  } else {
    if (!((mxGetM(xm) == 1) && (mxGetN(xm) == 1))) {
      printf("x_min_4 must be size (1,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_min_4 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_min_4 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_min_4 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_min_4;
      src = mxGetPr(xm);
      for (i = 0; i < 1; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_1");
  if (xm == NULL) {
    /* Attempt to pull x_ss_1 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 0);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_1 or params.x_ss{1}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_1 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_1 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_1 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_1 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_1;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_2");
  if (xm == NULL) {
    /* Attempt to pull x_ss_2 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 1);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_2 or params.x_ss{2}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_2 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_2 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_2 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_2 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_2;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_3");
  if (xm == NULL) {
    /* Attempt to pull x_ss_3 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 2);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_3 or params.x_ss{3}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_3 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_3 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_3 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_3 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_3;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_4");
  if (xm == NULL) {
    /* Attempt to pull x_ss_4 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 3);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_4 or params.x_ss{4}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_4 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_4 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_4 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_4 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_4;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_5");
  if (xm == NULL) {
    /* Attempt to pull x_ss_5 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 4);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_5 or params.x_ss{5}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_5 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_5 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_5 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_5 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_5;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_6");
  if (xm == NULL) {
    /* Attempt to pull x_ss_6 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 5);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_6 or params.x_ss{6}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_6 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_6 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_6 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_6 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_6;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_7");
  if (xm == NULL) {
    /* Attempt to pull x_ss_7 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 6);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_7 or params.x_ss{7}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_7 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_7 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_7 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_7 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_7;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_8");
  if (xm == NULL) {
    /* Attempt to pull x_ss_8 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 7);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_8 or params.x_ss{8}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_8 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_8 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_8 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_8 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_8;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_9");
  if (xm == NULL) {
    /* Attempt to pull x_ss_9 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 8);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_9 or params.x_ss{9}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_9 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_9 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_9 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_9 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_9;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_10");
  if (xm == NULL) {
    /* Attempt to pull x_ss_10 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 9);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_10 or params.x_ss{10}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_10 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_10 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_10 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_10 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_10;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_11");
  if (xm == NULL) {
    /* Attempt to pull x_ss_11 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 10);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_11 or params.x_ss{11}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_11 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_11 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_11 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_11 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_11;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_12");
  if (xm == NULL) {
    /* Attempt to pull x_ss_12 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 11);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_12 or params.x_ss{12}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_12 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_12 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_12 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_12 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_12;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_13");
  if (xm == NULL) {
    /* Attempt to pull x_ss_13 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 12);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_13 or params.x_ss{13}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_13 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_13 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_13 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_13 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_13;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_14");
  if (xm == NULL) {
    /* Attempt to pull x_ss_14 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 13);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_14 or params.x_ss{14}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_14 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_14 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_14 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_14 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_14;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_15");
  if (xm == NULL) {
    /* Attempt to pull x_ss_15 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 14);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_15 or params.x_ss{15}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_15 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_15 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_15 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_15 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_15;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_16");
  if (xm == NULL) {
    /* Attempt to pull x_ss_16 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 15);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_16 or params.x_ss{16}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_16 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_16 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_16 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_16 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_16;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_17");
  if (xm == NULL) {
    /* Attempt to pull x_ss_17 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 16);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_17 or params.x_ss{17}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_17 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_17 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_17 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_17 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_17;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_18");
  if (xm == NULL) {
    /* Attempt to pull x_ss_18 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 17);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_18 or params.x_ss{18}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_18 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_18 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_18 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_18 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_18;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_19");
  if (xm == NULL) {
    /* Attempt to pull x_ss_19 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 18);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_19 or params.x_ss{19}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_19 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_19 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_19 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_19 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_19;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_20");
  if (xm == NULL) {
    /* Attempt to pull x_ss_20 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 19);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_20 or params.x_ss{20}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_20 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_20 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_20 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_20 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_20;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_21");
  if (xm == NULL) {
    /* Attempt to pull x_ss_21 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 20);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_21 or params.x_ss{21}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_21 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_21 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_21 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_21 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_21;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_22");
  if (xm == NULL) {
    /* Attempt to pull x_ss_22 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 21);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_22 or params.x_ss{22}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_22 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_22 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_22 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_22 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_22;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_23");
  if (xm == NULL) {
    /* Attempt to pull x_ss_23 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 22);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_23 or params.x_ss{23}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_23 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_23 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_23 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_23 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_23;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_24");
  if (xm == NULL) {
    /* Attempt to pull x_ss_24 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 23);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_24 or params.x_ss{24}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_24 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_24 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_24 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_24 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_24;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_25");
  if (xm == NULL) {
    /* Attempt to pull x_ss_25 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 24);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_25 or params.x_ss{25}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_25 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_25 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_25 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_25 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_25;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_26");
  if (xm == NULL) {
    /* Attempt to pull x_ss_26 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 25);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_26 or params.x_ss{26}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_26 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_26 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_26 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_26 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_26;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_27");
  if (xm == NULL) {
    /* Attempt to pull x_ss_27 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 26);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_27 or params.x_ss{27}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_27 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_27 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_27 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_27 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_27;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_28");
  if (xm == NULL) {
    /* Attempt to pull x_ss_28 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 27);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_28 or params.x_ss{28}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_28 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_28 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_28 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_28 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_28;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_29");
  if (xm == NULL) {
    /* Attempt to pull x_ss_29 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 28);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_29 or params.x_ss{29}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_29 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_29 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_29 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_29 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_29;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_30");
  if (xm == NULL) {
    /* Attempt to pull x_ss_30 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 29);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_30 or params.x_ss{30}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_30 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_30 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_30 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_30 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_30;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_31");
  if (xm == NULL) {
    /* Attempt to pull x_ss_31 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 30);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_31 or params.x_ss{31}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_31 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_31 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_31 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_31 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_31;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_32");
  if (xm == NULL) {
    /* Attempt to pull x_ss_32 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 31);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_32 or params.x_ss{32}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_32 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_32 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_32 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_32 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_32;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_33");
  if (xm == NULL) {
    /* Attempt to pull x_ss_33 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 32);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_33 or params.x_ss{33}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_33 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_33 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_33 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_33 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_33;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_34");
  if (xm == NULL) {
    /* Attempt to pull x_ss_34 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 33);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_34 or params.x_ss{34}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_34 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_34 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_34 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_34 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_34;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_35");
  if (xm == NULL) {
    /* Attempt to pull x_ss_35 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 34);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_35 or params.x_ss{35}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_35 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_35 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_35 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_35 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_35;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_36");
  if (xm == NULL) {
    /* Attempt to pull x_ss_36 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 35);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_36 or params.x_ss{36}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_36 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_36 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_36 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_36 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_36;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_37");
  if (xm == NULL) {
    /* Attempt to pull x_ss_37 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 36);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_37 or params.x_ss{37}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_37 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_37 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_37 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_37 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_37;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_38");
  if (xm == NULL) {
    /* Attempt to pull x_ss_38 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 37);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_38 or params.x_ss{38}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_38 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_38 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_38 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_38 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_38;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_39");
  if (xm == NULL) {
    /* Attempt to pull x_ss_39 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 38);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_39 or params.x_ss{39}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_39 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_39 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_39 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_39 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_39;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_40");
  if (xm == NULL) {
    /* Attempt to pull x_ss_40 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 39);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_40 or params.x_ss{40}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_40 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_40 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_40 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_40 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_40;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_41");
  if (xm == NULL) {
    /* Attempt to pull x_ss_41 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 40);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_41 or params.x_ss{41}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_41 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_41 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_41 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_41 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_41;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_42");
  if (xm == NULL) {
    /* Attempt to pull x_ss_42 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 41);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_42 or params.x_ss{42}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_42 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_42 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_42 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_42 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_42;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_43");
  if (xm == NULL) {
    /* Attempt to pull x_ss_43 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 42);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_43 or params.x_ss{43}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_43 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_43 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_43 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_43 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_43;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_44");
  if (xm == NULL) {
    /* Attempt to pull x_ss_44 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 43);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_44 or params.x_ss{44}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_44 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_44 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_44 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_44 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_44;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_45");
  if (xm == NULL) {
    /* Attempt to pull x_ss_45 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 44);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_45 or params.x_ss{45}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_45 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_45 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_45 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_45 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_45;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_46");
  if (xm == NULL) {
    /* Attempt to pull x_ss_46 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 45);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_46 or params.x_ss{46}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_46 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_46 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_46 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_46 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_46;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_47");
  if (xm == NULL) {
    /* Attempt to pull x_ss_47 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 46);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_47 or params.x_ss{47}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_47 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_47 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_47 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_47 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_47;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_48");
  if (xm == NULL) {
    /* Attempt to pull x_ss_48 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 47);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_48 or params.x_ss{48}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_48 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_48 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_48 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_48 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_48;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_49");
  if (xm == NULL) {
    /* Attempt to pull x_ss_49 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 48);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_49 or params.x_ss{49}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_49 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_49 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_49 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_49 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_49;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_50");
  if (xm == NULL) {
    /* Attempt to pull x_ss_50 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 49);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_50 or params.x_ss{50}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_50 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_50 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_50 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_50 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_50;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_51");
  if (xm == NULL) {
    /* Attempt to pull x_ss_51 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 50);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_51 or params.x_ss{51}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_51 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_51 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_51 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_51 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_51;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_52");
  if (xm == NULL) {
    /* Attempt to pull x_ss_52 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 51);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_52 or params.x_ss{52}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_52 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_52 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_52 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_52 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_52;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_53");
  if (xm == NULL) {
    /* Attempt to pull x_ss_53 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 52);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_53 or params.x_ss{53}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_53 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_53 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_53 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_53 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_53;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_54");
  if (xm == NULL) {
    /* Attempt to pull x_ss_54 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 53);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_54 or params.x_ss{54}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_54 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_54 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_54 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_54 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_54;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_55");
  if (xm == NULL) {
    /* Attempt to pull x_ss_55 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 54);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_55 or params.x_ss{55}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_55 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_55 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_55 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_55 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_55;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_56");
  if (xm == NULL) {
    /* Attempt to pull x_ss_56 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 55);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_56 or params.x_ss{56}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_56 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_56 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_56 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_56 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_56;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_57");
  if (xm == NULL) {
    /* Attempt to pull x_ss_57 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 56);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_57 or params.x_ss{57}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_57 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_57 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_57 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_57 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_57;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_58");
  if (xm == NULL) {
    /* Attempt to pull x_ss_58 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 57);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_58 or params.x_ss{58}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_58 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_58 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_58 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_58 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_58;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_59");
  if (xm == NULL) {
    /* Attempt to pull x_ss_59 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 58);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_59 or params.x_ss{59}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_59 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_59 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_59 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_59 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_59;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  this_var_errors = 0;
  xm = mxGetField(prhs[0], 0, "x_ss_60");
  if (xm == NULL) {
    /* Attempt to pull x_ss_60 from a cell array, as an additional option. */
    cell = mxGetField(prhs[0], 0, "x_ss");
    if (cell != NULL)
      xm = mxGetCell(cell, 59);
  }
  if (xm == NULL) {
    printf("could not find params.x_ss_60 or params.x_ss{60}.\n");
  } else {
    if (!((mxGetM(xm) == 4) && (mxGetN(xm) == 1))) {
      printf("x_ss_60 must be size (4,1), not (%d,%d).\n", mxGetM(xm), mxGetN(xm));
      this_var_errors++;
    }
    if (mxIsComplex(xm)) {
      printf("parameter x_ss_60 must be real.\n");
      this_var_errors++;
    }
    if (!mxIsClass(xm, "double")) {
      printf("parameter x_ss_60 must be a full matrix of doubles.\n");
      this_var_errors++;
    }
    if (mxIsSparse(xm)) {
      printf("parameter x_ss_60 must be a full matrix.\n");
      this_var_errors++;
    }
    if (this_var_errors == 0) {
      dest = params.x_ss_60;
      src = mxGetPr(xm);
      for (i = 0; i < 4; i++)
        *dest++ = *src++;
      valid_vars++;
    }
  }
  if (valid_vars != 74) {
    printf("Error: %d parameters are invalid.\n", 74 - valid_vars);
    mexErrMsgTxt("invalid parameters found.");
  }
  if (prepare_for_c) {
    printf("settings.prepare_for_c == 1. thus, outputting for C.\n");
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_1[%d] = %.6g;\n", i, params.x_ss_1[i]);
    for (i = 0; i < 4; i++)
      printf("  params.Q[%d] = %.6g;\n", i, params.Q[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_2[%d] = %.6g;\n", i, params.x_ss_2[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_3[%d] = %.6g;\n", i, params.x_ss_3[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_4[%d] = %.6g;\n", i, params.x_ss_4[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_5[%d] = %.6g;\n", i, params.x_ss_5[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_6[%d] = %.6g;\n", i, params.x_ss_6[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_7[%d] = %.6g;\n", i, params.x_ss_7[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_8[%d] = %.6g;\n", i, params.x_ss_8[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_9[%d] = %.6g;\n", i, params.x_ss_9[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_10[%d] = %.6g;\n", i, params.x_ss_10[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_11[%d] = %.6g;\n", i, params.x_ss_11[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_12[%d] = %.6g;\n", i, params.x_ss_12[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_13[%d] = %.6g;\n", i, params.x_ss_13[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_14[%d] = %.6g;\n", i, params.x_ss_14[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_15[%d] = %.6g;\n", i, params.x_ss_15[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_16[%d] = %.6g;\n", i, params.x_ss_16[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_17[%d] = %.6g;\n", i, params.x_ss_17[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_18[%d] = %.6g;\n", i, params.x_ss_18[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_19[%d] = %.6g;\n", i, params.x_ss_19[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_20[%d] = %.6g;\n", i, params.x_ss_20[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_21[%d] = %.6g;\n", i, params.x_ss_21[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_22[%d] = %.6g;\n", i, params.x_ss_22[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_23[%d] = %.6g;\n", i, params.x_ss_23[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_24[%d] = %.6g;\n", i, params.x_ss_24[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_25[%d] = %.6g;\n", i, params.x_ss_25[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_26[%d] = %.6g;\n", i, params.x_ss_26[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_27[%d] = %.6g;\n", i, params.x_ss_27[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_28[%d] = %.6g;\n", i, params.x_ss_28[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_29[%d] = %.6g;\n", i, params.x_ss_29[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_30[%d] = %.6g;\n", i, params.x_ss_30[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_31[%d] = %.6g;\n", i, params.x_ss_31[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_32[%d] = %.6g;\n", i, params.x_ss_32[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_33[%d] = %.6g;\n", i, params.x_ss_33[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_34[%d] = %.6g;\n", i, params.x_ss_34[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_35[%d] = %.6g;\n", i, params.x_ss_35[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_36[%d] = %.6g;\n", i, params.x_ss_36[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_37[%d] = %.6g;\n", i, params.x_ss_37[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_38[%d] = %.6g;\n", i, params.x_ss_38[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_39[%d] = %.6g;\n", i, params.x_ss_39[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_40[%d] = %.6g;\n", i, params.x_ss_40[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_41[%d] = %.6g;\n", i, params.x_ss_41[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_42[%d] = %.6g;\n", i, params.x_ss_42[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_43[%d] = %.6g;\n", i, params.x_ss_43[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_44[%d] = %.6g;\n", i, params.x_ss_44[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_45[%d] = %.6g;\n", i, params.x_ss_45[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_46[%d] = %.6g;\n", i, params.x_ss_46[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_47[%d] = %.6g;\n", i, params.x_ss_47[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_48[%d] = %.6g;\n", i, params.x_ss_48[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_49[%d] = %.6g;\n", i, params.x_ss_49[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_50[%d] = %.6g;\n", i, params.x_ss_50[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_51[%d] = %.6g;\n", i, params.x_ss_51[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_52[%d] = %.6g;\n", i, params.x_ss_52[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_53[%d] = %.6g;\n", i, params.x_ss_53[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_54[%d] = %.6g;\n", i, params.x_ss_54[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_55[%d] = %.6g;\n", i, params.x_ss_55[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_56[%d] = %.6g;\n", i, params.x_ss_56[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_57[%d] = %.6g;\n", i, params.x_ss_57[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_58[%d] = %.6g;\n", i, params.x_ss_58[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_59[%d] = %.6g;\n", i, params.x_ss_59[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_ss_60[%d] = %.6g;\n", i, params.x_ss_60[i]);
    for (i = 0; i < 9; i++)
      printf("  params.Af[%d] = %.6g;\n", i, params.Af[i]);
    for (i = 0; i < 4; i++)
      printf("  params.x_0[%d] = %.6g;\n", i, params.x_0[i]);
    for (i = 0; i < 1; i++)
      printf("  params.Bf[%d] = %.6g;\n", i, params.Bf[i]);
    for (i = 0; i < 9; i++)
      printf("  params.A[%d] = %.6g;\n", i, params.A[i]);
    for (i = 0; i < 1; i++)
      printf("  params.B[%d] = %.6g;\n", i, params.B[i]);
    for (i = 0; i < 1; i++)
      printf("  params.x_max_2[%d] = %.6g;\n", i, params.x_max_2[i]);
    for (i = 0; i < 1; i++)
      printf("  params.x_min_2[%d] = %.6g;\n", i, params.x_min_2[i]);
    for (i = 0; i < 1; i++)
      printf("  params.x_max_3[%d] = %.6g;\n", i, params.x_max_3[i]);
    for (i = 0; i < 1; i++)
      printf("  params.x_min_3[%d] = %.6g;\n", i, params.x_min_3[i]);
    for (i = 0; i < 1; i++)
      printf("  params.x_max_4[%d] = %.6g;\n", i, params.x_max_4[i]);
    for (i = 0; i < 1; i++)
      printf("  params.x_min_4[%d] = %.6g;\n", i, params.x_min_4[i]);
    for (i = 0; i < 1; i++)
      printf("  params.u_max[%d] = %.6g;\n", i, params.u_max[i]);
    for (i = 0; i < 1; i++)
      printf("  params.u_min[%d] = %.6g;\n", i, params.u_min[i]);
  }
  /* Perform the actual solve in here. */
  steps = solve();
  /* For profiling purposes, allow extra silent solves if desired. */
  settings.verbose = 0;
  for (i = 0; i < extra_solves; i++)
    solve();
  /* Update the status variables. */
  plhs[1] = mxCreateStructArray(1, dims1x1of1, 4, status_names);
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[1], 0, "optval", xm);
  *mxGetPr(xm) = work.optval;
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[1], 0, "gap", xm);
  *mxGetPr(xm) = work.gap;
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[1], 0, "steps", xm);
  *mxGetPr(xm) = steps;
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[1], 0, "converged", xm);
  *mxGetPr(xm) = work.converged;
  /* Extract variable values. */
  plhs[0] = mxCreateStructArray(1, dims1x1of1, num_var_names, var_names);
  /* Create cell arrays for indexed variables. */
  dims[0] = 59;
  cell = mxCreateCellArray(1, dims);
  mxSetField(plhs[0], 0, "u", cell);
  dims[0] = 60;
  cell = mxCreateCellArray(1, dims);
  mxSetField(plhs[0], 0, "x", cell);
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_0", xm);
  dest = mxGetPr(xm);
  src = vars.u_0;
  for (i = 0; i < 1; i++) {
    *dest++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_1", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 0, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_1;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_2", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 1, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_2;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_3", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 2, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_3;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_4", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 3, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_4;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_5", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 4, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_5;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_6", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 5, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_6;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_7", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 6, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_7;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_8", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 7, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_8;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_9", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 8, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_9;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_10", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 9, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_10;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_11", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 10, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_11;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_12", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 11, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_12;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_13", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 12, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_13;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_14", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 13, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_14;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_15", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 14, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_15;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_16", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 15, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_16;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_17", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 16, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_17;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_18", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 17, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_18;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_19", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 18, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_19;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_20", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 19, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_20;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_21", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 20, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_21;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_22", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 21, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_22;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_23", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 22, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_23;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_24", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 23, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_24;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_25", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 24, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_25;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_26", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 25, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_26;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_27", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 26, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_27;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_28", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 27, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_28;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_29", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 28, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_29;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_30", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 29, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_30;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_31", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 30, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_31;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_32", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 31, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_32;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_33", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 32, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_33;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_34", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 33, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_34;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_35", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 34, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_35;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_36", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 35, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_36;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_37", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 36, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_37;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_38", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 37, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_38;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_39", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 38, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_39;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_40", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 39, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_40;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_41", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 40, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_41;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_42", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 41, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_42;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_43", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 42, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_43;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_44", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 43, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_44;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_45", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 44, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_45;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_46", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 45, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_46;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_47", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 46, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_47;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_48", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 47, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_48;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_49", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 48, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_49;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_50", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 49, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_50;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_51", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 50, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_51;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_52", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 51, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_52;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_53", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 52, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_53;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_54", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 53, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_54;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_55", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 54, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_55;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_56", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 55, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_56;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_57", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 56, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_57;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_58", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 57, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_58;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(1, 1, mxREAL);
  mxSetField(plhs[0], 0, "u_59", xm);
  xm_cell = mxCreateDoubleMatrix(1, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "u");
  mxSetCell(cell, 58, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.u_59;
  for (i = 0; i < 1; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_1", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 0, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_1;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_2", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 1, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_2;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_3", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 2, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_3;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_4", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 3, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_4;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_5", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 4, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_5;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_6", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 5, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_6;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_7", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 6, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_7;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_8", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 7, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_8;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_9", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 8, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_9;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_10", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 9, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_10;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_11", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 10, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_11;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_12", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 11, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_12;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_13", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 12, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_13;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_14", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 13, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_14;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_15", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 14, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_15;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_16", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 15, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_16;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_17", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 16, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_17;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_18", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 17, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_18;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_19", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 18, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_19;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_20", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 19, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_20;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_21", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 20, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_21;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_22", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 21, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_22;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_23", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 22, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_23;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_24", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 23, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_24;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_25", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 24, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_25;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_26", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 25, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_26;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_27", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 26, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_27;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_28", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 27, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_28;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_29", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 28, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_29;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_30", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 29, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_30;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_31", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 30, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_31;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_32", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 31, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_32;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_33", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 32, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_33;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_34", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 33, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_34;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_35", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 34, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_35;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_36", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 35, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_36;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_37", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 36, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_37;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_38", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 37, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_38;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_39", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 38, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_39;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_40", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 39, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_40;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_41", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 40, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_41;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_42", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 41, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_42;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_43", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 42, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_43;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_44", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 43, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_44;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_45", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 44, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_45;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_46", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 45, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_46;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_47", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 46, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_47;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_48", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 47, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_48;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_49", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 48, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_49;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_50", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 49, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_50;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_51", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 50, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_51;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_52", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 51, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_52;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_53", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 52, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_53;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_54", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 53, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_54;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_55", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 54, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_55;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_56", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 55, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_56;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_57", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 56, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_57;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_58", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 57, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_58;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_59", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 58, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_59;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
  xm = mxCreateDoubleMatrix(4, 1, mxREAL);
  mxSetField(plhs[0], 0, "x_60", xm);
  xm_cell = mxCreateDoubleMatrix(4, 1, mxREAL);
  cell = mxGetField(plhs[0], 0, "x");
  mxSetCell(cell, 59, xm_cell);
  dest = mxGetPr(xm);
  dest_cell = mxGetPr(xm_cell);
  src = vars.x_60;
  for (i = 0; i < 4; i++) {
    *dest++ = *src;
    *dest_cell++ = *src++;
  }
}
