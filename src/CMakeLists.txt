add_definitions(-DENABLE_KMESSAGEWIDGET)

add_subdirectory( mimetypes )
add_subdirectory( syntax )
add_subdirectory( lib )
include_directories(. lib ${CMAKE_CURRENT_BINARY_DIR}/lib)
add_subdirectory( backends )
add_subdirectory( widgets )

kconfig_add_kcfg_files(cirkuit_SRCS GENERATE_MOC cirkuitsettings.kcfgc)
ki18n_wrap_ui(cirkuit_SRCS cirkuit_general_settings.ui)
add_executable(cirkuit main.cpp
	mainwindow.cpp
	circuitmacrosmanager.cpp
	generatorthread.cpp
	renderthread.cpp)

target_link_libraries(cirkuit KF5::KIOCore KF5::TextEditor KF5::NewStuff ${POPPLER_LIBRARY} cirkuitlibs cirkuitwidgets)

install(TARGETS cirkuit ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES cirkuitui.rc DESTINATION ${DATA_INSTALL_DIR}/cirkuit)
install(FILES cirkuit.kcfg DESTINATION ${KCFG_INSTALL_DIR})
install(FILES cirkuit_example.knsrc cirkuit_template.knsrc DESTINATION  ${CONFIG_INSTALL_DIR} )

install(FILES cirkuit.notifyrc DESTINATION ${KNOTIFYRC_INSTALL_DIR})
install(PROGRAMS cirkuit.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
