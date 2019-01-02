//constructor and destructor for ellipticBVP class
#include "../../include/ellipticBVP.h"

//constructor
template <int dim>
ellipticBVP<dim>::ellipticBVP (userInputParameters _userInputs):
  Subscriptor(),
  mpi_communicator (MPI_COMM_WORLD),
  userInputs(_userInputs),
  triangulation (mpi_communicator,
		 typename Triangulation<dim>::MeshSmoothing
		 (Triangulation<dim>::smoothing_on_refinement |
		  Triangulation<dim>::smoothing_on_coarsening)),
  FE (FE_Q<dim>(_userInputs.feOrder), dim),
  FE_Scalar (FE_Q<dim>(_userInputs.feOrder), 1),
  F(dim,dim),
  Fprev(dim,dim),
  deltaF(dim,dim),
  targetVelGrad(dim,dim),
  dofHandler (triangulation),
  dofHandler_Scalar (triangulation),
  delT(_userInputs.delT),
  totalT(_userInputs.totalTime),
  currentT(0),
  currentIteration(0),
  currentIncrement(0),
  resetIncrement(false),
  loadFactorSetByModel(1.0),
  totalLoadFactor(0.0),
  pcout (std::cout, Utilities::MPI::this_mpi_process(MPI_COMM_WORLD)==0),
  computing_timer (pcout, TimerOutput::summary, TimerOutput::wall_times),
  numPostProcessedFields(0),
  delTreduced(0)
{
  //Nodal Solution names - this is for writing the output file
  for (unsigned int i=0; i<dim; ++i){
    nodal_solution_names.push_back("u");
    nodal_data_component_interpretation.push_back(DataComponentInterpretation::component_is_part_of_vector);
  }
  if(userInputs.enableCyclicLoading)
    cycleTime=4*userInputs.quarterCycleTime;
  remainIncrements=totalT/delT;
}

//destructor
template <int dim>
ellipticBVP<dim>::~ellipticBVP ()
{
}

#include "../../include/ellipticBVP_template_instantiations.h"
