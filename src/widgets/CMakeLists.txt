ki18n_wrap_ui( cirkuitwidgets_SRCS backendchooser.ui templatechooser.ui)
add_library(cirkuitwidgets STATIC
    templatechoosedialog.cpp
    imageview.cpp
    previewwidget.cpp
    logviewwidget.cpp
    backendchoosedialog.cpp
    widgetfloater.cpp
    ${cirkuitwidgets_SRCS}
)
target_link_libraries(cirkuitwidgets Qt5::Widgets KF5::I18n KF5::TextWidgets KF5::NewStuff KF5::KDELibs4Support)
