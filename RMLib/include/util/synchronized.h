#pragma once

#define synchronized(_x) for (auto _ul = std::unique_lock<decltype(_x)>(_x); _ul; _ul.unlock())
