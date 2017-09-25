#include "Inventario.h"			// base header
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
 , producto_out(addOutputPort( "producto_out" ))
 , query_out(addOutputPort( "query_out" ))

 , producto_in(addInputPort( "producto_in" ))
 , encargo(addInputPort( "encargo" ))
 , query_in(addInputPort( "query_in" ))
 , get(addInputPort( "get" ))
 , cola(0)
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
    
    state = idle;
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
	
	if (msg.port() ==  producto_in){
		Tuple<Product> t = Tuple<Product>::from_value(msg.value());
		for(int i = 0; i < t.size() ; i++){
			cola.push(Real::from_value(Tuple[i]));		
		}
		state = State::push;
		holdIn(AtomicState::active, Time::Inf); 
	}

	if (msg.port() ==  query_in){
		holdIn(AtomicState::active, Time::Zero); 
		state = State::query;
	}

	if (msg.port() ==  encargo_in){
		state = State::encargo;
		holdIn(AtomicState::active, Time::Inf); 
	}

	if (msg.port() ==  get){
		state = State::get;
	    holdIn(AtomicState::active, Time::Zero); 
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Inventario::internalFunction(const InternalMessage &msg )
{
	this->elapsed = VTime::Zero;
    this->timeLeft = VTime::Inf;
    this->sigma = VTime::Inf; // stays in active state until an external event occurs;

	switch(state)
		case State::idle:
			break;
		case State::query:
			break;		
		case State::encargo:
			break;
		case State::get:
			break;		
		case State::push:
			break;		
		default:
			break;		
		
	holdIn(AtomicState::active, this->sigma);
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Inventario::outputFunction(const CollectMessage &msg)
{
	switch(state)
		case State::idle:
			break;
		case State::query:
			break;		
		case State::encargo:
			break;
		case State::get:
			break;		
		case State::push:
			break;		
		default:
			break;	
	
	return *this;

}

Inventario::~Inventario()
{}
