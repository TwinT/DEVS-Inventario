#ifndef _INVENTARIO_H_
#define _INVENTARIO_H_

#include <random>
#include <queue>

#include "atomic.h"
#include "VTime.h"
#include "real.h"
#include "Product.h"

#define INVENTARIO_NAME "Inventario"

class ProveedorEncargo : public Atomic {
  public:
    
    ProveedorEncargo(const string &name = INVENTARIO_NAME );
    virtual string className() const {  return INVENTARIO_NAME ;}
    ~ProveedorEncargo();
  protected:
    Model &initFunction();
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const CollectMessage & );

  private:
    Port &producto_out;
    Port &query_out;
    const Port &producto_in;
    const Port &encargo;
    const Port &query_in;
    const Port &get;

    enum class State{
      idle,
      query,
      encargo,
      push,
      get
    };
    State state;

    // contiene los vencimientos de cada producto en ms
    // Usar VTime::makeFrom() para convertir a VTime
    // Usar VTime::asMsecs() para convertir a float
    std::queue<Product> cola; 
    int N; // tamaño de la cola

    // Lifetime programmed since the last state transition to the next planned internal transition.    
    VTime sigma; 
    
    // Time elapsed since the last state transition until now
    VTime elapsed;
    
    // Time remaining to complete the last programmed Lifetime
    VTime timeLeft;  
};

#endif