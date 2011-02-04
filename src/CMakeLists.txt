project(cirkuit)

find_package(KDE4 REQUIRED)
find_package(Poppler REQUIRED)
include_directories(${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/widgets ${QT_QTNETWORK_INCLUDE_DIR} ${POPPLER_INCLUDE_DIR})

add_subdirectory( mimetypes )
add_subdirectory( syntax )
add_subdirectory( lib )
include_directories( lib ${CMAKE_CURRENT_BINARY_DIR}/lib)
add_subdirectory( backends )
add_subdirectory( widgets )

set(cirkuit_SRCS 
	main.cpp
	mainwindow.cpp
	circuitmacrosmanager.cpp
	generatorthread.cpp
	renderthread.cpp
)

kde4_add_kcfg_files(cirkuit_SRCS GENERATE_MOC cirkuitsettings.kcfgc)
kde4_add_ui_files(cirkuit_SRCS cirkuit_general_settings.ui)
kde4_add_executable(cirkuit ${cirkuit_SRCS})

target_link_libraries(cirkuit ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KTEXTEDITOR_LIBS} ${KDE4_KNEWSTUFF3_LIBS} ${POPPLER_LIBRARY} cirkuitlibs cirkuitwidgets)

install(TARGETS cirkuit ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES cirkuitui.rc 
DESTINATION ${DATA_INSTALL_DIR}/cirkuit)
install(FILES cirkuit.kcfg DESTINATION ${KCFG_INSTALL_DIR})
install(FILES cirkuit.knsrc  DESTINATION  ${CONFIG_INSTALL_DIR} )
install(FILES cirkuit_example.knsrc  DESTINATION  ${CONFIG_INSTALL_DIR} )

install( FILES cirkuit.notifyrc DESTINATION ${DATA_INSTALL_DIR}/cirkuit)
install (PROGRAMS cirkuit.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
