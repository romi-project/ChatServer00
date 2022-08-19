#pragma once

#include <plog/Log.h>

#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>

#include <array>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <iterator>

#include <string>
#include <format>
#include <codecvt>
#include <locale>

#include <thread>
#include <atomic>
#include <mutex>

#include <memory>
#include <concepts>
#include <algorithm>
#include <functional>
#include <bit>
#include <chrono>
using namespace std::chrono_literals;

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2ipdef.h>
#include <windns.h>
#include <iphlpapi.h>

#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "IPHLPAPI.lib")

constexpr size_t    MAX_SOCKETS = 8192;
