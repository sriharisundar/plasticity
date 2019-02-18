#include "../../include/crystalElement.h"

template <int dim>
void crystalPlasticity<dim>::updateBeforeIncrement()
{
  microvol=0.0;
	local_strain = 0.0;
	local_stress = 0.0;
	local_microvol = 0.0;
  if(this->userInputs.useVelocityGrad){

    FullMatrix<double> iMinusL,temp,temp1;


    // Fnew=inverse(I-L)*Fprev
    iMinusL=IdentityMatrix(dim);
    temp.reinit(dim,dim);
    temp1.reinit(dim,dim);

    F = 0.0;
    temp1=this->targetVelGrad;
    temp1*=this->delT;

    iMinusL.add(-1,temp1); //I-L
    temp.invert(iMinusL); //inverse(I-L)

    temp.mmult(this->F,this->Fprev); // F=inverse(I-L)*Fprev

    this->deltaF=this->F;
    this->deltaF.add(-1,this->Fprev); //deltaF=F-Fprev

    this->Fprev=this->F;
  }
    //call base class project() function to project post processed fields
    //ellipticBVP<dim>::project();
}

#include "../../include/crystalElement_template_instantiations.h"
