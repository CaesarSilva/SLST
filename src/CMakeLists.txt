project(SLST)

cmake_minimum_required(VERSION 2.8)
find_package(wxWidgets COMPONENTS core base REQUIRED)


include( "${wxWidgets_USE_FILE}" )
set(wxWidgets_USE_STATIC ON)

set(SRC_FILES
    cApp.cpp
    cMain.cpp
    Lobby.cpp
    MainNotebook.cpp
    NotificationTab.cpp
    ServerLine.cpp

    )
add_executable(
    ${PROJECT_NAME}
    ${SRC_FILES}
    )
target_include_directories(SLST PRIVATE rapidjson)
target_include_directories(SLST PRIVATE include)
target_link_libraries(
    ${PROJECT_NAME}
    ${wxWidgets_LIBRARIES}
    )
