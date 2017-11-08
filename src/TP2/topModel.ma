[top]
components : cinta inventario despacho
in :  productIn queryIn
out : productOut

%Ins
link : productIn in@cinta
link : queryIn pedidosIn@despacho
%Outs
link : pedidosOut@despacho productOut

%Internals: Cinta-Inventario
%Productos:
link : out1@cinta pin1@inventario
link : out2@cinta pin2@inventario
link : out3@cinta pin3@inventario
link : out4@cinta pin4@inventario
link : out5@cinta pin5@inventario
link : out6@cinta pin6@inventario
%Consultas
link : qtopout1@inventario in1@cinta
link : qtopout2@inventario in2@cinta
link : qtopout3@inventario in3@cinta
link : qtopout4@inventario in4@cinta
link : qtopout5@inventario in5@cinta
link : qtopout6@inventario in6@cinta

%Inventario-despacho
%Productos
link : pout1@inventario in1@despacho
link : pout2@inventario in2@despacho
link : pout3@inventario in3@despacho
link : pout4@inventario in4@despacho
link : pout5@inventario in5@despacho
link : pout6@inventario in6@despacho
%Consultas
link : out1@despacho qbotin1@inventario
link : out2@despacho qbotin2@inventario
link : out3@despacho qbotin3@inventario
link : out4@despacho qbotin4@inventario
link : out5@despacho qbotin5@inventario
link : out6@despacho qbotin6@inventario

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Componentes
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[cinta]
type : cell
dim : (1,6)
delay : transport
defaultDelayTime  : 0
border : nowrapped
neighbors : cinta(0,-1) cinta(0,0) cinta(0,1)
initialvalue : 0
initialCellsValue : cinta.val
in : in in1 in2 in3 in4 in5 in6
out : out1 out2 out3 out4 out5 out6
link : in in@cinta(0,5)
link : in1 in1@cinta(0,5)
link : in2 in2@cinta(0,4)
link : in3 in3@cinta(0,3)
link : in4 in4@cinta(0,2)
link : in5 in5@cinta(0,1)
link : in6 in6@cinta(0,0)
link : output@cinta(0,5) out1
link : output@cinta(0,4) out2
link : output@cinta(0,3) out3
link : output@cinta(0,2) out4
link : output@cinta(0,1) out5
link : output@cinta(0,0) out6
portintransition : in@cinta(0,5) in-regla
portintransition : in1@cinta(0,5) inventario-regla
portintransition : in2@cinta(0,4) inventario-regla
portintransition : in3@cinta(0,3) inventario-regla
portintransition : in4@cinta(0,2) inventario-regla
portintransition : in5@cinta(0,1) inventario-regla
portintransition : in6@cinta(0,0) inventario-regla
localtransition : cinta-reglas

[inventario]
type : cell
dim : (6,6)
delay : transport
defaultDelayTime  : 0
border : nowrapped

neighbors : inventario(-1,-1) inventario(-1,0) inventario(-1,1)
neighbors : inventario(0,-1)  inventario(0,0)  inventario(0,1)
neighbors : inventario(1,-1)  inventario(1,0)  inventario(1,1)

initialvalue : 0
initialCellsValue : inventario.val
in : pin1 pin2 pin3 pin4 pin5 pin6 qbotin1 qbotin2 qbotin3 qbotin4 qbotin5 qbotin6
out : qtopout1 qtopout2 qtopout3 qtopout4 qtopout5 qtopout6 pout1 pout2 pout3 pout4 pout5 pout6

link : qbotin6 in@inventario(5,5)
link : qbotin5 in@inventario(5,4)
link : qbotin4 in@inventario(5,3)
link : qbotin3 in@inventario(5,2)
link : qbotin2 in@inventario(5,1)
link : qbotin1 in@inventario(5,0)

link : pin6 pin@inventario(0,5)
link : pin5 pin@inventario(0,4)
link : pin4 pin@inventario(0,3)
link : pin3 pin@inventario(0,2)
link : pin2 pin@inventario(0,1)
link : pin1 pin@inventario(0,0)

link : output@inventario(0,5) qtopout6
link : output@inventario(0,4) qtopout5
link : output@inventario(0,3) qtopout4
link : output@inventario(0,2) qtopout3
link : output@inventario(0,1) qtopout2
link : output@inventario(0,0) qtopout1

link : output@inventario(5,5) pout6
link : output@inventario(5,4) pout5
link : output@inventario(5,3) pout4
link : output@inventario(5,2) pout3
link : output@inventario(5,1) pout2
link : output@inventario(5,0) pout1

portintransition : pin@inventario(0,5) prod-top-in
portintransition : pin@inventario(0,4) prod-top-in
portintransition : pin@inventario(0,3) prod-top-in
portintransition : pin@inventario(0,2) prod-top-in
portintransition : pin@inventario(0,1) prod-top-in
portintransition : pin@inventario(0,0) prod-top-in

portintransition : in@inventario(5,5) query-bot-in
portintransition : in@inventario(5,4) query-bot-in
portintransition : in@inventario(5,3) query-bot-in
portintransition : in@inventario(5,2) query-bot-in
portintransition : in@inventario(5,1) query-bot-in
portintransition : in@inventario(5,0) query-bot-in

localtransition : inventario-reglas


[despacho]
type : cell
dim : (1,7)
delay : transport
defaultDelayTime  : 0
border : nowrapped
neighbors : despacho(0,-1) despacho(0,0) despacho(0,1)
initialvalue : 0
initialCellsValue : despacho.val
in : pedidosIn in1 in2 in3 in4 in5 in6
out : pedidosOut out1 out2 out3 out4 out5 out6
link : pedidosIn in@despacho(0,6)
link : in6 in@despacho(0,5)
link : in5 in@despacho(0,4)
link : in4 in@despacho(0,3)
link : in3 in@despacho(0,2)
link : in2 in@despacho(0,1)
link : in1 in@despacho(0,0)
link : output@despacho(0,6) pedidosOut
link : output@despacho(0,5) out6
link : output@despacho(0,4) out5
link : output@despacho(0,3) out4
link : output@despacho(0,2) out3
link : output@despacho(0,1) out2
link : output@despacho(0,0) out1
portintransition : in@despacho(0,6) pedidosIn-regla
portintransition : in@despacho(0,5) despacho-ins-regla
portintransition : in@despacho(0,4) despacho-ins-regla
portintransition : in@despacho(0,3) despacho-ins-regla
portintransition : in@despacho(0,2) despacho-ins-regla
portintransition : in@despacho(0,1) despacho-ins-regla
portintransition : in@despacho(0,0) despacho-ins-regla
localtransition : despacho-reglas

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Reglas
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%% Cinta %%%%%%%%%%
[cinta-reglas]
% celda: (y_celda,x_celda,z_celda)!idx_tupla=val
% tupla: [idx_0,idx_1,...] -> sin espacios
rule : { [(0,0)!0,(0,1)!1,0] } { 100 } { NOT isUndefined((0,1)!1) AND (0,1)!1!=0 AND (0,1)!1>(0,1)!0+time/1000 }
rule : { [(0,0)!0,0,0] } { 100 } { NOT isUndefined((0,-1)!1) AND (0,0)!1!=0 AND (0,0)!1>(0,0)!0+time/1000 AND (0,-1)!1=0 }
rule : { [(0,0)!0,(0,1)!1,0] } { 100 } { (0,1)!2=1 }
rule : { [(0,0)!0,0,0] } { 100 } { (0,0)!2=1 AND NOT isUndefined((0,-1)!1) AND (0,-1)!1=0 }
rule : { [(0,0)!0,(0,0)!1,2] } { 100 } { (0,0)!2=1 AND (isUndefined((0,-1)!1) OR (0,-1)!1!=0) }
rule : { [(0,0)!0,(0,0)!1+send(output,-1),0] } { 100 } { (0,0)!2!=2 AND (0,0)!1!=0 AND (0,0)!1<=(0,0)!0+time/1000 } % con -1 pregunta al inventario si hay lugar
rule : { (0,0) } 0 { t } % always true

[in-regla]
rule : { [(0,0)!0,portValue(thisPort),0] } { 1 } { t }

[inventario-regla]
rule : { [(0,0)!0,0+send(output,(0,0)!1),0] } { 1 } { portValue(thisPort)!=0 }
rule : { [(0,0)!0,(0,0)!1,1] } { 1 } { portValue(thisPort)=0 } % el [x,y,1] indica que la columna del inventario esta llena

%%%%%%%%%% Inventario %%%%%%%%%%
[inventario-reglas]
% Hacia abajo si está vacío y el de la izquierda quiere entrar tb
% Tiene prioridad el de arriba en caso de empate

% Gana el de arriba
rule : { [(0,0)!0,0] }        100 {not isUndefined((1,-1)!1) and not isUndefined((1,0)!1)  and (1,0)!1=0   and (1,-1)!1!=0 and (1,-1)!1<(1,-1)!0+time/1000 and (0,0)!1!=0 and (0,0)!1<=(1,-1)!1}
rule : { [(0,0)!0,(-1,0)!1] } 100 {not isUndefined((-1,0)!1) and not isUndefined((0,-1)!1) and (-1,0)!1!=0 and (0,-1)!1!=0 and (0,-1)!1<(0,-1)!0+time/1000 and (0,0)!1=0 and (-1,0)!1<=(0,-1)!1}

% Gana el de la izquierda
rule : { [(0,0)!0,0] }        100 {not isUndefined((-1,1)!1) and not isUndefined((0,1)!1)  and (0,1)!1=0 and (-1,1)!1!=0 and (0,0)!1<(0,0)!0+time/1000   and (0,0)!1!=0  and (0,0)!1<(-1,1)!1}  
rule : { [(0,0)!0,(0,-1)!1] } 100 {not isUndefined((-1,0)!1) and not isUndefined((0,-1)!1) and (0,0)!1=0 and (0,-1)!1!=0 and (0,-1)!1<(0,-1)!0+time/1000 and (-1,0)!1!=0 and (0,-1)!1<(-1,0)!1 and not isUndefined((1,-1)!1) and (1,-1)!1!=0} 
% caso particular: fila de abajo, se puede ir a la derecha
rule : { [(0,0)!0,(0,-1)!1] } 100 {not isUndefined((-1,0)!1) and not isUndefined((0,-1)!1) and (0,0)!1=0 and (0,-1)!1!=0 and (0,-1)!1<(0,-1)!0+time/1000 and (-1,0)!1!=0 and (0,-1)!1<(-1,0)!1 and isUndefined((1,0)!1)} 


% caso particular: gana el de arriba porque no hay nada a la izquierda
rule : { [(0,0)!0,0] }        100 {not isUndefined((1,-1)!1) and not isUndefined((1,0)!1)  and (1,0)!1=0   and (1,-1)!1=0 and (0,0)!1!=0 }
rule : { [(0,0)!0,(-1,0)!1] } 100 {not isUndefined((-1,0)!1) and not isUndefined((0,-1)!1) and (-1,0)!1!=0 and (0,-1)!1=0 and (0,0)!1=0 }

% caso particular: gana el de la izquierda porque no hay nada arriba
rule : { [(0,0)!0,0] }        100 {not isUndefined((-1,1)!1) and not isUndefined((0,1)!1)  and (0,1)!1=0 and (-1,1)!1=0 and (0,0)!1<(0,0)!0+time/1000 and (0,0)!1!=0 }  
rule : { [(0,0)!0,(0,-1)!1] } 100 {not isUndefined((-1,0)!1) and not isUndefined((0,-1)!1) and (0,0)!1=0 and (0,-1)!1!=0 and (0,-1)!1<(0,-1)!0+time/1000 and (-1,0)!1=0 and not isUndefined((1,-1)!1) and (1,-1)!1!=0} 
rule : { [(0,0)!0,(0,-1)!1] } 100 {not isUndefined((-1,0)!1) and not isUndefined((0,-1)!1) and (0,0)!1=0 and (0,-1)!1!=0 and (0,-1)!1<(0,-1)!0+time/1000 and (-1,0)!1=0 and isUndefined((1,0)!1)} 

% caso particular: columna de la izquierda, solo se puede bajar
rule : { [(0,0)!0,0] }        100 {isUndefined((1,-1)!1) and not isUndefined((1,0)!1)  and (1,0)!1=0  and (0,0)!1!=0}
rule : { [(0,0)!0,(-1,0)!1] } 100 {not isUndefined((-1,0)!1) and isUndefined((0,-1)!1) and (-1,0)!1!=0 and (0,0)!1=0}

% caso particular: fila de arriba, se puede ir a la derecha sin preguntar arriba
rule : { [(0,0)!0,0] }        100 {isUndefined((-1,1)!1) and not isUndefined((0,1)!1) and (0,1)!1=0 and (0,0)!1<(0,0)!0+time/1000 and (0,0)!1!=0 }  
rule : { [(0,0)!0,(0,-1)!1] } 100 {isUndefined((-1,0)!1) and not isUndefined((0,-1)!1) and (0,0)!1=0 and (0,-1)!1!=0 and (0,-1)!1<(0,-1)!0+time/1000 and not isUndefined((1,-1)!1) and (1,-1)!1!=0} 
rule : { [(0,0)!0,(0,-1)!1] } 100 {isUndefined((-1,0)!1) and not isUndefined((0,-1)!1) and (0,0)!1=0 and (0,-1)!1!=0 and (0,-1)!1<(0,-1)!0+time/1000 and isUndefined((1,0)!1)} 


rule : { (0,0) } 0 { t }

[prod-top-in]

rule:  { [(0,0)!0,(0,0)!1+send(output,(0,0)!1)] } 1 { portValue(thisPort)=-1 }
rule:  { [(0,0)!0,portValue(thisPort)] } 1 { portValue(thisPort)!=-1 }

[query-bot-in]

%borra producto
rule:  { [(0,0)!0,0+send(output,(0,0)!1)] } 1 { t }


%%%%%%%%%% Despacho %%%%%%%%%%%%
[despacho-reglas]
% celda: (y_celda,x_celda)!idx_tupla=val
% tupla: [idx_0,idx_1,...] -> sin espacios
% con -1 pregunta al inventario si hay lugar

% Movimiento del producto sacado del inventario
% Las tres reglas sigueintes preguntan por >0 para no actuar con el pedido.
rule : { (0,-1) } 100 { not isUndefined((0,-1)!0) and (0,-1)!0>0 and (0,0)!0=0 }
rule : { [0,0] } 100 { not isUndefined((0,1)!0) and (0,0)!0>0 and (0,1)!0=0 }
rule : { [0+send(output,(0,0)!0),0] } 100 { cellPos(1)=6 and (0,0)!0>0 }
% Movimiento del despachante buscando el producto
rule : {[-1+send(output,-1),0]} 100 { not isUndefined((0,1)!0) and (0,1)=[0,-1] and (0,0)!0=0 }
rule : {[0,0]} 100 { not isUndefined((0,-1)!0) and (0,0)=[0,-1]}
% always true (condicion default)
rule : { (0,0) } 0 { t }

[pedidosIn-regla]
rule : { [0,portValue(thisPort)] } 1 { portValue(thisPort)=-1 }

[despacho-ins-regla]
rule : { [0,-1] } 1 { portValue(thisPort)=0 }
rule : { [portValue(thisPort),0] } 1 { portValue(thisPort)>0 }
