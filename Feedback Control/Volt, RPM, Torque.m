V=3:0.1:12;
T=-7.8453/9*(V-12);
plot(V, T)
axis([0 15 0 10])
grid on
xlabel('����(V)')
ylabel('��ũ(Ncm)')
title('���а� ��ũ, ȸ���ӵ��� ����')
rpm=180/9*(V-3)+60; %�̳� �����ؾ���
yyaxis right
plot(V, rpm)
ylabel('rpm(rev/min)')
axis([0 15 0 300])
