#include <random>
#include <string>

#include "message.h"
#include "parsimu.h"
#include "real.h"
#include "tuple_value.h"

#include "pulse.h"

using namespace std;


Pulse::Pulse(const string &name) :
	Atomic(name),
	start(addInputPort("start")),
	out(addOutputPort("out")),
	frequency_time(0,0,1,0),
	on(true),
	dist(0,100),
	rng(random_device()())
{
}


Model &Pulse::initFunction()
{
	holdIn(AtomicState::active, this->frequency_time); // estado = on
	if(this->on)
		cout << "inicializando..." << endl;
	return *this;
}


Model &Pulse::externalFunction(const ExternalMessage &msg)
{
	if(msg.port() == start)
	{
		if(this->on) // this->on == true
		{
			holdIn(AtomicState::active, nextChange() - (msg.time() - lastChange()));
		}
		else // this->on == false
		{
			this->on = true;
			holdIn(AtomicState::active, this->frequency_time);
		}
	}

	return *this;
}


Model &Pulse::internalFunction(const InternalMessage &)
{
	if(this->on)
	{
		this->on = false;
		passivate();
	}
	cout << "transicion interna" << endl;

	return *this ;
}


Model &Pulse::outputFunction(const CollectMessage &msg)
{
	auto random_int = this->dist(this->rng);
	Tuple<Real> out_value{Real(random_int), 0, 1};
	sendOutput(msg.time(), out, out_value);
	cout << "ejecuto la output function" << endl;
	return *this ;
}

