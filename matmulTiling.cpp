#include <stdlib.h>
#include "matmul.h"

Matrix Allocate2ndMatrix(int height, int width, int init);

void matmul( float*, const float*, const float*, unsigned int, unsigned int, unsigned int);

////////////////////////////////////////////////////////////////////////////////
//! C = A * B
//! @param C          result matrix
//! @param A          matrix A 
//! @param B          matrix B
//! @param hA         height of matrix A
//! @param wB         width of matrix B
////////////////////////////////////////////////////////////////////////////////

/* You'll need to modify this function such that matrix B is accessed
 * correctly once you change the memory layout to column-major. */
void matmul(float* C, const float* A, const float* B, unsigned int hA, 
    unsigned int wA, unsigned int wB)
{
  for (unsigned int i = 0; i < (int)(hA/16); ++i) {                                   //Left to right tile index A
    for (unsigned int j = 0; j < (int)(wB/16); ++j) {                                 //Up to down tile index A
      for (unsigned int k = 0; k < (int)(wA/16); ++k) {                               //Up to down tile index of all
        //A[i-tile][k-tile]
        //B[j-tile][k-tile]
        //C[i-tile][j-tile]
        int AtileStart = (i * 16 * hA) + (k * 16);
        int BtileStart = (j * 16 * hB) + (k * 16);
        int CtileStart = (i * 16 * hA) + (j * 16);
        
        for (unsigned int l = 0; l < 16; ++l) {                                     //Up to down tile index B/C
          for (unsigned int m = 0; m < 16; ++m) {
            for (unsigned int n = 0; n < 16; ++n){

              double a = A[AtileStart + l + (n * hA)];
              //double a = A[(((i * 16) + l) * hA) + (k * 16) + m];
              double b = B[BtileStart + m + (n * hA)];
              //double b = B[(((j * 16) + l) * hA) + (k * 16) + m];
              C[CtileStart + (l * hA) + m] += a * b;
              // int Cind = (((i * 16) + l) * hA) + (j * 16) + m;
              // C[Cind] += a * b;
            }
          }  
        }
      }
      /*for (unsigned int k = 0; k < 16; ++k) {                                       //Left to right index within tile 0-15
        for (unsigned int l = 0; l < 16; ++l) {                                     //Up to down index within tile 0-15. At this point we have every index
          int indexA = (((i * 16) + k) * hA) + (j * 16) + l;                        //overall index, ordered from left to right up to down within each tile
          double a = A[indexA];                                                     //A[] at the specified index
          for (unsigned int m = 0; m < 16; ++m) {
            int indexBC = (((i * 16) + m) * hA) + (j * 16) + l;
            double b = B[indexBC];
            C[indexBC] +=

          }
        }      
      }*/
    }
  }
}
/*
double a = A[i * wA + k];
double b = B[j * wB + k];
sum += a * b;

double a = A[(((i * 16) + k) * wA) + (j * 16) + l];
double b = B[(((j * 16) + k) * wB) + (i * 16) + l];
C[(((i * 16) + k) * wB) + (j * 16) + l] += (float) a * b;


*/

// Allocate a matrix of dimensions height*width
Matrix Allocate2ndMatrix(int height, int width)
{
  Matrix M;
  M.width = M.pitch = width;
  M.height = height;
  int size = M.width * M.height;
  M.elements = NULL;

  M.elements = (float*) malloc(size*sizeof(float));

  /* This is a row-major allocation and initialization.
   * You need to modify this function which is only called
   * for Matrix B such that a column-major ordering is
   * performed. */
  for(unsigned int i = 0; i < M.height * M.width; i++)
  {
    M.elements[(i % M.width)* M.height + (int)( i / M.height)] = (rand() / (float)RAND_MAX);
  }
  return M;
}

