dataset = fopen('dataset.csv','r');
output = fopen('output.csv','w');
k=10;
%k = input('�п�J K = ');
%if isempty(k) k=5; end
%mode = intput('�п�J mode ( 0:categorical  1:numerical )  ');
%if isempty(mode) mode=1; end

data = csvread('dataset.csv',1);% �N data.csv �����eŪ��x�} A
target = data(:,end); % �^�� lable
data(:,end) = [];
distance = pdist2(data,data); % �p���V�q���Z��
[sorted,index] = sort(distance,2); % �Z���Ƨ�
clear distance data;

index_out = index(:,1:k); % �^���̾F�� K ���I
lable = sum(reshape([target(index_out,1)],1000,k),2); % �p��w����
lable(lable < k/2) = 0 ;
lable(lable >= k/2) = 1 ;
index_out = [index_out-1 lable target]; % �X�־F���I�B�w���ȡB��ڭ�

for i = 1:k  % ��X���� Title ���ɮפ�
    fprintf(output,'NO.%d ',i);
    fprintf(output,',');
end
fprintf(output,'prediction,True lable\n');
dlmwrite('output.csv',index_out,'-append'); % ��X���ׯx�}�ιw�����G

fclose('all');