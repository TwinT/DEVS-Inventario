#include <algorithm>            // std::min_element
#include <vector>               // std::vector
#include "Inventario.h"			    // base header
#include "message.h"            // InternalMessage ....
#include "distri.h"             // class Distribution 
#include "strutil.h"            // str2Value( ... )
#include "parsimu.h"            // class Simulator

/*******************************************************************
* Function Name: Inventario
* Description: constructor
********************************************************************/
Inventario::Inventario(const string &name)
: Atomic( name )
 , producto_out(addOutputPort("producto_out"))
 , query_out(addOutputPort("query_out"))

 , producto_in_A(addInputPort("producto_in_A"))
 , producto_in_B(addInputPort("producto_in_B"))
 , producto_in_C(addInputPort("producto_in_C"))
 , encargo(addInputPort("encargo"))
 , query_in(addInputPort("query_in"))
 , get(addInputPort("get"))
 , cola(), colaA(), colaB(), colaC()
 , encargos_q(0), query_q(0), get_q(0)
{
	try{
		if( ParallelMainSimulator::Instance().existsParameter(description(), "N")){
			N = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "N" ));
		}
		else{
			N = 100;
		}
	} catch(MException &e){
		MTHROW(e);
	}
	cout << "Inventario Creado" << endl;
	
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Inventario::initFunction()
{
	this->elapsed = VTime::Zero;
  this->timeLeft = VTime::Inf;
  this->sigma = VTime::Inf; // stays in active state until an external event occurs;
    
  state = State::idle;
  cout << "Inventario - Init finalizado" << endl;

  holdIn(AtomicState::active, this->sigma);
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Inventario::externalFunction( const ExternalMessage &msg )
{
	this->sigma = nextChange();	
	this->elapsed = msg.time()-lastChange();	
  this->timeLeft = this->sigma - this->elapsed; 
	
  state = State::idle;    

	if (msg.port() ==  producto_in_A){

		Tuple<Product> t = Tuple<Product>::from_value(msg.value());
		for(int i = 0; i < t.size() ; i++){
			colaA.push(Real::from_value(t[i]));		
		}
    this->sigma = VTime::Inf; 
	}

  if (msg.port() ==  producto_in_B){
    Tuple<Product> t = Tuple<Product>::from_value(msg.value());
    for(int i = 0; i < t.size() ; i++){
      colaB.push(Real::from_value(t[i]));   
    }
    this->sigma = VTime::Inf; 
  }

  if (msg.port() ==  producto_in_C){
    Tuple<Product> t = Tuple<Product>::from_value(msg.value());
    for(int i = 0; i < t.size() ; i++){
      colaC.push(Real::from_value(t[i]));   
    }
    this->sigma = VTime::Inf; 
  }

  int nuevos = 0;
  
  while(!colaA.empty() and !colaB.empty() and !colaC.empty()){
    vector<Product> partes;
    partes.push_back(colaA.front());
    partes.push_back(colaB.front());
    partes.push_back(colaC.front());
    colaA.pop();
    colaB.pop();
    colaC.pop();

    Product resultante = *std::min_element(partes.begin(),partes.end());
    cola.push(resultante);
    nuevos++;
  }

  if(nuevos){
    cout << msg.time() << " Inventario - Nuevos: " << nuevos <<  endl;
    state = State::push;    
    this->sigma = VTime::Zero; 
  }

	if (msg.port() ==  query_in){
    query_q = static_cast<int>(Real::from_value(msg.value()).value());
		state = State::query;
    this->sigma = VTime::Zero; 
	}

	if (msg.port() ==  encargo){
    encargos_q += static_cast<int>(Real::from_value(msg.value()).value());
		state = State::encargo;
    this->sigma = VTime::Zero; 
	}

	if (msg.port() ==  get){
    get_q = static_cast<int>(Real::from_value(msg.value()).value());   
		state = State::get;
	  this->sigma = VTime::Zero; 
	}

  holdIn(AtomicState::active, this->sigma); 

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Inventario::internalFunction(const InternalMessage &msg )
{
	switch(state)
  {
		case State::idle:
      this->sigma = VTime::Inf;
			break;
		case State::query:
      state = State::idle;
      this->sigma = VTime::Inf;
			break;		
		case State::encargo:
      state = State::idle;
      this->sigma = VTime::Inf;
			break;
		case State::get:
      state = State::idle;
      this->sigma = VTime::Inf;
			break;		
		case State::push:
      state = State::idle;
      this->sigma = VTime::Inf;
			break;		
		default:
      state = State::idle;
      this->sigma = VTime::Inf;
			break;		
	}
	holdIn(AtomicState::active, this->sigma);
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Inventario::outputFunction(const CollectMessage &msg)
{
	switch(state)
  {
		case State::idle:
			break;

		case State::query:
      {
      int N = static_cast<int>(cola.size());
      sendOutput(msg.time(), query_out, Real(N - encargos_q));
      cout << msg.time() << " Inventario - Query out(N - E): " << Real(N - encargos_q) <<  endl;
      cout << msg.time() << " Inventario - Cola(N): " << Real(N) <<  endl;
      }
			break;		

		case State::encargo:
      cout << msg.time() << " Inventario - Encargos(E): " << encargos_q <<  endl;
			break;

		case State::get:
      {
      std::vector<Product> productos;

      int i = 0;
      for(;(cola.size() != 0) && (i < get_q); i++){
        productos.push_back(cola.front()); 
        cola.pop();   
      }
      if(i != get_q){
        // No alcanzaron los productos
        productos.push_back(Real(0));
      }

      Tuple<Product> t(&productos);
      sendOutput(msg.time(), producto_out, t);
      cout << msg.time() << " Inventario - " << "Entrega: " << t <<  endl;
      }
			break;		

		case State::push:
      {
      if(encargos_q){
        std::vector<Product> productos;
        while(cola.size() != 0 && encargos_q){
          productos.push_back(cola.front()); 
          cola.pop();
          --encargos_q;  
        }

        Tuple<Product> t(&productos);
        sendOutput(msg.time(), producto_out, t);
        cout << msg.time() << " Inventario - Encargos despachados:" << productos.size() <<  endl;
        cout << msg.time() << " Inventario - Encargos en cola:" << encargos_q <<  endl;
      }
      cout << msg.time() << " Inventario - Hay en cola N:" << cola.size() <<  endl;
      }
			break;	

		default:
			break;	
	}

	return *this;

}

Inventario::~Inventario()
{}
