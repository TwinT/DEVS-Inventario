[top]
components : Inventario@Inventario
out  : producto_out
out  : query_out
in   : producto_in_A
in   : producto_in_B
in   : producto_in_C
in   : query_in
in   : get
in   : encargo

link : producto_in_A producto_in_A@Inventario
link : producto_in_B producto_in_B@Inventario
link : producto_in_C producto_in_C@Inventario
link : query_in query_in@Inventario
link : get get@Inventario
link : encargo encargo@Inventario

link : producto_out@Inventario producto_out
link : query_out@Inventario query_out

[Inventario]
N : 100
    