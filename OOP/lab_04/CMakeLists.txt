cmake_minimum_required(VERSION 3.5)

project(lab_04 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

function(add_include_directories_recursive dir)
    include_directories("${dir}")
    get_filename_component(abs_dir "${dir}" ABSOLUTE)
    file(GLOB subdirs RELATIVE "${abs_dir}" "${abs_dir}/*")
    foreach(subdir ${subdirs})
        if(IS_DIRECTORY "${abs_dir}/${subdir}")
            include_directories("${abs_dir}/${subdir}")
            add_include_directories_recursive("${abs_dir}/${subdir}")
        endif()
    endforeach()
endfunction()

add_include_directories_recursive("${CMAKE_CURRENT_LIST_DIR}/qt_ui")
add_include_directories_recursive("${CMAKE_CURRENT_LIST_DIR}/elevator")
add_include_directories_recursive("${CMAKE_CURRENT_LIST_DIR}/controller")
add_include_directories_recursive("${CMAKE_CURRENT_LIST_DIR}/cabin")
add_include_directories_recursive("${CMAKE_CURRENT_LIST_DIR}/doors")

set(PROJECT_SOURCES
    main.cpp
    qt_ui/mainwindow.cpp
    qt_ui/mainwindow.h
    qt_ui/mainwindow.ui

    constants.h

    elevator/elevator.h elevator/elevator.cpp

    controller/controller.h controller/controller.cpp

    cabin/cabin.h cabin/cabin.cpp

    doors/doors.h doors/doors.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lab_04
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET lab_04 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(lab_04 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(lab_04
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(lab_04 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.lab_04)
endif()
set_target_properties(lab_04 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS lab_04
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab_04)
endif()
