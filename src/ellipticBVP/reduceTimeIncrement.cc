#include "../../include/ellipticBVP.h"

void ellipticBVP::reduceTimeIncrement(){

  unsigned int faceID,dof;

  delT=delT/2;
  
  remainIncrements=(totalT-currentT)/delT;

  for(faceID=0;faceID<6;faceID++)
    for(dof=0;dof<3;faceID++)
      deluConstraint[faceID][dof]=deluConstraint[faceID][dof]/2;


}
