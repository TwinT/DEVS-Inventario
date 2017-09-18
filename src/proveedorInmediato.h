#ifndef _PROVEEDOR1_H_
#define _PROVEEDOR1_H_

#include <random>

#include "atomic.h"

#define ATOMIC_MODEL_NAME "ProveedorInmediato"

class ProveedorInmediato : public Atomic {
  public:
    
    ProveedorInmediato(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}
    ~ProveedorInmediato();
  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &pedido;
    Port &entrega;

    // Lifetime programmed since the last state transition to the next planned internal transition.    
    Time sigma; 
    
    // Time elapsed since the last state transition until now
    Time elapsed;
    
    // Time remaining to complete the last programmed Lifetime
    Time timeLeft;  
};

#endif