# Bassenji

An utility to get a set of unique conformations
from a molecular dynamics trajectory computing
their populations from their occurrence in the trajectory.

The selection (at least at this moment) is based on RMSD.

## Input formats

* multi-molecular XYZ file
* PDB file (to be implemented)

## Output formats

* multi-molecular XYZ file
  (second string contains normalized population)
* separate XYZ files + population file (to be implemented)

## Usage

`./MDConfGen -i <input_file> -o <output_file> -r <rmsd_value> -j <n_jobs>
-v <output_verbosity>`

NB: the order of atoms in input XYZ file should not change.

## References

Yamin, P., Isele-Holder, R., & Leonhard, K. (2016). Predicting octanol/water partition coefficients of
alcohol ethoxylate surfactants using a combination of molecular dynamics and the conductor-like
screening model for realistic solvents. Industrial & Engineering Chemistry Research, 55(16), 4782-4789.

## Disclamer

This is mostly a learning project, so it may not work as intended or not work at all.