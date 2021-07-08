#pragma once

#include <vulkan/vulkan_core.h>
#include <malloc.h>

class vk_allocator
{
public:
	vk_allocator() {};
	~vk_allocator() {};

	inline operator VkAllocationCallbacks() const
	{
		VkAllocationCallbacks result;
		result.pUserData = (void*)this;
		result.pfnAllocation = &allocation;
		result.pfnReallocation = &reallocation;
		result.pfnFree = &free;
		result.pfnInternalAllocation = nullptr;
		result.pfnInternalFree = nullptr;
	}

	static void* VKAPI_CALL allocation(
		void* pUserData,
		size_t                                      size,
		size_t                                      alignment,
		VkSystemAllocationScope                     allocationScope)
	{
		static_cast<vk_allocator*>(pUserData)->allocation(size, alignment, allocationScope);
	}

	static void* VKAPI_CALL reallocation(
		void* pUserData,
		void* pOriginal,
		size_t                                      size,
		size_t                                      alignment,
		VkSystemAllocationScope                     allocationScope)
	{
		static_cast<vk_allocator*>(pUserData)->reallocation(pOriginal, size, alignment, allocationScope);
	}

	static void VKAPI_CALL free(
		void* pUserData,
		void* pMemory)
	{
		static_cast<vk_allocator*>(pUserData)->free(pMemory);
	}

private:
	void* allocation(
		size_t                                      size,
		size_t                                      alignment,
		VkSystemAllocationScope                     allocationScop)
	{
		return _aligned_malloc(size, alignment);
	}

	void free(
		void* pMemory)
	{
		return _aligned_free(pMemory);
	}

	void* reallocation(
		void* pOriginal,
		size_t                                      size,
		size_t                                      alignment,
		VkSystemAllocationScope                     allocationScope)
	{
		return _aligned_realloc(pOriginal, size, allocationScope);
	}
};