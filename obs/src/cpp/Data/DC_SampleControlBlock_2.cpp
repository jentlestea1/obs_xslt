  
//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SampleControlBlock_2.cpp
//
// This file was automatically generated by an XSL program

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"  
#include "../Data/DataPool.h" 
#include "../Data/DataPoolControlBlock.h"
#include "../Data/DC_SampleControlBlock_2.h"

DC_SampleControlBlock_2::DC_SampleControlBlock_2(void) {
      setNumberOfInputs(1);
      setNumberOfOutputs(1);
      setNumberOfParameters(1);
      setNumberOfStates(0);
      // Update the number of states (if necessary) and insert any other application-specific code here
}
    
void DC_SampleControlBlock_2::propagateState(void) {
      return;
      // remove previous statement and insert application-specific code here
}

void DC_SampleControlBlock_2::updateOutput(void) {

      return;
      // remove previous statements and insert application-specific code here
}

void DC_SampleControlBlock_2::reset(void) {
      return;
      // remove previous statement and insert application-specific code here
}
    

            