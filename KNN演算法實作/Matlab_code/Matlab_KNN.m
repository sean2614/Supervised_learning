dataset = fopen('dataset.csv','r');
output = fopen('output.csv','w');
k=10;
%k = input('請輸入 K = ');
%if isempty(k) k=5; end
%mode = intput('請輸入 mode ( 0:categorical  1:numerical )  ');
%if isempty(mode) mode=1; end

data = csvread('dataset.csv',1);% 將 data.csv 的內容讀到矩陣 A
target = data(:,end); % 擷取 lable
data(:,end) = [];
distance = pdist2(data,data); % 計算兩向量之距離
[sorted,index] = sort(distance,2); % 距離排序
clear distance data;

index_out = index(:,1:k); % 擷取最鄰近的 K 個點
lable = sum(reshape([target(index_out,1)],1000,k),2); % 計算預測值
lable(lable < k/2) = 0 ;
lable(lable >= k/2) = 1 ;
index_out = [index_out-1 lable target]; % 合併鄰近點、預測值、實際值

for i = 1:k  % 輸出答案 Title 到檔案中
    fprintf(output,'NO.%d ',i);
    fprintf(output,',');
end
fprintf(output,'prediction,True lable\n');
dlmwrite('output.csv',index_out,'-append'); % 輸出答案矩陣及預測結果

fclose('all');