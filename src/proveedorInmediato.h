#ifndef _PROVEEDOR1_H_
#define _PROVEEDOR1_H_

#include <random>

#include "atomic.h"
#include "VTime.h"
#include "real.h"

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
    Port &entrega;
    const Port &pedido;

    enum State{
	  idle,
      serve,
    };
    State state;
    std::vector<VTime> productos;

    // Lifetime programmed since the last state transition to the next planned internal transition.    
    VTime sigma; 
    
    // Time elapsed since the last state transition until now
    VTime elapsed;
    
    // Time remaining to complete the last programmed Lifetime
    VTime timeLeft;
    
    double cantidad; //?
};

#endif
