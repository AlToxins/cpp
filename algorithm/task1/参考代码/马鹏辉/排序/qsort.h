#ifndef QSORT_H
#define QSORT_H
#include "msort.h"

//øÏÀŸ≈≈–Ú


class Qsort : public Msort
{
public:
    Qsort(std::string _unsort):Msort(_unsort){}
    void sort() override;
private:
    void qsort(size_t low,size_t high);
   // void partition(size_t m,size_t &p);
};

#endif // QSORT_H
