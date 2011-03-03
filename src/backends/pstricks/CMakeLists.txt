include_directories(${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory (templates)

set( PstricksBackend_SRCS 
 pstricksbackend.cpp  
 pstricksdocumentsettings.cpp
 pstricksgenerator.cpp
)

kde4_add_kcfg_files(PstricksBackend_SRCS GENERATE_MOC settings.kcfgc)
install(FILES pstricksbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

kde4_add_ui_files(PstricksBackend_SRCS settings.ui)

kde4_add_plugin( cirkuit_pstricksbackend ${PstricksBackend_SRCS} )
target_link_libraries( cirkuit_pstricksbackend ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} cirkuitlibs)

install( FILES pstricksbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_pstricksbackend DESTINATION ${PLUGIN_INSTALL_DIR})