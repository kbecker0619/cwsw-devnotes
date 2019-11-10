# CWSW Library

## Overview


This repo holds the small CWSW Library.
Being the building block upon which other CWSW components are built, it
has no dependencies to other CWSW components.

This repo is the composed of a mixture of direct files and folders, and
GIT submodules for reusable portions of the component; namely, sources,
documentation, and unit testing (this component uses CUnit, hosted
natively by NetBeans).

@startuml
"CWSW Library Core" --|> "OSAL": uses
"CWSW Library Core" --|> "BSW": uses
"CWSW Library Core" --|> "SWC": uses
"CWSW Library Core" --|> "etc...": uses
@enduml

The source repo for this component is best inserted in the Services
layer (if you have one). It contains core, stateless, utility functions
that can be called by any application or driver layer module.

## Important folders

Folder          | Description
:---            | :---
cwsw_lib        | GIT submodule: Container for the CWSW LIB submodule
doc             | GIT submodule: Documentation folder for this component
ut              | GIT submodule: Unit Test sources for this component
---             | ---
app             | demo app that illustrates how to use this component
cfg             | Project-specific configuration headers (demo app)
---             | ---
ecproject       | Home for the Eclipse project files
nbproject       | NetBeans project files
vsproject       | VS2010 project home
lwproject       | LabWindows/CVI project folder

## Important files

Almost all of the files in the root directory, are for various IDEs and build environments supported by this component.
