# Requirements: CWSW Arch Component

<!-- Note: This document is not pure Markdown format: it is intended to be used inside of a
Doxygen project, and therefore contains some embedded Doxy commands -->

## Purpose of Arch Component

The CWSW Arch Component provides the foundation of the dependency tree for the CWSW suite of 
reusable software components. They are primarily intended for use in an embedded environment, but they may find utility in a variety of environments.

The Arch component contains a minimal set of functions, with supporting User Defined Types, 
macros and function-like macros.

<br>

## Scope of Arch Requirements

The requirements documented here cover functional and non-functional
requirements specific to the Library component.

<br>

## Arch Requirements

### Arch Operating State

| ID 								    | Title 								| Description 																					| Status 	| Trace From	| Comment 	|
| :---:								    | :---									| :---																							| :---		| :---			| :---		|
| @anchor RQT_ARCH_0000 SR_ARCH_0000    | Initialize API						| The Component shall provide an API for initializing the component.							| Draft 	| @ref RQT_LIB_0000 "SR_LIB_0000"   | |
| @anchor RQT_ARCH_0001 SR_ARCH_0001	| Determine initialization status		| The Component shall provide an API for determining initialization status.						| Draft		| @ref RQT_LIB_0001 "SR_LIB_0001"	| |
| @anchor RQT_ARCH_0002 SR_ARCH_0002	| Responsibilities of Initialize method | The Initialize method shall set the component's operating internal state to initial status.	| Draft		| @ref RQT_LIB_0002 "SR_LIB_0002"	| |
| @anchor RQT_ARCH_0003 SR_ARCH_0003	| Component's Uninitialized indication	| If executed prior to initialization, the features of the component that have stateful behavior by design, shall return an `Uninitilialized` indication.	| Draft | @ref RQT_LIB_0003 "SR_LIB_0003"	| "Return" could be via callback, component-level attribute, function output parameter, function return code, etc. |
| @anchor RQT_ARCH_0004 SR_ARCH_0004	| Component's Uninitialized behavior	| If executed prior to initialization, the features of the component that have stateful behavior by design, shall not change their operating state.			| Draft	| @ref RQT_LIB_0004 "SR_LIB_0004"	| |

<br>

<!-->
### Tasking API

| ID 	| Title	| Description		| Status 	| Trace From	| Comment 	|
| :---:	| :---	| :---				| :---		| :---			| :---		|
|   	|  		| 					|   		|   			| |

<br>

### Critical Sections / Protected Regions

| ID 	| Title	| Description		| Status 	| Trace From	| Comment 	|
| :---:	| :---	| :---				| :---		| :---			| :---		|
|   	|  		| 					|   		|   			| |

<br>
-->
