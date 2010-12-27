set( NullBackend_SRCS 
 nullbackend.cpp  
)

kde4_add_plugin( cirkuit_nullbackend ${NullBackend_SRCS} )
target_link_libraries( cirkuit_nullbackend ${KDE4_KDEUI_LIBS} cirkuit)

install( FILES nullbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_nullbackend DESTINATION ${PLUGIN_INSTALL_DIR})
