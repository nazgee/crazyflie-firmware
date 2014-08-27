/*
 * matrix.h
 *
 *  Created on: Aug 25, 2014
 *      Author: michal
 */

#include <stdint.h>
#include <hal/interface/imu_types.h>

#ifndef MATRIX_H_
#define MATRIX_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t matrix_sz;

typedef struct {
  matrix_sz rows;
  matrix_sz cols;
  float* data;
} MatrixObj;

void matrixMultiply(MatrixObj* a, MatrixObj* b, MatrixObj* out);
void calculateRotationMatrix(Axis3f* from, Axis3f* to, MatrixObj* res);

#ifdef __cplusplus
}
#endif

#endif /* MATRIX_H_ */
