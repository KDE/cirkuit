include_directories(${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory (templates)

set( CircuitMacrosBackend_SRCS dpiclogparser.cpp 
 circuitmacrosbackend.cpp  
 circuitmacrosdocumentsettings.cpp
 circuitmacrosgenerator.cpp
 settingswidget.cpp
)

kde4_add_kcfg_files(CircuitMacrosBackend_SRCS GENERATE_MOC settings.kcfgc)
install(FILES circuitmacrosbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

kde4_add_ui_files(CircuitMacrosBackend_SRCS settings.ui)

kde4_add_plugin( cirkuit_circuitmacrosbackend ${CircuitMacrosBackend_SRCS} )
target_link_libraries( cirkuit_circuitmacrosbackend ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} cirkuitlibs cirkuit)

install( FILES circuitmacrosbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_circuitmacrosbackend DESTINATION ${PLUGIN_INSTALL_DIR})
