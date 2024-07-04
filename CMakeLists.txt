# CMakeList.txt : CMake project for Canonical C++ Multipass Technical Interview, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project (UbuntuParser LANGUAGES CXX)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


find_package(daw-json-link)
if(NOT daw-json-link_FOUND)
	include(FetchContent)
	FetchContent_Declare(
		daw_json_link
		GIT_REPOSITORY https://github.com/beached/daw_json_link
		GIT_TAG release
	)
	FetchContent_MakeAvailable(daw_json_link)
endif(NOT daw-json-link_FOUND)

add_executable (UbuntuParser parser.cpp parser.hpp)
target_link_libraries(UbuntuParser PRIVATE daw::daw-json-link)
target_compile_features(UbuntuParser PRIVATE cxx_std_20)
