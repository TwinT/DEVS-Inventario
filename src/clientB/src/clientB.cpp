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
	//TODO: pasar los parámetros de la distribución por le .ma
	dist = Distribution::create("exponential");
	dist->setVar(0, 12) ;
	cout << "Model Created" << endl;
}


Model &ClientB::initFunction()
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


Model &ClientB::externalFunction(const ExternalMessage &msg)
{
	this->sigma    = nextChange();
	this->elapsed  = msg.time() - lastChange();
	this->timeLeft = this->sigma - this->elapsed;

	if(msg.port() == disponibles_i){
		if(this->stateC == StateClient::QUERY)
		{
			this->inStock = Real::from_value(msg.value());
			this->stateC = StateClient::CALC;
			holdIn(AtomicState::active, VTime::Zero);
		}else{ // si llegara un msg cuando stateC != QUERY
			holdIn(AtomicState::active, this->elapsed);
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


Model &ClientB::outputFunction(const CollectMessage &msg)
{
	switch(this->stateC)
	{
		case StateClient::IDLE: // pregunto disponibilidad de productos por puerto query_o 
			this->lastQuery = Real(this->distval(this->rng)+1);
			//Tuple<Real> out_value{lastQuery};
			sendOutput(msg.time(), query_o, this->lastQuery);
		case StateClient::CALC: // pido n productos por puerto pedido_o
			Tuple<Real> out_val{Real(this->inStock),Real(this->lastQuery-this->inStock)}
			sendOutput(msg.time(), pedido_o, out_val);
			// en lugar de usar una tupla podría hacer 2 envíos por 2 puertos
			// pero para eso debería usar un flag y entre los dos envíos setear
			// un holdIn(active,VTime::Zero).
			//sendOutput(msg.time(), pedido_o, this->inStock);
			//sendOutput(msg.time(), encargado_o, this->lastQuery - this->inStock);
	}

	return *this ;
}
