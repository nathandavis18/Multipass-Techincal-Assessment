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


find_package(nlohmann_json)
if(NOT nlohmann_json_FOUND)
	include(FetchContent)
	FetchContent_Declare(
		nlohmann_json
		GIT_REPOSITORY https://github.com/nlohmann/json
		GIT_TAG v3.11.3
	)
	FetchContent_MakeAvailable(nlohmann_json)
endif(NOT nlohmann_json_FOUND)

if(WIN32)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

find_package(cpr)
if(NOT cpr_FOUND)
	include(FetchContent)
	FetchContent_Declare(
		cpr
		GIT_REPOSITORY https://github.com/libcpr/cpr.git
		GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8
	)
	FetchContent_MakeAvailable(cpr)
endif(NOT cpr_FOUND)

add_executable (UbuntuParser "src/ubuntu-parser.cpp" "src/main.cpp")
target_include_directories(UbuntuParser PRIVATE "src/include")
target_link_libraries(UbuntuParser PRIVATE nlohmann_json::nlohmann_json cpr::cpr)
target_compile_features(UbuntuParser PRIVATE cxx_std_20)