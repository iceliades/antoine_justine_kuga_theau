
set(lib_client_target client_static)

# Generate header files from dia UML files
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../client.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../render.dia")

# Find all source files to include in library
file(GLOB_RECURSE client_sources *.cpp)
list(REMOVE_ITEM client_sources "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

# Build the "client" library, add required include and link against dependencies
add_library(${lib_client_target} STATIC ${client_sources} client/Command_Client_Autre.cpp client/Command_Client_Engine.cpp client/Command_Client_Render.cpp client/Command_Client_RAI.cpp client/ICommand_Client.cpp client/Command_Client_Hello.cpp client/Command_Client_PAI.cpp client/Client.cpp client/Command_Client_Thread.cpp client/Command_Client_Network.cpp)
add_dependencies(${lib_client_target} generate-headers)
target_include_directories(${lib_client_target} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${SFML_INCLUDE_DIR}
  )
target_link_libraries(${lib_client_target} PUBLIC
  ${SFML_LIBRARIES}
  $<TARGET_NAME:shared_static>
  )

# Compile "client" executable
set(client_target client)
add_executable(${client_target} main.cpp)
target_link_libraries(${client_target} ${lib_client_target})
if(BUILD_CODE_COVERAGE)
  add_dependencies(code-coverage ${client_target})
endif()

# vim: set sw=2 sts=2 et:

