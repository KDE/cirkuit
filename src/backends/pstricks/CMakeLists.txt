add_subdirectory(templates)

#include_directories(${PROJECT_SOURCE_DIR}
#                    ${PROJECT_BINARY_DIR}
#)
set (CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set( PstricksBackend_SRCS 
 pstricksbackend.cpp  
 pstricksdocumentsettings.cpp
 pstricksgenerator.cpp
)

kconfig_add_kcfg_files(PstricksBackend_SRCS GENERATE_MOC settings.kcfgc)
#install(FILES pstricksbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

qt5_wrap_ui(PstricksBackend_SRCS settings.ui)

add_library( cirkuit_pstricksbackend SHARED ${PstricksBackend_SRCS} )
target_link_libraries( cirkuit_pstricksbackend ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} cirkuitlibs)

install( FILES pstricksbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_pstricksbackend DESTINATION ${BACKEND_INSTALL_DIR})
