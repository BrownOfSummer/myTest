%test harris
clc
%clear
close all

%% harris
% R = det(M) - a*(trace(M))^2
I = checkerboard(50,2,2);
window = 3;
% GaussWeight = [0.000007 0.000425 0.001704 0.000425 0.000007;
%                0.000425 0.027398 0.109878 0.027398 0.000425;
%                0.001704 0.109878 0.440655 0.109878 0.001704;
%                0.000425 0.027398 0.109878 0.027398 0.000425;
%                0.000007 0.000425 0.001704 0.000425 0.000007];

GaussWeight = [0.001631 0.037126 0.001631
               0.037126 0.844973 0.037126
               0.001631 0.037126 0.001631];
[row, col] = size(I);
% dx = double(abs(I(:,2:end) - I(:,1:end-1)));
dx = double(I(:,2:end) - I(:,1:end-1));
dx = [dx,zeros(row,1)];

% dy = double(abs(I(2:end,:) - I(1:end-1,:)));
dy = double(I(2:end,:) - I(1:end-1,:));
dy = [dy;zeros(1,col)];
figure,imshow(dx),title('dx');
figure,imshow(dy),title('dy');
Ix2 = dx.^2;
Iy2 = dy.^2;
pic = zeros(row, col);
wstart = (window - 1)/2;
Hcorner = zeros(1000,2);

maxR = 0;
for i=wstart+1 :row-wstart
    for j=wstart+1 :col-wstart
        A = sum( sum( Ix2(i-wstart:i+wstart, j-wstart:j+wstart).*GaussWeight ) );
        B = sum( sum( Iy2(i-wstart:i+wstart, j-wstart:j+wstart).*GaussWeight ) );
        %C = sum( sum( abs(dx(i-wstart:i+wstart, j-wstart:j+wstart) .* dy(i-wstart:i+wstart, j-wstart:j+wstart)) .*GaussWeight ) );
        C = sum( sum( dx(i-wstart:i+wstart, j-wstart:j+wstart) .* dy(i-wstart:i+wstart, j-wstart:j+wstart) .*GaussWeight ) );
        R = A * B - C^2 - 0.04*(A + B)^2;
        if(R > maxR)
            maxR = R;
        end
    end
end
count = 0;
count2 = 0;
for i=wstart+1 :row-wstart
    for j=wstart+1 :col-wstart
        A = sum( sum( Ix2(i-wstart:i+wstart, j-wstart:j+wstart).*GaussWeight ) );
        B = sum( sum( Iy2(i-wstart:i+wstart, j-wstart:j+wstart).*GaussWeight ) );
        %C = sum( sum( abs(dx(i-wstart:i+wstart, j-wstart:j+wstart) .* dy(i-wstart:i+wstart, j-wstart:j+wstart)) .*GaussWeight ) );
        C = sum( sum( dx(i-wstart:i+wstart, j-wstart:j+wstart) .* dy(i-wstart:i+wstart, j-wstart:j+wstart) .*GaussWeight ) );
        R = A * B - C^2 - 0.04*(A + B)^2;

        if(R > 0.04*maxR)
            count2 = count2 + 1;
            if( max(max(I(i-wstart:i+wstart, j-wstart:j+wstart))) <= I(i,j) ) 
               pic(i,j) = 1;
               count = count + 1;
               Hcorner(count,1) = j;
               Hcorner(count,2) = row - i + 1; 
            end
        end
    end
end

Hcorner = Hcorner(1:count,:);
figure,imshow(pic),title('harris');
figure,imshow(I),title('src');
hold on
plot(Hcorner(:,1),Hcorner(:,2),'r*');