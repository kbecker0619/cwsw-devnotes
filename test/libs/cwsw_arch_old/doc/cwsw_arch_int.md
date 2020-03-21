@page Arch_Integration  Integration Guide: CWSW Architecture

# Integration Guide: CWSW Architecture

<!-- Note: This document is not pure Markdown format: it is intended to be used inside of a
Doxygen project, and therefore contains some embedded Doxy commands -->

@tableofcontents

To add the facilities of the CWSW Architecture component to your project, follow these steps.

**Author's note**: These steps are generic for all IDEs; however, the specific details
(e.g., screen shots) are oriented toward IDEs based on Eclipse, such as NXP S32DS; ARM DS-5; or
TI's Code Composer.
While I have implemented these steps in Microchip's MPLAB v4.x, the steps are so close that I
didn't feel IDE-specific instructions were required.

<!--
Integration Steps:
-# [Share the Source](#arch_source_share)
-# [Add Dependencies](#arch_add_depends)
-# [Update Includes paths](#arch_update_includes)
-# [Configuration](#arch_comp_configuration)
-# [Update Initialization Code](#arch_init_code)
-# Optional APIs.

	/**	@page Arch_Integration				Integrating the Reusable Component
	 *	@section arch_source_share			Share the Source
	 *	Designed to be a reusable component, the CWSW Architecture component is
	 *	organized into a reusable section, and requires additional project-
	 *	specific configuration items in the project.
	 *
	 *	The component layout in your workspace looks like this:
	 *	@code{.sh}

		cwsw_arch_prj/
		├── cwsw_arch
		│   ├── i386
		│   │   └── ...
		│   ├── MPC57xx
		│   │   ├── ...
		│   └── pic32mz
		│       └── ...
		├── doc
		│   ├── dox
		│   └── images
		└── ut

	 *	@endcode
	 *	@note This component is presently under construction; as support is added
	 *	for additional MCU architecture, the exact form of the directory tree
	 *	shown above may change.
	 *	@note Some features have been omitted for clarity.
	 *
	 *	The <code>cwsw_arch_prj</code> directory is the home to the various
	 *	project-management files (such as the Doxygen configuration, the Eclipse
	 *	project files, etc.), and is the parent for the component.
	 *
	 *	The <code>ut</code> directory is the source for the developer workspace
	 *	for this reusable component, and illustrates how to configure the
	 *	component is client projects.
	 *
	 *	The <code>doc</code> directory holds relevant design information not
	 *	included in this Doxygen format.
	 *
	 *	The <code>cwsw_arch</code> directory is the sharable and reusable portion
	 *	of the component.\n
	 *	The design intent is for this folder to be shared into your project's
	 *	directory structure.
	 *	-	@b Preferred: If your code management system can share folders
	 *		(e.g., PVCS / Dimensions, MKS), this might be a good solution; else,
	 *	-	@b Symlinks: filesystem symlinks are supported by GIT, with
	 *		appropriate configuration options set properly.
	 *	-	Example (using symlinks):\n
	 *	Given the following workspace directory structure:
	 *	@code{.sh}

	 	(workspace)
	 	├── components
	 	│   ├── cwsw_arch_prj
	 	│   ├── cwsw_board_prj
	 	│   └── cwsw_lib_prj
	 	├── cwsw_example_proj
	 	│   ├── appl_swc
	 	│   ├── cfg
	 	│   ├── drivers
	 	│   ├── libs
	 	│   ├── os
	 	│   ├── rte
	 	│   └── services
	 	├── doc
	 	└── ut

	 *	@endcode
	 *	Execute the following. @note This example is given using Cygwin; the same
	 *	command line verbatim would be done in Git Bash.\n
	 *	Also, 7-Zip can create symlinks, and there are other methods in Windows to create symbolic
	 *	links.
	 *
	 *	@code{.sh}

		$ cd cwsw_example_proj/drivers/
		$ ln -s ../../components/cwsw_arch_prj/cwsw_arc cwsw_arch
		$ git add cwsw_arch

		$ tree -dL 4
		(workspace)
	 	├── components
	 	│   ├── cwsw_arch_prj
	 	│   ├── cwsw_board_prj
	 	│   └── cwsw_lib_prj
	 	├── cwsw_example_proj
	 	│   ├── appl_swc
	 	│   ├── cfg
	 	│   ├── drivers
		│   │   └── cwsw_arch -> ../../components/cwsw_arch_prj/cwsw_arch
		│   ├── libs
		│   ├── os
		│   ├── rte
	 	│   └── services
	 	├── doc
	 	└── ut

	 *	@endcode
	 *	@note The placement above, in the <code> drivers </code> folder, is
	 *	only a suggestion. Wherever you locate it, if you are using filesystem
	 *	symlinks, it is important to use relative symlinks to maintain
	 *	portability from one dev system to another. <em>(If you are using a
	 *	sharing mechanism from your source versioning system, use the most
	 *	appropriate linking or referencing mechanism is appropriate.)</em>
	 *	\n \n
	 */

	/**	@page Arch_Integration
	 *	@section arch_add_depends			Add Component Dependencies
	 *
	 *	The <code>cwsw_arch</code> component has only one dependency to any
	 *	other cwsw component: to <code>cwsw_lib</code>. To integrate this
	 *	component, refer to the integration instructions [here](@ref Lib_Integration).
	 *	\n \n
	 */

	/**	@page Arch_Integration
	 *	@section arch_update_includes		Update Includes paths
	 *	@subsection arch_update_includes_paths	Include Paths
	 *	Update your build system to add the relative paths to the selected
	 *	architecture folder in the <code>cwsw_arch</code> folder. @b Note this is
	 *	different than in other CWSW components; this path is one level "deeper."
	 *
	 *	To clarify what you're looking for, here is the annotation for each of
	 *	the files in the <code> arch </code> project.
	 *	@note The design intent, is for all references within the project, to be
	 *	relative to the project itself. Portability is greatly reduced when the
	 *	project refers to fully qualified pathnames, or those outside of the
	 *	project tree itself.
	 *
	 *	@code{.sh}

		$ tree cwsw_arch_prj/ -dL 2
		cwsw_arch_prj/
		├── cwsw_arch				<<== target for symlink into your project
		│   ├── i386					<<== point your includes path to one and only one ...
		│   ├── MPC57xx					<<== of the arch folders, and exclude the rest from ...
		│   └── pic32mz					<<== within your build system (see next section).
		├── doc
		└── ut

	 *	@endcode
	 *	@note Some elements of the tree above have been excluded for clarity.
	 *
	 *	To illustrate how this might be done in an Eclipse-based project, see
	 *	the following screen capture: \n
	 *	@image html eclipse_add_includes_path.png			"Example Includes Path"
	 *	\n
	 *
	 *	@subsection arch_exclude_undesireables	Exclude Optional Architectures
	 *	Because (at least a portion of) the API that faces "upwards" must be
	 *	the same across all supported architectures, multiple definitions of
	 *	those API functions will exist unless those modules are excluded from
	 *	your build.
	 *
	 *	In Eclipse and IDEs derived from it, the easiest way to do this is to
	 *	specifically exclude a folder from the Project Properties dialog. Here
	 *	is an example: \n
	 *	@image html eclipse_exclude_folder_from_build.png	"Exclude Directory Item from Build"
	 *	This same "exclude" checkbox appears in multiple places in the project
	 *	properties dialog.
	 *
	 *	In makefile-based projects, simply omit reference to the undesired
	 *	architectures.
	 *	\n \n
	 */

	/**	@page Arch_Integration
	 *	@section arch_comp_configuration		Configure the Reusable Component and its dependencies
	 *	In some or the supported architectures, no configuration beyond what
	 *	has already been described is necessary. In some others, additional
	 *	items may need to be configured.
	 *
	 *	If the configurations are configured via preprocessor defines, there are two
	 *	easy methods of accomplishing this:
	 *	+ command-line defines
	 *	+ preprocessor defines in the file "projcfg.h"
	 */

	/**	@page Arch_Integration
	 *	@section arch_init_code					Update application's initialization code
	 *	At the time of this writing, none of the supported architectures require
	 *	any secondary initialization (e.g., initialization calls made after the
	 *	scheduler is started).
	 *
	 *	While not strictly required, it is recommended that the CWSW Library is
	 *	initialized first; following this, the Architecture component can be
	 *	initialized. Because, conceptually, the Architecture component lies at
	 *	the "bottom" (i.e., foundation) of the dependency tree, it should be the
	 *	initialized before other components.
	 *
	 *	One of the APIs introduced is an abstraction intended to give the same signature to all
	 *	CWSW modules: <code>Init(Component)</code>. This is optional, but when used, looks like
	 *	this:
	 *	@code{.c}

	 	void main(void)
	 	{
	 		(void)Init(Cwsw_Lib);
	 		(void)Init(Cwsw_Arch);
	 		... more initilization

	 		... main code follows ...
	 	}

	 *	@endcode
	 *	\n \n
	 */

-->
