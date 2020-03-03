w=0:0.1:24;
T_1=1^2*10.3053./w;
T_2=2^2*10.3053./w;
T_3=3^2*10.3053./w;
T_4=4^2*10.3053./w;
T_5=5^2*10.3053./w;
T_6=6^2*10.3053./w;

plot(w, T_1)
hold on
plot(w, T_2)
plot(w, T_3)
plot(w, T_4)
plot(w, T_5)
plot(w, T_6)
grid on
axis([0 24 0 40])

xlabel('각속도(rad/s)')
ylabel('토크(kgf?cm)')

legend('1V', '2V', '3V', '4V', '5V', '6V')