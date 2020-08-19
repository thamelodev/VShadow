#include "vmt_shadow_fucker.h"


// Initializes the VMTShadowFucker
VMTShadowFucker::VMTShadowFucker ( void* object )
{
	// Initialize essential class members
	this->m_ptr_object = object;
	this->m_ptr_object_vtable = *reinterpret_cast< uintptr_t** >( object );
	this->m_object_vtable_size = 0;
	
	// Calculates the VMT Size
	while ( reinterpret_cast< uintptr_t* >( this->m_ptr_object_vtable [ this->m_object_vtable_size ] ) )
		this->m_object_vtable_size++;

	// Creates the Fake VMT
	this->m_ptr_object_fake_vtable = new uintptr_t [ this->m_object_vtable_size ];

	// Fill the Fake Virtual Method Table with the Function Pointers from Original
	for ( size_t i = 0; i <= this->m_object_vtable_size; ++i )
		this->m_ptr_object_fake_vtable [ i ] = this->m_ptr_object_vtable [ i ];

	// Swap VTable Pointer
	*reinterpret_cast< uintptr_t** >( object ) = this->m_ptr_object_fake_vtable;
}

uintptr_t* VMTShadowFucker::Apply ( int index, uintptr_t* hook_function )
{
	// Get the Pointer to Original Func
	uintptr_t* p_original_func = *reinterpret_cast< uintptr_t** >( this->m_ptr_object_fake_vtable + index );

	// Swap pointer to Original Function to Hook Function Pointer
	*reinterpret_cast< uintptr_t** >( this->m_ptr_object_fake_vtable + index ) = hook_function;

	// Insert the hook function to the list
	this->m_object_hooks [ index ] = p_original_func;
	
	return p_original_func;
}

void VMTShadowFucker::Remove ( int index )
{
	// Swap the pointer from hook function to original function using the hook list
	*reinterpret_cast< uintptr_t** >( this->m_ptr_object_fake_vtable + index ) = this->m_object_hooks [ index ];

	// Removes the hook function from hook list
	this->m_object_hooks.erase ( index );
}
