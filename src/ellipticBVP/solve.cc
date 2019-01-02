//solve method for ellipticBVP class
#include "../../include/ellipticBVP.h"

//loop over increments and solve each increment
template <int dim>
void ellipticBVP<dim>::solve(){
  pcout << "begin solve...\n\n";
  pcout<< currentT<<" "<<totalT<<"\n";
  //load increments
  unsigned int successiveIncs=0;

  if(userInputs.enableAdaptiveTimeStepping){
    for (;totalLoadFactor<remainIncrements;){
      ++currentIncrement;
      loadFactorSetByModel=std::min(loadFactorSetByModel, remainIncrements-totalLoadFactor);
      pcout << "\nincrement: "  << currentIncrement << std::endl;
      char buffer[100];
      sprintf(buffer, "current load factor: %12.6e\ntotal load factor:   %12.6e\n", loadFactorSetByModel, totalLoadFactor);
      pcout << buffer;

      //call updateBeforeIncrement, if any
      updateBeforeIncrement();

      //solve time increment
      bool success=solveNonLinearSystem();

      //call updateAfterIncrement, if any
      if (success){
      computing_timer.enter_section("updateAfterIncrement");
      updateAfterIncrement();
      computing_timer.exit_section("updateAfterIncrement");

        //update totalLoadFactor
        totalLoadFactor+=loadFactorSetByModel;

        //increase loadFactorSetByModel, if succesiveIncForIncreasingTimeStep satisfied.
        successiveIncs++;

        if (successiveIncs>=userInputs.succesiveIncForIncreasingTimeStep){
          loadFactorSetByModel*=userInputs.adaptiveLoadIncreaseFactor;
          char buffer1[100];
        	sprintf(buffer1, "current increment increased. Restarting increment with loadFactorSetByModel: %12.6e\n", loadFactorSetByModel);
        	pcout << buffer1;
        }


        if (currentIncrement%userInputs.skipOutputSteps==0)
          if (userInputs.writeOutput){
      computing_timer.enter_section("postprocess");
	output();
              computing_timer.exit_section("postprocess");}
}
      else{
        successiveIncs=0;
      }
    }
    char buffer[100];
    sprintf(buffer, "\nfinal load factor  : %12.6e\n", totalLoadFactor);
    pcout << buffer;
  }
  else
    while(currentT<totalT){
    pcout << "\Current time: "  << currentT << std::endl;
    //call updateBeforeIncrement, if any
    updateBeforeIncrement();

    //solve time increment
    bool success=solveNonLinearSystem();

    //call updateAfterIncrement, if any
    if (success){
      computing_timer.enter_section("updateAfterIncrement");
      updateAfterIncrement();
      computing_timer.exit_section("updateAfterIncrement");

      //update totalLoadFactor
      totalLoadFactor+=loadFactorSetByModel;

      //increase loadFactorSetByModel, if succesiveIncForIncreasingTimeStep satisfied.
      successiveIncs++;
      currentT+=delT;
      //output results to file

      if (currentIncrement%userInputs.skipOutputSteps==0)
        if (userInputs.writeOutput){
	computing_timer.enter_section("postprocess");
      	output();
	computing_timer.exit_section("postprocess");}
      }
    else{
      if(userInputs.reduceTimeIncrement && delTreduced<userInputs.numberofDelTReductions)
        reduceTimeIncrement();
      else if(userInputs.stopOnConvergenceFailure){
        pcout<<"Problem doesn't converge after time step reductions";
        exit(1);
      }

      successiveIncs=0;
      continue;
    }

    ++currentIncrement;
  }
}
#include "../../include/ellipticBVP_template_instantiations.h"
