# Demanded bits analysis

## Building

```sh
cmake -S . -B build
cmake --build build
```


## Compiling the test file

```
clang -S -emit-llvm -o - input.c | mlir-translate --import-llvm > test.mlir
mlir-opt -cse test.mlir -o testout.mlir
```

We run the CSE optimization pass to eliminate a duplicated load, which
allows us to get more interesting facts from the analysis

## Running

```sh
./run.sh testout.mlir
```

The annotated output should display
```
%18 = llvm.load %11 <alignment = 4> : !llvm.ptr -> i32 // %18 is 
0000000000000000000000000000000000000000000000000011000000000011
```

This load represents the input to the expression; the annotation shows which bits
might affect the output.