#ifndef IMERGESORT_H
#define IMERGESORT_H
#include "msort.h"


//改进的归并排序

class ImergeSort : public Msort
{
public:
    ImergeSort(std::string _unsort):Msort(_unsort) {}
    void sort() override;
protected:
    bool WriteSortedFile(size_t &p);
private:
    std::vector<unsigned int> LINK;
    void insertSort(size_t low,size_t hight,size_t &p);
    void mergeSort(size_t low,size_t hight,size_t &p);
    void merge(size_t q,size_t r,size_t &p);

};

#endif // IMERGESORT_H
