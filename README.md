# Canonical C++ Multipass Technical Assessment

A CLI tool to parse data from the Ubuntu Cloud Images JSON page.

## Commands

	-current-version {ALIAS -cv}		Displays the current LTS version of Ubuntu.

	-disk-image [version] {ALIAS -d}	Displays the SHA256 of the disk1.img of the given version.
										Defaults to the current version of Ubuntu.

	-help {ALIAS -h}					Displays the help page

	-supported-versions {ALIAS -s}		Displays all currently supported versions of Ubuntu.


## Building

Requires CMake 3.8+ and a C++ compiler with C++17 support.