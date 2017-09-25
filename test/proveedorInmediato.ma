[top]
components : ProveedorInmediato@ProveedorInmediato
out  : entrega
in   : pedido
link : pedido pedido@ProveedorInmediato
link : entrega@ProveedorInmediato entrega

[ProveedorInmediato]
distribution : exponential
mean : 1.5
