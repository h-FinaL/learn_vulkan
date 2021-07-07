#pragma once

#include <vulkan/vulkan_core.h>

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

	}

	static void* VKAPI_CALL reallocation(
		void* pUserData,
		void* pOriginal,
		size_t                                      size,
		size_t                                      alignment,
		VkSystemAllocationScope                     allocationScope)
	{

	}

	static void VKAPI_CALL free(
		void* pUserData,
		void* pMemory)
	{

	}
};