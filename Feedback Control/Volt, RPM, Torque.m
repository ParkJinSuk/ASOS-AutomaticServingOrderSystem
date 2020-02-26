V=3:0.1:12;
T=-7.8453/9*(V-12);
plot(V, T)
axis([0 15 0 10])
grid on
xlabel('전압(V)')
ylabel('토크(Ncm)')
title('전압과 토크, 회전속도의 관계')
rpm=180/9*(V-3)+60; %이놈 수정해야함
yyaxis right
plot(V, rpm)
ylabel('rpm(rev/min)')
axis([0 15 0 300])
