#include "qsort.h"
#include<iostream>
void Qsort::sort(){
    if(!ReadUnsortFile()){
        std::cerr<<"read data error"<<std::endl;
        return;
    }
    auto start = std::chrono::system_clock::now();
    qsort(0,data.size()-1);
    auto end = std::chrono::system_clock::now();

    auto elapsed = std::chrono::duration<double,std::milli>(end - start);
    std::cout<<elapsed.count() <<"ms" <<std::endl;
    WriteSortedFile();
}

void Qsort::qsort(size_t low, size_t high){
    if(high<=low)
        return;
    size_t i = low;
    size_t j = high+1;
    unsigned int key = data[low];
    while (true) {
        while (data[++i]<key) {
            if(i==high) break;
        }
        while (data[--j]>key) {
            if(j==low)  break;
        }
        if(i>=j)    break;
        unsigned int temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
    unsigned int temp = data[low];
    data[low] = data[j];
    data[j] = temp;
    qsort(low,j);
    qsort(j+1,high);
}

