add_subdirectory (templates)

kconfig_add_kcfg_files(TikzBackend_SRCS GENERATE_MOC settings.kcfgc)
install(FILES tikzbackend.kcfg DESTINATION ${KCFG_INSTALL_DIR})

ki18n_wrap_ui(TikzBackend_SRCS settings.ui)

add_library(cirkuit_tikzbackend
 MODULE 
 ${TikzBackend_SRCS}
 tikzbackend.cpp
 tikzdocumentsettings.cpp
 tikzgenerator.cpp)
target_link_libraries( cirkuit_tikzbackend  KF5::KIOCore cirkuitlibs)

install( FILES tikzbackend.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/cirkuit)
install(TARGETS cirkuit_tikzbackend DESTINATION ${PLUGIN_INSTALL_DIR})
