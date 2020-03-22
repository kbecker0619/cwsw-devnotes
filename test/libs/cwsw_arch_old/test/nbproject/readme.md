# NetBeans 8.2 Project

## Important folders

Folder              | Description
:---                | :---
Debug               | Created by VS, home to all build artifacts

## Important files

File                | Description
:---                | :---
../Makefile         | Main NB makefile. While this can change frequently, its absence will cripple NB's build.
../Makefile.mak     | NB makefile
../.dep.inc         | Component of NB makefile; tracks dependencies

## Tool-Related Tidbits

The NB-managed makefiles are critical to the health of the NB environment, and NB seems exceptionally sensitive to outside changes. For example, it is very hard to restore the ability to build if the top-level Makefile is deleted.
