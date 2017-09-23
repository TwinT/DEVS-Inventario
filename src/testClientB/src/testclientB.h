#ifndef _TEST_H_
#define _TEST_H_

#include <random>

#include "atomic.h"
#include "VTime.h"
#include "distri.h"        // class Distribution 


#define ATOMIC_MODEL_NAME "TestClientB"


class TestClientB : public Atomic {
  public:
    
    TestClientB(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}
  
  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &query_i; // consulta de disponibilidad de productos
    Port &available_o;   // respuesta de cantidad de productos disponibles
    // Lifetime programmed since the last state transition to the next planned internal transition.
    VTime sigma;
	
    // Time elapsed since the last state transition until now
    VTime elapsed;
	
    // Time remaining to complete the last programmed Lifetime
    VTime timeLeft;	

    Real pedido{0};

};

#endif
