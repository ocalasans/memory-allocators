#include "CAllocator.h"
#include <cstdlib>
#include <cstdint>

CAllocator::CAllocator() noexcept : Allocator(0) {}

CAllocator::~CAllocator() noexcept {}

void CAllocator::Init() {}

void* CAllocator::Allocate(const std::size_t size, const std::size_t alignment) {
    if (alignment > 1) {
        void* ptr = NULL;
        const std::size_t align = (alignment < sizeof(void*)) ? sizeof(void*) : alignment;
        const std::size_t aligned_size = (size + align - 1) & ~(align - 1);

        if (posix_memalign(&ptr, align, aligned_size) != 0)
            return NULL;

        return ptr;
    }
    
    return std::malloc(size);
}

void CAllocator::Free(void* ptr) {
    std::free(ptr);
}