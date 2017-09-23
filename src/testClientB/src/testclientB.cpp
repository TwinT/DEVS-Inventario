#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "testclientB.h"

using namespace std;


TestClientB::TestClientB(const string &name) :
	Atomic(name),
	query_i(addInputPort("query_i")),
	available_o(addOutputPort("available_o"))
{
	cout << "Model Created" << endl;
}


Model &TestClientB::initFunction()
{
	
	this->elapsed = VTime::Zero;
	this->timeLeft = VTime::Inf;
	this->sigma = VTime::Inf;

	holdIn(AtomicState::passive, VTime::Inf);
	cout << "Model Initialized" << endl;

	return *this;
}


Model &TestClientB::externalFunction(const ExternalMessage &msg)
{
	this->sigma    = nextChange();
	this->elapsed  = msg.time() - lastChange();
	this->timeLeft = this->sigma - this->elapsed;

	if(msg.port() == query_i){
		this->pedido = Real::from_value(msg.value());
		holdIn(AtomicState::active, VTime::Zero);
	}

	return *this;
}


Model &TestClientB::internalFunction(const InternalMessage &)
{
	holdIn(AtomicState::passive, VTime::Inf); // equivalente a: passivate();

	return *this ;
}


Model &TestClientB::outputFunction(const CollectMessage &msg)
{
	sendOutput(msg.time(), available_o, this->pedido - 1);

	return *this ;
}
