[top]
components : CI@ControlInventario
out : supplier_out inventory_out
in : invLevel
link : invLevel numProd_i@CI
link : supplier_out querySuppliers_o@CI
link : inventory_out queryInventory_o@CI
