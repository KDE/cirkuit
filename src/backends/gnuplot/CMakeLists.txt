include_directories(${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory (templates)

set( GnuplotBackend_SRCS 
 gnuplotbackend.cpp  
 gnuplotdocumentsettings.cpp
 gnuplotgenerator.cpp
)

kde4_add_kcfg_files(GnuplotBackend_SRCS GENERATE_MOC settings.kcfgc)
install(FILES gnuplotbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

kde4_add_ui_files(GnuplotBackend_SRCS settings.ui)

kde4_add_plugin( cirkuit_gnuplotbackend ${GnuplotBackend_SRCS} )
target_link_libraries( cirkuit_gnuplotbackend ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} cirkuitlibs)

install( FILES gnuplotbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_gnuplotbackend DESTINATION ${PLUGIN_INSTALL_DIR})
