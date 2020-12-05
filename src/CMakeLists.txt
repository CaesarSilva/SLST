find_package(wxWidgets COMPONENTS core base net REQUIRED)
if (UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(deps REQUIRED IMPORTED_TARGET glib-2.0)
    pkg_check_modules(depss REQUIRED IMPORTED_TARGET gdk-pixbuf-2.0)   
endif(UNIX)
    


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
if(UNIX)
target_link_libraries(
    ${PROJECT_NAME}
    ${wxWidgets_LIBRARIES}
    PkgConfig::deps
    PkgConfig::depss
    notify
    )
else(UNIX)
target_link_libraries(
    ${PROJECT_NAME}
    ${wxWidgets_LIBRARIES}
    )
endif()
