add_subdirectory (templates)

#include_directories(${PROJECT_SOURCE_DIR}
#                    ${PROJECT_BINARY_DIR}
#)
set (CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set( GnuplotBackend_SRCS 
 gnuplotbackend.cpp  
 gnuplotdocumentsettings.cpp
 gnuplotgenerator.cpp
)

kconfig_add_kcfg_files(GnuplotBackend_SRCS GENERATE_MOC settings.kcfgc)
#install(FILES gnuplotbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

qt5_wrap_ui(GnuplotBackend_SRCS settings.ui)

add_library( cirkuit_gnuplotbackend SHARED ${GnuplotBackend_SRCS} )
target_link_libraries( cirkuit_gnuplotbackend ${KF5_KFUI_LIBS} ${KF5_KIO_LIBS} cirkuitlibs)

install( FILES gnuplotbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_gnuplotbackend DESTINATION ${BACKEND_INSTALL_DIR})
