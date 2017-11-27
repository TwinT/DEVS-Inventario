[top]
components : clientA@ClientA clientB@ClientB clientC@ClientC pi@ProveedorInmediato pe@ProveedorEncargo pf@ProveedorFijo Industria

link : query_o@clientA encargo_i@Industria

link : query_o@clientC queryClient_i@Industria
link : pedido_o@clientC numProdClient_i@Industria
link : queryClient_o@Industria disponibles_i@clientC

link : query_o@clientB queryClient_i@Industria
link : pedido_o@clientB numProdClient_i@Industria
link : queryClient_o@Industria disponibles_i@clientB
link : encargado_o@clientB encargo_i@Industria

link : querySuppliers_o@Industria pedido@pi
link : entrega@pi prod_i_A@Industria

link : querySuppliers_o@Industria pedido@pf
link : entrega@pf prod_i_B@Industria

link : querySuppliers_o@Industria pedido@pe
link : entrega@pe prod_i_C@Industria

[Industria]
components : I@Inventario CI@ControlInventario AC@AtencionAlCliente CC@ControlCalidad

out  : prod_o queryClient_o querySuppliers_o
in   : prod_i_A prod_i_B prod_i_C queryClient_i encargo_i numProdClient_i

link : queryInventory_o@CI query_in@I
link : queryInventory_o@AC query_in@I 
link : query_out@I queryInventory_i@AC
link : query_out@I numProd_i@CI
link : producto_out@I prod_i@CC
link : queryInventory_o@CC get@I
link : prodInventory_o@AC queryClient_i@CC

link : numProdClient_i numProdClient_i@AC
link : queryClient_i queryClient_i@AC
link : prod_i_A producto_in_A@I 
link : prod_i_B producto_in_B@I 
link : prod_i_C producto_in_C@I 
link : encargo_i encargo@I

link : queryClient_o@AC queryClient_o
link : querySuppliers_o@CI querySuppliers_o
link : prod_o@CC prod_o

[clientA]
distribution : Exponential
mean : 0.12

[clientB]
distribution : Exponential
mean : 0.12 

[clientC]
distribution : Exponential
mean : 0.12

[pi]
distribution : exponential
mean : 0.12

[pe]
distribution : exponential
mean : 0.12

[pf]
productos_por_paquete : 5

[I]
N : 0

[CI]
n : 50
S : 85
K : 350
p : 25
h : 8
r : 50
