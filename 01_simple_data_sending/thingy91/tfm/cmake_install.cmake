# Install script for directory: D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "MinSizeRel")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "D:/nordicsemi/toolchains/31f4403e35/opt/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/lib/ext/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/lib/fih/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/tools/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/secure_fw/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/interface/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/platform/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/platform/ext/accelerator/cmake_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/outputs/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/outputs" TYPE DIRECTORY MESSAGE_NEVER FILES "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/bin/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/lib/s_veneers.o")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/lib" TYPE FILE MESSAGE_NEVER FILES "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/secure_fw/s_veneers.o")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa/client.h;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa/error.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa" TYPE FILE MESSAGE_NEVER FILES
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/psa/client.h"
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/psa/error.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa_manifest/sid.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa_manifest" TYPE FILE MESSAGE_NEVER FILES "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/generated/interface/include/psa_manifest/sid.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/tfm_api.h;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/tfm_ns_interface.h;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa_config.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include" TYPE FILE MESSAGE_NEVER FILES
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/tfm_api.h"
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/tfm_ns_interface.h"
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/psa_config.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/tfm_ns_client_ext.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include" TYPE FILE MESSAGE_NEVER FILES "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/tfm_ns_client_ext.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/config_impl.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include" TYPE FILE MESSAGE_NEVER FILES "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/generated/interface/include/config_impl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/tfm_psa_call_pack.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include" TYPE FILE MESSAGE_NEVER FILES "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/tfm_psa_call_pack.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa/framework_feature.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa" TYPE FILE MESSAGE_NEVER FILES "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/generated/interface/include/psa/framework_feature.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa/crypto_extra.h;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa/crypto_compat.h;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa/crypto.h;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa/crypto_client_struct.h;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa/crypto_sizes.h;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa/crypto_struct.h;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa/crypto_types.h;D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa/crypto_values.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/psa" TYPE FILE MESSAGE_NEVER FILES
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/psa/crypto_extra.h"
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/psa/crypto_compat.h"
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/psa/crypto.h"
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/psa/crypto_client_struct.h"
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/psa/crypto_sizes.h"
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/psa/crypto_struct.h"
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/psa/crypto_types.h"
    "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/psa/crypto_values.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/tfm_crypto_defs.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include" TYPE FILE MESSAGE_NEVER FILES "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/tfm_crypto_defs.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include/tfm_platform_api.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/include" TYPE FILE MESSAGE_NEVER FILES "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/include/tfm_platform_api.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/src/tfm_psa_ns_api.c")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/src" TYPE FILE MESSAGE_NEVER FILES "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/src/tfm_psa_ns_api.c")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/src/tfm_ns_interface.c.example")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/src" TYPE FILE MESSAGE_NEVER FILES "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/src/tfm_ns_interface.c.example")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/src/tfm_crypto_api.c")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/src" TYPE FILE MESSAGE_NEVER FILES "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/src/tfm_crypto_api.c")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/src/tfm_platform_api.c")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/install/interface/src" TYPE FILE MESSAGE_NEVER FILES "D:/nordicsemi/v2.4.0/modules/tee/tf-m/trusted-firmware-m/interface/src/tfm_platform_api.c")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/Root/Github_projects/NRF9160/01_simple_data_sending/thingy91/tfm/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
