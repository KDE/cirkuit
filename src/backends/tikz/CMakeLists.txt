add_subdirectory(templates)

#include_directories(${PROJECT_SOURCE_DIR}
#                    ${PROJECT_BINARY_DIR}
#)
set (CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set( TikzBackend_SRCS 
 tikzbackend.cpp  
 tikzdocumentsettings.cpp
 tikzgenerator.cpp
)

kconfig_add_kcfg_files(TikzBackend_SRCS GENERATE_MOC settings.kcfgc)
#install(FILES tikzbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

qt5_wrap_ui(TikzBackend_SRCS settings.ui)

add_library( cirkuit_tikzbackend SHARED ${TikzBackend_SRCS} )
target_link_libraries( cirkuit_tikzbackend ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} cirkuitlibs)

install( FILES tikzbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_tikzbackend DESTINATION ${BACKEND_INSTALL_DIR})
