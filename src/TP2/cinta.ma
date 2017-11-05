[top]
components : cinta %productos@Generator
in :  in in1 in2 in3 in4 in5 in6
out : out1 out2 out3 out4 out5 out6
link : in in@cinta
link : in1 in1@cinta
link : in2 in2@cinta
link : in3 in3@cinta
link : in4 in4@cinta
link : in5 in5@cinta
link : in6 in6@cinta
link : out1@cinta out1
link : out2@cinta out2
link : out3@cinta out3
link : out4@cinta out4
link : out5@cinta out5
link : out6@cinta out6

%[productos]
%distribution : Exponential
%mean : 0.12

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
