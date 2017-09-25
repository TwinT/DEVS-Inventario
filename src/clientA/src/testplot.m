A = importdata('salida',' ');
hh = A(:,1); mm = A(:,2); ss = A(:,3); mss = A(:,4); n = A(:,5);
figure()
histogram(n,4,'Normalization','probability')
title('Distribucion de cantidad de pedidos')
xlabel('n')
ylabel('densidad')
t = hh.*(60*60)+mm.*60+ss+mss./1000; % en seg
dt = diff(t);
figure()
histogram(dt,'Normalization','pdf')
title('Distribucion exponencial de pedidos de producto')
xlabel('t [s]')
ylabel('densidad')