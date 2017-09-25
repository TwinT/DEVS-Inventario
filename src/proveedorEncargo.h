#ifndef _PROVEEDOR_ENCARGO_H_
#define _PROVEEDOR_ENCARGO_H_

#include <random>
#include <vector>

#include "atomic.h"
#include "VTime.h"
#include "real.h"
#include "Product.h"

#define PROVEEDOR_ENCARGO_NAME "ProveedorEncargo"

class Distribution;

class ProveedorEncargo : public Atomic {
  public:
    
    ProveedorEncargo(const string &name = PROVEEDOR_ENCARGO_NAME );
    virtual string className() const {  return PROVEEDOR_ENCARGO_NAME ;}
    ~ProveedorEncargo();
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

    // Distribution
    int initial, increment;
    Distribution *dist;
    Distribution &distribution() {return *dist;}

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