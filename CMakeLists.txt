cmake_minimum_required(VERSION 3.0)

project(PEPlus LANGUAGES CXX VERSION 1.0.0)

set(CPACK_SYSTEM_NAME generic)

include(CPack)
include(GNUInstallDirs)

find_package(Boost REQUIRED)

add_library(peplus INTERFACE)
add_library(PEPlus::peplus ALIAS peplus)
target_compile_features(peplus INTERFACE cxx_std_17)
target_link_libraries(peplus INTERFACE ${Boost_LIBRARIES})

target_include_directories(peplus INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
                                            $<INSTALL_INTERFACE:include> ${Boost_INCLUDE_DIRS})

install(TARGETS peplus EXPORT peplus_targets INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT peplus_targets FILE PEPlusConfig.cmake NAMESPACE PEPlus:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
export(EXPORT peplus_targets FILE PEPlusTargets.cmake NAMESPACE PEPlus::)

configure_file(include/peplus/version.hpp.cmake include/peplus/version.hpp)
install(DIRECTORY include/peplus DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN *.hpp)
install(FILES ${CMAKE_BINARY_DIR}/include/peplus/version.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/peplus)

include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/PEPlusConfig.cmake PEPlusConfig.cmake
                              INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)
write_basic_package_version_file(PEPlusConfigVersion.cmake VERSION ${PROJECT_VERSION}
                                                           COMPATIBILITY AnyNewerVersion)

install(FILES ${CMAKE_BINARY_DIR}/PEPlusTargets.cmake
              ${CMAKE_BINARY_DIR}/PEPlusConfigVersion.cmake
              DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake)