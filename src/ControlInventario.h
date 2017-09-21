#ifndef _CONTROLINVENTARIO_H_
#define _CONTROLINVENTARIO_H_

#include "atomic.h"
#include "VTime.h"


#define ATOMIC_MODEL_NAME "ControlInventario"

#define S 200 // Inventario máximo

class ControlInventario : public Atomic {
  public:
    ControlInventario(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {return ATOMIC_MODEL_NAME;}
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
    int s{50};     // Parámetro de la política de pedidos
    State state{State::WAITING};
};

#endif
