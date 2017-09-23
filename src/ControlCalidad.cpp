#include <string>

#include "message.h"
#include "parsimu.h"
#include "Product.h"
#include "tuple_value.h"

#include "ControlCalidad.h"

using namespace std;


ControlCalidad::ControlCalidad(const string &name) :
	Atomic(name),
	prod_i(addInputPort("prod_i")),
	queryClient_i(addInputPort("queryInventory_o")), 
	queryInventory_o(addOutputPort("queryInventory_o")), 
	prod_o(addOutputPort("prod_o"))
{
}


Model &ControlCalidad::initFunction()
{
	holdIn(AtomicState::passive, VTime::Inf);
	state = State::WAITING;
	return *this;
}


Model &ControlCalidad::externalFunction(const ExternalMessage &msg)
{
	if (msg.port() == prod_i)
	{
		Tuple<Product> products = Tuple<Product>::from_value(msg.value());
		std::cout<<products.size();
	}
	
	if (msg.port() == queryClient_i)
	{
		if (state == State::WAITING)	// Redundant
		{
			numClientQuery = (Real::from_value(msg.value())).value();
			state = State::QUERY;
		}
	}
	else
		// No time Advance in this module
		holdIn(AtomicState::passive, VTime::Inf);
	
	return *this;
}


Model &ControlCalidad::internalFunction(const InternalMessage &)
{
	switch(state)
	{
		case State::QUERY:
			holdIn(AtomicState::passive, VTime::Inf);
			state = State::INV_WAIT;
			break;
		case State::CHECK:
			if (numPassProd <= numClientQuery)
				state = State::QUERY;
			else
				state = State::WAITING;
			break;
		default:	// Shouldnt enter here
			holdIn(AtomicState::passive, VTime::Inf);
			state = State::WAITING;
			break;
	}
	return *this ;
}


Model &ControlCalidad::outputFunction(const CollectMessage &msg)
{
	switch(state)
	{
		case State::QUERY:
			sendOutput(msg.time(), queryInventory_o, numClientQuery);
			break;
		default:
			break;
	}
	return *this ;
}
