#ifndef _CLIENTC_H_
#define _CLIENTC_H_

#include <random>

#include "atomic.h"
#include "VTime.h"
#include "distri.h"        // class Distribution 


#define CLIENT_C_NAME "ClientC"


class ClientC : public Atomic {
  public:
    
    ClientC(const string &name = CLIENT_C_NAME );
    virtual string className() const {  return CLIENT_C_NAME ;}
    enum class StateClient {IDLE, QUERY, ACCEPT, DECLINE};
  
  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &disponibles_i; // respuesta de cantidad de productos disponibles
    Port &query_o;       // consulta de disponibilidad de productos
    Port &pedido_o;      // cantidad de productos pedidos

    // Lifetime programmed since the last state transition to the next planned internal transition.
    VTime sigma;
	
    // Time elapsed since the last state transition until now
    VTime elapsed;
	
    // Time remaining to complete the last programmed Lifetime
    VTime timeLeft;	

    VTime query_time;
    StateClient stateC{StateClient::IDLE};

    Real inStock{0}; // lo que me dijeron que está disponible
    Real lastQuery{0}; // lo que pedi

    // Distribution
    int initial, increment;
    Distribution *dist ;
    std::discrete_distribution<int> distval; // para generar numquery
    std::mt19937 rng;
};

#endif
