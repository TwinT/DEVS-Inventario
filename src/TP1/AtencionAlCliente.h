#ifndef _ATENCIONALCLIENTE_H_
#define _ATENCIONALCLIENTE_H_

#include "atomic.h"
#include "VTime.h"


#define ATENCIONALCLIENTE_NAME "AtencionAlCliente"


class AtencionAlCliente : public Atomic {
  public:
    AtencionAlCliente(const string &name = ATENCIONALCLIENTE_NAME );
    virtual string className() const {return ATENCIONALCLIENTE_NAME;}
    enum class State {WAITING, QUERY, INV_WAIT, CLI_RPLY, SEND, CLI_WAIT, INV_GET};

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &numProdClient_i;
    const Port &queryClient_i;
    const Port &queryInventory_i;
    Port &queryInventory_o;
    Port &prodInventory_o;
    Port &queryClient_o;
    
    State state{State::WAITING};
	
	double queryClient, inventoryStock, productsBuyed;
};

#endif
