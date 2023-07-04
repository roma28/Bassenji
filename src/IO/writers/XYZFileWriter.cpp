#include <fstream>

#include "XYZFileWriter.h"
void XYZFileWriter::WriteFile(const std::vector<std::pair<Molecule*, double>>& ensemble,
        const std::string& fname) const
{
    auto out = std::ofstream(fname);
    for (auto c : ensemble) {
        out << fmt::format("{}\n", c.first->atoms.size());
        out << fmt::format("{:.4f}\n", c.second);
        out << formatMolecule(c.first);
    }
}
std::string XYZFileWriter::formatMolecule(const Molecule* m)
{
    std::string s;

    for (auto a : m->atoms) {
        s += formatAtom(a);
    }
    s += "\n";
    return s;
}
std::string XYZFileWriter::formatAtom(const Atom* a)
{
    return fmt::format("{0}\t{1:.6f}\t{2:.6f}\t{3:.6f}\n",
            a->GetSymbol(),
            a->coordinates.x(),
            a->coordinates.y(),
            a->coordinates.z());
}
