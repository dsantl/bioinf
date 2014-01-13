bioinf
======

## Neighbour joining project

### Infra

Main script is nj_process.

### Usage

```sh
./nj_process exec_of_nj input_fasta_file
```

### Code

Source codes and bin files.

### Test

Infrastructure for test.

### Examples

#### With infrastructure

```sh
cd Infra
```

###### Objective-C:

Objective-C programs can not be run on GNU/Linux, so you should contact Filip for the details: <filip.bec@fer.hr>

###### Python:
```sh
./nj_process ../Code/Curkovic/Bin/nj.py test1.fasta
```

###### Java:
```sh
./nj_process ../Code/Gasic/Bin/neighbour_joining test1.fasta 
```

###### Ruby:
```sh
./nj_process ../Code/Kokot/Bin/neighbour_joining.rb test1.fasta 
```

###### C:
```sh
./nj_process ../Code/Santl/Bin/neighbour_joining test1.fasta 
```

###### C++
```sh
./nj_process ../Code/Smolkovic/Bin/LAB test1.fasta 
```

Resulting trees may slightly differ one from the other for the same input data because the algorithm is nondeterministic. Check the Documentation (chapter Testiranje) for the details. 

#### Without infrastructure

###### Python:
```sh
 ../Code/Curkovic/Bin/nj.py < wiki.in
```

###### Java:
```sh
../Code/Gasic/Bin/neighbour_joining < wiki.in 
```

###### Ruby:
```sh
../Code/Kokot/Bin/neighbour_joining.rb < wiki.in 
```

###### C:
```sh
../Code/Santl/Bin/neighbour_joining < wiki.in 
```

###### C++
```sh
../Code/Smolkovic/Bin/LAB < wiki.in 
```

### Other

```sh
./alignament.py input_fasta_file # to stdout print distance matrix (bridges)
```

```sh
./generate_graph.py # to stdin graph in bridge format
```
