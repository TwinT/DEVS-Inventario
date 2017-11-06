[top]
components : inventario
in :  in1 in2 in3 in4 in5
out : out1 out2 out3 out4 out5
link : in1 in1@inventario
link : in2 in2@inventario
link : in3 in3@inventario
link : in4 in4@inventario
link : in5 in5@inventario
link : out1@inventario out1
link : out2@inventario out2
link : out3@inventario out3
link : out4@inventario out4
link : out5@inventario out5

[inventario]
type : cell
dim : (5,5)
delay : transport
defaultDelayTime  : 0
border : nowrapped

neighbors : inventario(-1,-1) inventario(-1,0) inventario(-1,1)
neighbors : inventario(0,-1)  inventario(0,0)  inventario(0,1)
neighbors : inventario(1,-1)  inventario(1,0)  inventario(1,1)

initialvalue : 0
initialCellsValue : inventario.val
in : in1 in2 in3 in4 in5
out : out1 out2 out3 out4 out5
link : in5 in@inventario(0,4)
link : in4 in@inventario(0,3)
link : in3 in@inventario(0,2)
link : in2 in@inventario(0,1)
link : in1 in@inventario(0,0)
link : output@inventario(0,4) out5
link : output@inventario(0,3) out4
link : output@inventario(0,2) out3
link : output@inventario(0,1) out2
link : output@inventario(0,0) out1

localtransition : inventario-reglas

zone : left-rule  { (0,0)..(5,0) }
zone : right-rule { (0,5)..(5,5) }


[left-rule]

% hacia abajo si está vacío
rule : { [(0,0)!0,0] } 100 { not isUndefined((1,0)!1) and (1,0)!1=0 and (0,0)!1>0} 
rule : { [(0,0)!0,(-1,0)!1] } 100 { not isUndefined((-1,0)!1) and (0,0)!1=0 and (-1,0)!1>0}

% hacia la derecha si su fecha de vencimiento es menor que la de la columna derecha
% y gana la competencia con (-1,1)
rule : { [(0,0)!0,0]} 100 {not isUndefined((-1,1)!1) and (0,0)!1<(-1,1)!1 and (0,0)!1>0 and (0,0)!1<(0,0)!0+time/1000}
rule : { [(0,0)!0,0]} 100 {isUndefined((-1,1)!1) and (0,0)!1>0 and (0,0)!1<(0,0)!0+time/1000}
rule : { (0,0) } 0 { t }

[right-rule]

% hacia abajo si está vacío y (1,-1) quiere entrar pero es menor a (1,-1)
rule : { [(0,0)!0,0] }        100 {not isUndefined((1,-1)!1) and (1,-1)!1<(1,-1)!0+time/1000 and (0,0)!1>0 and (0,0)!1<(1,-1)!1}  

% absorción del de la izquierda o el de arriba
% izquierda
rule : { [(0,0)!0,(0,-1)!1] } 100 {not isUndefined((-1,0)!1) and (0,0)!1=0 and (-1,0)!1>=(0,-1)!1} 
% arriba
rule : { [(0,0)!0,(-1,0)!1] } 100 {not isUndefined((-1,0)!1) and (0,0)!1=0 and (-1,0)!1<(0,-1)!1} 
% casillero de arriba (0,5)
rule : { [(0,0)!0,(0,-1)!1] } 100 {isUndefined((-1,0)!1) and (0,0)!1=0 and (0,-1)!1<(0,-1)!0+time/1000 and (0,-1)!1>0} 
rule : { (0,0) } 0 { t }

[inventario-reglas]

% hacia abajo si está vacío y (1,-1) quiere entrar pero es menor a (1,-1)
rule : { [(0,0)!0,0] }        100 {not isUndefined((1,-1)!1) and (1,-1)!1<(1,-1)!0+time/1000 and (0,0)!1>0 and (0,0)!1<(1,-1)!1}  

% absorción del de la izquierda o el de arriba
% izquierda
rule : { [(0,0)!0,(0,-1)!1] } 100 {not isUndefined((-1,0)!1) and (0,0)!1=0 and (-1,0)!1>=(0,-1)!1} 
% arriba
rule : { [(0,0)!0,(-1,0)!1] } 100 {not isUndefined((-1,0)!1) and (0,0)!1=0 and (-1,0)!1<(0,-1)!1} 
% casillero de arriba (,5)
rule : { [(0,0)!0,(-1,0)!1] } 100 {isUndefined((-1,0)!1) and (0,0)!1=0 and (-1,0)!1<(-1,0)!0+time/1000 and (-1,0)!1>0} 

%hacia la derecha
rule : { [(0,0)!0,0] } 100 {not isUndefined((-1,1)!1) and (0,0)!1<(-1,1)!1 and (0,0)!1>0 and (0,0)!1<(0,0)!0+time/1000}
rule : { [(0,0)!0,0] } 100 { isUndefined((-1,1)!1) and (0,0)!1>0 and (0,0)!1<(0,0)!0+time/1000 }

rule : { (0,0) } 0 { t }


