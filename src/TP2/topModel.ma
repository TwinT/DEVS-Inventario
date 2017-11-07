#include(cinta.ma)
#include(inventario.ma)
#include(despacho.ma)

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

link : @cinta qtopin1@inventario
link : @cinta qtopin2@inventario
link : @cinta qtopin3@inventario
link : @cinta qtopin4@inventario
link : @cinta qtopin5@inventario
link : @cinta qtopin6@inventario

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

#Cinta

#Inventario

#Despacho
