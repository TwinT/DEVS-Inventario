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
	  cout << "Control de Calidad creado" << endl;

}


Model &ControlCalidad::initFunction()
{
	holdIn(AtomicState::passive, VTime::Inf);
	state = State::WAITING;
  cout << "Control de Calidad - Init finalizado" << endl;

	return *this;
}


Model &ControlCalidad::externalFunction(const ExternalMessage &msg)
{
	if (msg.port() == prod_i)
	{
		if (state == State::INV_WAIT)
		{
			Tuple<Real> products = Tuple<Real>::from_value(msg.value());
			int tupleSize = products.size();
			// Process input
			for (int i=0; i<tupleSize; i++)
			{
				if (products[i].value() == 0)
					invEmpty = true;

				if (VTime(static_cast<float>(products[i].value())) > msg.time())
				{
					passProducts.push_back(products[i]);
					numPassProd++;
				}
			}
			
			cout << msg.time() << " Control Calidad - recibe " << tupleSize << " productos" <<  endl;
			cout << msg.time() << " Control Calidad - se queda con " << numPassProd << " productos" <<  endl;
			numRejectProd = tupleSize - numPassProd;

			if(invEmpty){
				cout << msg.time() << " Control Calidad - el inventario está vacío!" <<  endl;
			}
			// Next State
			state = State::CHECK;
			holdIn(AtomicState::active, VTime::Zero);
		}
	}
	
	else if (msg.port() == queryClient_i)
	{
		if (state == State::WAITING)	// Redundant
		{
			numClientQuery = (Real::from_value(msg.value())).value();
		  cout << msg.time() << " Control Calidad - le piden: " << numClientQuery << " productos" <<  endl;


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
			if ((numPassProd < numClientQuery) & (~invEmpty))
				state = State::QUERY;
			else
				state = State::SEND;
				
			holdIn(AtomicState::active, VTime::Zero);
			break;
			
		case State::SEND:
			holdIn(AtomicState::passive, VTime::Inf);
			state = State::WAITING;
			numPassProd = 0;
			invEmpty = false;
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
		  cout << msg.time() << " Control Calidad - pide: " << numQueryProds << " productos" <<  endl;

			break;
		case State::CHECK:
      			cout << "CONTROLDECALIDAD , " << msg.time() 
           		<< " , " << numRejectProd 
           		<< endl; 
			break;
		case State::SEND:
			sendOutput(msg.time(), prod_o, Tuple<Real>(&passProducts));
		  cout << msg.time() << " Control Calidad - envia: " << passProducts.size() << " productos" <<  endl;

			break;
		default:
			break;
	}
	return *this ;
}
