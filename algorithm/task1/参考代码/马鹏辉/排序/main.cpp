#include <iostream>
#include "createrandom.h"
#include "mergesort.h"
#include "imergesort.h"
#include "qsort.h"

int main()
{
        size_t test[5] = {3000,5000,10000,30000,50000};
        CreateRandom *rdm = nullptr;
        Msort* testSort[3];
        std::cout<<"first line : mergeSort,second line : improve merge sort,third line : quick sort"<<std::endl;
        for(size_t t:test){
            rdm = new CreateRandom(t);
            rdm->GenerateFile();
            testSort[0] = new MergeSort(rdm->getFileName());
            testSort[2] = new ImergeSort(rdm->getFileName());
            testSort[1] = new Qsort(rdm->getFileName());
            delete rdm;
            rdm = nullptr;
            std::cout<<"data size : "<<t<<std::endl;
            for(auto tsort:testSort){
                tsort->sort();
                delete  tsort;
                tsort = nullptr;

            }
        }
    return 0;

}
