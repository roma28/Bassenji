#include "WriterFactory.h"
#include "writers/XYZFileWriter.h"

FileWriter* WriterFactory::GetWriter(const std::string& specifier)
{
    return new XYZFileWriter();
}
