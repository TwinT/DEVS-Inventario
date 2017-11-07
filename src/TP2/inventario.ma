[top]
components : inventario
in :  qtopin1 qtopin2 qtopin3 qtopin4 qtopin5 qtopin6 pin1 pin2 pin3 pin4 pin5 pin6 qbotin1 qbotin2 qbotin3 qbotin4 qbotin5 qbotin6
out : qtopout1 qtopout2 qtopout3 qtopout4 qtopout5 qtopout6 pout1 pout2 pout3 pout4 pout5 pout6

link : qtopin1 qtopin1@inventario
link : qtopin2 qtopin2@inventario
link : qtopin3 qtopin3@inventario
link : qtopin4 qtopin4@inventario
link : qtopin5 qtopin5@inventario
link : qtopin6 qtopin6@inventario

link : qbotin1 qbotin1@inventario
link : qbotin2 qbotin2@inventario
link : qbotin3 qbotin3@inventario
link : qbotin4 qbotin4@inventario
link : qbotin5 qbotin5@inventario
link : qbotin6 qbotin6@inventario

link : pin1 pin1@inventario
link : pin2 pin2@inventario
link : pin3 pin3@inventario
link : pin4 pin4@inventario
link : pin5 pin5@inventario
link : pin6 pin6@inventario

link : qtopout1@inventario qtopout1
link : qtopout2@inventario qtopout2
link : qtopout3@inventario qtopout3
link : qtopout4@inventario qtopout4
link : qtopout5@inventario qtopout5
link : qtopout6@inventario qtopout6

link : pout1@inventario pout1
link : pout2@inventario pout2
link : pout3@inventario pout3
link : pout4@inventario pout4
link : pout5@inventario pout5
link : pout6@inventario pout6

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
in : qtopin1 qtopin2 qtopin3 qtopin4 qtopin5 qtopin6 pin1 pin2 pin3 pin4 pin5 pin6 qbotin1 qbotin2 qbotin3 qbotin4 qbotin5 qbotin6
out : qtopout1 qtopout2 qtopout3 qtopout4 qtopout5 qtopout6 pout1 pout2 pout3 pout4 pout5 pout6
link : qtopin6 in@inventario(0,5)
link : qtopin5 in@inventario(0,4)
link : qtopin4 in@inventario(0,3)
link : qtopin3 in@inventario(0,2)
link : qtopin2 in@inventario(0,1)
link : qtopin1 in@inventario(0,0)

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

link : poutput@inventario(5,5) pout6
link : poutput@inventario(5,4) pout5
link : poutput@inventario(5,3) pout4
link : poutput@inventario(5,2) pout3
link : poutput@inventario(5,1) pout2
link : poutput@inventario(5,0) pout1

portintransition : in@inventario(0,5) query-top-in
portintransition : in@inventario(0,4) query-top-in
portintransition : in@inventario(0,3) query-top-in
portintransition : in@inventario(0,2) query-top-in
portintransition : in@inventario(0,1) query-top-in
portintransition : in@inventario(0,0) query-top-in

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

[query-top-in]

%mantiene valor
rule : { [(0,0)!0,(0,0)!1+send(output,(0,0)!1)] } 1 { t }

[prod-top-in]

rule:  { [(0,0)!0,portValue(thisPort)] } 1 { t }

[query-bot-in]

%borra producto
rule:  { [(0,0)!0,0+send(output,(0,0)!1)] } 1 { t }

