project(cirkuit)

find_package(KDE4 REQUIRED)
include_directories(${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${QT_QTNETWORK_INCLUDE_DIR})

add_subdirectory( mimetypes )
add_subdirectory( syntax )
add_subdirectory( widgets )
add_subdirectory( lib )
include_directories( lib ${CMAKE_CURRENT_BINARY_DIR}/lib)
add_subdirectory( backends )

set(cirkuit_SRCS 
	main.cpp
	mainwindow.cpp
	circuitmacrosmanager.cpp
	generatorthread.cpp
)

kde4_add_kcfg_files(cirkuit_SRCS GENERATE_MOC cirkuitsettings.kcfgc)
kde4_add_ui_files(cirkuit_SRCS cirkuit_general_settings.ui)
kde4_add_executable(cirkuit ${cirkuit_SRCS})

target_link_libraries(cirkuit ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KTEXTEDITOR_LIBS} ${QT_QTNETWORK_LIBRARIES} cirkuitlibs cirkuitwidgets)

install(TARGETS cirkuit ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES cirkuitui.rc 
DESTINATION ${DATA_INSTALL_DIR}/cirkuit)
install(FILES cirkuit.kcfg DESTINATION ${KCFG_INSTALL_DIR})

install( FILES cirkuit.notifyrc DESTINATION ${DATA_INSTALL_DIR}/cirkuit)
install (PROGRAMS cirkuit.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
