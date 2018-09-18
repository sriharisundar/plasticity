//methods to allow for pre/post iteration level updates
#include "../../include/ellipticBVP.h"

//method called before each iteration
template <int dim>
void ellipticBVP<dim>::updateBeforeIteration(){
  //default method does nothing
}

//method called after each iteration
template <int dim>
void ellipticBVP<dim>::updateAfterIteration(){
  //default method does nothing
}

#include "../../include/ellipticBVP_template_instantiations.h"
