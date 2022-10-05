#include "s21_matrix.h"

matrix_t s21_create_matrix(int rows, int columns) {
  matrix_t new_matrix = {0};
  if (rows > 0 && columns > 0) {
    new_matrix.rows = rows;
    new_matrix.columns = columns;
    new_matrix.matrix = (double**) malloc(rows * sizeof(double*) + columns * rows * sizeof(double));
    if (new_matrix.matrix != NULL) {
      new_matrix.matrix[0] = (double*)(new_matrix.matrix + rows);
      for (int i = 1; i < rows; i++) {
        new_matrix.matrix[i] = new_matrix.matrix[0] + i * columns;
      }
       s21_setZeroMatrix(&new_matrix);
    } else {
      printf("memory error 1");
    }
  } else  {
    new_matrix.matrix_type = INCORRECT_MATRIX;
    new_matrix.columns = 0;
    new_matrix.rows = 0;
    new_matrix.matrix = NULL;
  }
  return new_matrix;
}

void s21_remove_matrix(matrix_t *A) {
  free(A->matrix);
  A->columns = 0;
  A->rows = 0;
  A->matrix = NULL;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = 0;
  if (s21_sizeMatrixEq(*A, *B) == 1) {
    flag = 1;
  }
  if (flag == 1) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        flag = fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-7 ? 0 : flag;
      }
    }
  }
  return flag;
}

matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B) {
  matrix_t rez = s21_create_matrix(A->rows, A->columns);
  if (s21_sizeMatrixEq(*A, *B) == 1 && A->matrix_type != INCORRECT_MATRIX &&
      B->matrix_type != INCORRECT_MATRIX) {
    s21_smb(&rez, *A, *B, 1);
    s21_setMatrixType(&rez);
  } else {
    rez.matrix_type = INCORRECT_MATRIX;
    s21_remove_matrix(&rez);
  }
  return rez;
}

matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
  matrix_t rez = s21_create_matrix(A->rows, A->columns);
  if (s21_sizeMatrixEq(*A, *B) == 1 && A->matrix_type != INCORRECT_MATRIX &&
      B->matrix_type != INCORRECT_MATRIX) {
    s21_smb(&rez, *A, *B, -1);
    s21_setMatrixType(&rez);
  } else {
    rez.matrix_type = INCORRECT_MATRIX;
    s21_remove_matrix(&rez);
  }
  return rez;
}

matrix_t s21_mult_number(matrix_t *A, double number) {
  matrix_t rez = s21_create_matrix(A->rows, A->columns);
  if (A->matrix_type != INCORRECT_MATRIX) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        rez.matrix[i][j] = A->matrix[i][j] * number;
      }
    }
    s21_setMatrixType(&rez);
  } else {
    rez.matrix_type = INCORRECT_MATRIX;
    s21_remove_matrix(&rez);
  }
  return rez;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
  matrix_t rez = s21_create_matrix(A->rows, B->columns);
  if (A->columns == B->rows && A->matrix_type != INCORRECT_MATRIX && B->matrix_type != INCORRECT_MATRIX) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        rez.matrix[i][j] = 0;
        for (int k = 0; k < B->rows; k++) {
          rez.matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          if (rez.matrix[i][j] >= -1e-7 && rez.matrix[i][j] < 0) {
            rez.matrix[i][j] = 0.0;
          }
        }
      }
    }
    s21_setMatrixType(&rez);
  } else {
    rez.matrix_type = INCORRECT_MATRIX;
    s21_remove_matrix(&rez);
  }
  return rez;
}

matrix_t s21_transpose(matrix_t *A) {
  matrix_t rez = s21_create_matrix(A->columns, A->rows);
  if (A->matrix_type != INCORRECT_MATRIX) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        rez.matrix[j][i] = A->matrix[i][j];
      }
    }
    s21_setMatrixType(&rez);
  } else {
    rez.matrix_type = INCORRECT_MATRIX;
    s21_remove_matrix(&rez);
  }
  return rez;
}

matrix_t s21_calc_complements(matrix_t *A) {
  matrix_t rez = s21_create_matrix(A->rows, A->columns);
  if (s21_sqareMatrix(*A) == 1 && A->matrix_type != INCORRECT_MATRIX) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t tmp = s21_create_matrix(A->rows - 1, A->columns - 1);
         s21_reducedMatrix(*A, &tmp, j, i);
        rez.matrix[j][i] = pow(-1, i + j) * s21_determinant(&tmp);
        if (rez.matrix[j][i] == -0.0) {
          rez.matrix[j][i] *= -1.0;
        }
        s21_remove_matrix(&tmp);
      }
    }
    s21_setMatrixType(&rez);
  } else {
    rez.matrix_type = INCORRECT_MATRIX;
    s21_remove_matrix(&rez);
  }
  return rez;
}

double s21_determinant(matrix_t *A) {
  double det = 0.0;
  if (s21_sqareMatrix(*A) == 1 && A->matrix_type != INCORRECT_MATRIX) {
    if (A->rows == 1) {
      det = A->matrix[0][0];
    } else if (A->rows == 2) {
      det = A->matrix[0][0] * A->matrix[1][1] - (A->matrix[0][1] * A->matrix[1][0]);
    } else {
      matrix_t tmp = s21_create_matrix(A->rows - 1, A->columns - 1);
      for (int i = 0; i < A->rows; i++) {
        s21_reducedMatrix(*A, &tmp, i, 0);
        det += A->matrix[i][0] * pow(-1, i) * s21_determinant(&tmp);
      }
      s21_remove_matrix(&tmp);
    }
  } else {
    det = NAN;
  }
  return det;
}

matrix_t s21_inverse_matrix(matrix_t *A) {
  matrix_t rez;
  if (s21_sqareMatrix(*A) == 1 && s21_determinant(A) != 0.0 && A->matrix_type != INCORRECT_MATRIX) {
    matrix_t alg = s21_calc_complements(A);
    matrix_t transp = s21_transpose(&alg);
    rez = s21_mult_number(&transp, 1 / s21_determinant(A));
    s21_setMatrixType(&rez);
    s21_remove_matrix(&alg);
    s21_remove_matrix(&transp);
  } else {
    rez = s21_create_matrix(A->rows, A->columns);
    rez.matrix_type = INCORRECT_MATRIX;
    s21_remove_matrix(&rez);
  }
  return rez;
}

void s21_setZeroMatrix(matrix_t *matrix) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] = 0;
    }
  }
  matrix->matrix_type = ZERO_MATRIX;
}

int s21_sizeMatrixEq(matrix_t A, matrix_t B) {
  int flagEq = 0;
  if (A.columns == B.columns && A.rows == B.rows && A.matrix_type != INCORRECT_MATRIX &&
      B.matrix_type != INCORRECT_MATRIX) {
    flagEq = 1;
  }
  return flagEq;
}

void s21_smb(matrix_t *Rez, matrix_t A, matrix_t B, int sign) {
  for (int i = 0; i < A.rows; i++) {
      for (int j = 0; j < A.columns; j++) {
        Rez->matrix[i][j] = A.matrix[i][j] + (sign * B.matrix[i][j]);
      }
    }
}

int s21_zeroType(matrix_t A) {
  int flag = 1;
  if (A.rows > 0 && A.columns > 0) {
    for (int i = 0; i < A.rows; i++) {
      for (int j = 0; j < A.columns; j++) {
        flag = A.matrix[i][j] != 0 ? 0 : flag;
      }
    }
  }
  return flag;
}

int s21_sqareMatrix(matrix_t A) {
  int flag = 0;
  flag = A.rows == A.columns ? 1 : flag;
  flag = A.rows == 0 ? 0 : flag;
  return flag;
}

int s21_oneMatrix(matrix_t A) {
  int flag = 1;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      if (i == j && fabs(A.matrix[i][j]) - 1.0 > 1e-7 || A.matrix[i][j] < 0.0) {
        flag = 0;
      } else if (i != j && fabs(A.matrix[i][j]) > 1e-7) {
        flag = 0;
      }
    }
  }
  return flag;
}

void s21_setMatrixType(matrix_t *A) {
  if (s21_zeroType(*A) == 1) {
    A->matrix_type = ZERO_MATRIX;
  } else if (s21_oneMatrix(*A) == 1) {
    A->matrix_type = IDENTITY_MATRIX;
  } else {
    A->matrix_type = CORRECT_MATRIX;
  }
}

void s21_reducedMatrix(matrix_t A, matrix_t *tmp, int del_row, int del_column) {
  int new_rows = 0;
  int new_columns = 0;
  for (int i = 0; i < A.rows; i++) {
    if (i != del_row) {
      for (int j = 0; j < A.rows; j++) {
        if (j != del_column) {
          tmp->matrix[new_rows][new_columns] = A.matrix[i][j];
          new_columns++;
        }
      }
      new_rows++;
      new_columns = 0;
    }
  }
}

void s21_init_matrix(matrix_t *A, double num) {
  if (A->matrix_type != INCORRECT_MATRIX) {
    for (int i = 0; i < A -> rows; i++) {
      for (int j = 0; j < A -> columns; j++) {
        A -> matrix[i][j] = num;
      }
    }
    s21_setMatrixType(A);
  }
}

