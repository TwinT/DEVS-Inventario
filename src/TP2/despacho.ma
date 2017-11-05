[top]
components : despacho %pedidos@Generator
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

%[productos]
%distribution : Exponential
%mean : 0.12

[depacho]
type : cell
dim : (1,5)
delay : transport
defaultDelayTime  : 0
border : nowrapped
neighbors : despacho(0,-1) despacho(0,0) despacho(0,1)
initialvalue : 0
%initialCellsValue : despacho.val
in : pedidosIn in1 in2 in3 in4 in5
out : pedidosOut out1 out2 out3 out4 out5
link : pedidosIn in@cinta(0,5)
link : in5 in@cinta(0,4)
link : in4 in@cinta(0,3)
link : in3 in@cinta(0,2)
link : in2 in@cinta(0,1)
link : in1 in@cinta(0,0)
link : output@cinta(0,5) pedidosOut
link : output@cinta(0,4) out5
link : output@cinta(0,3) out4
link : output@cinta(0,2) out3
link : output@cinta(0,1) out2
link : output@cinta(0,0) out1
portintransition : in@cinta(0,5) pedidosIn-regla
portintransition : in@cinta(0,4) in5-regla
portintransition : in@cinta(0,3) in4-regla
portintransition : in@cinta(0,2) in3-regla
portintransition : in@cinta(0,1) in2-regla
portintransition : in@cinta(0,0) in1-regla
localtransition : despacho-reglas

[cinta-reglas]
% celda: (y_celda,x_celda)!idx_tupla=val
% tupla: [idx_0,idx_1,...] -> sin espacios
rule : { [(0,0)!0,(0,1)!1] } { 100 } { NOT isUndefined((0,1)!1) AND (0,1)!1!=0 AND (0,1)!1>(0,1)!0+time/1000 }
rule : { [(0,0)!0,0] } { 100 } { NOT isUndefined((0,-1)!1) AND (0,0)!1!=0 AND (0,0)!1>(0,0)!0+time/1000 AND (0,-1)!1=0 }
rule : { [(0,0)!0,(0,0)!1+send(output,-1)] } { 100 } { (0,0)!1!=0 AND (0,0)!1<=(0,0)!0+time/1000 } % con -1 pregunta al inventario si hay lugar
% rule : { [(0,0)!0,0+send(output,(0,0)!1)] } { 0 } { (0,0)!1=-1 }
rule : { (0,0) } 0 { t } % always true (condicion default)

[pedidosIn-regla]
rule : { [(0,0)!0,portValue(thisPort)] } 1 { t }

[in1-regla]
rule : { [(0,0)!0,0+send(output,(0,0)!1)] } 1 { portValue(thisPort)!=0 }
[in2-regla]
rule : { [(0,0)!0,0+send(output,(0,0)!1)] } 1 { portValue(thisPort)!=0 }
[in3-regla]
rule : { [(0,0)!0,0+send(output,(0,0)!1)] } 1 { portValue(thisPort)!=0 }
[in4-regla]
rule : { [(0,0)!0,0+send(output,(0,0)!1)] } 1 { portValue(thisPort)!=0 }
[in5-regla]
rule : { [(0,0)!0,0+send(output,(0,0)!1)] } 1 { portValue(thisPort)!=0 }
[in6-regla]
rule : { [(0,0)!0,0+send(output,(0,0)!1)] } 1 { portValue(thisPort)!=0 }
