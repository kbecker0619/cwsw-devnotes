# CWSW MCU Architecture Support

This repository is the "integration project" for the CWSW Arch software libraries.

This component is intended to supplement the architecture-specific drivers used in the project.

@startuml
"CWSW Library Core: --|> "CWSW Arch Support"
@enduml

The actual CWSW Arch repo is inserted into this project as a submodule.

Also present in submodule form, is the CWSW Lib component, to both illustrate one method of combining the services provided by both components, but also to improve testing coverage of both components.


~~Looking "down," this component knows how to talk to the actual MCU. Code that lives here is beyond the scope of this library module; as long as the API is compatible, this module can interface with it.~~

~~Looking "up," it provides a (somewhat-)standardized API to users of the MCU. In the CWSW ecosystem, this is provided by the CWSW BSP component.~~

This component does not know anything about the board that uses the MCU; 
that support is provided by the CWSW Board package.

There is one directory for each supported architecture; in your build system, simply exclude all architectures except for the one around which your project is built.

Please see the detailed design documentation, created by Doxygen, for detailed information.

---
Eclipse:	 `XPRJ_Win_MinGW_${ConfigName}`

NetBeans:	 `XPRJ_NB_${CONF}`

MSVC (2010): `XPRJ_MSVC_$(ConfigurationName)`