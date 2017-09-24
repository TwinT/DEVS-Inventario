#include "proveedorInmediato.h" // base header
#include "message.h"            // InternalMessage ....
#include "distri.h"             // class Distribution 
#include "strutil.h"            // str2Value( ... )
#include "parsimu.h"            // class Simulator

/*******************************************************************
* Function Name: proveedorInmediato
* Description: constructor
********************************************************************/
ProveedorInmediato::ProveedorInmediato( const string &name )
: Atomic( name )
 , entrega(addOutputPort( "entrega" ))
 , pedido(addInputPort( "pedido" ))
 , productos(0)
{
	try{
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

	} catch(InvalidDistribution &e){
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} catch(MException &e){
		MTHROW(e);
	}
	cout << "Proveedor Inmediato Creado" << endl;
	
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &ProveedorInmediato::initFunction()
{
	this->elapsed = VTime::Zero;
    this->timeLeft = VTime::Inf;
    this->sigma = VTime::Inf; // stays in active state until an external event occurs;
    
    state = idle;
    cout << "Init finalizado" << endl;

    holdIn(AtomicState::active, this->sigma);
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &ProveedorInmediato::externalFunction( const ExternalMessage &msg )
{
	this->sigma = nextChange();	
	this->elapsed = msg.time()-lastChange();	
    this->timeLeft = this->sigma - this->elapsed; 
	
	int cantidad;

	if (msg.port() ==  pedido){
		cantidad = static_cast<int>(Real::from_value(msg.value()).value());
     	cout << msg.time() << ": Se recibe un pedido de " << cantidad <<  endl;

		for(int i = 0; i < cantidad; i++){
			cout << "float: " << static_cast<float>(fabs(distribution().get())) << endl;
			VTime t = VTime(static_cast<float>(fabs(distribution().get())));
			cout << "distribution: " << t << endl;
			productos.push_back(Real(t.asMsecs()));
		}

		for(int i = 0; i < productos.size(); i++){
			cout << "Producto en entrega "<< i << ":" << productos[i] << endl;
		}
		state = serve;
		holdIn(AtomicState::active, VTime::Zero);
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &ProveedorInmediato::internalFunction( const InternalMessage &msg )
{

	if(state == idle)
		this->sigma =  VTime::Inf;
	else
		this->sigma = VTime::Zero;
	
	state = idle;
	holdIn(AtomicState::active, this->sigma);
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &ProveedorInmediato::outputFunction(const CollectMessage &msg)
{
	if(state == serve){
		Tuple<Product> t(&productos);
		sendOutput( msg.time(), entrega, t);
		cout << msg.time() << ": pedido entregado. Entrega:" << t <<  endl;
		productos.clear(); // limpio vector
	}
	
	return *this;

}

ProveedorInmediato::~ProveedorInmediato()
{
	delete dist;
}
