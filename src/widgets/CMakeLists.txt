include_directories(${CMAKE_CURRENT_BINARY_DIR} ..)
set (cirkuitwidgets_SRCS imageview.cpp
    livepreviewwidget.cpp
    logviewwidget.cpp
    qimagedisplay.cpp
    backendchoosedialog.cpp
)

kde4_add_ui_files( cirkuitwidgets_SRCS backendchooser.ui)
kde4_add_library( cirkuitwidgets STATIC ${cirkuitwidgets_SRCS} )
