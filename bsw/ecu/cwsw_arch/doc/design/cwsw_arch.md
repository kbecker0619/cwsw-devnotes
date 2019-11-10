@page Arch_Head Component: CWSW Architecture
	@subpage Arch_Design \n
	@subpage Arch_Integration
    @subpage Arch_srs \n

<!-- Note: This document is not pure Markdown format: it is intended to be used inside of a
Doxygen project, and therefore contains some embedded Doxy commands -->

@tableofcontents
 
# Introduction to the Architecture reusable component

This chapter briefly describes the design and implementation of the Architecture reusable
component member of the CWSW library.

This chapter also briefly describes the integration of this feature into the larger code base
of the user software project.

The intended audience of this document is any software engineer who uses the CWSW library and
wants to add support for one (or more) of the supported architectures.

## Directory Layout

The Includes structure here is slightly different than in other CWSW components designed for
reuse / multiple deployments.

In most CWSW components, the main API is published at the root of the component folder;
any local-to-component headers are located within appropriate subfolders.

For this component, the main API is at the root of the architecture-specific folder.
While there is an API file that exposes all APIs common to all architectures located at the
component root, this is not intended to be used by projects that use the Architecture-Support
component.


## Applicable Documents

TBD


## Terms, Acronyms, Abbreviations

TBD
