set(GENERIC_LIB_VERSION "2.0.0")
set(GENERIC_LIB_SOVERSION "2")

set (CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set ( cirkuit_LIB_SRCS 
    backend_interface.cpp
    command.cpp
    document.cpp
    generator.cpp
    format.cpp
    documenttemplate.cpp
    logparser.cpp
    failcodes.cpp
)

set( cirkuit_LIB_HDRS
    cirkuit_export.h
)

add_library( cirkuitlibs SHARED ${cirkuit_LIB_SRCS} )


set_target_properties( cirkuitlibs
  PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} 
)

target_link_libraries( cirkuitlibs Qt5::Core Qt5::Widgets KF5::TextEditor KF5::TextWidgets KF5::Parts KF5::Service KF5::KIOCore)

install( TARGETS cirkuitlibs  ${INSTALL_TARGETS_DEFAULT_ARGS} )

install( FILES cirkuit_backend.desktop  DESTINATION ${SERVICETYPES_INSTALL_DIR})
