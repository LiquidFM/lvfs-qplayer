# - Find phonon
# Find the phonon library
#
#  This module defines the following variables:
#     PHONON_FOUND   - True if PHONON_INCLUDE is found
#     PHONON_INCLUDE - where to find header files
#     PHONON_LIB     - the library files


if (NOT PHONON_FOUND)
    find_path (PHONON_INCLUDE
               NAMES "phonon/videoplayer.h"
               PATH_SUFFIXES include
               DOC "Phonon include directory")

    find_library (PHONON_LIB
                  NAMES phonon
                  DOC "Phonon library file")

    # handle the QUIETLY and REQUIRED arguments and set PHONON_FOUND to TRUE if all listed variables are TRUE
    include (FindPackageHandleStandardArgs)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS (Phonon DEFAULT_MSG PHONON_INCLUDE PHONON_LIB)

    mark_as_advanced (PHONON_INCLUDE PHONON_LIB)
endif ()
