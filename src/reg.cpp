#include "pmodeladm.h"
#include "register.h"

#include "ControlInventario.h"
#include "proveedorInmediato.h"
#include "proveedorFijo.h"
#include "proveedorEncargo.h"

void register_atomics_on(ParallelModelAdmin &admin)
{
	// TODO: cambiar 'MiModelo' por el nombre de la clase que representa
	// el modelo atómico y "Nombre del modelo" por el string utilizado en
	// dicha clase como valor de retorno del método className().
	admin.registerAtomic(NewAtomicFunction<ProveedorInmediato>(), PROVEEDOR_INMEDIATO_NAME);
	admin.registerAtomic(NewAtomicFunction<ControlInventario>(), CONTROL_INVENTARIO_NAME);
	admin.registerAtomic(NewAtomicFunction<ProveedorFijo>(), PROVEEDOR_FIJO_NAME);
	admin.registerAtomic(NewAtomicFunction<ProveedorEncargo>(), PROVEEDOR_ENCARGO_NAME);
}
