cmake_minimum_required(VERSION 3.5)

project(lab_03 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        qt_ui/mainwindow.cpp
        qt_ui/mainwindow.h
        qt_ui/mainwindow.ui

        commands/Facade.h
        commands/Command.h
        commands/Camera/CameraCommand.h commands/Camera/CameraCommand.cpp
        commands/Scene/SceneCommand.h commands/Scene/SceneCommand.cpp
        commands/Object/ObjectCommand.h commands/Object/ObjectCommand.cpp

        managers/ManagerSolution.h managers/ManagerSolution.cpp
        managers/BaseManager.h
        managers/draw/DrawManager.h managers/draw/DrawManager.cpp
        managers/draw/DrawManagerCreator.h managers/draw/DrawManagerCreator.cpp
        managers/scene/SceneManager.h managers/scene/SceneManager.cpp
        managers/scene/SceneManagerCreator.h managers/scene/SceneManagerCreator.cpp
        managers/camera/CameraManager.h managers/camera/CameraManager.cpp
        managers/camera/CameraManagerCreator.h managers/camera/CameraManagerCreator.cpp
        managers/transform/TransformManager.h managers/transform/TransformManager.cpp
        managers/transform/TransformManagerCreator.h managers/transform/TransformManagerCreator.cpp
        managers/load/LoadManager.h managers/load/LoadManager.cpp
        managers/load/LoadManagerCreator.h managers/load/LoadManagerCreator.cpp

        objects/BaseObject.h objects/BaseObject.cpp
        objects/ObjectComposite.h objects/ObjectComposite.cpp

        drawer/DrawerSolution.h
        drawer/AbstractFactory.h
        drawer/BaseDrawer.h
        drawer/Qt/QtFactory.h drawer/Qt/QtFactory.cpp
        drawer/Qt/QtDrawer.h drawer/Qt/QtDrawer.cpp
        drawer/DrawerSolution.hpp

        visitor/BaseVisitor.h
        visitor/draw/DrawVisitor.h visitor/draw/DrawVisitor.cpp

        scene/Scene.h scene/Scene.cpp
        scene/SceneGroup.h scene/SceneGroup.cpp
)

include_directories("${CMAKE_CURRENT_LIST_DIR}/qt_ui")
include_directories("${CMAKE_CURRENT_LIST_DIR}/commands")
include_directories("${CMAKE_CURRENT_LIST_DIR}/managers")
include_directories("${CMAKE_CURRENT_LIST_DIR}/drawer")
include_directories("${CMAKE_CURRENT_LIST_DIR}/objects")
include_directories("${CMAKE_CURRENT_LIST_DIR}/visitor")
include_directories("${CMAKE_CURRENT_LIST_DIR}/scene")


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lab_03
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        objects/VisibleObjects/VisibleObject.h
        objects/InvisibleObjects/InVisibleObject.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET lab_03 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(lab_03 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(lab_03
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(lab_03 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.lab_03)
endif()
set_target_properties(lab_03 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS lab_03
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab_03)
endif()
