@page cwsw_arch_ovr Component: CWSW Architecture (overview: documentation folder)

# Project-specific documentation folder for the Arch component

<!-- Note: This document is not pure Markdown format: it is intended to be used inside of a
Doxygen project, and therefore contains some embedded Doxy commands -->

## Overview

This folder contains items that pertain only to this project. 
The actual component documentation is in the `doc_arch` folder.


## Important folders

Folder              | Description
:---                | :---
doc_arch            | home to the documentation for this component

## Important files

File                | Description
:---                | :---
cwsw_arch.doxyfile  | Project-specific Doxygen project. For most developers, this will be the project to use to generate output.

## Tool-Related Tidbits

File `cwsw_arch.klb.doxyfile` is an example of how to override behavior or
settings of the project, in case they don't work for the specific
deployment environment.
