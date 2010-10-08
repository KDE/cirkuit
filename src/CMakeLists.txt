project(cirkuit)

find_package(KDE4 REQUIRED)
find_package(Poppler REQUIRED)
include_directories(${KDE4_INCLUDES} ${POPPLER_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${QT_QTNETWORK_INCLUDE_DIR})

add_subdirectory( mimetypes )
add_subdirectory( syntax )
add_subdirectory( templates )

set(cirkuit_SRCS 
	main.cpp
	mainwindow.cpp
	livepreviewwidget.cpp
	logviewwidget.cpp
	qimagedisplay.cpp
	graphicsdocument.cpp
	circuitmacrosmanager.cpp
	httpdownloader.cpp
	graphicsgenerator.cpp
	command.cpp
	documenttemplate.cpp
	circuitmacrosbackend.cpp
	tikzbackend.cpp	
	gnuplotbackend.cpp
)
kde4_add_kcfg_files(cirkuit_SRCS GENERATE_MOC cirkuitsettings.kcfgc)
kde4_add_ui_files(cirkuit_SRCS cirkuit_general_settings.ui cirkuit_backend_settings.ui)
kde4_add_executable(cirkuit ${cirkuit_SRCS})

target_link_libraries(cirkuit ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KTEXTEDITOR_LIBS} ${POPPLER_LIBRARY} ${QT_QTNETWORK_LIBRARIES})

install(TARGETS cirkuit DESTINATION ${BIN_INSTALL_DIR})
install(FILES cirkuitui.rc 
DESTINATION ${DATA_INSTALL_DIR}/cirkuit)
install(FILES cirkuit.kcfg DESTINATION ${KCFG_INSTALL_DIR})

install( FILES cirkuit.notifyrc DESTINATION ${DATA_INSTALL_DIR}/cirkuit)
kde4_install_icons( ${ICON_INSTALL_DIR} )
install (FILES application-x-cirkuit.svgz DESTINATION ${ICON_INSTALL_DIR}/oxygen/scalable/mimetypes)
install (FILES cirkuit.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})

