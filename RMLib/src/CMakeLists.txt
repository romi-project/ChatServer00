cmake_minimum_required(VERSION 3.13)

add_library(${PROJECT_NAME}
    "std.cpp"
    "util/Locale.cpp"
    "util/NetAddress.cpp"
    "util/SocketUtil.cpp"
    "RMSession.cpp"
)
