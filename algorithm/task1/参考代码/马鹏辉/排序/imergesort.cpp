#include "imergesort.h"
#include <iostream>
#include <fstream>
void ImergeSort::sort(){
    if(!ReadUnsortFile()){
        std::cerr<<"read data error"<<std::endl;
        return;
    }
    LINK.resize(data.size()+1,0);
    auto start = std::chrono::system_clock::now();
    size_t p = 0;
    mergeSort(0,data.size()-1,p);
    auto end = std::chrono::system_clock::now();

    auto elapsed = std::chrono::duration<double,std::milli>(end - start);
    std::cout<<elapsed.count() <<"ms" <<std::endl;

    WriteSortedFile(p);
}

void ImergeSort::insertSort(size_t low,size_t hight,size_t &p){
    p = low+1;
    for(size_t i = low+1;i<=hight;++i){
        unsigned int key = data[i];
        size_t j = p;
        unsigned int t = 0;
        while (j!=0&&key>data[j-1]) {
            t = j;
            j = LINK[j];
        }
        if(key<=data[j-1]){//插入
            LINK[i+1] = j;
            if(j==p) p = i+1;//更新最小值指针
            else LINK[t] = i+1;
        }
        if(j==0){//插入到尾部
            LINK[t] = i+1;
            LINK[i+1] = 0;
        }
    }
}

void ImergeSort::mergeSort(size_t low, size_t hight, size_t &p){
    if(hight-low+1<=20)
        insertSort(low,hight,p);
    else {
        unsigned int mid = (low+hight)/2;
        size_t q,r;
        mergeSort(low,mid,q);
        mergeSort(mid+1,hight,r);
        merge(q,r,p);
    }
}

void ImergeSort::merge(size_t q, size_t r, size_t &p){
    size_t i = q,j = r,k = 0;
    while (i!=0&&j!=0) {
        if(data[i-1]<=data[j-1]){
            LINK[k] = i;
            k = i;
            i = LINK[i];
        }else {
            LINK[k] = j;
            k = j;
            j = LINK[j];
        }
    }
    if(i==0) LINK[k] = j;
    else LINK[k] = i;
    p = LINK[0];
}

bool ImergeSort::WriteSortedFile(size_t &p){
    std::ofstream write(sortedFile);
    if(!write)
    {
        std::cerr<<"Can't open the "<<sortedFile<<" file"<<std::endl;
        return false;
    }
    while (p!=0) {
        write<<data[p-1]<<' ';
        p = LINK[p];
    }
    write.close();
    return true;
}
