set( NullBackend_SRCS 
 nullbackend.cpp  
 nulldocumentsettings.cpp
 nullgenerator.cpp
)

add_library(cirkuit_nullbackend MODULE ${NullBackend_SRCS} )
target_link_libraries( cirkuit_nullbackend  cirkuitlibs)

install( FILES nullbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_nullbackend DESTINATION ${PLUGIN_INSTALL_DIR})
