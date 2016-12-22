/*************************************************************************
    > File Name: string_charstart.cpp
    > Author: li_pengju
    > Mail: li_pengju@vobile.cn 
    > Copyright (c) Vobile Inc. All Rights Reserved
    > Created Time: 2016-12-16 16:02:18
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main()
{
    char arr1[] = "Tihs is test1 !";
    char arr2[] = "This is test2 !";

    string str = string(arr1);
    cout<<"arr = "<<arr1<<endl;
    cout<<"str = "<<arr1<<endl;

    vector<char *>_idList;
    _idList.push_back(arr1);
    _idList.push_back(arr2);
    cout<<"arr1 = "<<_idList[0]<<endl;
    cout<<"arr2 = "<<_idList[1]<<endl;
    return 0;
}
