#ifndef MAI_OOP_2025_MEMORY_RESOURCE_H
#define MAI_OOP_2025_MEMORY_RESOURCE_H

#include <memory>
#include <vector>


class MemoryResource : public std::pmr::memory_resource {
private:

    struct Block {
        std::uint64_t offset;

        std::uint64_t size;
    };

public:

    explicit MemoryResource(std::uint64_t size);

    ~MemoryResource() override;

private:

    void *do_allocate(std::size_t bytes,
                      std::size_t alignment) override;

    void do_deallocate(void *pointer,
                       std::size_t bytes,
                       std::size_t alignment) override;

    bool do_is_equal(const memory_resource &other) const noexcept override;

private:

    char *_buffer;
    uint64_t _size;

    std::vector<Block> _used;
};

#endif //MAI_OOP_2025_MEMORY_RESOURCE_H