#include <string>

#include "message.h"
#include "parsimu.h"
//#include "real.h"
//#include "tuple_value.h"

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
	holdIn(AtomicState::active, query_time);
	state = State::WAITING;
	return *this;
}


Model &ControlInventario::externalFunction(const ExternalMessage &msg)
{
	// Tiene un puerto solo de entrada, sino hay que preguntar por el puerto.
	double invStock = (Real::from_value(msg.value())).value();

	if(state == State::QUERY)
	{
		quantity = 0;
		if (invStock < s)
			quantity = S - invStock;

		state = State::CALC;
		holdIn(AtomicState::active, VTime::Zero);
	}
	else
		// TODO: ver timeLeft()
		holdIn(AtomicState::active, nextChange() - (msg.time() - lastChange()));
		
	return *this;
}


Model &ControlInventario::internalFunction(const InternalMessage &)
{
	switch(state)
	{
		case State::WAITING:
			holdIn(AtomicState::passive, VTime::Inf);
			state = State::QUERY;
			break;
		default:	// sirve para case: CALC
			holdIn(AtomicState::active, query_time);
			state = State::WAITING;
			break;
	}
	return *this ;
}


Model &ControlInventario::outputFunction(const CollectMessage &msg)
{
	switch(state)
	{
		case State::WAITING:
			sendOutput(msg.time(), queryInventory_o, 1);
			break;
		default:
			sendOutput(msg.time(), querySuppliers_o, quantity);
			break;
	}
	return *this ;
}
