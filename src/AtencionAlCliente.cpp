#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"

#include "AtencionAlCliente.h"

using namespace std;


AtencionAlCliente::AtencionAlCliente(const string &name) :
	Atomic(name),
	numProdClient_i(addInputPort("numProdClient_i")),
	queryClient_i(addInputPort("queryClient_i")),
	queryInventory_i(addInputPort("queryInventory_i")),
	queryInventory_o(addOutputPort("queryInventory_o")),
	prodInventory_o(addOutputPort("prodInventory_o")),
	queryClient_o(addOutputPort("queryClient_o"))
{
}


Model &AtencionAlCliente::initFunction()
{
	holdIn(AtomicState::passive, VTime::Inf);
	state = State::WAITING;
	return *this;
}


Model &AtencionAlCliente::externalFunction(const ExternalMessage &msg)
{
	if (msg.port() == queryClient_i)
		if (state == State::WAITING)
		{
			queryClient = Real::from_value(msg.value()).value();
			state = State::QUERY;
			holdIn(AtomicState::active, VTime::Zero);
		}
	
	if (msg.port() == queryInventory_i)
		if (state == State::INV_WAIT)
		{
			inventoryStock = Real::from_value(msg.value()).value();
			state = State::CLI_RPLY;
			holdIn(AtomicState::active, VTime::Zero);
		}
		
	if (msg.port() == numProdClient_i){
		if (state == State::CLI_WAIT)
		{
			productsBuyed = Real::from_value(msg.value()).value();
			cout<<"Ext func prodBuyed: "<<productsBuyed<<endl;
			if (productsBuyed != 0)
			{
				state = State::INV_GET;
				holdIn(AtomicState::active, VTime::Zero);
			}
			else
			{
				state = State::WAITING;
				holdIn(AtomicState::passive, VTime::Inf);
			}
		}
	}
	else
		holdIn(AtomicState::passive,VTime::Inf);
		
	return *this;
}


Model &AtencionAlCliente::internalFunction(const InternalMessage &)
{
	switch(state)
	{
		case State::QUERY:
			state = State::INV_WAIT;
			holdIn(AtomicState::passive, VTime::Inf);
			break;
		case State::CLI_RPLY:
			state = State::CLI_WAIT;
			holdIn(AtomicState::passive, VTime::Inf);
			break;
		case State::INV_GET:
			state = State::WAITING;
			holdIn(AtomicState::passive, VTime::Inf);
			break;
		default:	// Should not get here
			state = State::WAITING;
			holdIn(AtomicState::passive, VTime::Inf);
			break;
	}
	return *this ;
}


Model &AtencionAlCliente::outputFunction(const CollectMessage &msg)
{
	switch(state)
	{
		case State::QUERY:
			sendOutput(msg.time(), queryInventory_o, queryClient);
			cout<<"Inv query: "<< queryClient<<endl;
			break;
		case State::CLI_RPLY:
			sendOutput(msg.time(), queryClient_o, inventoryStock);
			cout<<"To clientreply: "<< inventoryStock<<endl;
			break;
		case State::INV_GET:
			sendOutput(msg.time(), prodInventory_o, productsBuyed);
			cout<<"Inv get: "<< productsBuyed<<endl;
			break;
		default:
			break;
	}
	return *this ;
}
