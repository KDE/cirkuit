set(GENERIC_LIB_VERSION "1.0.0")
set(GENERIC_LIB_SOVERSION "1")

include(ECMQtDeclareLoggingCategory)
ecm_qt_declare_logging_category(LOGGING_SOURCE
                                HEADER cirkuitlib_debug.h
                                IDENTIFIER CIRKUIT_DEBUG
                                CATEGORY_NAME org.kde.cirkuitlib)

add_library(cirkuitlibs
    ${LOGGING_SOURCE}
    backend.cpp
    command.cpp
    document.cpp
    generator.cpp
    format.cpp
    documenttemplate.cpp
    logparser.cpp)

target_link_libraries( cirkuitlibs PUBLIC KF5::TextEditor KF5::KDELibs4Support)

set_target_properties( cirkuitlibs PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})

generate_export_header(cirkuitlibs BASE_NAME CIRKUIT)

install( TARGETS cirkuitlibs  ${INSTALL_TARGETS_DEFAULT_ARGS} )
