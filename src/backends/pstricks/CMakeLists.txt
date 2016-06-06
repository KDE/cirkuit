include_directories( ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory (templates)

set( PstricksBackend_SRCS 
 pstricksbackend.cpp  
 pstricksdocumentsettings.cpp
 pstricksgenerator.cpp
)

kconfig_add_kcfg_files(PstricksBackend_SRCS GENERATE_MOC settings.kcfgc)
install(FILES pstricksbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

ki18n_wrap_ui(PstricksBackend_SRCS settings.ui)

add_library(cirkuit_pstricksbackend MODULE ${PstricksBackend_SRCS} )
target_link_libraries( cirkuit_pstricksbackend  KF5::KIOCore cirkuitlibs)

install( FILES pstricksbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_pstricksbackend DESTINATION ${PLUGIN_INSTALL_DIR})