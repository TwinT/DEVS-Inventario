[top]
components : CB@ClientB
out : eout_port pout_port qout_port
in : in_port
link : in_port disponibles_i@CB
link : query_o@CB qout_port
link : pedido_o@CB pout_port
link : encargado_o@CB eout_port

[CB]
distribution : Exponential
mean : 0.12

