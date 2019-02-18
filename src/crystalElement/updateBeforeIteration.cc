#include "../../include/crystalElement.h"

template <int dim>
void crystalPlasticity<dim>::updateBeforeIteration()
{
    local_Truestrain = 0.0;
    local_strain=0.0;
    local_stress=0.0;
    local_microvol=0.0;

    //call base class project() function to project post processed fields
    //ellipticBVP<dim>::project();
}

#include "../../include/crystalElement_template_instantiations.h"
