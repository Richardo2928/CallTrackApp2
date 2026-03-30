cmake_minimum_required(VERSION 4.1)
project(CallTrackApp2)

set(CMAKE_CXX_STANDARD 20)

add_executable(CallTrackApp2 main.cpp
        main.cpp
        src/calltrackapp.cpp
        src/agent.cpp
        src/agentlist.cpp
        src/agentnode.cpp
        src/call.cpp
        src/calllist.cpp
        src/callnode.cpp
        src/date.cpp
        src/name.cpp
        src/schedule.cpp
        src/time.cpp)
