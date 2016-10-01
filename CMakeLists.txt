project (lvfs-qplayer)

# Custom modules
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Project header
project_header_default ("POSITION_INDEPENDENT_CODE:YES")

# 3rdparty
find_package (Lvfs-Core REQUIRED)
include_directories (${LVFS_CORE_INCLUDE})

find_package (Phonon REQUIRED)
include_directories (${PHONON_INCLUDE})

list (APPEND ${PROJECT_NAME}_LIBS ${EFC_LIB})
list (APPEND ${PROJECT_NAME}_LIBS ${LVFS_LIB})
list (APPEND ${PROJECT_NAME}_LIBS ${PHONON_LIB})
list (APPEND ${PROJECT_NAME}_LIBS ${QT_LIBRARIES})
list (APPEND ${PROJECT_NAME}_LIBS ${LVFS_CORE_LIB})

# Sources
add_subdirectory (src)
QT4_WRAP_CPP (${PROJECT_NAME}_MOC_SOURCES ${${PROJECT_NAME}_HEADERS} OPTIONS "-nw")
list (APPEND ${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_MOC_SOURCES})

# Target - lvfs-qplayer
add_library (lvfs-qplayer SHARED ${${PROJECT_NAME}_SOURCES})
target_link_libraries (lvfs-qplayer ${${PROJECT_NAME}_LIBS})

# Documentation
add_documentation ("LVFS-QPlayer" 0.0.1 "LVFS Plugin to play audio/video files")

# Install rules
install_target (lvfs-qplayer)
