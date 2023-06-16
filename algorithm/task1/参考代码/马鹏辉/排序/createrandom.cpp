#include "createrandom.h"
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>

bool CreateRandom::GenerateFile()
{
    std::ofstream write;
    write.open(filename);
    if(!write)
    {
        std::cerr<<"Can't open the "<<filename<<" file"<<std::endl;
        return false;
    }

    unsigned int * data = new unsigned int [size];
    for(unsigned int i = 0;i<size;++i)
        data[i] = i;

    std::random_device rd;//随机种子
    std::minstd_rand gen(rd());//使用的随机引擎，LGC
    std::uniform_int_distribution<unsigned int> dis;// 等概率分布模型
    using param_t = std::uniform_int_distribution<unsigned int>::param_type;
    for(unsigned int i = size-1;i>0;--i)//shuffle 算法
    {
        using std::swap;
        swap(data[i],data[dis(gen,param_t(0,i))]);
    }
    for(size_t i = 0;i<size/2-1;++i)
        write<<data[i]<<' ';
    write<<data[size/2-1];
    write.close();
    delete [] data;
    return  true;
}
