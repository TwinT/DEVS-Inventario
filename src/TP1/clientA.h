#ifndef _CLIENTA_H_
#define _CLIENTA_H_

#include <random>

#include "atomic.h"
#include "VTime.h"
#include "distri.h"        // class Distribution 


#define CLIENT_A_NAME "ClientA"


class ClientA : public Atomic {
  public:
    
    ClientA(const string &name = CLIENT_A_NAME );
    virtual string className() const {  return CLIENT_A_NAME ;}
  
  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    Port &query_o; // pedido de productos

    // Lifetime programmed since the last state transition to the next planned internal transition.
    VTime sigma;
	
    // Time elapsed since the last state transition until now
    VTime elapsed;
	
    // Time remaining to complete the last programmed Lifetime
    VTime timeLeft;	

    VTime query_time;


    // Distribution
    int initial, increment;
    Distribution *dist ;
    std::discrete_distribution<int> distval; // para generar numquery
    std::mt19937 rng;
};

#endif
