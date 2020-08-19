#include "VMTShadowFucker.h"
#include <iostream>

class Car
{
public:
	virtual void run ( )
	{
		printf( "Running!\n" );
	}
	virtual void stop ( )
	{
		printf ( "Stopping!\n" );
	}
};

void drift ( )
{
	printf ( "Drifting!\n" );
}


void main ( )
{
	Car car1;

	VMTShadowFucker CarVMTHook ( &car1 );

	CarVMTHook.Apply ( 1, reinterpret_cast< uintptr_t* >( drift ) );

	car1.stop ( );
}