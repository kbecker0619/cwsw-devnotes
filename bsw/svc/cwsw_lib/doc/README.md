@page cwsw_lib Component: CWSW Library (overview: documentation folder)

# Project-specific documentation folder for the Library component

## Overview

This folder contains items that pertain only to this project. 
The actual component documentation is in the `doc_lib` folder.


## Important folders

Folder              | Description
:---                | :---
doc_lib             | GIT submodule, home to the standardized, reusable portion of the documentation for this component

## Important files

File                | Description
:---                | :---
cwsw_lib.doxyfile   | Project-specific Doxygen project. For most developers, this will be the project to use to generate output.

## Tool-Related Tidbits

File `cwsw_lib.klb.doxyfile` is an example of how to override behvior or
settings of the project, in case they don't work for the specific
deployment environment.
