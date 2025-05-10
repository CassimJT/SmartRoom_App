cmake_minimum_required(VERSION 3.16)

project(SmartRoom VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
add_subdirectory(core/qtmqtt)

find_package(Qt6 REQUIRED COMPONENTS Quick Core Network )

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appSmartRoom
    main.cpp
    rsource.qrc
)

qt_add_qml_module(appSmartRoom
    URI SmartRoom
    VERSION 1.0
    QML_FILES
        Main.qml
        RESOURCES android/AndroidManifest.xml android/build.gradle android/res/values/libs.xml android/res/xml/qtprovider_paths.xml android/gradle/wrapper/gradle-wrapper.jar android/gradle/wrapper/gradle-wrapper.properties android/gradle.properties android/gradlew android/gradlew.bat
        QML_FILES CircularProgressBar.qml
        SOURCES systemcontroller.h
        SOURCES systemcontroller.cpp

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSmartRoom PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSmartRoom
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSmartRoom
    PRIVATE Qt6::Quick Qt6::Mqtt Qt6::Core Qt6::Network
)
set_property(TARGET appSmartRoom APPEND PROPERTY
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)

include(GNUInstallDirs)
install(TARGETS appSmartRoom
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
