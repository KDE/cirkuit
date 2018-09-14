# root CMakeLists.txt
#
# Note: Install path by default is CMAKE_INSTALL_PREFIX:PATH=/usr/local
#       An alternative path can be given on the command line, e.g.  -DCMAKE_INSTALL_PREFIX=/usr/bin
#
#set(CMAKE_VERBOSE_MAKEFILE ON)

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(CIRKUIT VERSION "0.5.0")

set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.3.0")
set(SHARED_MIME_INFO_MINIMUM_VERSION "0.30")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

#include(CheckIncludeFile)
include(KDEInstallDirs)
include(ECMInstallIcons)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

# Find Qt modules
find_package(Qt5 ${QT5_MIN_VERSION} REQUIRED COMPONENTS
    Core    # QCommandLineParser, QStringLiteral
    Widgets # QApplication
    Gui
)

# Find KF5 modules
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    CoreAddons      # KAboutData
    I18n            # KLocalizedString
    WidgetsAddons   # KMessageBox
    Completion      # KCombobox
    Parts
    TextWidgets
    TextEditor
    Service
    KIO
    XmlGui
    Crash
    IconThemes
    Config
    NewStuff
    Archive
)

find_library( LIBPOPPLER_QT5 poppler-qt5 REQUIRED)
# Poppler_INCLUDE_DIRS does not seem to be available on some systems
if(NOT EXISTS ${Poppler_INCLUDE_DIRS})
   set(Poppler_INCLUDE_DIRS "/usr/include/poppler/qt5")
endif()

# For compilation/link
set( CMAKE_AUTOMOC ON)
set( CMAKE_INCLUDE_CURRENT_DIR ON)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin ) # for the executable
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/sharedlib ) # shared libraries

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/cirkuitconfig.h.in"
  "${PROJECT_BINARY_DIR}/cirkuitconfig.h"
  )

# For installation of backends (plugin shared object files) 
set (BACKEND_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/cirkuit_backends )

add_definitions(
    -DQT_DEPRECATED_WARNINGS
    -DQT_DISABLE_DEPRECATED_BEFORE=0x050700
#    -DQT_NO_SIGNALS_SLOTS_KEYWORDS            # when defining -DQT_NO_KEYWORDS, must use Q_SLOTS instead of slots, Q_SIGNALS
    -DQT_NO_URL_CAST_FROM_STRING
    -DQT_STRICT_ITERATORS
    -DBACKEND_INSTALL_DIR=\"${BACKEND_INSTALL_DIR}\" # do not use PLUGIN_INSTALL_DIR as this refers to Qt5 plugins
)

if (Qt5_POSITION_INDEPENDENT_CODE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# recurse into the following ...
add_subdirectory(src)
add_subdirectory(icons)

include(ECMOptionalAddSubdirectory)
ecm_optional_add_subdirectory( po )

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

