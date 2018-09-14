add_subdirectory(templates)

set (CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set( CircuitMacrosBackend_SRCS
 dpiclogparser.cpp 
 circuitmacrosbackend.cpp  
 circuitmacrosdocumentsettings.cpp
 circuitmacrosgenerator.cpp
 settingswidget.cpp
)


kconfig_add_kcfg_files(CircuitMacrosBackend_SRCS GENERATE_MOC settings.kcfgc)
#install(FILES circuitmacrosbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

qt5_wrap_ui(CircuitMacrosBackend_SRCS settings.ui)

add_library( cirkuit_circuitmacrosbackend SHARED ${CircuitMacrosBackend_SRCS} )
target_link_libraries( cirkuit_circuitmacrosbackend KF5::ConfigCore KF5::ConfigGui cirkuitlibs)
 
install( FILES circuitmacrosbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_circuitmacrosbackend DESTINATION ${BACKEND_INSTALL_DIR})

