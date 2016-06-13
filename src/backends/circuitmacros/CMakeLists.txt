include_directories( ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory (templates)

set( CircuitMacrosBackend_SRCS dpiclogparser.cpp 
 circuitmacrosbackend.cpp  
 circuitmacrosdocumentsettings.cpp
 circuitmacrosgenerator.cpp
 settingswidget.cpp
)

include(ECMQtDeclareLoggingCategory)

ecm_qt_declare_logging_category(CircuitMacrosBackend_SRCS
                                HEADER cirkuit_circuitmacrosbackend_debug.h
                                IDENTIFIER CIRKUIT_DEBUG
                                CATEGORY_NAME org.kde.cirkuit_circuitmacrosbackend_debug)


kconfig_add_kcfg_files(CircuitMacrosBackend_SRCS GENERATE_MOC settings.kcfgc)
install(FILES circuitmacrosbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

ki18n_wrap_ui(CircuitMacrosBackend_SRCS settings.ui)

add_library(cirkuit_circuitmacrosbackend MODULE ${CircuitMacrosBackend_SRCS} )
target_link_libraries( cirkuit_circuitmacrosbackend  KF5::KIOCore cirkuitlibs)

install( FILES circuitmacrosbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_circuitmacrosbackend DESTINATION ${PLUGIN_INSTALL_DIR})
