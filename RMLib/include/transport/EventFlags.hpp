#pragma once

enum EventFlags : int
{
    None = 0,
    Readable = 1 << 0,
    Writable = 1 << 1
};
