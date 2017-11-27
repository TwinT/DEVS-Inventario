[top]
components : CI@ControlInventario
out : queryInventory_o querySuppliers_o
in : numProd_i
link : numProd_i numProd_i@CI
link : querySuppliers_o@CI querySuppliers_o 
link : queryInventory_o@CI queryInventory_o 
