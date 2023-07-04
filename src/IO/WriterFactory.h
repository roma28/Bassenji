#ifndef BASSENJI_WRITERFACTORY_H
#define BASSENJI_WRITERFACTORY_H

#include "writers/FileWriter.h"

class WriterFactory {
    WriterFactory();
public:
    static FileWriter* GetWriter(const std::string& specifier);

};

#endif //BASSENJI_WRITERFACTORY_H
