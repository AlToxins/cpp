#ifndef MERGESORT_H
#define MERGESORT_H
#include "msort.h"

// πÈ≤¢≈≈–Ú
class MergeSort : public Msort
{
public:
    MergeSort(std::string _unsort):Msort(_unsort){}
    void sort() override;
private:
    void mergeSort(size_t low,size_t hight);
    void merge(size_t low,size_t mid,size_t hight);
};

#endif // MERGESORT_H
