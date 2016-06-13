include_directories( ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory (templates)

set( GnuplotBackend_SRCS 
 gnuplotbackend.cpp  
 gnuplotdocumentsettings.cpp
 gnuplotgenerator.cpp 
)

include(ECMQtDeclareLoggingCategory)

ecm_qt_declare_logging_category(GnuplotBackend_SRCS
                                HEADER cirkuit_gnuplotbackend_debug.h
                                IDENTIFIER CIRKUIT_DEBUG
                                CATEGORY_NAME org.kde.cirkuit_gnuplotbackend)
                                
kconfig_add_kcfg_files(GnuplotBackend_SRCS GENERATE_MOC settings.kcfgc)
install(FILES gnuplotbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

ki18n_wrap_ui(GnuplotBackend_SRCS settings.ui)

add_library(cirkuit_gnuplotbackend MODULE ${GnuplotBackend_SRCS} )
target_link_libraries( cirkuit_gnuplotbackend  KF5::KIOCore cirkuitlibs)

install( FILES gnuplotbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_gnuplotbackend DESTINATION ${PLUGIN_INSTALL_DIR})
