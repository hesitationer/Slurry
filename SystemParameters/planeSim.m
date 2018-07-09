%%%��άƽ�����
%%%�����������
%�ڵ�
data = reshape(laserPoints3D',3,21402*2/3);
iter = 1000; 

%%% �������ݵ�
 figure;plot3(data(1,:),data(2,:),data(3,:),'.');hold on; % ��ʾ���ݵ�
 number = size(data,2); % �ܵ���
 bestParameter1=0; bestParameter2=0; bestParameter3=0; % ���ƥ��Ĳ���
 sigma = 0.02;
 pretotal=0;     %�������ģ�͵����ݵĸ���

 xAxis = -0.3:0.02:0.3;
 yAxis = -0.1:0.02:0.1;
  [x,y] = meshgrid(xAxis, yAxis);
 z = -0.071 * x -2.1 * y + 0.363;
 surf(x, y, z);
%{
for i=1:iter
 %%% ���ѡ��������
     idx = randperm(number,3); 
     sample = data(:,idx); 


     %%%���ֱ�߷��� z=ax+by+c
     plane = zeros(1,3);
     x = sample(:, 1);
     y = sample(:, 2);
     z = sample(:, 3);

     a = ((z(1)-z(2))*(y(1)-y(3)) - (z(1)-z(3))*(y(1)-y(2)))/((x(1)-x(2))*(y(1)-y(3)) - (x(1)-x(3))*(y(1)-y(2)));
     b = ((z(1) - z(3)) - a * (x(1) - x(3)))/(y(1)-y(3));
     c = z(1) - a * x(1) - b * y(1);
     plane = [a b -1 c];


     mask=abs(plane*[data; ones(1,size(data,2))]);    %��ÿ�����ݵ����ƽ��ľ���
     total=sum(mask<sigma);              %�������ݾ���ƽ��С��һ����ֵ�����ݵĸ���


     if total>pretotal            %�ҵ��������ƽ�������������ƽ��
         pretotal=total;
         bestplane=plane;          %�ҵ���õ����ƽ��
    end  
 end
 %��ʾ���������ϵ�����
mask=abs(bestplane*[data; ones(1,size(data,2))])<sigma;    
hold on;
k = 1;
for i=1:length(mask)
    if mask(i)
        inliers(1,k) = data(1,i);
        inliers(2,k) = data(2,i);
        plot3(data(1,i),data(2,i),data(3,i),'r+');
        k = k+1;
    end
end

pretotal
 %%% �������ƥ��ƽ��
 bestParameter1 = bestplane(1);
 bestParameter2 = bestplane(2);
 bestParameter3 = bestplane(4);
 xAxis = min(inliers(1,:)):0.01:max(inliers(1,:));
 yAxis = min(inliers(2,:)):0.01:max(inliers(2,:));
 [x,y] = meshgrid(xAxis, yAxis);
 z = bestParameter1 * x + bestParameter2 * y + bestParameter3;
 surf(x, y, z);
 title(['bestPlane:  z =  ',num2str(bestParameter1),'x + ',num2str(bestParameter2),'y + ',num2str(bestParameter3)]);
 %}