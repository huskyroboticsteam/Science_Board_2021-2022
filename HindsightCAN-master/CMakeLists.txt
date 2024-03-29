cmake_minimum_required(VERSION 3.12)

# Include some helper packages for installation
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Define project. Version number should be updated with changes according to
# Semantic Versioning (https://semver.org)
# - Major version (first number) should be incremented when
#   backwards-incompatible changes are made (such as removing packets)
# - Minor version (second number) should be incremented when features are added
#   in a backwards-compatible manner (such as adding packets, or adding packet
#   fields) 
# - Patch version (third number) should be incremented when you make small
#   backwards-compatible changes or bug fixes.
project(HindsightCAN
  LANGUAGES C
  VERSION 1.1.0) # <-- Change when you make commits to master; see above

# The list of header files for the CAN library
set(CAN_HEADERS
  CANCommon.h
  CANGPIO.h
  CANLibrary.h
  CANLocalization.h
  CANMotorUnit.h
  CANPacket.h
  CANPower.h
  CANScience.h
  CANSerialNumbers.h
  Port.h)

# The list of sources for the CAN library
set(CAN_SOURCES
  CANCommon.c
  CANGPIO.c
  CANLocalization.c
  CANMotorUnit.c
  CANPacket.c
  CANPower.c
  CANScience.c
  PortFiles/PortTemplate.c)

# Preprocessor flag required for the CAN library; see
# https://github.com/huskyroboticsteam/HindsightCAN#how-to-port-to-a-new-chip
add_definitions(-DCHIP_TYPE=CHIP_TYPE_TEMPLATE)

# Define a static library, compiled from the files in the CAN_SOURCES list
add_library(HindsightCAN STATIC ${CAN_SOURCES})
# Include the header files when installed to the system
target_include_directories(HindsightCAN
  PUBLIC $<INSTALL_INTERFACE:include>)

### Installation config ###

# If the project name is defined (i.e. if this project is not being included as
# a submodule)
if (DEFINED PROJECT_NAME)
  # Install the static library to the system, and export the list of installed
  # targets to hindsight-can-targets
  install(TARGETS HindsightCAN
	EXPORT hindsight-can-targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
  # Install the header files to the system
  install(FILES ${CAN_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/HindsightCAN)

  # Install the list of targets to the system
  install(EXPORT hindsight-can-targets
	FILE HindsightCANTargets.cmake
	NAMESPACE HindsightCAN::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HindsightCAN)

  # Generate a CMake package configuration file for the library
  configure_package_config_file(
	${CMAKE_CURRENT_LIST_DIR}/cmake/HindsightCANConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/HindsightCANConfig.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HindsightCAN)
  # Install the CMake package configuration file
  install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/HindsightCANConfig.cmake"
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HindsightCAN)

  ### Packaging configuration ###
  # Borrowed/adapted from https://www.scivision.dev/cmake-cpack-basic/
  set(CPACK_GENERATOR "DEB")
  set(CPACK_PACKAGE_NAME "hindsight-can")
  # Version format: major.minor.patch
  set(CPACK_PACKAGE_VERSION "${CMAKE_PROJECT_VERSION}")
  set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION})
  set(CPACK_PACKAGE_CONTACT "Husky Robotics Team <uwrobots@uw.edu>")
  set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
  set(CPACK_PACKAGE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

  install(FILES ${CPACK_RESOURCE_FILE_README}
	DESTINATION share/docs/${PROJECT_NAME})

  include(CPack)

endif()

  
