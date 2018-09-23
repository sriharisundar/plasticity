#include "../../include/ellipticBVP.h"

template <int dim>
void ellipticBVP<dim>::reduceTimeIncrement(){

  unsigned int faceID,dof;
  pcout << "Reducing time increment\n";
  
  solution=oldSolution;
  solutionWithGhosts=oldSolution;

  delT=delT*userInputs.timeReductionFactor;

  remainIncrements=(totalT-currentT)/delT+currentIncrement;

  for(faceID=0;faceID<6;faceID++)
    for(dof=0;dof<3;dof++)
      deluConstraint[faceID][dof]=deluConstraint[faceID][dof]*userInputs.timeReductionFactor;

  delTreduced++;
}

#include "../../include/ellipticBVP_template_instantiations.h"
