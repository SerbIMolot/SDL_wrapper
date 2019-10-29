#include "pch.h"
#include "../stdafx.h"

State* temp = nullptr;



TEST( StateMachineTest, addState ) {
 
	temp = new TestState( );



	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}