[top]
components : CI@ControlInventario
out : supplier_out inventory_out
in : invLevel
link : invLevel numProd_i@CI
link : querySuppliers_o@CI supplier_out 
link : queryInventory_o@CI inventory_out 
