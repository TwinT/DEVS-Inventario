[top]
components : CC@ClientC
out : pout_port qout_port
in : in_port
link : in_port disponibles_i@CC
link : query_o@CC qout_port
link : pedido_o@CC pout_port

[CC]
distribution : Exponential
mean : 0.12
