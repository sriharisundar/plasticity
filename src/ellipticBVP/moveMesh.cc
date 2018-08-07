#include "../../include/ellipticBVP.h"

template <int dim>
void ellipticBVP<dim>::moveMesh (){

  pcout << "Moving mesh" << std::endl;
  std::vector<bool> vertex_touched (triangulation.n_vertices(),
                                    false);
  typename DoFHandler<dim>::active_cell_iterator cell = dofHandler.begin_active(), endc = dofHandler.end();
  for (; cell!=endc; ++cell) {
    if (cell->is_locally_owned()){
      for (unsigned int v=0; v<GeometryInfo<dim>::vertices_per_cell; ++v)
        if (vertex_touched[cell->vertex_index(v)] == false)
          {
            vertex_touched[cell->vertex_index(v)] = true;
            Point<dim> vertex_displacement;
            for (unsigned int d=0; d<dim; ++d){
              vertex_displacement[d]
                = solutionWithGhosts(cell->vertex_dof_index(v,d));
              pcout<<vertex_displacement[d]<<" ";}
            pcout<<"\n";
            //cell->vertex(v) += vertex_displacement;
          }
    }
  }

  cell = dofHandler_Scalar_moveMesh.begin_active();
  endc = dofHandler_Scalar_moveMesh.end();
  for (; cell!=endc; ++cell) {
    if (cell->is_locally_owned()){
      for (unsigned int v=0; v<GeometryInfo<dim>::vertices_per_cell; ++v)
        if (vertex_touched[cell->vertex_index(v)] == false)
          {
            vertex_touched[cell->vertex_index(v)] = true;
            Point<dim> vertex_displacement;
            for (unsigned int d=0; d<dim; ++d)
              vertex_displacement[d]
                = solutionIncWithGhosts(cell->vertex_dof_index(v,d));
            cell->vertex(v) += vertex_displacement;
          }
    }
  }
}

#include "../../include/ellipticBVP_template_instantiations.h"
