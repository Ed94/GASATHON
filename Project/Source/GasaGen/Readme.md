# GasaGen

This is a single translation unit meta-program for generating code for the Gasa modules.
It runs before UHT.

GasaGen.cpp is the effective translation unit.
All related code for GasaGen is prefixed with:

```GasaGen_```

Anything with the `gen` namespace (case sensitive, including the files), is related to the Gencpp header. Genccp is used.
Gencpp is a cpp library to make ergonomic use of stage metaprogramming for C++ in C++.

For how GasaGen is built see [`scripts/gen_pass_gasa.ps1`](../../../scripts/gen_pass_gasa.ps1)
