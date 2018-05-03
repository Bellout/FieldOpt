
# Dbg ======================================================
message("\n================================================")
message(STATUS "PROJECT_NAME => ${PROJECT_NAME}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

# System info ==============================================
message("==================================================")
cmake_host_system_information(RESULT HOST_HOSTNAME QUERY HOSTNAME)
cmake_host_system_information(RESULT HOST_NUMBER_OF_LOGICAL_CORES QUERY NUMBER_OF_LOGICAL_CORES)
cmake_host_system_information(RESULT HOST_NUMBER_OF_PHYSICAL_CORES QUERY NUMBER_OF_PHYSICAL_CORES)
cmake_host_system_information(RESULT HOST_TOTAL_VIRTUAL_MEMORY QUERY TOTAL_VIRTUAL_MEMORY)
cmake_host_system_information(RESULT HOST_AVAILABLE_VIRTUAL_MEMORY QUERY AVAILABLE_VIRTUAL_MEMORY)
cmake_host_system_information(RESULT HOST_TOTAL_PHYSICAL_MEMORY QUERY TOTAL_PHYSICAL_MEMORY)
cmake_host_system_information(RESULT HOST_AVAILABLE_PHYSICAL_MEMORY QUERY AVAILABLE_PHYSICAL_MEMORY)

# ==========================================================
message(STATUS "HOSTNAME: ${HOST_HOSTNAME}")
message(STATUS "NUMBER_OF_LOGICAL_CORES: ${HOST_NUMBER_OF_LOGICAL_CORES}")
message(STATUS "NUMBER_OF_PHYSICAL_CORES: ${HOST_NUMBER_OF_PHYSICAL_CORES}")
message(STATUS "TOTAL_VIRTUAL_MEMORY: ${HOST_TOTAL_VIRTUAL_MEMORY}")
message(STATUS "AVAILABLE_VIRTUAL_MEMORY: ${HOST_AVAILABLE_VIRTUAL_MEMORY}")
message(STATUS "TOTAL_PHYSICAL_MEMORY: ${HOST_TOTAL_PHYSICAL_MEMORY}")
message(STATUS "AVAILABLE_PHYSICAL_MEMORY: ${HOST_AVAILABLE_PHYSICAL_MEMORY}")

message(STATUS "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message("==================================================")
