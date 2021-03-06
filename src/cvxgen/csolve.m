% csolve  Solves a custom quadratic program very rapidly.
%
% [vars, status] = csolve(params, settings)
%
% solves the convex optimization problem
%
%   minimize(quad_form(x_1 - x_ss_1, Q) + quad_form(x_2 - x_ss_2, Q) + quad_form(x_3 - x_ss_3, Q) + quad_form(x_4 - x_ss_4, Q) + quad_form(x_5 - x_ss_5, Q) + quad_form(x_6 - x_ss_6, Q) + quad_form(x_7 - x_ss_7, Q) + quad_form(x_8 - x_ss_8, Q) + quad_form(x_9 - x_ss_9, Q) + quad_form(x_10 - x_ss_10, Q) + quad_form(x_11 - x_ss_11, Q) + quad_form(x_12 - x_ss_12, Q) + quad_form(x_13 - x_ss_13, Q) + quad_form(x_14 - x_ss_14, Q) + quad_form(x_15 - x_ss_15, Q) + quad_form(x_16 - x_ss_16, Q) + quad_form(x_17 - x_ss_17, Q) + quad_form(x_18 - x_ss_18, Q) + quad_form(x_19 - x_ss_19, Q) + quad_form(x_20 - x_ss_20, Q) + quad_form(x_21 - x_ss_21, Q) + quad_form(x_22 - x_ss_22, Q) + quad_form(x_23 - x_ss_23, Q) + quad_form(x_24 - x_ss_24, Q) + quad_form(x_25 - x_ss_25, Q) + quad_form(x_26 - x_ss_26, Q) + quad_form(x_27 - x_ss_27, Q) + quad_form(x_28 - x_ss_28, Q) + quad_form(x_29 - x_ss_29, Q) + quad_form(x_30 - x_ss_30, Q) + quad_form(x_31 - x_ss_31, Q) + quad_form(x_32 - x_ss_32, Q) + quad_form(x_33 - x_ss_33, Q) + quad_form(x_34 - x_ss_34, Q) + quad_form(x_35 - x_ss_35, Q) + quad_form(x_36 - x_ss_36, Q) + quad_form(x_37 - x_ss_37, Q) + quad_form(x_38 - x_ss_38, Q) + quad_form(x_39 - x_ss_39, Q) + quad_form(x_40 - x_ss_40, Q) + quad_form(x_41 - x_ss_41, Q) + quad_form(x_42 - x_ss_42, Q) + quad_form(x_43 - x_ss_43, Q) + quad_form(x_44 - x_ss_44, Q) + quad_form(x_45 - x_ss_45, Q) + quad_form(x_46 - x_ss_46, Q) + quad_form(x_47 - x_ss_47, Q) + quad_form(x_48 - x_ss_48, Q) + quad_form(x_49 - x_ss_49, Q) + quad_form(x_50 - x_ss_50, Q) + quad_form(x_51 - x_ss_51, Q) + quad_form(x_52 - x_ss_52, Q) + quad_form(x_53 - x_ss_53, Q) + quad_form(x_54 - x_ss_54, Q) + quad_form(x_55 - x_ss_55, Q) + quad_form(x_56 - x_ss_56, Q) + quad_form(x_57 - x_ss_57, Q) + quad_form(x_58 - x_ss_58, Q) + quad_form(x_59 - x_ss_59, Q) + quad_form(x_60 - x_ss_60, Q))
%   subject to
%     x_1 == Af*x_0 + Bf*u_0
%     x_2 == A*x_1 + B*u_1
%     x_3 == A*x_2 + B*u_2
%     x_4 == A*x_3 + B*u_3
%     x_5 == A*x_4 + B*u_4
%     x_6 == A*x_5 + B*u_5
%     x_7 == A*x_6 + B*u_6
%     x_8 == A*x_7 + B*u_7
%     x_9 == A*x_8 + B*u_8
%     x_10 == A*x_9 + B*u_9
%     x_11 == A*x_10 + B*u_10
%     x_12 == A*x_11 + B*u_11
%     x_13 == A*x_12 + B*u_12
%     x_14 == A*x_13 + B*u_13
%     x_15 == A*x_14 + B*u_14
%     x_16 == A*x_15 + B*u_15
%     x_17 == A*x_16 + B*u_16
%     x_18 == A*x_17 + B*u_17
%     x_19 == A*x_18 + B*u_18
%     x_20 == A*x_19 + B*u_19
%     x_21 == A*x_20 + B*u_20
%     x_22 == A*x_21 + B*u_21
%     x_23 == A*x_22 + B*u_22
%     x_24 == A*x_23 + B*u_23
%     x_25 == A*x_24 + B*u_24
%     x_26 == A*x_25 + B*u_25
%     x_27 == A*x_26 + B*u_26
%     x_28 == A*x_27 + B*u_27
%     x_29 == A*x_28 + B*u_28
%     x_30 == A*x_29 + B*u_29
%     x_31 == A*x_30 + B*u_30
%     x_32 == A*x_31 + B*u_31
%     x_33 == A*x_32 + B*u_32
%     x_34 == A*x_33 + B*u_33
%     x_35 == A*x_34 + B*u_34
%     x_36 == A*x_35 + B*u_35
%     x_37 == A*x_36 + B*u_36
%     x_38 == A*x_37 + B*u_37
%     x_39 == A*x_38 + B*u_38
%     x_40 == A*x_39 + B*u_39
%     x_41 == A*x_40 + B*u_40
%     x_42 == A*x_41 + B*u_41
%     x_43 == A*x_42 + B*u_42
%     x_44 == A*x_43 + B*u_43
%     x_45 == A*x_44 + B*u_44
%     x_46 == A*x_45 + B*u_45
%     x_47 == A*x_46 + B*u_46
%     x_48 == A*x_47 + B*u_47
%     x_49 == A*x_48 + B*u_48
%     x_50 == A*x_49 + B*u_49
%     x_51 == A*x_50 + B*u_50
%     x_52 == A*x_51 + B*u_51
%     x_53 == A*x_52 + B*u_52
%     x_54 == A*x_53 + B*u_53
%     x_55 == A*x_54 + B*u_54
%     x_56 == A*x_55 + B*u_55
%     x_57 == A*x_56 + B*u_56
%     x_58 == A*x_57 + B*u_57
%     x_59 == A*x_58 + B*u_58
%     x_60 == A*x_59 + B*u_59
%     x_1(2) <= x_max_2
%     x_2(2) <= x_max_2
%     x_3(2) <= x_max_2
%     x_4(2) <= x_max_2
%     x_5(2) <= x_max_2
%     x_6(2) <= x_max_2
%     x_7(2) <= x_max_2
%     x_8(2) <= x_max_2
%     x_9(2) <= x_max_2
%     x_10(2) <= x_max_2
%     x_11(2) <= x_max_2
%     x_12(2) <= x_max_2
%     x_13(2) <= x_max_2
%     x_14(2) <= x_max_2
%     x_15(2) <= x_max_2
%     x_16(2) <= x_max_2
%     x_17(2) <= x_max_2
%     x_18(2) <= x_max_2
%     x_19(2) <= x_max_2
%     x_20(2) <= x_max_2
%     x_21(2) <= x_max_2
%     x_22(2) <= x_max_2
%     x_23(2) <= x_max_2
%     x_24(2) <= x_max_2
%     x_25(2) <= x_max_2
%     x_26(2) <= x_max_2
%     x_27(2) <= x_max_2
%     x_28(2) <= x_max_2
%     x_29(2) <= x_max_2
%     x_30(2) <= x_max_2
%     x_31(2) <= x_max_2
%     x_32(2) <= x_max_2
%     x_33(2) <= x_max_2
%     x_34(2) <= x_max_2
%     x_35(2) <= x_max_2
%     x_36(2) <= x_max_2
%     x_37(2) <= x_max_2
%     x_38(2) <= x_max_2
%     x_39(2) <= x_max_2
%     x_40(2) <= x_max_2
%     x_41(2) <= x_max_2
%     x_42(2) <= x_max_2
%     x_43(2) <= x_max_2
%     x_44(2) <= x_max_2
%     x_45(2) <= x_max_2
%     x_46(2) <= x_max_2
%     x_47(2) <= x_max_2
%     x_48(2) <= x_max_2
%     x_49(2) <= x_max_2
%     x_50(2) <= x_max_2
%     x_51(2) <= x_max_2
%     x_52(2) <= x_max_2
%     x_53(2) <= x_max_2
%     x_54(2) <= x_max_2
%     x_55(2) <= x_max_2
%     x_56(2) <= x_max_2
%     x_57(2) <= x_max_2
%     x_58(2) <= x_max_2
%     x_59(2) <= x_max_2
%     x_60(2) <= x_max_2
%     x_1(2) >= -x_min_2
%     x_2(2) >= -x_min_2
%     x_3(2) >= -x_min_2
%     x_4(2) >= -x_min_2
%     x_5(2) >= -x_min_2
%     x_6(2) >= -x_min_2
%     x_7(2) >= -x_min_2
%     x_8(2) >= -x_min_2
%     x_9(2) >= -x_min_2
%     x_10(2) >= -x_min_2
%     x_11(2) >= -x_min_2
%     x_12(2) >= -x_min_2
%     x_13(2) >= -x_min_2
%     x_14(2) >= -x_min_2
%     x_15(2) >= -x_min_2
%     x_16(2) >= -x_min_2
%     x_17(2) >= -x_min_2
%     x_18(2) >= -x_min_2
%     x_19(2) >= -x_min_2
%     x_20(2) >= -x_min_2
%     x_21(2) >= -x_min_2
%     x_22(2) >= -x_min_2
%     x_23(2) >= -x_min_2
%     x_24(2) >= -x_min_2
%     x_25(2) >= -x_min_2
%     x_26(2) >= -x_min_2
%     x_27(2) >= -x_min_2
%     x_28(2) >= -x_min_2
%     x_29(2) >= -x_min_2
%     x_30(2) >= -x_min_2
%     x_31(2) >= -x_min_2
%     x_32(2) >= -x_min_2
%     x_33(2) >= -x_min_2
%     x_34(2) >= -x_min_2
%     x_35(2) >= -x_min_2
%     x_36(2) >= -x_min_2
%     x_37(2) >= -x_min_2
%     x_38(2) >= -x_min_2
%     x_39(2) >= -x_min_2
%     x_40(2) >= -x_min_2
%     x_41(2) >= -x_min_2
%     x_42(2) >= -x_min_2
%     x_43(2) >= -x_min_2
%     x_44(2) >= -x_min_2
%     x_45(2) >= -x_min_2
%     x_46(2) >= -x_min_2
%     x_47(2) >= -x_min_2
%     x_48(2) >= -x_min_2
%     x_49(2) >= -x_min_2
%     x_50(2) >= -x_min_2
%     x_51(2) >= -x_min_2
%     x_52(2) >= -x_min_2
%     x_53(2) >= -x_min_2
%     x_54(2) >= -x_min_2
%     x_55(2) >= -x_min_2
%     x_56(2) >= -x_min_2
%     x_57(2) >= -x_min_2
%     x_58(2) >= -x_min_2
%     x_59(2) >= -x_min_2
%     x_60(2) >= -x_min_2
%     x_1(3) <= x_max_3
%     x_2(3) <= x_max_3
%     x_3(3) <= x_max_3
%     x_4(3) <= x_max_3
%     x_5(3) <= x_max_3
%     x_6(3) <= x_max_3
%     x_7(3) <= x_max_3
%     x_8(3) <= x_max_3
%     x_9(3) <= x_max_3
%     x_10(3) <= x_max_3
%     x_11(3) <= x_max_3
%     x_12(3) <= x_max_3
%     x_13(3) <= x_max_3
%     x_14(3) <= x_max_3
%     x_15(3) <= x_max_3
%     x_16(3) <= x_max_3
%     x_17(3) <= x_max_3
%     x_18(3) <= x_max_3
%     x_19(3) <= x_max_3
%     x_20(3) <= x_max_3
%     x_21(3) <= x_max_3
%     x_22(3) <= x_max_3
%     x_23(3) <= x_max_3
%     x_24(3) <= x_max_3
%     x_25(3) <= x_max_3
%     x_26(3) <= x_max_3
%     x_27(3) <= x_max_3
%     x_28(3) <= x_max_3
%     x_29(3) <= x_max_3
%     x_30(3) <= x_max_3
%     x_31(3) <= x_max_3
%     x_32(3) <= x_max_3
%     x_33(3) <= x_max_3
%     x_34(3) <= x_max_3
%     x_35(3) <= x_max_3
%     x_36(3) <= x_max_3
%     x_37(3) <= x_max_3
%     x_38(3) <= x_max_3
%     x_39(3) <= x_max_3
%     x_40(3) <= x_max_3
%     x_41(3) <= x_max_3
%     x_42(3) <= x_max_3
%     x_43(3) <= x_max_3
%     x_44(3) <= x_max_3
%     x_45(3) <= x_max_3
%     x_46(3) <= x_max_3
%     x_47(3) <= x_max_3
%     x_48(3) <= x_max_3
%     x_49(3) <= x_max_3
%     x_50(3) <= x_max_3
%     x_51(3) <= x_max_3
%     x_52(3) <= x_max_3
%     x_53(3) <= x_max_3
%     x_54(3) <= x_max_3
%     x_55(3) <= x_max_3
%     x_56(3) <= x_max_3
%     x_57(3) <= x_max_3
%     x_58(3) <= x_max_3
%     x_59(3) <= x_max_3
%     x_60(3) <= x_max_3
%     x_1(3) >= -x_min_3
%     x_2(3) >= -x_min_3
%     x_3(3) >= -x_min_3
%     x_4(3) >= -x_min_3
%     x_5(3) >= -x_min_3
%     x_6(3) >= -x_min_3
%     x_7(3) >= -x_min_3
%     x_8(3) >= -x_min_3
%     x_9(3) >= -x_min_3
%     x_10(3) >= -x_min_3
%     x_11(3) >= -x_min_3
%     x_12(3) >= -x_min_3
%     x_13(3) >= -x_min_3
%     x_14(3) >= -x_min_3
%     x_15(3) >= -x_min_3
%     x_16(3) >= -x_min_3
%     x_17(3) >= -x_min_3
%     x_18(3) >= -x_min_3
%     x_19(3) >= -x_min_3
%     x_20(3) >= -x_min_3
%     x_21(3) >= -x_min_3
%     x_22(3) >= -x_min_3
%     x_23(3) >= -x_min_3
%     x_24(3) >= -x_min_3
%     x_25(3) >= -x_min_3
%     x_26(3) >= -x_min_3
%     x_27(3) >= -x_min_3
%     x_28(3) >= -x_min_3
%     x_29(3) >= -x_min_3
%     x_30(3) >= -x_min_3
%     x_31(3) >= -x_min_3
%     x_32(3) >= -x_min_3
%     x_33(3) >= -x_min_3
%     x_34(3) >= -x_min_3
%     x_35(3) >= -x_min_3
%     x_36(3) >= -x_min_3
%     x_37(3) >= -x_min_3
%     x_38(3) >= -x_min_3
%     x_39(3) >= -x_min_3
%     x_40(3) >= -x_min_3
%     x_41(3) >= -x_min_3
%     x_42(3) >= -x_min_3
%     x_43(3) >= -x_min_3
%     x_44(3) >= -x_min_3
%     x_45(3) >= -x_min_3
%     x_46(3) >= -x_min_3
%     x_47(3) >= -x_min_3
%     x_48(3) >= -x_min_3
%     x_49(3) >= -x_min_3
%     x_50(3) >= -x_min_3
%     x_51(3) >= -x_min_3
%     x_52(3) >= -x_min_3
%     x_53(3) >= -x_min_3
%     x_54(3) >= -x_min_3
%     x_55(3) >= -x_min_3
%     x_56(3) >= -x_min_3
%     x_57(3) >= -x_min_3
%     x_58(3) >= -x_min_3
%     x_59(3) >= -x_min_3
%     x_60(3) >= -x_min_3
%     x_1(4) <= x_max_4
%     x_2(4) <= x_max_4
%     x_3(4) <= x_max_4
%     x_4(4) <= x_max_4
%     x_5(4) <= x_max_4
%     x_6(4) <= x_max_4
%     x_7(4) <= x_max_4
%     x_8(4) <= x_max_4
%     x_9(4) <= x_max_4
%     x_10(4) <= x_max_4
%     x_11(4) <= x_max_4
%     x_12(4) <= x_max_4
%     x_13(4) <= x_max_4
%     x_14(4) <= x_max_4
%     x_15(4) <= x_max_4
%     x_16(4) <= x_max_4
%     x_17(4) <= x_max_4
%     x_18(4) <= x_max_4
%     x_19(4) <= x_max_4
%     x_20(4) <= x_max_4
%     x_21(4) <= x_max_4
%     x_22(4) <= x_max_4
%     x_23(4) <= x_max_4
%     x_24(4) <= x_max_4
%     x_25(4) <= x_max_4
%     x_26(4) <= x_max_4
%     x_27(4) <= x_max_4
%     x_28(4) <= x_max_4
%     x_29(4) <= x_max_4
%     x_30(4) <= x_max_4
%     x_31(4) <= x_max_4
%     x_32(4) <= x_max_4
%     x_33(4) <= x_max_4
%     x_34(4) <= x_max_4
%     x_35(4) <= x_max_4
%     x_36(4) <= x_max_4
%     x_37(4) <= x_max_4
%     x_38(4) <= x_max_4
%     x_39(4) <= x_max_4
%     x_40(4) <= x_max_4
%     x_41(4) <= x_max_4
%     x_42(4) <= x_max_4
%     x_43(4) <= x_max_4
%     x_44(4) <= x_max_4
%     x_45(4) <= x_max_4
%     x_46(4) <= x_max_4
%     x_47(4) <= x_max_4
%     x_48(4) <= x_max_4
%     x_49(4) <= x_max_4
%     x_50(4) <= x_max_4
%     x_51(4) <= x_max_4
%     x_52(4) <= x_max_4
%     x_53(4) <= x_max_4
%     x_54(4) <= x_max_4
%     x_55(4) <= x_max_4
%     x_56(4) <= x_max_4
%     x_57(4) <= x_max_4
%     x_58(4) <= x_max_4
%     x_59(4) <= x_max_4
%     x_60(4) <= x_max_4
%     x_1(4) >= -x_min_4
%     x_2(4) >= -x_min_4
%     x_3(4) >= -x_min_4
%     x_4(4) >= -x_min_4
%     x_5(4) >= -x_min_4
%     x_6(4) >= -x_min_4
%     x_7(4) >= -x_min_4
%     x_8(4) >= -x_min_4
%     x_9(4) >= -x_min_4
%     x_10(4) >= -x_min_4
%     x_11(4) >= -x_min_4
%     x_12(4) >= -x_min_4
%     x_13(4) >= -x_min_4
%     x_14(4) >= -x_min_4
%     x_15(4) >= -x_min_4
%     x_16(4) >= -x_min_4
%     x_17(4) >= -x_min_4
%     x_18(4) >= -x_min_4
%     x_19(4) >= -x_min_4
%     x_20(4) >= -x_min_4
%     x_21(4) >= -x_min_4
%     x_22(4) >= -x_min_4
%     x_23(4) >= -x_min_4
%     x_24(4) >= -x_min_4
%     x_25(4) >= -x_min_4
%     x_26(4) >= -x_min_4
%     x_27(4) >= -x_min_4
%     x_28(4) >= -x_min_4
%     x_29(4) >= -x_min_4
%     x_30(4) >= -x_min_4
%     x_31(4) >= -x_min_4
%     x_32(4) >= -x_min_4
%     x_33(4) >= -x_min_4
%     x_34(4) >= -x_min_4
%     x_35(4) >= -x_min_4
%     x_36(4) >= -x_min_4
%     x_37(4) >= -x_min_4
%     x_38(4) >= -x_min_4
%     x_39(4) >= -x_min_4
%     x_40(4) >= -x_min_4
%     x_41(4) >= -x_min_4
%     x_42(4) >= -x_min_4
%     x_43(4) >= -x_min_4
%     x_44(4) >= -x_min_4
%     x_45(4) >= -x_min_4
%     x_46(4) >= -x_min_4
%     x_47(4) >= -x_min_4
%     x_48(4) >= -x_min_4
%     x_49(4) >= -x_min_4
%     x_50(4) >= -x_min_4
%     x_51(4) >= -x_min_4
%     x_52(4) >= -x_min_4
%     x_53(4) >= -x_min_4
%     x_54(4) >= -x_min_4
%     x_55(4) >= -x_min_4
%     x_56(4) >= -x_min_4
%     x_57(4) >= -x_min_4
%     x_58(4) >= -x_min_4
%     x_59(4) >= -x_min_4
%     x_60(4) >= -x_min_4
%     u_0(1) <= u_max
%     u_1(1) <= u_max
%     u_2(1) <= u_max
%     u_3(1) <= u_max
%     u_4(1) <= u_max
%     u_5(1) <= u_max
%     u_6(1) <= u_max
%     u_7(1) <= u_max
%     u_8(1) <= u_max
%     u_9(1) <= u_max
%     u_10(1) <= u_max
%     u_11(1) <= u_max
%     u_12(1) <= u_max
%     u_13(1) <= u_max
%     u_14(1) <= u_max
%     u_15(1) <= u_max
%     u_16(1) <= u_max
%     u_17(1) <= u_max
%     u_18(1) <= u_max
%     u_19(1) <= u_max
%     u_20(1) <= u_max
%     u_21(1) <= u_max
%     u_22(1) <= u_max
%     u_23(1) <= u_max
%     u_24(1) <= u_max
%     u_25(1) <= u_max
%     u_26(1) <= u_max
%     u_27(1) <= u_max
%     u_28(1) <= u_max
%     u_29(1) <= u_max
%     u_30(1) <= u_max
%     u_31(1) <= u_max
%     u_32(1) <= u_max
%     u_33(1) <= u_max
%     u_34(1) <= u_max
%     u_35(1) <= u_max
%     u_36(1) <= u_max
%     u_37(1) <= u_max
%     u_38(1) <= u_max
%     u_39(1) <= u_max
%     u_40(1) <= u_max
%     u_41(1) <= u_max
%     u_42(1) <= u_max
%     u_43(1) <= u_max
%     u_44(1) <= u_max
%     u_45(1) <= u_max
%     u_46(1) <= u_max
%     u_47(1) <= u_max
%     u_48(1) <= u_max
%     u_49(1) <= u_max
%     u_50(1) <= u_max
%     u_51(1) <= u_max
%     u_52(1) <= u_max
%     u_53(1) <= u_max
%     u_54(1) <= u_max
%     u_55(1) <= u_max
%     u_56(1) <= u_max
%     u_57(1) <= u_max
%     u_58(1) <= u_max
%     u_59(1) <= u_max
%     u_0(1) >= -u_min
%     u_1(1) >= -u_min
%     u_2(1) >= -u_min
%     u_3(1) >= -u_min
%     u_4(1) >= -u_min
%     u_5(1) >= -u_min
%     u_6(1) >= -u_min
%     u_7(1) >= -u_min
%     u_8(1) >= -u_min
%     u_9(1) >= -u_min
%     u_10(1) >= -u_min
%     u_11(1) >= -u_min
%     u_12(1) >= -u_min
%     u_13(1) >= -u_min
%     u_14(1) >= -u_min
%     u_15(1) >= -u_min
%     u_16(1) >= -u_min
%     u_17(1) >= -u_min
%     u_18(1) >= -u_min
%     u_19(1) >= -u_min
%     u_20(1) >= -u_min
%     u_21(1) >= -u_min
%     u_22(1) >= -u_min
%     u_23(1) >= -u_min
%     u_24(1) >= -u_min
%     u_25(1) >= -u_min
%     u_26(1) >= -u_min
%     u_27(1) >= -u_min
%     u_28(1) >= -u_min
%     u_29(1) >= -u_min
%     u_30(1) >= -u_min
%     u_31(1) >= -u_min
%     u_32(1) >= -u_min
%     u_33(1) >= -u_min
%     u_34(1) >= -u_min
%     u_35(1) >= -u_min
%     u_36(1) >= -u_min
%     u_37(1) >= -u_min
%     u_38(1) >= -u_min
%     u_39(1) >= -u_min
%     u_40(1) >= -u_min
%     u_41(1) >= -u_min
%     u_42(1) >= -u_min
%     u_43(1) >= -u_min
%     u_44(1) >= -u_min
%     u_45(1) >= -u_min
%     u_46(1) >= -u_min
%     u_47(1) >= -u_min
%     u_48(1) >= -u_min
%     u_49(1) >= -u_min
%     u_50(1) >= -u_min
%     u_51(1) >= -u_min
%     u_52(1) >= -u_min
%     u_53(1) >= -u_min
%     u_54(1) >= -u_min
%     u_55(1) >= -u_min
%     u_56(1) >= -u_min
%     u_57(1) >= -u_min
%     u_58(1) >= -u_min
%     u_59(1) >= -u_min
%
% with variables
%      u_0   1 x 1
%      u_1   1 x 1
%      u_2   1 x 1
%      u_3   1 x 1
%      u_4   1 x 1
%      u_5   1 x 1
%      u_6   1 x 1
%      u_7   1 x 1
%      u_8   1 x 1
%      u_9   1 x 1
%     u_10   1 x 1
%     u_11   1 x 1
%     u_12   1 x 1
%     u_13   1 x 1
%     u_14   1 x 1
%     u_15   1 x 1
%     u_16   1 x 1
%     u_17   1 x 1
%     u_18   1 x 1
%     u_19   1 x 1
%     u_20   1 x 1
%     u_21   1 x 1
%     u_22   1 x 1
%     u_23   1 x 1
%     u_24   1 x 1
%     u_25   1 x 1
%     u_26   1 x 1
%     u_27   1 x 1
%     u_28   1 x 1
%     u_29   1 x 1
%     u_30   1 x 1
%     u_31   1 x 1
%     u_32   1 x 1
%     u_33   1 x 1
%     u_34   1 x 1
%     u_35   1 x 1
%     u_36   1 x 1
%     u_37   1 x 1
%     u_38   1 x 1
%     u_39   1 x 1
%     u_40   1 x 1
%     u_41   1 x 1
%     u_42   1 x 1
%     u_43   1 x 1
%     u_44   1 x 1
%     u_45   1 x 1
%     u_46   1 x 1
%     u_47   1 x 1
%     u_48   1 x 1
%     u_49   1 x 1
%     u_50   1 x 1
%     u_51   1 x 1
%     u_52   1 x 1
%     u_53   1 x 1
%     u_54   1 x 1
%     u_55   1 x 1
%     u_56   1 x 1
%     u_57   1 x 1
%     u_58   1 x 1
%     u_59   1 x 1
%      x_1   4 x 1
%      x_2   4 x 1
%      x_3   4 x 1
%      x_4   4 x 1
%      x_5   4 x 1
%      x_6   4 x 1
%      x_7   4 x 1
%      x_8   4 x 1
%      x_9   4 x 1
%     x_10   4 x 1
%     x_11   4 x 1
%     x_12   4 x 1
%     x_13   4 x 1
%     x_14   4 x 1
%     x_15   4 x 1
%     x_16   4 x 1
%     x_17   4 x 1
%     x_18   4 x 1
%     x_19   4 x 1
%     x_20   4 x 1
%     x_21   4 x 1
%     x_22   4 x 1
%     x_23   4 x 1
%     x_24   4 x 1
%     x_25   4 x 1
%     x_26   4 x 1
%     x_27   4 x 1
%     x_28   4 x 1
%     x_29   4 x 1
%     x_30   4 x 1
%     x_31   4 x 1
%     x_32   4 x 1
%     x_33   4 x 1
%     x_34   4 x 1
%     x_35   4 x 1
%     x_36   4 x 1
%     x_37   4 x 1
%     x_38   4 x 1
%     x_39   4 x 1
%     x_40   4 x 1
%     x_41   4 x 1
%     x_42   4 x 1
%     x_43   4 x 1
%     x_44   4 x 1
%     x_45   4 x 1
%     x_46   4 x 1
%     x_47   4 x 1
%     x_48   4 x 1
%     x_49   4 x 1
%     x_50   4 x 1
%     x_51   4 x 1
%     x_52   4 x 1
%     x_53   4 x 1
%     x_54   4 x 1
%     x_55   4 x 1
%     x_56   4 x 1
%     x_57   4 x 1
%     x_58   4 x 1
%     x_59   4 x 1
%     x_60   4 x 1
%
% and parameters
%        A   4 x 4
%       Af   4 x 4
%        B   4 x 1
%       Bf   4 x 1
%        Q   4 x 4    positive, PSD, diagonal
%    u_max   1 x 1
%    u_min   1 x 1
%      x_0   4 x 1
%  x_max_2   1 x 1
%  x_max_3   1 x 1
%  x_max_4   1 x 1
%  x_min_2   1 x 1
%  x_min_3   1 x 1
%  x_min_4   1 x 1
%   x_ss_1   4 x 1
%   x_ss_2   4 x 1
%   x_ss_3   4 x 1
%   x_ss_4   4 x 1
%   x_ss_5   4 x 1
%   x_ss_6   4 x 1
%   x_ss_7   4 x 1
%   x_ss_8   4 x 1
%   x_ss_9   4 x 1
%  x_ss_10   4 x 1
%  x_ss_11   4 x 1
%  x_ss_12   4 x 1
%  x_ss_13   4 x 1
%  x_ss_14   4 x 1
%  x_ss_15   4 x 1
%  x_ss_16   4 x 1
%  x_ss_17   4 x 1
%  x_ss_18   4 x 1
%  x_ss_19   4 x 1
%  x_ss_20   4 x 1
%  x_ss_21   4 x 1
%  x_ss_22   4 x 1
%  x_ss_23   4 x 1
%  x_ss_24   4 x 1
%  x_ss_25   4 x 1
%  x_ss_26   4 x 1
%  x_ss_27   4 x 1
%  x_ss_28   4 x 1
%  x_ss_29   4 x 1
%  x_ss_30   4 x 1
%  x_ss_31   4 x 1
%  x_ss_32   4 x 1
%  x_ss_33   4 x 1
%  x_ss_34   4 x 1
%  x_ss_35   4 x 1
%  x_ss_36   4 x 1
%  x_ss_37   4 x 1
%  x_ss_38   4 x 1
%  x_ss_39   4 x 1
%  x_ss_40   4 x 1
%  x_ss_41   4 x 1
%  x_ss_42   4 x 1
%  x_ss_43   4 x 1
%  x_ss_44   4 x 1
%  x_ss_45   4 x 1
%  x_ss_46   4 x 1
%  x_ss_47   4 x 1
%  x_ss_48   4 x 1
%  x_ss_49   4 x 1
%  x_ss_50   4 x 1
%  x_ss_51   4 x 1
%  x_ss_52   4 x 1
%  x_ss_53   4 x 1
%  x_ss_54   4 x 1
%  x_ss_55   4 x 1
%  x_ss_56   4 x 1
%  x_ss_57   4 x 1
%  x_ss_58   4 x 1
%  x_ss_59   4 x 1
%  x_ss_60   4 x 1
%
% Note:
%   - Check status.converged, which will be 1 if optimization succeeded.
%   - You don't have to specify settings if you don't want to.
%   - To hide output, use settings.verbose = 0.
%   - To change iterations, use settings.max_iters = 20.
%   - You may wish to compare with cvxsolve to check the solver is correct.
%
% Specify params.A, ..., params.x_ss_60, then run
%   [vars, status] = csolve(params, settings)
% Produced by CVXGEN, 2021-02-16 11:21:46 -0500.
% CVXGEN is Copyright (C) 2006-2017 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2017 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: csolve.m.
% Description: Help file for the Matlab solver interface.
