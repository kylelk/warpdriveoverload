include_directories(${WPOServer_SOURCE_DIR}/src/)

set(
CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/
)

add_executable(client main.cpp
			ship.cpp
			player.cpp
			room.cpp
            sqlite.cpp
            shell.cpp
            game_engine.cpp
            term_control.cpp
            window.cpp
            menu.cpp
            graphchart.cpp
            ncursespanel.cpp
            )

set (CMAKE_CXX_FLAGS "-std=c++0x -lsqlite3 -lboost_system -lpthread -ltermcap -lpanel -lncurses")
