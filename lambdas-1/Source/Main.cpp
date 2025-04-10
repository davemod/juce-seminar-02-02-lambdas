/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

using namespace juce;

/**
 	Lambdas are lightweight, inline function objects. They are used to create anonymous functions that can be called later in scope or passed
	as arguments to other functions. Each one is type-specific and has a unique, compiler-generated type.

	Some key points about lambdas:
	[] capture list - specifies which variables from the surrounding scope are captured by the lambda.
	() parameter list - specifies the parameters that the lambda takes.
	{} body - specifies the body of the lambda, which contains the code to be executed.

	Some examples:
	
	[]() { } // empty capture list, empty parameter list, empty body
	[]() { return 1; } // empty capture list, empty parameter list, body returns 1
	[&]() { return a + b; } // capture all variables by reference
	[=]() { return a + b; } // capture all variables by value
	[]() { } // empty capture list, empty parameter list, empty body
	[]() { return 1; } // empty capture list, empty parameter list, body returns 1
	[&]() { return a + b; } // capture all variables by reference
	[=]() { return a + b; } // capture all variables by value


	std::function is a type-erased polymorphic wrapper for callable objects. std::function can wrap a lambda.

	It introduces overhead because it uses dynamic memory allocation if the callable
	object does not fit in its small object optimization (SOO) buffer.

 */
/** override new operator to see when heap memory is being allocated */
void* operator new(std::size_t size) {
    std::cout << "Allocating " << size << " bytes on the heap\n";
    return malloc(size);
}


//==============================================================================
int main (int argc, char* argv[])
{
	std::cout << "BEGIN ===========================================\n";

    int a, b, c, d, e, f, g, h, i, j;
    a = b = c = d = e = f = g = h = i = j = 1;
	
    // TODO: allocate heap memory to test the implementation above by just creating an int on the heap
    std::cout << "Int \n";
    
    // TODO: add some variables to the capture list and see if heap mem is allocated
	std::cout << "Lambda 1\n";
    auto lambda = [a](){
    };
    
    // TODO: again add some variables to the capture list and see if heap mem is allocated
	std::cout << "Lambda 2\n";
	std::function<void()> lambda2 = [a](){
    };

	std::cout << "END ===========================================\n";

    return 0;
}
