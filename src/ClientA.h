#ifndef _CLIENTA_H_
#define _CLIENTA_H_

#include "atomic.h"
#include "VTime.h"

#define ATOMIC_MODEL_NAME "ClientA"


class Pulse : public Atomic {
  public:
    
    Pulse(const string &name = ATOMIC_MODEL_NAME );
    virtual string className() const {  return ATOMIC_MODEL_NAME ;}
  
  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    const Port &start;
    const Port &stop;
    Port &out;

    VTime frequency_time;
    bool on;

    std::uniform_int_distribution<int> dist;
    std::mt19937 rng;
};

#endif
