#ifndef SRC_S21_MATRIX_H
#define SRC_S21_MATRIX_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;

  //  Создание матриц(matrix_type = ZERO_MATRIX)
matrix_t s21_create_matrix(int rows, int columns);
  //  Очистка матриц
void s21_remove_matrix(matrix_t *A);
  //  Сравнение матриц, если равны -> 1
int s21_eq_matrix(matrix_t *A, matrix_t *B);
  //  Сложение матриц
matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B);
  //  Вычитание матриц
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B);
  //  Умножение матрицы на число
matrix_t s21_mult_number(matrix_t *A, double number);
  //  Умножение двух матриц
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B);
  //  Транспонирование матрицы
matrix_t s21_transpose(matrix_t *A);
  //  Минор матрицы и матрица алгебраических дополнений
matrix_t s21_calc_complements(matrix_t *A);
  //  Определитель матрицы
double s21_determinant(matrix_t *A);
  //  Обратная матрица
matrix_t s21_inverse_matrix(matrix_t *A);
  // заполняет матрицу нулями
void s21_setZeroMatrix(matrix_t *matrix);
  //  Сравнивает количество строк и количество столбцов в матрицах, если ранвы -> 1
int s21_sizeMatrixEq (matrix_t a, matrix_t b);
  //  сложение или вычитание матриц, зависит от знака, без проверок
void s21_smb (matrix_t *Rez, matrix_t A, matrix_t B, int sign);
  //  Если матрица нулевая->1; если не нулевая->0
int s21_zeroType (matrix_t A);
  //  Если  матрица квадратная -> 1 иначе -> 0;
int s21_sqareMatrix (matrix_t A);
  //  Если матрица единичная -> 1 иначе -> 0
int s21_oneMatrix(matrix_t A);
  //  Устанавливает тип матрицы
void s21_setMatrixType (matrix_t *A);
  //  Транспонирование матрицы - замена строк матрицы ее столбцами с сохранением их номеров.
matrix_t s21_transpose(matrix_t *A);
  //  Минор матрицы и матрица алгебраических дополнений
matrix_t s21_calc_complements(matrix_t *A);
  //  Определитель матрицы
double s21_determinant(matrix_t *A);
  //  вычеркивает в матрице указанную строку и столбец, результат сохраняет в буферную матрицу
void s21_reducedMatrix(matrix_t A, matrix_t *tmp, int del_row, int del_column);
  //  Обратная матрица
matrix_t s21_inverse_matrix(matrix_t *A);
  //  Заполняет матрицу заданным числом
void s21_init_matrix(matrix_t *A, double num);

#endif  // SRC_S21_MATRIX_H_