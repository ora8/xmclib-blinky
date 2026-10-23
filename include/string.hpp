#pragma once

#include <cstddef>

class string_view
{
public:
    string_view(char *data, size_t size) : _data{data}, _size{size}
    {
    }
    char *data() const
    {
        return _data;
    }
    size_t size() const
    {
        return _size;
    }
private:
    char *_data;
    size_t _size;
};