#include "proveedorFijo.h" // base header
#include "message.h"            // InternalMessage ....
#include "strutil.h"            // str2Value( ... )
#include "parsimu.h"            // class Simulator

/*******************************************************************
* Function Name: ProveedorFijo
* Description: constructor
********************************************************************/
ProveedorFijo::ProveedorFijo(const string &name)
: Atomic( name )
 , entrega(addOutputPort( "entrega" ))
 , pedido(addInputPort( "pedido" ))
 , productos(0)
{
	try{
		if( ParallelMainSimulator::Instance().existsParameter(description(), "productos_por_paquete")){
			productos_por_paquete = str2Int(ParallelMainSimulator::Instance().getParameter( description(), "productos_por_paquete" ));
		}
		else{
			productos_por_paquete = 40;
		}
	} catch(MException &e){
		MTHROW(e);
	}
	cout << "Proveedor Fijo Creado" << " (Productos por paquete = " << productos_por_paquete << ")"<< endl;
	
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &ProveedorFijo::initFunction()
{
	this->elapsed = VTime::Zero;
    this->timeLeft = VTime::Inf;
    this->sigma = VTime::Inf; // stays in active state until an external event occurs;
    
    state = idle;
    cout << "Proveedor Fijo - Init finalizado" << endl;

    holdIn(AtomicState::active, this->sigma);
 	
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &ProveedorFijo::externalFunction( const ExternalMessage &msg )
{
	this->sigma = nextChange();	
	this->elapsed = msg.time()-lastChange();	
    this->timeLeft = this->sigma - this->elapsed; 
	
	if (msg.port() ==  pedido){
		int	cantidad_pedida = static_cast<int>(Real::from_value(msg.value()).value());

     	cout <<  msg.time() << " Proveedor Fijo - " << "Pedido: " << cantidad_pedida << " productos" << endl;

     	int cantidad = (cantidad_pedida / productos_por_paquete)*productos_por_paquete;

     	if(cantidad_pedida % productos_por_paquete != 0){
     		cantidad += productos_por_paquete;
     	}
     	
		for(int i = 0; i < cantidad; i++){
			VTime t = VTime::Inf;
			productos.push_back(Real(t.asMsecs()) / Real(1000));
		}

		state = serve;
		holdIn(AtomicState::active, VTime::Zero);
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &ProveedorFijo::internalFunction(const InternalMessage &msg )
{

	this->sigma =  VTime::Inf;
	state = idle;
  
	holdIn(AtomicState::active, this->sigma);
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &ProveedorFijo::outputFunction(const CollectMessage &msg)
{
	if(state == serve){
		Tuple<Product> t(&productos);
		sendOutput(msg.time(), entrega, t);
		cout << msg.time() << " Proveedor Fijo - " << "Entrega: " << productos.size() << " productos" <<  endl;
		productos.clear(); // limpio vector
	}
	
	return *this;

}

ProveedorFijo::~ProveedorFijo()
{}
