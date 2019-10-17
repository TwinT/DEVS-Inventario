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

 , producto_in(addInputPort("producto_in"))
 , query_in(addInputPort("query_in"))
 , get_in(addInputPort("get_in"))
 , cola()
 , query_q(0), get_q(0)
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
	cout << "Inventario Creado" << " (N = " << N << ")"<< endl;
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
  
	if (msg.port() ==  producto_in){
		Tuple<Product> t = Tuple<Product>::from_value(msg.value());
    cout << msg.time() << " Inventario - Entran " << t.size() << " productos" << endl;
		for(unsigned long int i = 0; i < t.size(); i++){
			cola.push(Real::from_value(t[i]));		
		}
    state = State::push;   
    this->sigma = VTime::Zero; 
  } else if (msg.port() ==  query_in){
    query_q = static_cast<int>(Real::from_value(msg.value()).value());
    state = State::query;
    this->sigma = VTime::Zero; 
  } else if (msg.port() ==  get_in){
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

		case State::query:{
      int N = static_cast<int>(cola.size());
      sendOutput(msg.time(), query_out, Real(N));
      cout << msg.time() << " Inventario - Cola(N): " << Real(N) <<  endl;
      }
			break;		

		case State::get:{
      std::vector<Product> productos;
      for(int i = 0; (cola.size() != 0) && (i < get_q); i++){
        productos.push_back(cola.front()); 
        cola.pop();   
      }

      Tuple<Product> t(&productos);
      sendOutput(msg.time(), producto_out, t);
      cout << msg.time() << " Inventario - " << "Entrega: " << t <<  endl;
      cout << "INVENTARIO , " << msg.time() << " , " << cola.size() << endl; 
      }
			break;		

		case State::push:{ //Tiene que estar?
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
