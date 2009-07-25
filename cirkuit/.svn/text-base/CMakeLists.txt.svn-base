PROJECT(cirkuit)
 
FIND_PACKAGE(KDE4 REQUIRED)
INCLUDE_DIRECTORIES( ${KDE4_INCLUDES} ${QT_QTNETWORK_INCLUDE_DIR} )

add_subdirectory( mimetypes )
 
SET(cirkuit_SRCS 
  main.cpp
  mainwindow.cpp
  kcmgeneralsettings.cpp
  qimagedisplay.cpp
  circuitbuilder.cpp
  livepreviewwidget.cpp
  twotermdialog.cpp
  httpdownloader.cpp
  circuitmacrosmanager.cpp
  externalbinmanager.cpp
  graphicdocument.cpp
)


kde4_add_kcfg_files(cirkuit_SRCS kcircuitmacrossettings.kcfgc)
kde4_add_ui_files(cirkuit_SRCS kcmgeneralsettings.ui)
KDE4_ADD_EXECUTABLE(cirkuit ${cirkuit_SRCS})
 
TARGET_LINK_LIBRARIES( cirkuit ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${QT_QTNETWORK_LIBRARIES}
)
 
install(TARGETS cirkuit RUNTIME DESTINATION bin)
install( FILES cirkuitui.rc 
         DESTINATION  ${DATA_INSTALL_DIR}/cirkuit )
			
install( FILES cirkuit.notifyrc DESTINATION ${DATA_INSTALL_DIR}/cirkuit)
kde4_install_icons( ${ICON_INSTALL_DIR} )
install (FILES application-x-cirkuit.svgz DESTINATION ${ICON_INSTALL_DIR}/oxygen/scalable/mimetypes)
install (FILES cirkuit.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})

