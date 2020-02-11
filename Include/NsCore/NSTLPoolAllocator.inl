////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


namespace eastl
{

////////////////////////////////////////////////////////////////////////////////////////////////////
PoolAllocator::PoolAllocator(const char*)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
PoolAllocator::PoolAllocator(const PoolAllocator&)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
PoolAllocator& PoolAllocator::operator=(const PoolAllocator&)
{
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void PoolAllocator::Init(uint32_t nodeSize, uint32_t nodeCount)
{
    mFixedAllocator.Initialize(nodeSize, nodeSize * nodeCount);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void* PoolAllocator::allocate(size_t n, int)
{
    if (n == mFixedAllocator.GetBlockSize())
    {
        return mFixedAllocator.Allocate();
    }
    else
    {
        return Noesis::Alloc(n);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void* PoolAllocator::allocate(size_t n, size_t, size_t, int flags)
{
    return allocate(n, flags);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void PoolAllocator::deallocate(void* p, size_t n)
{
    if (n == mFixedAllocator.GetBlockSize())
    {
        mFixedAllocator.Deallocate(p);
    }
    else
    {
        Noesis::Dealloc(p);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool operator==(const PoolAllocator&, const PoolAllocator&)
{
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool operator!=(const PoolAllocator&, const PoolAllocator&)
{
    return true;
}

}
