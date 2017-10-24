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
	//dist = Distribution::create("exponential");
	//dist->setVar(0, 12) ;

	try
	{
		dist = Distribution::create( ParallelMainSimulator::Instance().getParameter( description(), "distribution" ) );
		MASSERT( dist ) ;
		for ( register int i = 0; i < dist->varCount(); i++ )
		{
			string parameter( ParallelMainSimulator::Instance().getParameter( description(), dist->getVar( i ) ) ) ;
			dist->setVar( i, str2Value( parameter ) ) ;
		}

		if( ParallelMainSimulator::Instance().existsParameter( description(), "initial" ) )
			initial = str2Int( ParallelMainSimulator::Instance().getParameter( description(), "initial" ) );
		else
			initial = 0;

		if( ParallelMainSimulator::Instance().existsParameter( description(), "increment" ) )
			increment = str2Int( ParallelMainSimulator::Instance().getParameter( description(), "increment" ) );
		else
			increment = 1;

	}
	catch(InvalidDistribution &e)
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} 
	catch(MException &e)
	{
		MTHROW(e);
	}
	cout << "Cliente A creado" << endl;
}


Model &ClientA::initFunction()
{
	query_time = VTime(fabs(this->dist->get()));
	holdIn(AtomicState::active, this->query_time);
	cout << "Cliente A - Init finalizado" << endl;

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
	Real out_value(random_int);

  cout << msg.time() << " Client A - " << "encargo: " << out_value <<  endl;

	sendOutput(msg.time(), query_o, out_value);
	return *this ;
}
