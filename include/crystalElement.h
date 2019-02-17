//implementation of the crystal plasticity material model for FCC crystal structure
#ifndef CRYSTALELEMENT_H
#define CRYSTALELEMENT_H

//dealii headers
//dealii headers
//dealii headers
#include "dealIIheaders.h"
#include "userInputParameters.h"

using namespace dealii;

//compiler directives to handle warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic pop

//define data types
typedef PETScWrappers::MPI::Vector vectorType;
typedef PETScWrappers::MPI::SparseMatrix matrixType;
//LA::MPI::SparseMatrix

//material model class for crystal plasticity
//derives from ellipticBVP base abstract class
template <int dim>
class crystalElement : public Subscriptor
{
 public:
  /**
   *crystalPlasticity class constructor.
   */
   void output(Vector<double> &U);
};

#endif
