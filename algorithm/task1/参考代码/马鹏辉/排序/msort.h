#ifndef MSORT_H
#define MSORT_H
#include <string>
#include <vector>
#include <chrono>


// ≈≈–Ú¿‡ª˘¿‡
class Msort
{
public:
    Msort(std::string _unsort):unsortFile(_unsort),sortedFile("sorted"+_unsort){}
    virtual void sort() = 0;
protected:
    std::string unsortFile;
    std::string sortedFile;
    std::vector<unsigned int> data;

    virtual bool ReadUnsortFile();
    virtual bool WriteSortedFile();

};

#endif // MSORT_H
