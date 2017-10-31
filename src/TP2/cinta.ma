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
defaultDelayTime  : 10
border : nowrapped
neighbors : cinta(0,-1) cinta(0,0) cinta(0,1)
initialvalue : 0
initialCellsValue : cinta.val
in : in in1 in2 in3 in4 in5 in6
out : out1 out2 out3 out4 out5 out6
link : in in@cinta(0,5)
link : in1 in1@cinta(0,0)
link : in2 in2@cinta(0,1)
link : in3 in3@cinta(0,2)
link : in4 in4@cinta(0,3)
link : in5 in5@cinta(0,4)
link : in6 in6@cinta(0,5)
link : output@cinta(0,5) out1
link : output@cinta(0,4) out2
link : output@cinta(0,3) out3
link : output@cinta(0,2) out4
link : output@cinta(0,1) out5
link : output@cinta(0,0) out6
portintransition : in@cinta(0,5) in-regla
% portintransition : in1@cinta(0,0) in1-regla
% portintransition : in2@cinta(0,1) in2-regla
% portintransition : in3@cinta(0,2) in3-regla
% portintransition : in4@cinta(0,3) in4-regla
% portintransition : in5@cinta(0,4) in5-regla
% portintransition : in6@cinta(0,5) in6-regla
localtransition : cinta-reglas

[cinta-reglas]
% celda: (y_celda,x_celda)!idx_tupla=val
% tupla: [idx_0,idx_1,...] -> sin espacios
rule : { [(0,0)!0,(0,1)!1] } { 100 } { NOT isUndefined((0,1)!1) AND (0,1)!1!=0 AND (0,1)!1>(0,1)!0+time/1000 }
rule : { [(0,0)!0,0] } { 100 } { NOT isUndefined((0,-1)!1) AND (0,0)!1!=0 AND (0,0)!1>(0,0)!0+time/1000 AND (0,-1)!1=0 } 
rule : { [(0,0)!0,0+send(output,(0,0)!1)] } { 100 } { (0,0)!1!=0 AND (0,0)!1<=(0,0)!0+time/1000 }
rule : { (0,0) } 0 { t } % always true (condicion default)

[in-regla]
rule : { [(0,0)!0,portValue(thisPort)] } 1 { t }
