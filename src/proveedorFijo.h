#ifndef _PROVEEDOR_FIJO_H_
#define _PROVEEDOR_FIJO_H_

#include <random>
#include <vector>

#include "atomic.h"
#include "VTime.h"
#include "real.h"
#include "Product.h"

#define PROVEEDOR_FIJO_NAME "ProveedorFijo"

class ProveedorFijo : public Atomic {
  public:
    
    ProveedorFijo(const string &name = PROVEEDOR_FIJO_NAME );
    virtual string className() const {  return PROVEEDOR_FIJO_NAME ;}
    ~ProveedorFijo();
  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    Port &entrega;
    const Port &pedido;

    enum State{
	  idle,
      serve,
    };
    State state;

    int productos_por_paquete;
    // contiene los vencimientos de cada producto en ms
    // Usar VTime::makeFrom() para convertir a VTime
    // Usar VTime::asMsecs() para convertir a float
    std::vector<Product> productos; 

    // Lifetime programmed since the last state transition to the next planned internal transition.    
    VTime sigma; 
    
    // Time elapsed since the last state transition until now
    VTime elapsed;
    
    // Time remaining to complete the last programmed Lifetime
    VTime timeLeft;  
};

#endif