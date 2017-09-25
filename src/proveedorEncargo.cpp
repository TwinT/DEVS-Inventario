#include "proveedorEncargo.h" // base header
#include "message.h"            // InternalMessage ....
#include "distri.h"             // class Distribution 
#include "strutil.h"            // str2Value( ... )
#include "parsimu.h"            // class Simulator

/*******************************************************************
* Function Name: ProveedorEncargo
* Description: constructor
********************************************************************/
ProveedorEncargo::ProveedorEncargo(const string &name)
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
	cout << "Proveedor por Encargo Creado" << endl;
	
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &ProveedorEncargo::initFunction()
{
	this->elapsed = VTime::Zero;
  this->timeLeft = VTime::Inf;
  this->sigma = VTime::Inf; // stays in active state until an external event occurs;
    
  state = idle;
  cout << "Proveedor por Encargo - Init finalizado" << endl;

  holdIn(AtomicState::active, this->sigma);
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &ProveedorEncargo::externalFunction( const ExternalMessage &msg )
{
	this->sigma = nextChange();	
	this->elapsed = msg.time()-lastChange();	
  this->timeLeft = this->sigma - this->elapsed; 
	
	if (msg.port() ==  pedido){
		int	cantidad_pedida = static_cast<int>(Real::from_value(msg.value()).value());

     	cout <<  msg.time() << " Proveedor por Encargo - " << "Pedido: " << cantidad_pedida << " productos" << endl;

		for(int i = 0; i < cantidad_pedida; i++){
			float f =  static_cast<float>(fabs(distribution().get()));
			//cout << "float: " << f << endl;
			VTime t = VTime(f);
			//cout << "distribution: " << t << endl;
			productos.push_back(Real(t.asMsecs()));
		}

		state = serve;
		holdIn(AtomicState::active, VTime(0,0,1,0)); // 1 segundo
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &ProveedorEncargo::internalFunction(const InternalMessage &msg )
{
	state = idle;
	this->sigma =  VTime::Inf;

	holdIn(AtomicState::active, this->sigma);
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &ProveedorEncargo::outputFunction(const CollectMessage &msg)
{
	if(state == serve){
		for(int i = 0; i < productos.size(); i++){
			productos[i] = productos[i] + Real(msg.time().asMsecs());
		}
		Tuple<Product> t(&productos);
		sendOutput(msg.time(), entrega, t);
		cout << msg.time() << " Proveedor por Encargo - " << "Entrega: " << t <<  endl;
		productos.clear(); // limpio vector
	}
	
	return *this;

}

ProveedorEncargo::~ProveedorEncargo()
{
	delete dist;
}
