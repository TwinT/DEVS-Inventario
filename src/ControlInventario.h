#ifndef _CONTROLINVENTARIO_H_
#define _CONTROLINVENTARIO_H_

#include "atomic.h"
#include "VTime.h"


#define CONTROL_INVENTARIO_NAME "ControlInventario"

class ControlInventario : public Atomic {
  public:
    ControlInventario(const string &name = CONTROL_INVENTARIO_NAME );
    virtual string className() const {return CONTROL_INVENTARIO_NAME;}
    enum class State {WAITING, QUERY, CALC};

  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &numProd_i;
    Port &queryInventory_o;
    Port &querySuppliers_o;

    VTime query_time;
    int quantity{0};
    int invStock{0};
    int n{50};     // Parámetro de la política de pedidos
    State state{State::WAITING};
    int N;
};

#endif
