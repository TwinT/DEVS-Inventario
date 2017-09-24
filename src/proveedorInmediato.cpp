#include "proveedorInmediato.h" // base header
#include "message.h"              // InternalMessage ....


/*******************************************************************
* Function Name: proveedorInmediato
* Description: constructor
********************************************************************/
ProveedorInmediato::ProveedorInmediato( const string &name )
: Atomic( name )
 , entrega(addOutputPort( "entrega" ))
 , pedido(addInputPort( "pedido" ))
{
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
    
    cout << "Init finalizado" << endl;
    state = idle;

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
	
	if (msg.port() ==  pedido){
		cantidad = Real::from_value(msg.value());
		cout << msg.time() << ": Se recibe un pedido de " << cantidad <<  endl;
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
	holdIn(AtomicState::active, this->sigma  );
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &ProveedorInmediato::outputFunction(const CollectMessage &msg)
{
	sendOutput( msg.time(), entrega, cantidad) ;
	cout << msg.time() << ": pedido entregado. Entrega:" << cantidad <<  endl;
	
	return *this;

}

ProveedorInmediato::~ProveedorInmediato()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
