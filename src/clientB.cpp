#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "clientB.h"

using namespace std;


ClientB::ClientB(const string &name) :
	Atomic(name),
	disponibles_i(addInputPort("disponibles_i")),
	query_o(addOutputPort("query_o")),
	pedido_o(addOutputPort("pedido_o")),
	encargado_o(addOutputPort("encargado_o")),
	distval({1,2,2,1})
{
	//dist = Distribution::create("exponential");
	//dist->setVar(0, 12) ;
	try
	{
		dist = Distribution::create( ParallelMainSimulator::Instance().getParameter( description(), "distribution" ) );
		MASSERT( dist ) ;
		for ( register int i = 0; i < dist->varCount(); i++ )
		{
			string parameter( ParallelMainSimulator::Instance().getParameter( description(), dist->getVar( i ) ) ) ;
			dist->setVar( i, str2Value( parameter ) ) ;
		}

		if( ParallelMainSimulator::Instance().existsParameter( description(), "initial" ) )
			initial = str2Int( ParallelMainSimulator::Instance().getParameter( description(), "initial" ) );
		else
			initial = 0;

		if( ParallelMainSimulator::Instance().existsParameter( description(), "increment" ) )
			increment = str2Int( ParallelMainSimulator::Instance().getParameter( description(), "increment" ) );
		else
			increment = 1;

	}
	catch(InvalidDistribution &e)
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} 
	catch(MException &e)
	{
		MTHROW(e);
	}
	cout << "Cliente B creado" << endl;
}


Model &ClientB::initFunction()
{
	
	this->elapsed = VTime::Zero;
	this->timeLeft = VTime::Inf;
	this->sigma = VTime::Inf;

	// arranca en estado StateClient::IDLE
	this->query_time = VTime(fabs(this->dist->get()));
	holdIn(AtomicState::active, this->query_time );
	cout << "Cliente B - Init finalizado" << endl;

	return *this;
}


Model &ClientB::externalFunction(const ExternalMessage &msg)
{
	this->sigma    = nextChange();
	this->elapsed  = msg.time() - lastChange();
	this->timeLeft = this->sigma - this->elapsed;

	if(msg.port() == disponibles_i)
	{
		if(stateC == StateClient::QUERY)
		{
			inStock = Real::from_value(msg.value()).value();
  		cout << msg.time() << " Client B - " << "le dicen que hay: " << inStock << " productos" << endl;

  		stateC = StateClient::CALC;
			holdIn(AtomicState::active, VTime::Zero);
		}
		else
		{ // si llegara un msg cuando stateC != QUERY
			holdIn(AtomicState::active, this->timeLeft);
		}
	}

	return *this;
}


Model &ClientB::internalFunction(const InternalMessage &)
{
	switch(this->stateC)
	{
		case StateClient::CALC:
			this->stateC = StateClient::IDLE;
			this->query_time = VTime(fabs(this->dist->get()));
			holdIn(AtomicState::active, this->query_time);
			break;
		case StateClient::IDLE:
			this->stateC = StateClient::QUERY;
			holdIn(AtomicState::passive, VTime::Inf); // equivalente a: passivate();
			break;
		case StateClient::QUERY:	
		  break;
	}


	return *this ;
}


Model &ClientB::outputFunction(const CollectMessage &msg)
{
	switch(stateC)
	{
		case StateClient::IDLE: // pregunto disponibilidad de productos por puerto query_o 
			lastQuery = Real(distval(rng)+1);
			sendOutput(msg.time(), query_o, lastQuery);
  		cout << msg.time() << " Client B - " << "pregunta por: " << lastQuery << " productos" << endl;
			break;
		case StateClient::CALC: // pido n productos por puerto pedido_o
			sendOutput(msg.time(), pedido_o, inStock);
			sendOutput(msg.time(), encargado_o, lastQuery - inStock);

  		cout << msg.time() << " Client B - " << "pide: " << inStock << endl;
  		cout << msg.time() << " Client B - " << "encarga: " << lastQuery - inStock << endl;
   
			break;
		case StateClient::QUERY:
		  break;	
	}


	return *this ;
}
