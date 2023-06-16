#include "mergesort.h"
#include <iostream>

void MergeSort::sort(){
    if(!ReadUnsortFile()){
        std::cerr<<"read data error"<<std::endl;
        return;
    }
    auto start = std::chrono::system_clock::now();
    mergeSort(0,data.size()-1);
    auto end = std::chrono::system_clock::now();

    auto elapsed = std::chrono::duration<double,std::milli>(end - start);
    std::cout<<elapsed.count() <<"ms" <<std::endl;
    WriteSortedFile();
}
void MergeSort::mergeSort(size_t low,size_t hight)
{
    if(low<hight){
        size_t mid = (low+hight)/2;
        mergeSort(low,mid);
        mergeSort(mid+1,hight);
        merge(low,mid,hight);
    }

}
void MergeSort::merge(size_t low,size_t mid,size_t hight)
{
    size_t i,h,j;
    h = low;
    j = mid + 1;
    i = 0 ;
    std::vector<unsigned int > temp(hight-low+1);
    while (h<=mid&&j<=hight) {
        if(data[h]<=data[j])
            temp[i++] = data[h++];
        else
            temp[i++] = data[j++];
    }
    if(h>mid)
        for(size_t k = j;k<=hight;++k)
            temp[i++] = data[k];
    else
        for(size_t k = h;k<=mid;++k)
            temp[i++] = data[k];
    i = low;
    for(auto t:temp)
        data[i++] = t;
}
