#include "../../include/ellipticBVP.h"

void ellipticBVP::reduceTimeIncrement(){

  unsigned int faceID,dof;

  delT=delT/timereductionfactor;

  remainIncrements=(totalT-currentT)/delT+currentIncrement;

  for(faceID=0;faceID<6;faceID++)
    for(dof=0;dof<3;faceID++)
      deluConstraint[faceID][dof]=deluConstraint[faceID][dof]/2;

  delTreduced++;
}
