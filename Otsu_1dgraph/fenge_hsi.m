%%  ��HSI�ռ��½��в�ɫͼ��ָ�
clc
close all
clear all
%%  ��RGB�ռ�ת����HSI�ռ�
for k=1:40
close all
I = imread(strcat('F:\LPJ\firetest1\ceshi\zhong1\',num2str(k),'.bmp'));
Ir = I(:,:,1);
Ig = I(:,:,2);
Ib = I(:,:,3);
figure,imshow(I),title('ԭͼ')
I_hsi = rgb2hsi_2(I);
% figure,imshow(I_hsi),title('HSI�ռ�ͼ��')
I_h = I_hsi(:,:,1);
% figure,imshow(I_h),title('H����')
I_s = I_hsi(:,:,2);
% figure,imshow(I_s),title('S����')
I_i = I_hsi(:,:,3);
% figure,imshow(I_i),title('I����')

%%  ��ֵȡS>0.6 H<=60(�����H�Ѿ���һ����ȡpi/3/2*pi=1/6)

[M,N] = size(I_h);
for i = 1:M
    for j = 1:N
        if (I_s(i,j)>0.8)
            if (I_h(i,j)>1/6)
                Ir(i,j) = 0;
                Ig(i,j) = 0;
                Ib(i,j) = 0;
            end
        else
            if(I_i(i,j)<0.5)
                Ir(i,j) = 0;
                Ig(i,j) = 0;
                Ib(i,j) = 0;
            end
        end
    end
end
I1 = cat(3,Ir,Ig,Ib);
% figure,imshow(I1),title('���ƻ�������')

%%  ���������
Igray = rgb2gray(I1);
% figure,imshow(Igray),title('���ƻ�������Ҷ�')
H = imhist(Igray);
% H = H(2:end);               %��Ҫ��ɫ������ʱ����255*1��С��1
% figure, bar(H);
% figure,imhist(rgb2gray(I));
T0 = 0;
Maxfc = -inf;
for T=1:1:254
    N1 = sum(H(1:T));
    N0 = sum(H(T+1:end));
    w1 = N1/sum(H);
    w0 = N0/sum(H);
    Pi = H./(sum(H));
    u0 = 0;
    for i=T+1:1:255
        u0 = u0 + i*Pi(i)/w0;
    end
    u1 = 0;
    for i=1:1:T
        u1 = u1+i*Pi(i)/w1;
    end
    u = u0*w0 + u1*w1;
    fangcha = w0*(u0 - u)^2 + w1*(u1 - u)^2;
    if fangcha > Maxfc
        T0 = T; 
        Maxfc = fangcha;
    end
end
disp(T0)
for i=1:1:M
    for j=1:1:N
        if(Igray(i,j)<T0)
            Ir(i,j) = 0;
            Ig(i,j) = 0;
            Ib(i,j) = 0;
        end
    end
end
I1 = cat(3,Ir,Ig,Ib);
figure,imshow(I1),title('�ָ��')
% imwrite(I1,strcat('F:\LPJ\firetest1\fenge\',[num2str(k),'1.bmp']));
imwrite(I1,strcat('F:\LPJ\firetest1\zhong\',num2str(k), '.bmp'));
end
