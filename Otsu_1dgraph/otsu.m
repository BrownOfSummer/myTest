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
    
    avg0=round(sum0/count0);        %前景灰度均值
    avg1=round(sum1/count1);        %背景灰度均值
    w0=count0/F;             %前景灰度权值
    w1=count1/F;             %背景灰度权值
    pic_avg=w0*avg0+w1*avg1;        %图像灰度均值 
    t1=w0*((avg0-pic_avg)^2)+w1*((avg1-pic_avg)^2);   %计算方差
    count0=0;
    sum0=0;
    if t1>t0
        t0=t1;
        T=x;                 %阈值
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
