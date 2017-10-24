#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"

#include "ControlInventario.h"

using namespace std;


ControlInventario::ControlInventario(const string &name) :
	Atomic(name),
	numProd_i(addInputPort("numProd_i")),
	queryInventory_o(addOutputPort("queryInventory_o")), 
	querySuppliers_o(addOutputPort("querySuppliers_o")),
	query_time(0,0,1,0)
{
try{
		if( ParallelMainSimulator::Instance().existsParameter(description(), "S")){
			S = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "S" ));
		}
		else{
			S = 100;
		}

		if( ParallelMainSimulator::Instance().existsParameter(description(), "n")){
			n = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "n" ));
		}
		else{
			n = 50;
		}

		if( ParallelMainSimulator::Instance().existsParameter(description(), "K")){
			K = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "K" ));
		}
		else{
			K = 350;
		}

		if( ParallelMainSimulator::Instance().existsParameter(description(), "p")){
			p = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "p" ));
		}
		else{
			p = 25;
		}

		if( ParallelMainSimulator::Instance().existsParameter(description(), "h")){
			h = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "h" ));
		}
		else{
			h = 8;
		}

		if( ParallelMainSimulator::Instance().existsParameter(description(), "r")){
			r = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "r" ));
		}
		else{
			r = 50;
		}

	} catch(MException &e){
		MTHROW(e);
	}

	cout << "Control de Inventario Creado" << " (S = " << S << ")"<< endl;
}


Model &ControlInventario::initFunction()
{
	holdIn(AtomicState::active, query_time);
	state = State::WAITING;
  cout << "Control de Inventario - Init finalizado" << endl;

	return *this;
}


Model &ControlInventario::externalFunction(const ExternalMessage &msg)
{
	// Tiene un puerto solo de entrada, sino hay que preguntar por el puerto.
	double invStock = (Real::from_value(msg.value())).value();
  cout << msg.time() << " Control Inventario - Inventario responde: " << invStock <<  endl;

	if(state == State::QUERY)
	{
		quantity = 0;
		if (invStock < n)
			quantity = S - invStock;

		if (invStock <= 0)
			costo = 3 * (K + p * quantity) + r * (-invStock);
		else
			costo = 3 * (K + p * quantity) + h * invStock;

		state = State::CALC;
		holdIn(AtomicState::active, VTime::Zero);
	}
	else
		// TODO: ver timeLeft()
		holdIn(AtomicState::active, nextChange());
		
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
		case State::CALC:
			holdIn(AtomicState::passive, query_time);
			state = State::WAITING;
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
			sendOutput(msg.time(), queryInventory_o, Real(1));
			cout << msg.time() << " Control Inventario - Consulta a Inventario" <<  endl;
			break;
		default: //CALC
			sendOutput(msg.time(), querySuppliers_o, Real(quantity));
			cout << msg.time() << " Control Inventario - Pedido a proveedores: " << quantity <<  endl;
			cout << "CONTROLDEINV , " << msg.time()
			     << " , " << costo
			     << endl;
			break;
	}
	return *this ;
}
