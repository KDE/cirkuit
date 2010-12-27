set(GENERIC_LIB_VERSION "0.0.1")
set(GENERIC_LIB_SOVERSION "1")

set ( cirkuit_LIB_SRCS
)

set( cirkuit_LIB_HDRS
    cirkuit_export.h
)

kde4_add_library( libcirkuit SHARED ${cirkuit_LIB_SRCS} )

target_link_libraries( libcirkuit
  ${KDE4_KDECORE_LIBS}
)

set_target_properties( libcirkuit
  PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION}
)

install( TARGETS libcirkuit  ${INSTALL_TARGETS_DEFAULT_ARGS} )

install( FILES cirkuit_backend.desktop  DESTINATION ${SERVICETYPES_INSTALL_DIR})