/*
 * matrix.c
 *
 *  Created on: Aug 25, 2014
 *      Author: michal
 */

#include "matrix.h"
#include "lib/mathlib/Vector3D.h"

extern "C"
void matrixMultiply(MatrixObj* a, MatrixObj* b, MatrixObj* out) {
  matrix_sz c, d, k = 0;
  float sum;

  if (a->cols != b->rows || a->rows != out->rows || b->cols != out->cols) {
	while(1);
    return;
  }

  for (c = 0; c < a->rows; c++) {
    for (d = 0; d < b->cols; d++) {
      for (k = 0; k < b->rows; k++) {
        sum = sum + (*(a->data + c*a->cols + k)) * (*(b->data + k*b->cols + d));
      }

      *(out->data + c*out->cols + d) = sum;
      sum = 0;
    }
  }
}

static void getMatrixFromAxisAngle(Axis3f* axis, float angle, MatrixObj* m) {
    float c = cos(angle);
    float s = sin(angle);
    float t = 1.0 - c;

    m->data[0 * m->rows + 0] = c + axis->x*axis->x*t;
    m->data[1 * m->rows + 1] = c + axis->y*axis->y*t;
    m->data[2 * m->rows + 2] = c + axis->z*axis->z*t;

    float tmp1 = axis->x*axis->y*t;
    float tmp2 = axis->z*s;
    m->data[1 * m->rows + 0] = tmp1 + tmp2;
    m->data[0 * m->rows + 1] = tmp1 - tmp2;
    tmp1 = axis->x*axis->z*t;
    tmp2 = axis->y*s;
    m->data[2 * m->rows + 0]  = tmp1 - tmp2;
    m->data[0 * m->rows + 2]  = tmp1 + tmp2;
    tmp1 = axis->y*axis->z*t;
    tmp2 = axis->x*s;
    m->data[2 * m->rows + 1]  = tmp1 + tmp2;
    m->data[1 * m->rows + 2]  = tmp1 - tmp2;
}

extern "C"
void calculateRotationMatrix(Axis3f* from, Axis3f* to, MatrixObj* res) {
	MATHLIB3D::Vector3D v3from(from->x, from->y, from->z);
	MATHLIB3D::Vector3D v3to(to->x, to->y, to->z);
	v3from.SetNormalized();
	v3to.SetNormalized();

	float rotationAngle = v3from.GetAngle(v3to);

	MATHLIB3D::Vector3D v3rotationAxis;
	v3rotationAxis.SetCross(v3from, v3to);
	v3rotationAxis.SetNormalized();

	getMatrixFromAxisAngle((Axis3f*)(&v3rotationAxis.x), rotationAngle, res);
}

