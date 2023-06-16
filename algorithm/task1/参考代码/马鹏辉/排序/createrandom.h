#ifndef CREATERANDOM_H
#define CREATERANDOM_H
#include <string>

class CreateRandom
{

public:
    CreateRandom(unsigned int _size,std::string _filename = "testdata.txt"):size(_size*2),filename(std::to_string(_size)+_filename){}
    bool GenerateFile();
    std::string getFileName(){return filename;}

private:
    unsigned int size;//随机生成的数据规模
    std::string filename;

};

#endif // CREATERANDOM_H
