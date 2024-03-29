#include "test_s21_matrix.h"

START_TEST(transpose_test_1) {
  matrix_t A = {0}, result;
  int rows = 3, columns = 5;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &result), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_test_2) {
  matrix_t A = {0}, result = {0};
  A.matrix = NULL;
  ck_assert_int_eq(s21_transpose(&A, &result), 1);
}
END_TEST

START_TEST(transpose_test_3) {
  matrix_t A = {0}, result = {0}, result_tmp = {0};
  int rows = 3, columns = 2;
  int sum = 0;
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  s21_create_matrix(columns, rows, &result_tmp);
  result_tmp.matrix[0][0] = 1;
  result_tmp.matrix[0][1] = 2;
  result_tmp.matrix[0][2] = 3;
  result_tmp.matrix[1][0] = 4;
  result_tmp.matrix[1][1] = 5;
  result_tmp.matrix[1][2] = 6;
  s21_transpose(&A, &result);
  for (int i = 0; i < columns; i++) {
    for (int j = 0; j < rows; j++) {
      if (fabs(result_tmp.matrix[i][j] - result.matrix[i][j]) > 1e-8) {
        sum++;
      }
    }
  }
  ck_assert_int_eq(sum, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_tmp);
}
END_TEST

START_TEST(transpose_test_4) {
  matrix_t A = {S21_NULL, 0, 0};
  matrix_t result = {S21_NULL, 0, 0};
  s21_create_matrix(1, 2, &A);
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2.;
  int answer = s21_transpose(&A, &result);
  ck_assert_int_eq(answer, 0);
  ck_assert_double_eq(result.matrix[0][0], 1.);
  ck_assert_double_eq(result.matrix[1][0], 2.);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *st_s21_transpose(void) {
  Suite *s = suite_create("\033[5m\033[1;31m\033[47m-=TRANSPOSE=-\033[0m");
  TCase *tc_transpose = tcase_create("s21_transpose_tc");

  tcase_add_test(tc_transpose, transpose_test_1);
  tcase_add_test(tc_transpose, transpose_test_2);
  tcase_add_test(tc_transpose, transpose_test_3);
  tcase_add_test(tc_transpose, transpose_test_4);

  suite_add_tcase(s, tc_transpose);
  return s;
}