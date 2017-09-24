#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "ControlInventario.h"

using namespace std;


ControlInventario::ControlInventario(const string &name) :
	Atomic(name),
	numProd_i(addInputPort("numProd_i")),
	queryInventory_o(addOutputPort("queryInventory_o")), 
	querySuppliers_o(addOutputPort("querySuppliers_o")),
	query_time(0,0,1,0)
{
}


Model &ControlInventario::initFunction()
{
	holdIn(AtomicState::active, this->query_time);
	this->state = WAITING;
	return *this;
}


Model &ControlInventario::externalFunction(const ExternalMessage &msg)
{
	// Tiene un puerto solo de entrada
	if(this->state == QUERY)
	{
		quantity = 0;
		if (msg.value() < s)
			quantity = S - msg.value();

		this->state = CALC;
		holdIn(AtomicState::active, 0);
	}
	else
		holdin(AtomicState::active, nextChange() - (msg.time() - lastChange()));  // TODO: ver timeLeft()
	
	return *this;
}


Model &ControlInventario::internalFunction(const InternalMessage &)
{
	switch(this->state)
	{
		case WAITING:
			holdIn(AtomicState::passive, infinite);
			this->state = QUERY;
			break;
		default:	// sirve para case: CALC
			holdIn(AtomicState::active, query_time);
			this->state = WAITING;
			break;
	}
	return *this ;
}


Model &ControlInventario::outputFunction(const CollectMessage &msg)
{
	switch(this->state)
	{
		case WAITING:
			double query = 1;
			sendOuput(msg.time(), queryInventory_o, query);
			break;
		default:
			sendOuput(msg.time(), queryInventory_o, this->quantity);
			break;
	}
	return *this ;
}
