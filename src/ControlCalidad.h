#ifndef _CONTROLINVENTARIO_H_
#define _CONTROLINVENTARIO_H_

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "ControlCalidad"


class ControlCalidad : public Atomic {
  public:
    ControlCalidad(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {return ATOMIC_MODEL_NAME;}
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
	std::vector<VTime> passProducts;
    State state = {State::WAITING};
};

#endif
