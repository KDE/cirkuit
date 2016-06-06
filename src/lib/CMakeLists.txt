set(GENERIC_LIB_VERSION "1.0.0")
set(GENERIC_LIB_SOVERSION "1")

add_library(cirkuitlibs
    backend.cpp
    command.cpp
    document.cpp
    generator.cpp
    format.cpp
    documenttemplate.cpp
    logparser.cpp)

target_link_libraries( cirkuitlibs PRIVATE KF5::TextEditor PUBLIC KF5::KDELibs4Support)

set_target_properties( cirkuitlibs PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})

generate_export_header(cirkuitlibs BASE_NAME CIRKUIT)

install( TARGETS cirkuitlibs  ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( FILES cirkuit_backend.desktop  DESTINATION ${SERVICETYPES_INSTALL_DIR})
