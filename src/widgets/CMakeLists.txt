set(GENERIC_LIB_VERSION "2.0.0")
set(GENERIC_LIB_SOVERSION "2")

# Need this line
include_directories( ${CMAKE_SOURCE_DIR}/src)

set (CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (cirkuitwidgets_SRCS templatechoosedialog.cpp 
    imageview.cpp
    previewwidget.cpp
    logviewwidget.cpp
    backendchoosedialog.cpp
    widgetfloater.cpp
)

qt5_wrap_ui( cirkuitwidgets_SRCS backendchooser.ui templatechooser.ui)
add_library( cirkuitwidgets STATIC ${cirkuitwidgets_SRCS} )

target_link_libraries( cirkuitwidgets Qt5::Core Qt5::Widgets KF5::KIOCore KF5::I18n KF5::IconThemes cirkuitlibs )
# no longer need KF5::NewStuff

install( TARGETS cirkuitwidgets  ${INSTALL_TARGETS_DEFAULT_ARGS} )

