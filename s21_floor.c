#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = 0;

  if (!result || s21_correct(value)) {
    res = 1;
  } else {
    int rest = 0, flag = 0, e = s21_get_exp(value);
    s21_copy(result, value);
    for (; e > 0; e--) {
      rest = s21_cut_10(result);
      if (!flag && rest) flag = 1;
    }
    if (flag && s21_get_sign(*result) == -1) {
      s21_decimal temp = {{1, 0, 0, 0}};
      s21_dir_add(*result, temp, result);
    }
  }

  return res;
}
