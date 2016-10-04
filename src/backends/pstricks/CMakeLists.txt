include_directories( ${CMAKE_CURRENT_BINARY_DIR})
                           
add_subdirectory (templates)

set( PstricksBackend_SRCS 
 pstricksbackend.cpp  
 pstricksdocumentsettings.cpp
 pstricksgenerator.cpp
)

include(ECMQtDeclareLoggingCategory)

ecm_qt_declare_logging_category(PstricksBackend_SRCS
                                HEADER cirkuit_pstricksbackend_debug.h
                                IDENTIFIER CIRKUIT_DEBUG
                                CATEGORY_NAME org.kde.cirkuit_pstricksbackend)

kconfig_add_kcfg_files(PstricksBackend_SRCS GENERATE_MOC settings.kcfgc)
install(FILES pstricksbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

ki18n_wrap_ui(PstricksBackend_SRCS settings.ui)

add_library(cirkuit_pstricksbackend MODULE ${PstricksBackend_SRCS} )
kcoreaddons_desktop_to_json( cirkuit_pstricksbackend pstricksbackend.desktop
                             SERVICE_TYPES cirkuit_backend.desktop
)
target_link_libraries( cirkuit_pstricksbackend  KF5::KIOCore cirkuitlibs)

install( FILES pstricksbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_pstricksbackend DESTINATION ${PLUGIN_INSTALL_DIR})