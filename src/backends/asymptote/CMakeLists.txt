set( AsymptoteBackend_SRCS
 asymptotebackend.cpp  
 asymptotedocumentsettings.cpp
 asymptotegenerator.cpp
)

kde4_add_plugin( cirkuit_asymptotebackend ${AsymptoteBackend_SRCS} )
target_link_libraries( cirkuit_asymptotebackend ${KDE4_KDEUI_LIBS} cirkuitlibs)

install( FILES asymptotebackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_asymptotebackend DESTINATION ${PLUGIN_INSTALL_DIR})
