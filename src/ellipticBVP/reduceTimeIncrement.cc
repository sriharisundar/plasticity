#include "../../include/ellipticBVP.h"

template <int dim>
void ellipticBVP<dim>::reduceTimeIncrement(){

  unsigned int faceID,dof;

  solution=oldSolution;
  solutionWithGhosts=oldSolution;

  delT=delT*userInputs.timeReductionFactor;

  remainIncrements=(totalT-currentT)/delT+currentIncrement;

  for(faceID=0;faceID<6;faceID++)
    for(dof=0;dof<3;faceID++)
      deluConstraint[faceID][dof]=deluConstraint[faceID][dof]*userInputs.timeReductionFactor;

  delTreduced++;
  resetIncrement=false;
}

#include "../../include/ellipticBVP_template_instantiations.h"
