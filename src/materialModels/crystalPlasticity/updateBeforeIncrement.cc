#include "../../../include/crystalPlasticity.h"

template <int dim>
void crystalPlasticity<dim>::updateBeforeIncrement()
{
    microvol=0.0;
	local_strain = 0.0;
	local_stress = 0.0;
	local_microvol = 0.0;

  FullMatrix<double> iMinusL,temp;


  // Fnew=inverse(I-L)*Fprev
  iMinusL=IdentityMatrix(dim);
  temp.reinit(dim,dim);

  F = 0.0;

  iMinusL.add(-1,this->targetVelGrad); //I-L
  temp.invert(iMinusL); //inverse(I-L)

  temp.mmult(this->F,this->Fprev); // F=inverse(I-L)*Fprev

  this->deltaF=this->F;
  this->deltaF.add(-1,this->Fprev); //deltaF=F-Fprev

  this->Fprev=this->F;


    //call base class project() function to project post processed fields
    //ellipticBVP<dim>::project();
}

#include "../../../include/crystalPlasticity_template_instantiations.h"
