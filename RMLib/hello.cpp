#include "std.hpp"
#include "hello.hpp"

void RMHello::InnerHello()
{
	LOGF << "Hello World!!";
}

void RMHello::Hello()
{
	LOGW << "And I say...";
	InnerHello();
}
