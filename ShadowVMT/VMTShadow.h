#pragma once
#include <map>
#include <utility>

class VMTShadowFucker
{
private:
	// Pointer to Target Object
	void*					  m_ptr_object;
	// Pointer to Object Virtual Method Table
	uintptr_t*				  m_ptr_object_vtable;
	// Pointer to Object Fake Virtual Method Table
	uintptr_t*				  m_ptr_object_fake_vtable;
	// Size of Object Virtual Method Table
	size_t					  m_object_vtable_size;
	// Map Containing the index hooked and the original function
	std::map<int, uintptr_t*> m_object_hooks;

public:
	/// <summary>
	/// Initialize the class for hooking the VMT using the VMT Shadow Hooking technique
	/// </summary>
	/// <param name="object">The Object Target</param>
	VMTShadowFucker  ( void* object );

	/// <summary>
	/// Apply The Hook on function of VMT
	/// </summary>
	/// <param name="index">The function index in VMT</param>
	/// <param name="hook_function">The address of hook function</param>
	/// <returns>Returns the original function pointer</returns>
	uintptr_t* Apply ( int index, uintptr_t* hook_function );

	/// <summary>
	/// Remove the hook from the hooked function
	/// </summary>
	/// <param name="index">The function index in VMT</param>
	void Remove		 ( int index );
};