function pic=otsu(pic)
% pic=double(rgb2gray(pic));
max_pic=max(max(pic));
min_pic=min(min(pic));
[m,n]=size(pic);
count0=0;
sum0=0;
F=m*n;
t0=0;
T=0;
for x=min_pic+1:1:max_pic-1
    for i=1:1:m
        for j=1:1:n
            if pic(i,j)<x
                count0=count0+1;
                sum0=sum0+pic(i,j);
            end
        end
    end
    count1=F-count0;
    sum1=sum(sum(pic))-sum0; 
    
    avg0=round(sum0/count0);        %ǰ���ҶȾ�ֵ
    avg1=round(sum1/count1);        %�����ҶȾ�ֵ
    w0=count0/F;             %ǰ���Ҷ�Ȩֵ
    w1=count1/F;             %�����Ҷ�Ȩֵ
    pic_avg=w0*avg0+w1*avg1;        %ͼ��ҶȾ�ֵ 
    t1=w0*((avg0-pic_avg)^2)+w1*((avg1-pic_avg)^2);   %���㷽��
    count0=0;
    sum0=0;
    if t1>t0
        t0=t1;
        T=x;                 %��ֵ
    end
end
for i=1:1:m
    for j=1:1:n
        if pic(i,j)>T
            pic(i,j)=255;
        else
            pic(i,j)=0;
        end
    end
end
% figure;
% imshow(pic)
end
