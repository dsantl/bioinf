bioinf
======

## Neighbour joining project

### Infra

Main script is nj_process.

### Usage

```sh
./nj_process exec_of_nj input_fasta_file
```

### Other

```sh
./alignament.py input_fasta_file - to stdout print distance matrix (bridges)
```

```sh
./generate_graph.py - to stdin graph in bridge format
```

### Code

Source codes and bin files.

### Test

Infrastructure for test.

### Example

```sh
cd Infra
./nj_process ../Code/Bec/Bin/neighbor_joining test1.fasta  # Objective C
./nj_process ../Code/Curkovic/Bin/nj.py test1.fasta # Python
./nj_process ../Code/Gasic/Bin/neighbour_joining test1.fasta  # Java
./nj_process ../Code/Kokot/Bin/neighbour_joining.rb test1.fasta  # Ruby
./nj_process ../Code/Santl/Bin/neighbour_joining test1.fasta  # C
./nj_process ../Code/Smolkovic/Bin/LAB test1.fasta # C++
```