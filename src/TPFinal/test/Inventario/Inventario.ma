[top]
components : Inventario@Inventario
out  : producto_out
out  : query_out
in   : producto_in
in   : query_in
in   : get

link : producto_in producto_in@Inventario
link : query_in query_in@Inventario
link : get get@Inventario

link : producto_out@Inventario producto_out
link : query_out@Inventario query_out

[Inventario]
N : 100
    