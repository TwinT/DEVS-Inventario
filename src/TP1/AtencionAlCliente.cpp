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
  cout << "Atención al Cliente creado" << endl;
}


Model &AtencionAlCliente::initFunction()
{
	holdIn(AtomicState::passive, VTime::Inf);
	state = State::WAITING;
  cout << "Atención al Cliente - Init finalizado" << endl;

	return *this;
}


Model &AtencionAlCliente::externalFunction(const ExternalMessage &msg)
{
	if (msg.port() == queryClient_i){
		if (state == State::WAITING)
		{
			queryClient = Real::from_value(msg.value()).value();
			state = State::QUERY;
			cout << msg.time() << " Atencion al cliente - le piden " << queryClient << " productos" <<  endl;

			holdIn(AtomicState::active, VTime::Zero);
		}
	}
	else if (msg.port() == queryInventory_i){
		if (state == State::INV_WAIT)
		{
			inventoryStock = Real::from_value(msg.value()).value();
			cout << msg.time() << " Atencion al cliente - le dicen que hay " << inventoryStock << " stock" <<  endl;			

			state = State::CLI_RPLY;
			holdIn(AtomicState::active, VTime::Zero);
		}
  }		
	else if (msg.port() == numProdClient_i){
		if (state == State::CLI_WAIT)
		{
			productsBuyed = Real::from_value(msg.value()).value();
			cout << msg.time() << " Atencion al cliente - cliente pide " << productsBuyed << " productos" <<  endl;			
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
	}else{
		holdIn(AtomicState::passive,VTime::Inf);
	}
		
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
			cout << msg.time() << " Atencion al cliente - pregunta por " << queryClient << " productos" <<  endl;			
			break;
		case State::CLI_RPLY:
		  {
		  int disponibles = static_cast<int>(inventoryStock);
		  if(disponibles < 0){
		    disponibles = 0;	
		  }
			sendOutput(msg.time(), queryClient_o, Real(disponibles));
			cout << msg.time() << " Atencion al cliente - informa a cliente que hay " << Real(disponibles) << " stock" <<  endl;			
			break;
		  }
		case State::INV_GET:
			sendOutput(msg.time(), prodInventory_o, productsBuyed);
			cout << msg.time() << " Atencion al cliente - pide al inventario " << productsBuyed << " productos" <<  endl;			
			break;
		default:
			break;
	}
	return *this ;
}
