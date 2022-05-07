cmake_minimum_required(VERSION 3.5)

project(dentapp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Sql)

set(PROJECT_SOURCES
        main.cpp
       	adddoctor.cpp
	adddoctor.h
	adddoctor.ui
	addsession.cpp
	addsession.h
	addsession.ui
	adminmenu.cpp
	adminmenu.h
	adminmenu.ui
	clickablelabel.cpp
	clickablelabel.h
	clientmenu.cpp
	clientmenu.h
	clientmenu.ui
	database.cpp
	database.h
	doctormenu.cpp
	doctormenu.h
	doctormenu.ui
	entrywindow.cpp
	entrywindow.h
	entrywindow.ui
	registrateaccount.cpp
	registrateaccount.h
	registrateaccount.ui
	remindpassword.cpp
	remindpassword.h
	remindpassword.ui
	session.cpp
	session.h
	settings.cpp
	settings.h
	settings.ui
        user.cpp
        user.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(dentapp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    else()
        add_executable(dentapp
            ${PROJECT_SOURCES}
        )
endif()

get_property(QT_CORE_INCLUDE_DIRS TARGET Qt${QT_VERSION_MAJOR}::Core PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
list(GET QT_CORE_INCLUDE_DIRS 0 QT_CORE_MAIN_INCLUDE_DIR)
get_filename_component(QT_MAIN_DIR ${QT_CORE_MAIN_INCLUDE_DIR}/../.. ABSOLUTE)

install(TARGETS
            dentapp
        DESTINATION
            .
)

install(FILES
    $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Core>
    $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Gui>
    $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Widgets>
    $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Sql>
    DESTINATION .)

install(DIRECTORY
    ${QT_MAIN_DIR}/plugins/platforms/
        DESTINATION ./platforms USE_SOURCE_PERMISSIONS)

install(DIRECTORY
    ${QT_MAIN_DIR}/plugins/sqldrivers/
        DESTINATION ./sqldrivers USE_SOURCE_PERMISSIONS)

target_link_libraries(dentapp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Sql)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(dentapp)
endif()
