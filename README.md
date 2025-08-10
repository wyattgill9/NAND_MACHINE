# NAND Machine
PURE MACRO VERSION - pure_macro.cpp 
which implments a uint64_t valid type using std::bitset under the hood and pure NAND logic


-- OLD --

A simple hardware simulation that calculates Fibonacci numbers using only the NAND gate. (loops are used to compress code, not for other purposes),
- Currently it has a 64 bit computer with about 64kb of memory.
Future plans:
- Remove all possible abstraction 

## Building and Running

```bash
make
./cpu
```

This will output the first 20 Fibonacci numbers.

## Cleanup

```bash
make clean
``` 
