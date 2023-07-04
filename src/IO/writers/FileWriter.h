#ifndef BASSENJI_FILEWRITER_H
#define BASSENJI_FILEWRITER_H

#include "../../molecular/include/Molecule.h"

class FileWriter {
public:
     virtual void WriteFile(const
    std::vector<std::pair<Molecule*, double>>& ensemble, const std::string& fname) const = 0;
};

#endif //BASSENJI_FILEWRITER_H
