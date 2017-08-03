# - Finds if the compiler has C++14 support
# This module can be used to detect compiler flags for using C++14, and checks
# a small subset of the language.
#
# The following variables are set:
#   CXX14_FLAGS - flags to add to the CXX compiler for C++14 support
#   CXX14_FOUND - true if the compiler supports C++14
#

if(CXX14_FLAGS)
	set(CXX14_FOUND TRUE)
	return()
endif()

include(CheckCXXSourceCompiles)

if(MSVC)
	set(CXX14_FLAG_CANDIDATES
		" "
    )
else()
	set(CXX14_FLAG_CANDIDATES
        	#gcc
        	"-std=gnu++14"
        	#Gnu and Intel Linux
        	"-std=c++14"
        	#Microsoft Visual Studio, and everything that automatically accepts C++14
        	" "
        	#Intel windows
        	"/Qstd=c++14"
    )
endif()

set(CXX14_TEST_SOURCE
"
auto main() -> int
{
    auto add_two([](auto x, auto y){ return x + y; });
	return 0;
}
")

foreach(FLAG ${CXX14_FLAG_CANDIDATES})
	set(SAFE_CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS}")
	set(CMAKE_REQUIRED_FLAGS "${FLAG}")
	unset(CXX14_FLAG_DETECTED CACHE)
	message(STATUS "Try C++14 flag = [${FLAG}]")
	check_cxx_source_compiles("${CXX14_TEST_SOURCE}" CXX14_FLAG_DETECTED)
	set(CMAKE_REQUIRED_FLAGS "${SAFE_CMAKE_REQUIRED_FLAGS}")
	if(CXX14_FLAG_DETECTED)
		set(CXX14_FLAGS_INTERNAL "${FLAG}")
		break()
    	endif(CXX14_FLAG_DETECTED)
endforeach(FLAG ${CXX14_FLAG_CANDIDATES})

set(CXX14_FLAGS "${CXX14_FLAGS_INTERNAL}" CACHE STRING "C++14 Flags")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CXX14 DEFAULT_MSG CXX14_FLAGS)
mark_as_advanced(CXX14_FLAGS)
