#include "pmodeladm.h"
#include "register.h"

#include "ControlInventario.h"
#include "ControlCalidad.h"
#include "proveedorInmediato.h"
#include "proveedorFijo.h"
#include "proveedorEncargo.h"
#include "Inventario.h"
#include "clientA.h"
#include "clientB.h"
#include "clientC.h"
#include "AtencionAlCliente.h"

void register_atomics_on(ParallelModelAdmin &admin)
{
	// TODO: cambiar 'MiModelo' por el nombre de la clase que representa
	// el modelo atómico y "Nombre del modelo" por el string utilizado en
	// dicha clase como valor de retorno del método className().
	admin.registerAtomic(NewAtomicFunction<ProveedorInmediato>(), PROVEEDOR_INMEDIATO_NAME);
	admin.registerAtomic(NewAtomicFunction<ControlInventario>(), CONTROL_INVENTARIO_NAME);
	admin.registerAtomic(NewAtomicFunction<ProveedorFijo>(), PROVEEDOR_FIJO_NAME);
	admin.registerAtomic(NewAtomicFunction<ProveedorEncargo>(), PROVEEDOR_ENCARGO_NAME);
	admin.registerAtomic(NewAtomicFunction<Inventario>(), INVENTARIO_NAME);
  admin.registerAtomic(NewAtomicFunction<ClientA>(), CLIENT_A_NAME);
  admin.registerAtomic(NewAtomicFunction<ClientB>(), CLIENT_B_NAME);
  admin.registerAtomic(NewAtomicFunction<ClientC>(), CLIENT_C_NAME);
  admin.registerAtomic(NewAtomicFunction<ControlCalidad>(), CONTROLCALIDAD_NAME);
  admin.registerAtomic(NewAtomicFunction<AtencionAlCliente>(), ATENCIONALCLIENTE_NAME);
}
