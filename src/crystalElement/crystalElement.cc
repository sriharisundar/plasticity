#include "../../include/crystalElement.h"
#include <iostream>

//constructor
template <int dim>
void crystalElement<dim>::output(Vector<double> &U){
  char ch;
  U.print(std::cout, 15,10);
  std::cin>>ch;
}

#include "../../include/crystalElement_template_instantiations.h"
