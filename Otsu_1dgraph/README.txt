
I try to find real peaks using Otsu to set the threshold auto
Otsutest_1dgraph.cpp : the common way to implement Otsu, reference is otsu.m and fenge.m
findpeak_otsu.cpp : modify from Otsutest_1dgraph.cpp;
                    I suggest score is num of points while realscore is score^2
test.cpp : modify from Otsutest_1dgraph.cpp ;
            I suggest score is num of points while realscore is pos in hist( nPeaks )

result: findpeak_otsu.cpp is best, but if many peaks has similar value, the threshold does't do well

I suggest to add differential into account;

//////////////////////////////////////////
findpeak_Otsu_diff.cpp: add the feature of differential;
                    I suggest bin count is diff; bin value(real score) is diff * score;  

