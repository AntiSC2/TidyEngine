# - Finds if the compiler has C++17 support
# This module can be used to detect compiler flags for using C++17, and checks
# a small subset of the language.
#
# The following variables are set:
#   CXX1Z_FLAGS - flags to add to the CXX compiler for C++17 support
#   CXX1Z_FOUND - true if the compiler supports C++17
#

if(CXX1Z_FLAGS)
	set(CXX1Z_FOUND TRUE)
	return()
endif()

include(CheckCXXSourceCompiles)

if(MSVC)
	set(CXX1Z_FLAG_CANDIDATES
		" "
        )
else()
	set(CXX1Z_FLAG_CANDIDATES
        	#gcc
        	"-std=gnu++17"
        	"-std=gnu++1z"
        	#Gnu and Intel Linux
        	"-std=c++17"
        	"-std=c++1z"
        	#Microsoft Visual Studio, and everything that automatically accepts C++11
        	" "
        	#Intel windows
        	"/Qstd=c++17"
        	"/Qstd=c++1z"
        )
endif()

set(CXX1Z_TEST_SOURCE
"
int main()
{
	constexpr auto L = [](int i) { return i; };
	return 0;
}
")

foreach(FLAG ${CXX1Z_FLAG_CANDIDATES})
	set(SAFE_CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS}")
	set(CMAKE_REQUIRED_FLAGS "${FLAG}")
	unset(CXX1Z_FLAG_DETECTED CACHE)
	message(STATUS "Try C++17 flag = [${FLAG}]")
	check_cxx_source_compiles("${CXX1Z_TEST_SOURCE}" CXX1Z_FLAG_DETECTED)
	set(CMAKE_REQUIRED_FLAGS "${SAFE_CMAKE_REQUIRED_FLAGS}")
	if(CXX1Z_FLAG_DETECTED)
		set(CXX1Z_FLAGS_INTERNAL "${FLAG}")
		break()
    	endif(CXX1Z_FLAG_DETECTED)
endforeach(FLAG ${CXX1Z_FLAG_CANDIDATES})

set(CXX1Z_FLAGS "${CXX1Z_FLAGS_INTERNAL}" CACHE STRING "C++17 Flags")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CXX1Z DEFAULT_MSG CXX1Z_FLAGS)
mark_as_advanced(CXX1Z_FLAGS)
