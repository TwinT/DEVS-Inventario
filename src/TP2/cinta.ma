[top]
components : cinta
in : in
out : out1 out2 out3 out4 out5 out6
link : in in@cinta
link : out1@cinta out1
link : out2@cinta out2
link : out3@cinta out3
link : out4@cinta out4
link : out5@cinta out5
link : out6@cinta out6

[cinta]
type : cell
dim : (1,6)
delay : transport
defaultDelayTime  : 10
border : nowrapped
neighbors : cinta(0,-1) cinta(0,0) cinta(0,1)
initialvalue : 0
initialCellsValue : cinta.val
in : in
out : out1 out2 out3 out4 out5 out6
link : in in@cinta(0,5)
link : out@cinta(0,5) out1
link : out@cinta(0,4) out2
link : out@cinta(0,3) out3
link : out@cinta(0,2) out4
link : out@cinta(0,1) out5
link : out@cinta(0,0) out6
localtransition : cinta-reglas

[cinta-reglas]
% celda: (y_celda,x_celda)!idx_tupla=val
% tupla: [idx_0,idx_1,...] -> sin espacios
rule : { [(0,0)!0,(0,1)!1] } { 100 } { NOT isUndefined((0,1)!1) AND (0,1)!1!=0 AND (0,1)!1>(0,1)!0 }
rule : { [(0,0)!0,0] } { 100 } { NOT isUndefined((0,-1)!1) AND (0,0)!1!=0 AND (0,0)!1>(0,0)!0 AND (0,-1)!1=0 } 
% rule : { (0,0)!1 + send(out6,(0,0)!1) } { 100 } { (0,0)!1!=0 AND (0,0)!1<=(0,0)!0 }
rule : { [(0,0)!0,0+send(out,32)] } { 100 } { (0,0)!1=0 AND (0,0)!1<=(0,0)!0 }
rule : { (0,0) } 0 { t } % always true (condicion default)
