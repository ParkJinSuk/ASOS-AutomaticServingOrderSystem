x=128:0.1:255;
T=4.062*x+121.9;
rpm=0.4982*x+44.97;
ex_T=[200*3.25 250*3.25 300*3.25];
ex_rpm=[18*6 22*6 25*6 28.5*6];
x_T=[130 170 210];
x_rpm=[130 170 210 255];

plot(x, T, 'k')
hold on
plot(x_T, ex_T, 'ko')
grid on
axis([100 280 0 1400])
xlabel('PWM 입력값')
ylabel('Torque(gf?cm)')

yyaxis right
plot(x, rpm, 'b')
plot(x_rpm, ex_rpm, 'b*')
axis([100 280 0 200])
ylabel('rpm(rev/min)')
title('PWM 입력에 따른 RPM과 Torque')
legend('Torque Fitting Line', 'Torque Experimental Value', 'RPM Fitting Line', 'RPM Experimental Value')
