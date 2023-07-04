#ifndef BASSENJI_READERFACTORY_H
#define BASSENJI_READERFACTORY_H

#include "readers/FileReader.h"

class ReaderFactory
{
    ReaderFactory();
public:
    static FileReader* GetReader(const std::string& specifier);
};

#endif //BASSENJI_READERFACTORY_H
