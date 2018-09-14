cmake_policy(SET CMP0063 NEW)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory( mimetypes )
add_subdirectory( syntax )
add_subdirectory( lib )
include_directories( lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
add_subdirectory( backends )
add_subdirectory( widgets )
add_subdirectory( examples )

set(cirkuit_SRCS 
	main.cpp
	mainwindow.cpp
	circuitmacrosmanager.cpp
	generatorthread.cpp
	renderthread.cpp
    lib/failcodes.cpp
)

kconfig_add_kcfg_files(cirkuit_SRCS GENERATE_MOC cirkuitsettings.kcfgc)
qt5_wrap_ui(cirkuit_SRCS cirkuit_general_settings.ui)
add_executable(${PROJECT_NAME} ${cirkuit_SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "cirkuit")

# Does not seem to find poppler automatically, so add this.
include_directories(${Poppler_INCLUDE_DIRS})


target_link_libraries( CIRKUIT
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::WidgetsAddons
    KF5::TextWidgets
    KF5::TextEditor
    KF5::Service
    KF5::KIOCore
    KF5::Completion
    KF5::ConfigCore
    KF5::ConfigGui
    KF5::Archive
    KF5::KIONTLM

    ${LIBPOPPLER_QT5}
    cirkuitwidgets
    cirkuitlibs
)

install(TARGETS CIRKUIT ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES cirkuitui.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/cirkuit)
#install(FILES cirkuit.kcfg DESTINATION ${KCFG_INSTALL_DIR})
install(FILES cirkuit_example.knsrc cirkuit_template.knsrc DESTINATION  ${CONFIG_INSTALL_DIR} )
install( FILES cirkuit.notifyrc DESTINATION ${DATA_INSTALL_DIR}/cirkuit)
install (PROGRAMS cirkuit.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})

