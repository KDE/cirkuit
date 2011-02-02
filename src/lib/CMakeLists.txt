set(GENERIC_LIB_VERSION "0.0.1")
set(GENERIC_LIB_SOVERSION "1")

set ( cirkuit_LIB_SRCS
    backend.cpp
    command.cpp
    document.cpp
    generator.cpp
    format.cpp
    documenttemplate.cpp
)

set( cirkuit_LIB_HDRS
    cirkuit_export.h
)

kde4_add_library( cirkuitlibs SHARED ${cirkuit_LIB_SRCS} )

target_link_libraries( cirkuitlibs
  ${KDE4_KDECORE_LIBS} ${KDE4_KTEXTEDITOR_LIBS}
)

set_target_properties( cirkuitlibs
  PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION}
)

install( TARGETS cirkuitlibs  ${INSTALL_TARGETS_DEFAULT_ARGS} )

install( FILES cirkuit_backend.desktop  DESTINATION ${SERVICETYPES_INSTALL_DIR})
