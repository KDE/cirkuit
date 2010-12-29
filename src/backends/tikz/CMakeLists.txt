include_directories(${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set( TikzBackend_SRCS 
 tikzbackend.cpp  
 tikzdocumentsettings.cpp
 tikzgenerator.cpp
)

kde4_add_kcfg_files(TikzBackend_SRCS GENERATE_MOC settings.kcfgc)
install(FILES tikzbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

kde4_add_ui_files(TikzBackend_SRCS settings.ui)

kde4_add_plugin( cirkuit_tikzbackend ${TikzBackend_SRCS} )
target_link_libraries( cirkuit_tikzbackend ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} cirkuitlibs)

install( FILES tikzbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_tikzbackend DESTINATION ${PLUGIN_INSTALL_DIR})