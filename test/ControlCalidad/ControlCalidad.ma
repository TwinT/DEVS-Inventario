[top]
components : CC@ControlCalidad
out : prod_o queryInventory_o
in : prod_i queryClient_i
link : prod_i prod_i@CC
link : queryClient_i queryClient_i@CC
link : queryInventory_o@CC queryInventory_o 
link : prod_o@CC prod_o
