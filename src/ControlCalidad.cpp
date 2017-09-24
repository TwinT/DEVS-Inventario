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
	queryClient_i(addInputPort("queryClient_i")), 
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
		
		// Process input
		for (int i=0; i<products.size(); i++)
		{
			//Debug:
			std::cout<<"External function: "<<products[i]<<std::endl;
			if (products[i] > msg.time())
			{
				passProducts.push_back(products[i]);
				numPassProd++;
			}
		}
		
		// Next State
		state = State::CHECK;
		holdIn(AtomicState::active, VTime::Zero);
	}
	
	if (msg.port() == queryClient_i)
	{
		if (state == State::WAITING)	// Redundant
		{
			numClientQuery = (Real::from_value(msg.value())).value();
			state = State::QUERY;
			holdIn(AtomicState::active, VTime::Zero);
		}
	}
	else
		// No particular time Advance in this module
		holdIn(AtomicState::passive, VTime::Inf);
	
	return *this;
}


Model &ControlCalidad::internalFunction(const InternalMessage &)
{
	switch(state)
	{
		case State::QUERY:
			state = State::INV_WAIT;
			holdIn(AtomicState::passive, VTime::Inf);
			break;
		case State::CHECK:
			if (numPassProd <= numClientQuery)
				state = State::QUERY;
			else
				state = State::SEND;
			holdIn(AtomicState::active, VTime::Zero);
			break;
		case State::SEND:
			holdIn(AtomicState::passive, VTime::Inf);
			state = State::WAITING;
			numPassProd = 0;
			passProducts.clear();
			break;
		default:	// Should not enter here
			holdIn(AtomicState::passive, VTime::Inf);
			state = State::WAITING;
			break;
	}
	return *this ;
}


Model &ControlCalidad::outputFunction(const CollectMessage &msg)
{
	double numQueryProds{0};
	switch(state)
	{
		case State::QUERY:
			numQueryProds = numClientQuery - numPassProd;
			sendOutput(msg.time(), queryInventory_o, numQueryProds);
			break;
		case State::CHECK:
			break;
		case State::SEND:
			sendOutput(msg.time(), prod_o, Tuple<VTime>(&passProducts));
			break;
		default:
			break;
	}
	return *this ;
}
