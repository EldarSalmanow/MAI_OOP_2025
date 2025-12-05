#include <algorithm>
#include <cassert>

#include <lab5/memory_resource.h>


MemoryResource::MemoryResource(std::uint64_t size) {
    assert(size > 0);

    _buffer = new char[size];
    _size   = size;
}

MemoryResource::~MemoryResource() {
    delete[] _buffer;
}

void *MemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    (void)alignment;

    for (uint64_t i = 0; i < _used.size() + 1; ++i) {
        std::uint64_t begin = 0;
        std::uint64_t end   = _size;

        if (_used.empty()) {}
        else if (i == 0) {
            end = _used[0].offset;
        }
        else if (i == _used.size()) {
            begin = _used[_used.size() - 1].offset + _used[_used.size() - 1].size;
        }
        else {
            begin = _used[i - 1].offset + _used[i - 1].size;
            end   = _used[i].offset;
        }

        if (end - begin >= bytes) {
            _used.emplace_back(begin, bytes);

            std::ranges::sort(_used, [](const Block &first, const Block &second) {
                return first.offset < second.offset;
            });

            return _buffer + begin;
        }
    }

    return nullptr;
}


void MemoryResource::do_deallocate(void *pointer, std::size_t bytes, std::size_t alignment) {
    (void)alignment;

    std::uint64_t offset = static_cast<char *>(pointer) - _buffer;

    auto block = std::ranges::find_if(_used, [offset, bytes](const Block &block) {
        return block.offset == offset
               && block.size == bytes;
    });

    if (block == _used.end()) {
        return;
    }

    _used.erase(block);
}

bool MemoryResource::do_is_equal(const memory_resource &other) const noexcept {
    return this == &other;
}
