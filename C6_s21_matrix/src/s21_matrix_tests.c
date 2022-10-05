#include "s21_matrix.h"
#include <check.h>

START_TEST(test1_create) {
  matrix_t test1 = s21_create_matrix(3, 3);
  ck_assert_int_eq(test1.matrix_type, ZERO_MATRIX);
  s21_remove_matrix(&test1);
}
END_TEST

START_TEST(test2_create) {
  matrix_t test2 = s21_create_matrix(-4, 3);
  ck_assert_int_eq(test2.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(test3_create) {
  matrix_t test3 = s21_create_matrix(3, -3);
  ck_assert_int_eq(test3.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&test3);
}
END_TEST

START_TEST(test4_create) {
  matrix_t test4 = s21_create_matrix(0, 0);
  ck_assert_int_eq(test4.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&test4);
}
END_TEST

START_TEST(test5_create) {
  matrix_t test5 = s21_create_matrix(0, 6);
  ck_assert_int_eq(test5.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&test5);
}
END_TEST

Suite * s21_create_matrix_suite(void) {
  Suite *s;
  TCase *tc_create;
  s = suite_create("s21_create_matrix");
  tc_create = tcase_create("create_matrix");
  tcase_add_test(tc_create, test1_create);
  tcase_add_test(tc_create, test2_create);
  tcase_add_test(tc_create, test3_create);
  tcase_add_test(tc_create, test4_create);
  tcase_add_test(tc_create, test5_create);
  suite_add_tcase(s, tc_create);
  return s;
}

START_TEST(test1_eq) {
  matrix_t test1_a = s21_create_matrix(4, 4);
  matrix_t test1_b = s21_create_matrix(4, 4);
  ck_assert_int_eq(s21_eq_matrix(&test1_a, &test1_b), 1);
  s21_remove_matrix(&test1_a);
  s21_remove_matrix(&test1_b);
}
END_TEST

START_TEST(test2_eq) {
  matrix_t test2_a = s21_create_matrix(5, 5);
  s21_init_matrix(&test2_a, 3.9);
  matrix_t test2_b = s21_create_matrix(5, 5);
  s21_init_matrix(&test2_b, 3.9);
  ck_assert_int_eq(s21_eq_matrix(&test2_a, &test2_b), 1);
  s21_remove_matrix(&test2_a);
  s21_remove_matrix(&test2_b);
}
END_TEST

START_TEST(test3_eq) {
  double x3 = 1.12345678;
  double y3 = 1.12345679;
  matrix_t test3_a = s21_create_matrix(5, 5);
  s21_init_matrix(&test3_a, x3);
  matrix_t test3_b = s21_create_matrix(5, 5);
  s21_init_matrix(&test3_b, x3);
  test3_a.matrix[1][1] = y3;
  ck_assert_int_eq(s21_eq_matrix(&test3_a, &test3_b), 1);
  s21_remove_matrix(&test3_a);
  s21_remove_matrix(&test3_b);
}
END_TEST

START_TEST(test4_eq) {
  double x4 = 1.12345678;
  double y4 = 1.12345698;
  matrix_t test4_a = s21_create_matrix(5, 5);
  s21_init_matrix(&test4_a, x4);
  matrix_t test4_b = s21_create_matrix(5, 5);
  s21_init_matrix(&test4_b, x4);
  test4_a.matrix[1][1] = y4;
  ck_assert_int_eq(s21_eq_matrix(&test4_a, &test4_b), 0);
  s21_remove_matrix(&test4_a);
  s21_remove_matrix(&test4_b);
}
END_TEST

START_TEST(test5_eq) {
  double x5 = 1.12345678;
  matrix_t test5_a = s21_create_matrix(5, 5);
  s21_init_matrix(&test5_a, x5);
  matrix_t test5_b = s21_create_matrix(3, 3);
  s21_init_matrix(&test5_b, x5);
  ck_assert_int_eq(s21_eq_matrix(&test5_a, &test5_b), 0);
  s21_remove_matrix(&test5_a);
  s21_remove_matrix(&test5_b);
}
END_TEST

START_TEST(test6_eq) {
  double x6 = 0.000001;
  matrix_t test6_a = s21_create_matrix(5, 5);
  s21_init_matrix(&test6_a, x6);
  matrix_t test6_b = s21_create_matrix(5, 5);
  ck_assert_int_eq(s21_eq_matrix(&test6_a, &test6_b), 0);
  s21_remove_matrix(&test6_a);
  s21_remove_matrix(&test6_b);
}
END_TEST

START_TEST(test7_eq) {
  double x7 = 1.12345678;
  matrix_t test7_a = s21_create_matrix(5, 5);
  s21_init_matrix(&test7_a, x7);
  test7_a.matrix_type = INCORRECT_MATRIX;
  matrix_t test7_b = s21_create_matrix(5, 5);
  test7_b.matrix_type = INCORRECT_MATRIX;
  ck_assert_int_eq(s21_eq_matrix(&test7_a, &test7_b), 0);
  s21_remove_matrix(&test7_a);
  s21_remove_matrix(&test7_b);
}
END_TEST

START_TEST(test8_eq) {
  matrix_t test8_a = s21_create_matrix(5, 5);
  test8_a.matrix_type = INCORRECT_MATRIX;
  matrix_t test8_b = s21_create_matrix(5, 5);
  ck_assert_int_eq(s21_eq_matrix(&test8_a, &test8_b), 0);
  s21_remove_matrix(&test8_a);
  s21_remove_matrix(&test8_b);
}
END_TEST

START_TEST(test9_eq) {
  double x9 = 1.12345678;
  double y9 = -1.12345678;
  matrix_t test9_a = s21_create_matrix(5, 5);
  s21_init_matrix(&test9_a, x9);
  matrix_t test9_b = s21_create_matrix(5, 5);
  s21_init_matrix(&test9_b, y9);
  ck_assert_int_eq(s21_eq_matrix(&test9_a, &test9_b), 0);
  s21_remove_matrix(&test9_a);
  s21_remove_matrix(&test9_b);
}
END_TEST

START_TEST(test10_eq) {
  matrix_t test10_a = s21_create_matrix(2, 2);
  matrix_t test10_b = s21_create_matrix(2, 2);
  test10_a.matrix[0][0] = 1.0;
  test10_a.matrix[0][1] = 2.0;
  test10_a.matrix[1][0] = 3.0;
  test10_a.matrix[1][1] = 3.0;
  test10_b.matrix[0][0] = 2.0;
  test10_b.matrix[0][1] = 1.0;
  test10_b.matrix[1][0] = 3.0;
  test10_b.matrix[1][1] = 3.0;
  ck_assert_int_eq(s21_eq_matrix(&test10_a, &test10_b), 0);
  s21_remove_matrix(&test10_a);
  s21_remove_matrix(&test10_b);
}
END_TEST

Suite * s21_eq_matrix_suite(void) {
  Suite *s;
  TCase *tc_eq;
  s = suite_create("s21_eq_matrix");
  tc_eq = tcase_create("eq_matrix");
  tcase_add_test(tc_eq, test1_eq);
  tcase_add_test(tc_eq, test2_eq);
  tcase_add_test(tc_eq, test3_eq);
  tcase_add_test(tc_eq, test4_eq);
  tcase_add_test(tc_eq, test5_eq);
  tcase_add_test(tc_eq, test6_eq);
  tcase_add_test(tc_eq, test7_eq);
  tcase_add_test(tc_eq, test8_eq);
  tcase_add_test(tc_eq, test9_eq);
  tcase_add_test(tc_eq, test10_eq);
  suite_add_tcase(s, tc_eq);
  return s;
}

START_TEST(test1_sum) {
  matrix_t t1_sum_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t1_sum_a, 4.0);
  matrix_t t1_sum_b = s21_create_matrix(3, 3);
  t1_sum_b.matrix_type = INCORRECT_MATRIX;
  matrix_t t1_sum_c = s21_sum_matrix(&t1_sum_a, &t1_sum_b);
  ck_assert_int_eq(t1_sum_c.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t1_sum_a);
  s21_remove_matrix(&t1_sum_b);
  s21_remove_matrix(&t1_sum_c);
}
END_TEST

START_TEST(test2_sum) {
  matrix_t t2_sum_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t2_sum_a, 5.0);
  matrix_t t2_sum_b = s21_create_matrix(7, 3);
  s21_init_matrix(&t2_sum_b, 5.0);
  matrix_t t2_sum_c = s21_sum_matrix(&t2_sum_a, &t2_sum_b);
  ck_assert_int_eq(t2_sum_c.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t2_sum_a);
  s21_remove_matrix(&t2_sum_b);
  s21_remove_matrix(&t2_sum_c);
}
END_TEST

START_TEST(test3_sum) {
  matrix_t t3_sum_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t3_sum_a, 5.0);
  matrix_t t3_sum_b = s21_create_matrix(3, 4);
  s21_init_matrix(&t3_sum_b, 5.0);
  matrix_t t3_sum_c = s21_sum_matrix(&t3_sum_a, &t3_sum_b);
  ck_assert_int_eq(t3_sum_c.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t3_sum_a);
  s21_remove_matrix(&t3_sum_b);
  s21_remove_matrix(&t3_sum_c);
}
END_TEST

START_TEST(test4_sum) {
  matrix_t t4_sum_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t4_sum_a, 5.0);
  matrix_t t4_sum_b = s21_create_matrix(4, 3);
  s21_init_matrix(&t4_sum_b, 5.0);
  matrix_t t4_sum_c = s21_sum_matrix(&t4_sum_a, &t4_sum_b);
  ck_assert_int_eq(t4_sum_c.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t4_sum_a);
  s21_remove_matrix(&t4_sum_b);
  s21_remove_matrix(&t4_sum_c);
}
END_TEST

START_TEST(test5_sum) {
  double t5_sum_x = 134614366.436836582;
  double t5_sum_y = 3341436.3455476346;
  matrix_t t5_sum_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t5_sum_a, t5_sum_x);
  matrix_t t5_sum_b = s21_create_matrix(3, 3);
  s21_init_matrix(&t5_sum_b, t5_sum_y);
  matrix_t t5_sum_c = s21_sum_matrix(&t5_sum_a, &t5_sum_b);
  for (int i = 0; i < t5_sum_c.rows; i++) {
    for (int j = 0; j < t5_sum_c.columns; j++) {
      ck_assert_int_eq(floor(t5_sum_c.matrix[i][j] * 1e6), floor((t5_sum_x + t5_sum_y) * 1e6));
    }
  }
  s21_remove_matrix(&t5_sum_a);
  s21_remove_matrix(&t5_sum_b);
  s21_remove_matrix(&t5_sum_c);
}
END_TEST

START_TEST(test6_sum) {
  matrix_t t6_sum_a = s21_create_matrix(3, 3);
  matrix_t t6_sum_b = s21_create_matrix(3, 3);
  matrix_t t6_sum_c = s21_sum_matrix(&t6_sum_a, &t6_sum_b);
  for (int i = 0; i < t6_sum_c.rows; i++) {
    for (int j = 0; j < t6_sum_c.columns; j++) {
      ck_assert_int_eq(floor(t6_sum_c.matrix[i][j] * 1e6), 0);
    }
  }
  s21_remove_matrix(&t6_sum_a);
  s21_remove_matrix(&t6_sum_b);
  s21_remove_matrix(&t6_sum_c);
}
END_TEST

START_TEST(test7_sum) {
  matrix_t t7_sum_a = s21_create_matrix(4, 4);
  matrix_t t7_sum_b = s21_create_matrix(4, 4);
  s21_init_matrix(&t7_sum_a, 3.0);
  s21_init_matrix(&t7_sum_b, 4.0);
  matrix_t t7_sum_ref_rez = s21_create_matrix(4, 4);
  s21_init_matrix(&t7_sum_ref_rez, 7.0);
  matrix_t t7_sum_check_rez = s21_sum_matrix(&t7_sum_a, &t7_sum_b);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(t7_sum_ref_rez.matrix[i][j],
                          t7_sum_check_rez.matrix[i][j]);
    }
  }
  ck_assert_int_eq(t7_sum_ref_rez.matrix_type, t7_sum_check_rez.matrix_type);
  s21_remove_matrix(&t7_sum_a);
  s21_remove_matrix(&t7_sum_b);
  s21_remove_matrix(&t7_sum_ref_rez);
  s21_remove_matrix(&t7_sum_check_rez);
}
END_TEST

START_TEST(test8_sum) {
  matrix_t t8_sum_a = s21_create_matrix(4, 4);
  matrix_t t8_sum_b = s21_create_matrix(4, 4);
  t8_sum_b.matrix[0][0] = 1;
  t8_sum_b.matrix[1][1] = 1;
  t8_sum_b.matrix[2][2] = 1;
  t8_sum_b.matrix[3][3] = 1;
  matrix_t t8_sum_ref_rez = s21_create_matrix(4, 4);
  t8_sum_ref_rez.matrix[0][0] = 1;
  t8_sum_ref_rez.matrix[1][1] = 1;
  t8_sum_ref_rez.matrix[2][2] = 1;
  t8_sum_ref_rez.matrix[3][3] = 1;
  t8_sum_ref_rez.matrix_type = IDENTITY_MATRIX;
  matrix_t t8_check_rez_rez = s21_sum_matrix(&t8_sum_a, &t8_sum_b);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(t8_sum_ref_rez.matrix[i][j],
                          t8_check_rez_rez.matrix[i][j]);
    }
  }
  ck_assert_int_eq(t8_sum_ref_rez.matrix_type, t8_check_rez_rez.matrix_type);
  s21_remove_matrix(&t8_sum_a);
  s21_remove_matrix(&t8_sum_b);
  s21_remove_matrix(&t8_sum_ref_rez);
  s21_remove_matrix(&t8_check_rez_rez);
}
END_TEST

Suite * s21_sum_matrix_suite(void) {
  Suite *s;
  TCase *tc_sum;
  s = suite_create("s21_sum_matrix");
  tc_sum = tcase_create("sum_matrix");
  tcase_add_test(tc_sum, test1_sum);
  tcase_add_test(tc_sum, test2_sum);
  tcase_add_test(tc_sum, test3_sum);
  tcase_add_test(tc_sum, test4_sum);
  tcase_add_test(tc_sum, test5_sum);
  tcase_add_test(tc_sum, test6_sum);
  tcase_add_test(tc_sum, test7_sum);
  tcase_add_test(tc_sum, test8_sum);
  suite_add_tcase(s, tc_sum);
  return s;
}

START_TEST(test1_sub) {
  matrix_t t1_sub_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t1_sub_a, 2.0);
  matrix_t t1_sub_b = s21_create_matrix(3, 3);
  t1_sub_b.matrix_type = INCORRECT_MATRIX;
  matrix_t t1_sub_c = s21_sub_matrix(&t1_sub_a, &t1_sub_b);
  ck_assert_int_eq(t1_sub_c.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t1_sub_a);
  s21_remove_matrix(&t1_sub_b);
  s21_remove_matrix(&t1_sub_c);
}
END_TEST

START_TEST(test2_sub) {
  matrix_t t2_sub_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t2_sub_a, 1.0);
  matrix_t t2_sub_b = s21_create_matrix(7, 3);
  s21_init_matrix(&t2_sub_b, 1.0);
  matrix_t t2_sub_c = s21_sub_matrix(&t2_sub_a, &t2_sub_b);
  ck_assert_int_eq(t2_sub_c.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t2_sub_a);
  s21_remove_matrix(&t2_sub_b);
  s21_remove_matrix(&t2_sub_c);
}
END_TEST

START_TEST(test3_sub) {
  matrix_t t3_sub_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t3_sub_a, 4.0);
  matrix_t t3_sub_b = s21_create_matrix(3, 4);
  s21_init_matrix(&t3_sub_b, 3.0);
  matrix_t t3_sub_c = s21_sub_matrix(&t3_sub_a, &t3_sub_b);
  ck_assert_int_eq(t3_sub_c.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t3_sub_a);
  s21_remove_matrix(&t3_sub_b);
  s21_remove_matrix(&t3_sub_c);
}
END_TEST

START_TEST(test4_sub) {
  matrix_t t4_sub_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t4_sub_a, 6.0);
  matrix_t t4_sub_b = s21_create_matrix(4, 3);
  s21_init_matrix(&t4_sub_b, 2.0);
  matrix_t t4_sub_c = s21_sub_matrix(&t4_sub_a, &t4_sub_b);
  ck_assert_int_eq(t4_sub_c.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t4_sub_a);
  s21_remove_matrix(&t4_sub_b);
  s21_remove_matrix(&t4_sub_c);
}
END_TEST

START_TEST(test5_sub) {
  double t5_sub_x = 134614366.436836582;
  double t5_sub_y = 3341436.3455476346;
  matrix_t t5_sub_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t5_sub_a, t5_sub_x);
  matrix_t t5_sub_b = s21_create_matrix(3, 3);
  s21_init_matrix(&t5_sub_b, t5_sub_y);
  matrix_t t5_sub_c = s21_sub_matrix(&t5_sub_a, &t5_sub_b);
  for (int i = 0; i < t5_sub_c.rows; i++) {
    for (int j = 0; j < t5_sub_c.columns; j++) {
      ck_assert_int_eq(floor(t5_sub_c.matrix[i][j] * 1e6), floor((t5_sub_x - t5_sub_y) * 1e6));
      ck_assert_double_eq(t5_sub_c.matrix[i][j], t5_sub_x - t5_sub_y);
    }
  }
  s21_remove_matrix(&t5_sub_a);
  s21_remove_matrix(&t5_sub_b);
  s21_remove_matrix(&t5_sub_c);
}
END_TEST

START_TEST(test6_sub) {
  matrix_t t6_sub_a = s21_create_matrix(3, 3);
  matrix_t t6_sub_b = s21_create_matrix(3, 3);
  matrix_t t6_sub_c = s21_sub_matrix(&t6_sub_a, &t6_sub_b);
  for (int i = 0; i < t6_sub_c.rows; i++) {
    for (int j = 0; j < t6_sub_c.columns; j++) {
      ck_assert_int_eq(floor(t6_sub_c.matrix[i][j] * 1e6), 0);
      ck_assert_double_eq(t6_sub_c.matrix[i][j], 0);
    }
  }
  s21_remove_matrix(&t6_sub_a);
  s21_remove_matrix(&t6_sub_b);
  s21_remove_matrix(&t6_sub_c);
}
END_TEST

Suite * s21_sub_matrix_suite(void) {
  Suite *s;
  TCase *tc_sub;
  s = suite_create("s21_sub_matrix");
  tc_sub = tcase_create("sub_matrix");
  tcase_add_test(tc_sub, test1_sub);
  tcase_add_test(tc_sub, test2_sub);
  tcase_add_test(tc_sub, test3_sub);
  tcase_add_test(tc_sub, test4_sub);
  tcase_add_test(tc_sub, test5_sub);
  tcase_add_test(tc_sub, test6_sub);
  suite_add_tcase(s, tc_sub);
  return s;
}

START_TEST(test1_mult_number) {
  double t1_mn_x = 3.14;
  matrix_t t1_mn_a = s21_create_matrix(3, 3);
  t1_mn_a.matrix_type = INCORRECT_MATRIX;
  matrix_t t1_mn_b = s21_mult_number(&t1_mn_a, t1_mn_x);
  ck_assert_int_eq(t1_mn_b.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t1_mn_a);
  s21_remove_matrix(&t1_mn_b);
}
END_TEST

START_TEST(test2_mult_number) {
  double t2_mn_x = 2.12345;
  matrix_t t2_mn_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t2_mn_a, 5.0);
  matrix_t t2_mn_b = s21_mult_number(&t2_mn_a, t2_mn_x);

  for (int i = 0; i < t2_mn_b.rows; i++) {
    for (int j = 0; j < t2_mn_b.columns; j++) {
      ck_assert_int_eq(floor(t2_mn_b.matrix[i][j] * 1e6), floor((t2_mn_x * t2_mn_a.matrix[i][j]) * 1e6));
      ck_assert_double_eq(t2_mn_b.matrix[i][j], t2_mn_x * t2_mn_a.matrix[i][j]);
    }
  }
  ck_assert_int_eq(t2_mn_b.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&t2_mn_a);
  s21_remove_matrix(&t2_mn_b);
}
END_TEST

START_TEST(test3_mult_number) {
  double t3_mn_x = 0.0;
  matrix_t t3_mn_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t3_mn_a, 5);
  matrix_t t3_mn_b = s21_mult_number(&t3_mn_a, t3_mn_x);
  for (int i = 0; i < t3_mn_b.rows; i++) {
    for (int j = 0; j < t3_mn_b.columns; j++) {
      ck_assert_int_eq(t3_mn_b.matrix[i][j], t3_mn_x * t3_mn_a.matrix[i][j]);
      ck_assert_double_eq(t3_mn_b.matrix[i][j], t3_mn_x * t3_mn_a.matrix[i][j]);
    }
  }
  ck_assert_int_eq(t3_mn_b.matrix_type, ZERO_MATRIX);
  s21_remove_matrix(&t3_mn_a);
  s21_remove_matrix(&t3_mn_b);
}
END_TEST

START_TEST(test4_mult_number) {
  double t4_mn_x = -234523.234523;
  matrix_t t4_mn_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t4_mn_a, 5.532);
  matrix_t t4_mn_b = s21_mult_number(&t4_mn_a, t4_mn_x);
  for (int i = 0; i < t4_mn_b.rows; i++) {
    for (int j = 0; j < t4_mn_b.columns; j++) {
      ck_assert_int_eq(floor(t4_mn_b.matrix[i][j] * 1e6), floor((t4_mn_x * t4_mn_a.matrix[i][j]) * 1e6));
      ck_assert_double_eq(t4_mn_b.matrix[i][j], t4_mn_x * t4_mn_a.matrix[i][j]);
    }
  }
  ck_assert_int_eq(t4_mn_b.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&t4_mn_a);
  s21_remove_matrix(&t4_mn_b);
}
END_TEST

START_TEST(test5_mult_number) {
  matrix_t t5_mn_a = s21_create_matrix(3, 3);
  t5_mn_a.matrix[0][0] = 1.0;
  t5_mn_a.matrix[0][1] = 0.0;
  t5_mn_a.matrix[0][2] = 0.0;

  t5_mn_a.matrix[1][0] = 0.0;
  t5_mn_a.matrix[1][1] = 1.0;
  t5_mn_a.matrix[1][2] = 0.0;

  t5_mn_a.matrix[2][0] = 0.0;
  t5_mn_a.matrix[2][1] = 0.0;
  t5_mn_a.matrix[2][2] = 1.0;

  matrix_t t5_mn_b = s21_mult_number(&t5_mn_a, 1);
  ck_assert_int_eq(t5_mn_b.matrix_type, IDENTITY_MATRIX);
  s21_remove_matrix(&t5_mn_a);
  s21_remove_matrix(&t5_mn_b);
}
END_TEST

Suite * s21_mult_number_suite(void) {
  Suite *s;
  TCase *tc_mult_number;
  s = suite_create("s21_mult_number");
  tc_mult_number = tcase_create("mult_number");
  tcase_add_test(tc_mult_number, test1_mult_number);
  tcase_add_test(tc_mult_number, test2_mult_number);
  tcase_add_test(tc_mult_number, test3_mult_number);
  tcase_add_test(tc_mult_number, test4_mult_number);
  tcase_add_test(tc_mult_number, test5_mult_number);
  suite_add_tcase(s, tc_mult_number);
  return s;
}

START_TEST(test1_mult_matrix) {
  matrix_t t1_mm_a = s21_create_matrix(2, 2);
  s21_init_matrix(&t1_mm_a, 2.0);
  t1_mm_a.matrix_type = INCORRECT_MATRIX;
  matrix_t t1_mm_b = s21_create_matrix(2, 2);
  s21_init_matrix(&t1_mm_b, 2.0);
  matrix_t t1_mm_c = s21_mult_matrix(&t1_mm_a, &t1_mm_b);
  ck_assert_int_eq(t1_mm_c.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t1_mm_a);
  s21_remove_matrix(&t1_mm_b);
  s21_remove_matrix(&t1_mm_c);
}
END_TEST

START_TEST(test2_mult_matrix) {
  matrix_t t2_mm_a = s21_create_matrix(3, 3);
  s21_init_matrix(&t2_mm_a, 1.0);
  matrix_t t2_mm_b = s21_create_matrix(2, 2);
  matrix_t t2_mm_c = s21_mult_matrix(&t2_mm_a, &t2_mm_b);
  ck_assert_int_eq(t2_mm_c.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t2_mm_a);
  s21_remove_matrix(&t2_mm_b);
  s21_remove_matrix(&t2_mm_c);
}
END_TEST

START_TEST(test3_mult_matrix) {
  matrix_t t3_mm_a = s21_create_matrix(3, 2);
  s21_init_matrix(&t3_mm_a, 2.0);
  matrix_t t3_mm_b = s21_create_matrix(3, 3);
  s21_init_matrix(&t3_mm_b, 4.0);
  matrix_t t3_mm_c = s21_mult_matrix(&t3_mm_a, &t3_mm_b);
  ck_assert_int_eq(t3_mm_c.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t3_mm_a);
  s21_remove_matrix(&t3_mm_b);
  s21_remove_matrix(&t3_mm_c);
}
END_TEST

START_TEST(test4_mult_matrix) {
  matrix_t t4_mm_a = s21_create_matrix(3, 2);
  s21_init_matrix(&t4_mm_a, 3.0);
  matrix_t t4_mm_b = s21_create_matrix(1, 3);
  s21_init_matrix(&t4_mm_b, 3.0);
  matrix_t t4_mm_c = s21_mult_matrix(&t4_mm_a, &t4_mm_b);
  ck_assert_int_eq(t4_mm_c.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t4_mm_a);
  s21_remove_matrix(&t4_mm_b);
  s21_remove_matrix(&t4_mm_c);
}
END_TEST

START_TEST(test5_mult_matrix) {
  matrix_t t5_mm_a = s21_create_matrix(3, 6);
  matrix_t t5_mm_b = s21_create_matrix(6, 2);
  matrix_t t5_mm_c = s21_mult_matrix(&t5_mm_a, &t5_mm_b);
  for (int i = 0; i < t5_mm_c.rows; i++) {
    for (int j = 0; j < t5_mm_c.columns; j++) {
      ck_assert_int_eq(floor(t5_mm_c.matrix[i][j] * 1e6), 0);
      ck_assert_double_eq(t5_mm_c.matrix[i][j], 0.0);
    }
  }
  ck_assert_int_eq(t5_mm_c.matrix_type, ZERO_MATRIX);
  s21_remove_matrix(&t5_mm_a);
  s21_remove_matrix(&t5_mm_b);
  s21_remove_matrix(&t5_mm_c);
}
END_TEST

START_TEST(test6_mult_matrix) {
  matrix_t t6_mm_a = s21_create_matrix(3, 6);
  t6_mm_a.matrix[0][0] = 1.0;
  t6_mm_a.matrix[0][1] = 2.0;
  t6_mm_a.matrix[0][2] = 3.0;
  t6_mm_a.matrix[0][3] = 4.0;
  t6_mm_a.matrix[0][4] = 5.0;
  t6_mm_a.matrix[0][5] = 6.0;

  t6_mm_a.matrix[1][0] = 4.0;
  t6_mm_a.matrix[1][1] = 5.0;
  t6_mm_a.matrix[1][2] = 6.0;
  t6_mm_a.matrix[1][3] = 7.0;
  t6_mm_a.matrix[1][4] = 8.0;
  t6_mm_a.matrix[1][5] = 9.0;

  t6_mm_a.matrix[2][0] = 1.0;
  t6_mm_a.matrix[2][1] = 2.0;
  t6_mm_a.matrix[2][2] = 1.0;
  t6_mm_a.matrix[2][3] = 4.0;
  t6_mm_a.matrix[2][4] = 5.0;
  t6_mm_a.matrix[2][5] = 6.0;

  matrix_t t6_mm_b = s21_create_matrix(6, 2);
  t6_mm_b.matrix[0][0] = 1.0;
  t6_mm_b.matrix[0][1] = 2.0;

  t6_mm_b.matrix[1][0] = 4.0;
  t6_mm_b.matrix[1][1] = 5.0;

  t6_mm_b.matrix[2][0] = 1.0;
  t6_mm_b.matrix[2][1] = 2.0;

  t6_mm_b.matrix[3][0] = 1.0;
  t6_mm_b.matrix[3][1] = 2.0;

  t6_mm_b.matrix[4][0] = 4.0;
  t6_mm_b.matrix[4][1] = 5.0;

  t6_mm_b.matrix[5][0] = 1.0;
  t6_mm_b.matrix[5][1] = 2.0;

  double rez[6] = {42.0, 63.0, 78.0, 117.0, 40.0, 59.0};

  matrix_t t6_mm_c = s21_mult_matrix(&t6_mm_a, &t6_mm_b);
  int count = 0;
  for (int i = 0; i < t6_mm_c.rows; i++) {
    for (int j = 0; j < t6_mm_c.columns; j++) {
      ck_assert_int_eq(floor(t6_mm_c.matrix[i][j] * 1e6), floor(rez[count] * 1e6));
      ck_assert_double_eq(t6_mm_c.matrix[i][j], rez[count]);
      count++;
    }
  }
  ck_assert_int_eq(t6_mm_c.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&t6_mm_a);
  s21_remove_matrix(&t6_mm_b);
  s21_remove_matrix(&t6_mm_c);
}
END_TEST

Suite * s21_mult_matrix_suite(void) {
  Suite *s;
  TCase *tc_mult_matrix;
  s = suite_create("s21_mult_matrix");
  tc_mult_matrix = tcase_create("mult_matrix");
  tcase_add_test(tc_mult_matrix, test1_mult_matrix);
  tcase_add_test(tc_mult_matrix, test2_mult_matrix);
  tcase_add_test(tc_mult_matrix, test3_mult_matrix);
  tcase_add_test(tc_mult_matrix, test4_mult_matrix);
  tcase_add_test(tc_mult_matrix, test5_mult_matrix);
  tcase_add_test(tc_mult_matrix, test6_mult_matrix);
  suite_add_tcase(s, tc_mult_matrix);
  return s;
}

START_TEST(test1_transp) {
  matrix_t t1_tr_a = s21_create_matrix(2, 4);
  t1_tr_a.matrix[0][0] = 1.0;
  t1_tr_a.matrix[0][1] = 2.0;
  t1_tr_a.matrix[0][2] = 3.0;
  t1_tr_a.matrix[0][3] = 4.0;

  t1_tr_a.matrix[1][0] = 5.0;
  t1_tr_a.matrix[1][1] = 6.0;
  t1_tr_a.matrix[1][2] = 7.0;
  t1_tr_a.matrix[1][3] = 8.0;

  matrix_t t1_tr_b = s21_create_matrix(4, 2);
  t1_tr_b.matrix[0][0]= 1.0;
  t1_tr_b.matrix[0][1]= 5.0;

  t1_tr_b.matrix[1][0]= 2.0;
  t1_tr_b.matrix[1][1]= 6.0;

  t1_tr_b.matrix[2][0]= 3.0;
  t1_tr_b.matrix[2][1]= 7.0;

  t1_tr_b.matrix[3][0]= 4.0;
  t1_tr_b.matrix[3][1]= 8.0;

  matrix_t t1_tr_c = s21_transpose(&t1_tr_a);
  for (int i = 0; i < t1_tr_c.rows; i++) {
    for (int j = 0; j < t1_tr_c.columns; j++) {
      ck_assert_int_eq(t1_tr_c.matrix[i][j], t1_tr_b.matrix[i][j]);
      ck_assert_double_eq(t1_tr_c.matrix[i][j], t1_tr_b.matrix[i][j]);
    }
  }
  ck_assert_int_eq(t1_tr_c.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&t1_tr_a);
  s21_remove_matrix(&t1_tr_b);
  s21_remove_matrix(&t1_tr_c);
}
END_TEST

START_TEST(test2_transp) {
  matrix_t t2_tr_a = s21_create_matrix(3, 6);
  t2_tr_a.matrix[0][0] = 1.0;
  t2_tr_a.matrix[0][1] = 2.0;
  t2_tr_a.matrix[0][2] = 3.0;
  t2_tr_a.matrix[0][3] = 4.0;

  t2_tr_a.matrix[1][0] = 5.0;
  t2_tr_a.matrix[1][1] = 6.0;
  t2_tr_a.matrix[1][2] = 7.0;
  t2_tr_a.matrix[1][3] = 8.0;

  t2_tr_a.matrix_type = INCORRECT_MATRIX;
  matrix_t t2_tr_b = s21_transpose(&t2_tr_a);

  ck_assert_int_eq(t2_tr_b.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t2_tr_a);
  s21_remove_matrix(&t2_tr_b);
}
END_TEST

START_TEST(test3_transp) {
  matrix_t t3_tr_a = s21_create_matrix(3, 2);
  t3_tr_a.matrix[0][0] = 1.0;
  t3_tr_a.matrix[0][1] = 4.0;

  t3_tr_a.matrix[1][0] = 2.0;
  t3_tr_a.matrix[1][1] = 5.0;

  t3_tr_a.matrix[2][0] = 3.0;
  t3_tr_a.matrix[2][1] = 6.0;

  matrix_t t3_tr_b = s21_create_matrix(2, 3);
  t3_tr_b.matrix[0][0] = 1.0;
  t3_tr_b.matrix[0][1] = 2.0;
  t3_tr_b.matrix[0][2] = 3.0;

  t3_tr_b.matrix[1][0] = 4.0;
  t3_tr_b.matrix[1][1] = 5.0;
  t3_tr_b.matrix[1][2] = 6.0;

  matrix_t t3_tr_c = s21_transpose(&t3_tr_a);
  for (int i = 0; i < t3_tr_c.rows; i++) {
    for (int j = 0; j < t3_tr_c.columns; j++) {
      ck_assert_int_eq(t3_tr_c.matrix[i][j], t3_tr_b.matrix[i][j]);
      ck_assert_double_eq(t3_tr_c.matrix[i][j], t3_tr_b.matrix[i][j]);
    }
  }
  ck_assert_int_eq(t3_tr_c.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&t3_tr_a);
  s21_remove_matrix(&t3_tr_b);
  s21_remove_matrix(&t3_tr_c);
}
END_TEST

START_TEST(test4_transp) {
  matrix_t t4_tr_a = s21_create_matrix(3, 3);
  t4_tr_a.matrix[0][0] = 1.0;
  t4_tr_a.matrix[0][1] = 2.0;
  t4_tr_a.matrix[0][2] = 3.0;

  t4_tr_a.matrix[1][0] = 4.0;
  t4_tr_a.matrix[1][1] = 5.0;
  t4_tr_a.matrix[1][2] = 6.0;

  t4_tr_a.matrix[2][0] = 7.0;
  t4_tr_a.matrix[2][1] = 8.0;
  t4_tr_a.matrix[2][2] = 9.0;

  matrix_t t4_tr_b = s21_create_matrix(3, 3);
  t4_tr_b.matrix[0][0] = 1.0;
  t4_tr_b.matrix[0][1] = 4.0;
  t4_tr_b.matrix[0][2] = 7.0;

  t4_tr_b.matrix[1][0] = 2.0;
  t4_tr_b.matrix[1][1] = 5.0;
  t4_tr_b.matrix[1][2] = 8.0;

  t4_tr_b.matrix[2][0] = 3.0;
  t4_tr_b.matrix[2][1] = 6.0;
  t4_tr_b.matrix[2][2] = 9.0;

  matrix_t t4_tr_c = s21_transpose(&t4_tr_a);
  for (int i = 0; i < t4_tr_c.rows; i++) {
    for (int j = 0; j < t4_tr_c.columns; j++) {
      ck_assert_int_eq(t4_tr_c.matrix[i][j], t4_tr_b.matrix[i][j]);
     ck_assert_double_eq(t4_tr_c.matrix[i][j], t4_tr_b.matrix[i][j]);
    }
  }
  ck_assert_int_eq(t4_tr_c.matrix_type, CORRECT_MATRIX);
  s21_remove_matrix(&t4_tr_a);
  s21_remove_matrix(&t4_tr_b);
  s21_remove_matrix(&t4_tr_c);
}
END_TEST

START_TEST(test5_transp) {
  matrix_t t5_tr_a = s21_create_matrix(4, 4);
  t5_tr_a.matrix_type = INCORRECT_MATRIX;
  matrix_t t5_ref_rez = s21_create_matrix(4, 4);
  t5_ref_rez.matrix_type = INCORRECT_MATRIX;
  matrix_t t5_check_rez = s21_transpose(&t5_tr_a);
  ck_assert_uint_eq(t5_ref_rez.matrix_type, t5_check_rez.matrix_type);
  s21_remove_matrix(&t5_tr_a);
  s21_remove_matrix(&t5_ref_rez);
  s21_remove_matrix(&t5_check_rez);
}
END_TEST

Suite * s21_transpose_suite(void) {
  Suite *s;
  TCase *tc_transpose;
  s = suite_create("s21_transpose");
  tc_transpose = tcase_create("transpose");
  tcase_add_test(tc_transpose, test1_transp);
  tcase_add_test(tc_transpose, test2_transp);
  tcase_add_test(tc_transpose, test3_transp);
  tcase_add_test(tc_transpose, test4_transp);
  tcase_add_test(tc_transpose, test5_transp);
  suite_add_tcase(s, tc_transpose);
  return s;
}

START_TEST(test1_det) {
  matrix_t t1_det_a = s21_create_matrix(3, 4);
  s21_init_matrix(&t1_det_a, 5);
  double determinant = s21_determinant(&t1_det_a);
  ck_assert_double_nan(determinant);
  s21_remove_matrix(&t1_det_a);
}
END_TEST

START_TEST(test2_det) {
  matrix_t t2_det_a = s21_create_matrix(3, 3);
  t2_det_a.matrix_type = INCORRECT_MATRIX;
  double determinant = s21_determinant(&t2_det_a);
  ck_assert_double_nan(determinant);
  s21_remove_matrix(&t2_det_a);
}
END_TEST

START_TEST(test3_det) {
  double t3_det_rez = -54.0;
  matrix_t t3_det_a = s21_create_matrix(3, 3);
  t3_det_a.matrix[0][0] = -1.0;
  t3_det_a.matrix[0][1] = 2.0;
  t3_det_a.matrix[0][2] = -3.0;

  t3_det_a.matrix[1][0] = 4.0;
  t3_det_a.matrix[1][1] = -5.0;
  t3_det_a.matrix[1][2] = 6.0;

  t3_det_a.matrix[2][0] = -7.0;
  t3_det_a.matrix[2][1] = 8.0;
  t3_det_a.matrix[2][2] = 9.0;

  double t3_determinant = s21_determinant(&t3_det_a);
  ck_assert_int_eq(t3_determinant, t3_det_rez);
  ck_assert_double_eq(t3_determinant, t3_det_rez);
  s21_remove_matrix(&t3_det_a);
}
END_TEST

START_TEST(test4_det) {
  double t4_det_rez = 0.0;
  matrix_t t4_det_a = s21_create_matrix(3, 3);
  t4_det_a.matrix[0][0] = 1.0;
  t4_det_a.matrix[0][1] = 2.0;
  t4_det_a.matrix[0][2] = 3.0;

  t4_det_a.matrix[1][0] = 4.0;
  t4_det_a.matrix[1][1] = 5.0;
  t4_det_a.matrix[1][2] = 6.0;

  t4_det_a.matrix[2][0] = 7.0;
  t4_det_a.matrix[2][1] = 8.0;
  t4_det_a.matrix[2][2] = 9.0;

  double t4_determinant = s21_determinant(&t4_det_a);
  ck_assert_int_eq(t4_determinant, t4_det_rez);
  ck_assert_double_eq(t4_determinant, t4_det_rez);
  s21_remove_matrix(&t4_det_a);
}
END_TEST

START_TEST(test5_det) {
  double t5_det_rez = 0.0;
  matrix_t t5_det_a = s21_create_matrix(3, 3);
  double t5_determinant = s21_determinant(&t5_det_a);
  ck_assert_int_eq(t5_determinant, t5_det_rez);
  ck_assert_double_eq(t5_determinant, t5_det_rez);
  s21_remove_matrix(&t5_det_a);
}
END_TEST

START_TEST(test6_det) {
  double t6_det_rez = 1.0;
  matrix_t t6_det_a = s21_create_matrix(3, 3);
  t6_det_a.matrix_type = IDENTITY_MATRIX;
  t6_det_a.matrix[0][0] = 1.0;
  t6_det_a.matrix[0][1] = 0.0;
  t6_det_a.matrix[0][2] = 0.0;

  t6_det_a.matrix[1][0] = 0.0;
  t6_det_a.matrix[1][1] = 1.0;
  t6_det_a.matrix[1][2] = 0.0;

  t6_det_a.matrix[2][0] = 0.0;
  t6_det_a.matrix[2][1] = 0.0;
  t6_det_a.matrix[2][2] = 1.0;

  double t6_determinant = s21_determinant(&t6_det_a);
  ck_assert_int_eq(t6_determinant, t6_det_rez);
  ck_assert_double_eq(t6_determinant, t6_det_rez);
  s21_remove_matrix(&t6_det_a);
}
END_TEST

Suite * s21_determinant_suite(void) {
  Suite *s;
  TCase *tc_det;
  s = suite_create("s21_determinant");
  tc_det = tcase_create("determinant");
  tcase_add_test(tc_det, test1_det);
  tcase_add_test(tc_det, test2_det);
  tcase_add_test(tc_det, test3_det);
  tcase_add_test(tc_det, test4_det);
  tcase_add_test(tc_det, test5_det);
  tcase_add_test(tc_det, test6_det);
  suite_add_tcase(s, tc_det);
  return s;
}

START_TEST(test1_calc) {
  matrix_t t1_calc_a = s21_create_matrix(3, 3);
  t1_calc_a.matrix[0][0] = 1.0;
  t1_calc_a.matrix[0][1] = 2.0;
  t1_calc_a.matrix[0][2] = 3.0;

  t1_calc_a.matrix[1][0] = 0.0;
  t1_calc_a.matrix[1][1] = 4.0;
  t1_calc_a.matrix[1][2] = 2.0;

  t1_calc_a.matrix[2][0] = 5.0;
  t1_calc_a.matrix[2][1] = 2.0;
  t1_calc_a.matrix[2][2] = 1.0;

  matrix_t t1_calc_b = s21_create_matrix(3, 3);
  t1_calc_b.matrix[0][0] = 0.0;
  t1_calc_b.matrix[0][1] = 10.0;
  t1_calc_b.matrix[0][2] = -20.0;

  t1_calc_b.matrix[1][0] = 4.0;
  t1_calc_b.matrix[1][1] = -14.0;
  t1_calc_b.matrix[1][2] = 8.0;

  t1_calc_b.matrix[2][0] = -8.0;
  t1_calc_b.matrix[2][1] = -2.0;
  t1_calc_b.matrix[2][2] = 4.0;

  matrix_t t1_calc_c = s21_calc_complements(&t1_calc_a);

    for (int i = 0; i < t1_calc_c.rows; i++) {
      for (int j = 0; j < t1_calc_c.columns; j++) {
      ck_assert_int_eq(t1_calc_c.matrix[i][j], t1_calc_b.matrix[i][j]);
      ck_assert_double_eq(t1_calc_c.matrix[i][j], t1_calc_b.matrix[i][j]);
    }
  }
  s21_remove_matrix(&t1_calc_a);
  s21_remove_matrix(&t1_calc_b);
  s21_remove_matrix(&t1_calc_c);
}
END_TEST

START_TEST(test2_calc) {
  matrix_t t2_calc_a = s21_create_matrix(3, 3);
  t2_calc_a.matrix[0][0] = 2.0;
  t2_calc_a.matrix[0][1] = 5.0;
  t2_calc_a.matrix[0][2] = 7.0;

  t2_calc_a.matrix[1][0] = 6.0;
  t2_calc_a.matrix[1][1] = 3.0;
  t2_calc_a.matrix[1][2] = 4.0;

  t2_calc_a.matrix[2][0] = 5.0;
  t2_calc_a.matrix[2][1] = -2.0;
  t2_calc_a.matrix[2][2] = -3.0;

  matrix_t t2_calc_b = s21_create_matrix(3, 3);
  t2_calc_b.matrix[0][0] = -1.0;
  t2_calc_b.matrix[0][1] = 38.0;
  t2_calc_b.matrix[0][2] = -27.0;

  t2_calc_b.matrix[1][0] = 1.0;
  t2_calc_b.matrix[1][1] = -41.0;
  t2_calc_b.matrix[1][2] = 29.0;

  t2_calc_b.matrix[2][0] = -1.0;
  t2_calc_b.matrix[2][1] = 34.0;
  t2_calc_b.matrix[2][2] = -24.0;

  matrix_t t2_calc_c = s21_calc_complements(&t2_calc_a);
    for (int i = 0; i < t2_calc_c.rows; i++) {
      for (int j = 0; j < t2_calc_c.columns; j++) {
      ck_assert_int_eq(t2_calc_c.matrix[i][j], t2_calc_b.matrix[i][j]);
      ck_assert_double_eq(t2_calc_c.matrix[i][j], t2_calc_b.matrix[i][j]);
    }
  }
  s21_remove_matrix(&t2_calc_a);
  s21_remove_matrix(&t2_calc_b);
  s21_remove_matrix(&t2_calc_c);
}
END_TEST

START_TEST(test3_calc) {
  matrix_t t3_calc_a = s21_create_matrix(4, 3);
  s21_init_matrix(&t3_calc_a, 5.123);
  matrix_t t3_calc_b = s21_calc_complements(&t3_calc_a);
  ck_assert_int_eq(t3_calc_b.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t3_calc_a);
  s21_remove_matrix(&t3_calc_b);
}
END_TEST

START_TEST(test4_calc) {
  matrix_t t4_calc_a = s21_create_matrix(3, 3);
  t4_calc_a.matrix_type = INCORRECT_MATRIX;
  matrix_t t4_calc_b = s21_calc_complements(&t4_calc_a);
  ck_assert_int_eq(t4_calc_b.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t4_calc_a);
  s21_remove_matrix(&t4_calc_b);
}
END_TEST

Suite * s21_calc_complements_suite(void) {
  Suite *s;
  TCase *tc_calc;
  s = suite_create("s21_calc_complements");
  tc_calc = tcase_create("calc_complements");
  tcase_add_test(tc_calc, test1_calc);
  tcase_add_test(tc_calc, test2_calc);
  tcase_add_test(tc_calc, test3_calc);
  tcase_add_test(tc_calc, test4_calc);
  suite_add_tcase(s, tc_calc);
  return s;
}

START_TEST(test1_inverse) {
  matrix_t t1_inv_a = s21_create_matrix(3, 3);
  t1_inv_a.matrix[0][0] = 2.0;
  t1_inv_a.matrix[0][1] = 5.0;
  t1_inv_a.matrix[0][2] = 7.0;

  t1_inv_a.matrix[1][0] = 6.0;
  t1_inv_a.matrix[1][1] = 3.0;
  t1_inv_a.matrix[1][2] = 4.0;

  t1_inv_a.matrix[2][0] = 5.0;
  t1_inv_a.matrix[2][1] = -2.0;
  t1_inv_a.matrix[2][2] = -3.0;

  matrix_t t1_inv_b = s21_inverse_matrix(&t1_inv_a);
  matrix_t t1_inv_c = s21_mult_matrix(&t1_inv_a, &t1_inv_b);

  ck_assert_int_eq(t1_inv_c.matrix_type, IDENTITY_MATRIX);

  s21_remove_matrix(&t1_inv_a);
  s21_remove_matrix(&t1_inv_b);
  s21_remove_matrix(&t1_inv_c);
}
END_TEST

START_TEST(test2_inverse) {
  matrix_t t2_inv_a = s21_create_matrix(3, 3);
  t2_inv_a.matrix[0][0] = 0.625;
  t2_inv_a.matrix[0][1] = -432.543;
  t2_inv_a.matrix[0][2] = 56743112.321;

  t2_inv_a.matrix[1][0] = -2134.1155;
  t2_inv_a.matrix[1][1] = 7654.011;
  t2_inv_a.matrix[1][2] = -2345.2;

  t2_inv_a.matrix[2][0] = 0.006;
  t2_inv_a.matrix[2][1] = -12765.9856;
  t2_inv_a.matrix[2][2] = -8.099;

  matrix_t t2_inv_b = s21_inverse_matrix(&t2_inv_a);
  matrix_t t2_inv_c = s21_mult_matrix(&t2_inv_a, &t2_inv_b);

  ck_assert_int_eq(t2_inv_c.matrix_type, IDENTITY_MATRIX);

  s21_remove_matrix(&t2_inv_a);
  s21_remove_matrix(&t2_inv_b);
  s21_remove_matrix(&t2_inv_c);
}
END_TEST

START_TEST(test3_inverse) {
  matrix_t t3_inv_a = s21_create_matrix(3, 3);
  t3_inv_a.matrix_type = INCORRECT_MATRIX;
  matrix_t t3_inv_b = s21_inverse_matrix(&t3_inv_a);
  ck_assert_int_eq(t3_inv_b.matrix_type, INCORRECT_MATRIX);
  s21_remove_matrix(&t3_inv_a);
  s21_remove_matrix(&t3_inv_b);
}
END_TEST

Suite * s21_inverse_matrix_suite(void) {
  Suite *s;
  TCase *tc_inverse;
  s = suite_create("s21_inverse_matrix");
  tc_inverse = tcase_create("inverse_matrix");
  tcase_add_test(tc_inverse, test1_inverse);
  tcase_add_test(tc_inverse, test2_inverse);
  tcase_add_test(tc_inverse, test3_inverse);
  suite_add_tcase(s, tc_inverse);
  return s;
}

void s21_matrix_tests(SRunner **sr) {
  *sr = srunner_create(s21_eq_matrix_suite());
  srunner_add_suite(*sr, s21_create_matrix_suite());
  srunner_add_suite(*sr, s21_sum_matrix_suite());
  srunner_add_suite(*sr, s21_sub_matrix_suite());
  srunner_add_suite(*sr, s21_mult_number_suite());
  srunner_add_suite(*sr, s21_mult_matrix_suite());
  srunner_add_suite(*sr, s21_transpose_suite());
  srunner_add_suite(*sr, s21_determinant_suite());
  srunner_add_suite(*sr, s21_calc_complements_suite());
  srunner_add_suite(*sr, s21_inverse_matrix_suite());
}

int main(void) {
  int number_failed;
  SRunner *sr = NULL;
  s21_matrix_tests(&sr);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;;
}
