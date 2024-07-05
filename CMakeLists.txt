# CMakeList.txt : CMake project for Canonical C++ Multipass Technical Interview, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project (UbuntuParser)

#Finds Poco if locally installed
find_package(poco)

#If Poco is not locally installed, fetch it
if(NOT poco_FOUND)
	include(FetchContent)
	FetchContent_Declare(
		poco
		GIT_REPOSITORY https://github.com/pocoproject/poco
		GIT_TAG poco-1.13.3-release
	)
	FetchContent_MakeAvailable(poco)
endif()

add_executable (UbuntuParser "src/ubuntu-parser.cpp" "src/main.cpp")
target_include_directories(UbuntuParser PRIVATE "src/include")
target_link_libraries(UbuntuParser PRIVATE Poco::Net Poco::JSON)
target_compile_features(UbuntuParser PRIVATE cxx_std_17)

if(WIN32)
	set_target_properties(UbuntuParser PROPERTIES RUNTIME_OUTPUT_DIRECTORY 
   ${PROJECT_BINARY_DIR}/bin )
set_target_properties(UbuntuParser PROPERTIES LIBRARY_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin )
endif()