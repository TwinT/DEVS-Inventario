[top]
components : ProveedorFijo@ProveedorFijo
out  : entrega
in   : pedido
link : pedido pedido@ProveedorFijo
link : entrega@ProveedorFijo entrega

[ProveedorFijo]
productos_por_paquete : 30