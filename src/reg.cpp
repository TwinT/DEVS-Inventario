#include "pmodeladm.h"
#include "register.h"


//#include "proveedorInmediato.h"
//#include "ControlInventario.h"
#include "ControlCalidad.h"
//#include "AtencionAlCliente.h"
//#include "clientA.h"
//#include "clientB.h"
//#include "clientC.h"

void register_atomics_on(ParallelModelAdmin &admin)
{
	// TODO: cambiar 'MiModelo' por el nombre de la clase que representa
	// el modelo atómico y "Nombre del modelo" por el string utilizado en
	// dicha clase como valor de retorno del método className().
	//admin.registerAtomic(NewAtomicFunction<ProveedorInmediato>(), "ProveedorInmediato");
	//admin.registerAtomic(NewAtomicFunction<ControlInventario>(), CONTROLINVENTARIO_NAME);
	admin.registerAtomic(NewAtomicFunction<ControlCalidad>(), CONTROLCALIDAD_NAME);
	//admin.registerAtomic(NewAtomicFunction<AtencionAlCliente>(), ATENCIONALCLIENTE_NAME);
	//admin.registerAtomic(NewAtomicFunction<ClientA>(), "ClientA");
	//admin.registerAtomic(NewAtomicFunction<ClientB>(), "ClientB");
	//admin.registerAtomic(NewAtomicFunction<ClientC>(), "ClientC");
}
