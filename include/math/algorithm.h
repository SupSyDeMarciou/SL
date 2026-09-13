#ifndef _SL_ALGORITHM_H_
#define _SL_ALGORITHM_H_

#include <complex.h>

#include "math.h"
#include "vector.h"
#include "quaternion.h"
#include "matrix.h"

bool fmSolve_pivot(fm lhs, fv* rhs);
bool fmSolve_GaussSeidel(fm lhs, fv* rhs, float* x, float maxError, uint maxIter);



// double *fft(double *p, usize count, usize start, usize stride)
// {
//     if (count == 1) return p;

//     complex omega = cexp(SL_TAU * 1.0iF / count);

// }



#ifdef SL_IMPLEMENTATION
// Row reduction algorithm (I think)
// /!\ O(n^3), really slow for big systems (n = systemMatrix.r)
bool fmSolve_pivot(fm lhs, fv* rhs) {

    usize r = lhs.r;
    usize c = lhs.c;
    if (r != c || r != rhs->count) return __SL_ERROR(SL_ERR_MISSMATCHING_DIMENSIONS), false;

    // Make diagonal 1 and triangular
    for (usize t = 0; t < c; t++) {

        float vtt = SL_mget(lhs, t, t);
        if (vtt == 0.0) { // We have to find another factor for term t
            usize nt = 0;
            for (; nt < r && SL_mget(lhs, nt, t) == 0.0; nt++);

            // The entire column is 0
            if (nt >= r) __SL_ERROR(SL_ERR_DIVISION_BY_ZERO), false;

            // Set (t, t) to one using this new-found row
            float l = 1.0 / SL_mget(lhs, nt, t);
            for (usize j = t; j < c; j++) SL_mget(lhs, t, j) += l * SL_mget(lhs, nt, j);
            rhs->data[t] += rhs->data[nt] * l;
        }
        else { // Just divide the entire row
            float l = 1.0 / vtt;
            for (usize j = t; j < c; j++) SL_mget(lhs, t, j) *= l;
            rhs->data[t] *= l;
        }

        // Set all value under (t, t) to zero
        for (usize i = t + 1; i < r; i++) {
            float l = SL_mget(lhs, i, t); // Scalar for entire row
            if (l == 0.0) continue; // There is nothing to remove here

            for (usize j = t; j < r; j++) SL_mget(lhs, i, j) -= SL_mget(lhs, t, j) * l;
            rhs->data[i] -= rhs->data[t] * l;
        }
    }

    // Make diagonal
    for (usize j = c - 1; j > 0; j--) {
        for (usize i = 0; i < j; i++) {
            rhs->data[i] -= SL_mget(lhs, i, j) * rhs->data[j];
            SL_mget(lhs, i, j) = 0.0;
        }
    }

    // Tada!!!
    return true;
}
bool fmSolve_GaussSeidel(fm lhs, fv* rhs, float* x, float maxError, uint maxIter) {

    int size = lhs.r;
    if (lhs.c != size || rhs->count != size) return __SL_ERROR(SL_ERR_MISSMATCHING_DIMENSIONS), false;
    size = lhs.r;

    if (!x) x = (float*)malloc(sizeof(usize) + sizeof(float) * size);

    for (usize k = 0; k < maxIter; k++) {
        // Calc next generation
        for (usize i = 0; i < size; i++) {
            float new = rhs->data[i];

            usize j = 0;
            for (; j < i; j++) new -= SL_mget(lhs, i, j) * x[j]; // x[j] k+1
            for (j++; j < size; j++) new -= SL_mget(lhs, i, j) * x[j]; // x[j] k
            
            float vii = SL_mget(lhs, i, i);
            if (vii == 0.0) return __SL_ERROR(SL_ERR_DIVISION_BY_ZERO), false;
            x[i] = new / vii;
        }

        // Calc error
        float e = 0.0;
        for (usize i = 0; i < size; i++) {
            float dist = -rhs->data[i];
            for (usize j = 0; j < size; j++) dist += SL_mget(lhs, i, j) * x[j];
            float newError = fabs(dist);
            e = fmax(e, newError);
            if (e > maxError) goto NEXT;
        }
        if (e <= maxError) break;
        NEXT:
    }

    return x;
}
#endif
#endif // _SL_ALGORITHM_H_