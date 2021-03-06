#ifndef _CONTROLCALIDAD_H_
#define _CONTROLCALIDAD_H_

#include "atomic.h"
#include "VTime.h"


#define CONTROLCALIDAD_NAME "ControlCalidad"


class ControlCalidad : public Atomic {
  public:
    ControlCalidad(const string &name = CONTROLCALIDAD_NAME );
    virtual string className() const {return CONTROLCALIDAD_NAME;}
    enum class State {WAITING, CHECK, QUERY, INV_WAIT, SEND};

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &prod_i;
    const Port &queryClient_i;
    Port &queryInventory_o;
    Port &prod_o;
	
	double numClientQuery{0};
	double numPassProd{0};
	std::vector<Real> passProducts;
    State state = {State::WAITING};
    bool invEmpty{false};	//Flag to inform when invetory is empty
    int numRejectProd{0};
};

#endif
