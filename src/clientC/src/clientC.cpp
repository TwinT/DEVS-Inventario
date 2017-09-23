#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "clientC.h"

using namespace std;


ClientC::ClientC(const string &name) :
	Atomic(name),
	disponibles_i(addInputPort("disponibles_i")),
	query_o(addOutputPort("query_o")),
	pedido_o(addOutputPort("pedido_o")),
	distval({1,2,2,1})
{
	//TODO: pasar los parámetros de la distribución por le .ma
	dist = Distribution::create("exponential");
	dist->setVar(0, 12) ;
	cout << "Model Created" << endl;
}


Model &ClientC::initFunction()
{
	
	this->elapsed = VTime::Zero;
	this->timeLeft = VTime::Inf;
	this->sigma = VTime::Inf;

	// arranca en estado StateClient::IDLE
	query_time = VTime(fabs(this->dist->get()));
	holdIn(AtomicState::active, this->query_time);
	cout << "Model Initialized" << endl;

	return *this;
}


Model &ClientC::externalFunction(const ExternalMessage &msg)
{
	this->sigma    = nextChange();
	this->elapsed  = msg.time() - lastChange();
	this->timeLeft = this->sigma - this->elapsed;

	if(msg.port() == disponibles_i){
		if(this->stateC == StateClient::QUERY)
		{
			this->inStock = Real::from_value(msg.value());
			if(this->inStock >= this->lastQuery)
			{
				this->stateC = StateClient::ACCEPT;
			}
			else
			{
				this->stateC = StateClient::DECLINE;
			}
			holdIn(AtomicState::active, VTime::Zero);
		}else{ // si llegara un msg cuando stateC != QUERY
			holdIn(AtomicState::active, this->elapsed);
		}
	}

	return *this;
}


Model &ClientC::internalFunction(const InternalMessage &)
{
	switch(this->stateC)
	{
		case StateClient::ACCEPT:
			this->stateC = StateClient::IDLE;
			query_time = VTime(fabs(this->dist->get()));
			holdIn(AtomicState::active, this->query_time);
			break;
		case StateClient::IDLE:
			this->stateC = StateClient::QUERY;
			holdIn(AtomicState::passive, VTime::Inf); // equivalente a: passivate();
			break;
	}

	return *this ;
}


Model &ClientC::outputFunction(const CollectMessage &msg)
{
	switch(this->stateC)
	{
		case StateClient::IDLE: // pregunto disponibilidad de productos por puerto query_o 
			this->lastQuery = Real(this->distval(this->rng)+1);
			//Tuple<Real> out_value{lastQuery};
			sendOutput(msg.time(), query_o, this->lastQuery);
		case StateClient::ACCEPT: // pido n productos por puerto pedido_o
			sendOutput(msg.time(), pedido_o, this->lastQuery);
	}

	return *this ;
}
