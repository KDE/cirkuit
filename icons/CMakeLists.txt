#find_package(KF5 REQUIRED)
include(ECMInstallIcons)

ecm_install_icons( ${ICON_INSTALL_DIR} )
install (FILES application-x-cirkuit.svgz DESTINATION ${ICON_INSTALL_DIR}/oxygen/scalable/mimetypes)
