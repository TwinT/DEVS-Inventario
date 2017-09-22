#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "clientA.h"

using namespace std;


ClientA::ClientA(const string &name) :
	Atomic(name),
	query_o(addOutputPort("query_o")),
	// query_time(0,0,1,0),
	distval({1,2,2,1})
{
	dist = Distribution::create("exponential");
	dist->setVar(0, 12) ;
	cout << "Model Created" << endl;
}


Model &ClientA::initFunction()
{
	query_time = VTime(fabs(this->dist->get()));
	holdIn(AtomicState::active, this->query_time);
	cout << "Model Initialized" << endl;

	return *this;
}


Model &ClientA::externalFunction(const ExternalMessage &msg)
{
	// no hay entradas
	return *this;
}


Model &ClientA::internalFunction(const InternalMessage &)
{
	query_time = VTime(fabs(this->dist->get()));
	holdIn(AtomicState::active, this->query_time);

	return *this ;
}


Model &ClientA::outputFunction(const CollectMessage &msg)
{
	auto random_int = this->distval(this->rng)+1;
	Tuple<Real> out_value{Real(random_int)};

	sendOutput(msg.time(), query_o, out_value);
	return *this ;
}
