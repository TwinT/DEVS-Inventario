[top]
components : despacho
in :  pedidosIn in1 in2 in3 in4 in5
out : pedidosOut out1 out2 out3 out4 out5
link : in1 in1@despacho
link : in2 in2@despacho
link : in3 in3@despacho
link : in4 in4@despacho
link : in5 in5@despacho
link : pedidosIn pedidosIn@despacho
link : out1@despacho out1
link : out2@despacho out2
link : out3@despacho out3
link : out4@despacho out4
link : out5@despacho out5
link : pedidosOut@despacho pedidosOut


[despacho]
type : cell
dim : (1,6)
delay : transport
defaultDelayTime  : 0
border : nowrapped
neighbors : despacho(0,-1) despacho(0,0) despacho(0,1)
initialvalue : 0
initialCellsValue : despacho.val
in : pedidosIn in1 in2 in3 in4 in5
out : pedidosOut out1 out2 out3 out4 out5
link : pedidosIn in@despacho(0,5)
link : in5 in@despacho(0,4)
link : in4 in@despacho(0,3)
link : in3 in@despacho(0,2)
link : in2 in@despacho(0,1)
link : in1 in@despacho(0,0)
link : output@despacho(0,5) pedidosOut
link : output@despacho(0,4) out5
link : output@despacho(0,3) out4
link : output@despacho(0,2) out3
link : output@despacho(0,1) out2
link : output@despacho(0,0) out1
portintransition : in@despacho(0,5) pedidosIn-regla
portintransition : in@despacho(0,4) ins-regla
portintransition : in@despacho(0,3) ins-regla
portintransition : in@despacho(0,2) ins-regla
portintransition : in@despacho(0,1) ins-regla
portintransition : in@despacho(0,0) ins-regla
localtransition : despacho-reglas


[despacho-reglas]
% celda: (y_celda,x_celda)!idx_tupla=val
% tupla: [idx_0,idx_1,...] -> sin espacios
% con -1 pregunta al inventario si hay lugar

% Movimiento del producto sacado del inventario
% Todas las reglas a continuación preguntan por >0 para no actuar con el pedido.
rule : { (0,-1) } 1 { not isUndefined((0,-1)!0) and (0,-1)!0>0 and (0,0)!0=0 }
rule : { [0,0] } 1 { not isUndefined((0,1)!0) and (0,1)!0>0 }
rule : { [0+send(output,(0,0)!0),0] } 1 { cellPos(1)=5 and (0,0)!0>0 }

% Movimiento del despachante buscando el producto
rule : {[-1+send(output,-1),0]} 1 { not isUndefined((0,1)!0) and (0,1)=[0,-1] and (0,0)!0=0 }
rule : {[0,0]} 1 { not isUndefined((0,-1)!0) and (0,-1)=[-1,0]}

% always true (condicion default)
rule : { (0,0) } 0 { t }


[pedidosIn-regla]
rule : { [0,portValue(thisPort)] } 1 { portValue(thisPort)=-1 }


[ins-regla]
rule : { [0,-1] } 1 { portValue(thisPort)=0 }
rule : { [portValue(thisPort),0] } 1 { portValue(thisPort)>0 }
