//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyManoeuvre.h
//
// Version	1.0
// Date		11.04.03
// Author	A. Pasetti (P&P Software)

#ifndef DC_DummyManoeuvreH
#define DC_DummyManoeuvreH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "Manoeuvre.h"

/**
 * Dummy implementation of the <code>Manoeuvre</code> abstract class 
 * to be used for testing purposes.
 * This class provides dummy implementation for the abstract methods
 * declared by its base class. It does not implement any behaviour 
 * beyond that which it inherits from its base class.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_DummyManoeuvre: public Manoeuvre {

protected:

  /**
  * Implement a dummy continuation action. This method returns without
  * doing anything.
  * @see Manoeuvre#doContinue
  */
  virtual void doInternalContinue(void);

public:

  /**
  * Construct a dummy manoeuvre. The class identifier is set.
  */
  DC_DummyManoeuvre(void);

  /**
  * Implement a dummy termination check that always returns 
  * "manoeuvre can terminate". 
  * @return true if the manoeuvre has terminated execution
  */
  virtual bool isFinished(void);

};

#endif

