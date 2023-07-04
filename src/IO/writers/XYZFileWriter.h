#ifndef BASSENJI_XYZFILEWRITER_H
#define BASSENJI_XYZFILEWRITER_H

#include "FileWriter.h"

class XYZFileWriter : public FileWriter {
    static std::string formatMolecule(const Molecule* m);
    static std::string formatAtom(const Atom* a);
public:
    void WriteFile(const
    std::vector<std::pair<Molecule*, double>>& ensemble, const std::string& fname) const override;
};

#endif //BASSENJI_XYZFILEWRITER_H
