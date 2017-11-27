[top]
components : ProveedorEncargo@ProveedorEncargo
out  : entrega
in   : pedido
link : pedido pedido@ProveedorEncargo
link : entrega@ProveedorEncargo entrega

[ProveedorEncargo]
distribution : exponential
mean : 1.5
