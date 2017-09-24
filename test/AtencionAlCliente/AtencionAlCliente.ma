[top]
components : AC@AtencionAlCliente
out : prodInventory_o queryInventory_o queryClient_o
in : numProdClient_i queryClient_i queryInventory_i
link : numProdClient_i numProdClient_i@AC
link : queryClient_i queryClient_i@AC
link : queryInventory_i queryInventory_i@AC
link : queryInventory_o@AC queryInventory_o 
link : queryClient_o@AC queryClient_o 
link : prodInventory_o@AC prodInventory_o
