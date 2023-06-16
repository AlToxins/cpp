#include "msort.h"
#include <fstream>
#include <iostream>

bool Msort::ReadUnsortFile()
{
    std::ifstream read(unsortFile);
    if(!read){
        std::cerr<<"Can't open the "<<unsortFile<<" file"<<std::endl;
        return false;
    }
    unsigned int temp = 0;
    while (!read.eof()) {
        read>>temp;
        data.push_back(temp);
    }
    read.close();
    return true;
}

bool Msort::WriteSortedFile()
{
    std::ofstream write(sortedFile);
    if(!write)
    {
        std::cerr<<"Can't open the "<<sortedFile<<" file"<<std::endl;
        return false;
    }
    for(auto t:data){
        write<<t<<' ';
    }
    write.close();
    return true;

}
