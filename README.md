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

If you have git installed, first run

	git clone https://github.com/nathandavis18/Multipass-Techincal-Assessment.git
	cd "./Multipass-Techincal-Assessment"

Otherwise, you will have to download and extract the archive.

To build, run

	cmake -B {buildDir} -S {sourceDir} -DCMAKE_BUILD_TYPE=Release -G {buildGenerator}

* buildDir is the path where you want the project built.
* sourceDir is the path to the CMakeLists.txt file.
* buildGenerator is your build Generator of choice. Examples:
	* Ninja
	* Visual Studio
	* Make
		

After generating the build files, run

	cmake --build {buildDir} --config Release

An example of building while in the source directory would be

	cmake -B ./out/build -S ./ -DCMAKE_BUILD_TYPE=Release -G Ninja

	cmake --build ./out/build --config Release

