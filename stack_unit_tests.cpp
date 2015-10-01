#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "stack.h"

typedef int test_type; // change this to test other types

TEST_CASE("init, delete, new list empty (no pointer)", "[init][is_empty][constructor][destructor]")
{
	stack<test_type> s(5);
	REQUIRE(s.is_empty());
}

TEST_CASE("init, delete, new list empty (using pointer)", "[init][is_empty][constructor][destructor]")
{
	stack<test_type>* sp = new stack<test_type>(10);
	REQUIRE(sp->is_empty());
	delete sp;
}

TEST_CASE("push onto empty stack", "[push]")
{
	// init
	stack<test_type> s(5);
	
	REQUIRE_NOTHROW(s.push(1));
	REQUIRE_FALSE(s.is_empty());
}

TEST_CASE("push onto non-empty stack", "[push]")
{
	// init
	stack<test_type> s(5);
	s.push(1);
	
	REQUIRE_NOTHROW(s.push(2));
	REQUIRE_FALSE(s.is_empty());
	
	REQUIRE_NOTHROW(s.push(3));
	REQUIRE_FALSE(s.is_empty());
}

TEST_CASE("push onto full stack", "[push]")
{
	// init
	stack<test_type> s(3);
	s.push(1);
	s.push(2);
	s.push(3);
	
	REQUIRE_THROWS(s.push(4));
}

TEST_CASE("pop from existing, non-full stack", "[pop]")
{
	// init
	stack<test_type> s(5);
	s.push(1);
	s.push(2);
	s.push(3);
	
	REQUIRE(s.pop() == 3);
	REQUIRE(s.pop() == 2);
	REQUIRE(s.pop() == 1);
}

TEST_CASE("pop from existing full stack", "[pop]")
{
	// init
	stack<test_type> s(3);
	s.push(1);
	s.push(2);
	s.push(3);
	
	REQUIRE(s.pop() == 3);
	REQUIRE(s.pop() == 2);
	REQUIRE(s.pop() == 1);
}

TEST_CASE("pop from empty stack", "[pop]")
{
	// init
	stack<test_type> s(3);
	
	REQUIRE_THROWS(s.pop());
}

TEST_CASE("pop from empty stack after popping other elements", "[pop]")
{
	// init
	stack<test_type> s(3);
	s.push(1);
	s.push(2);
	s.push(3);
	s.pop();
	s.pop();
	s.pop();
	
	REQUIRE_THROWS(s.pop());
}

TEST_CASE("new stack is empty", "[is_empty]")
{
	// init
	stack<test_type> s(3);
	
	REQUIRE(s.is_empty());
}

TEST_CASE("existing stack is not empty", "[is_empty]")
{
	// init
	stack<test_type> s(3);
	s.push(1);
	s.push(2);
	
	REQUIRE_FALSE(s.is_empty());
}

TEST_CASE("full stack is not empty", "[is_empty]")
{
	// init
	stack<test_type> s(3);
	s.push(1);
	s.push(2);
	s.push(3);
	
	REQUIRE_FALSE(s.is_empty());
}

TEST_CASE("existing stack popped entirely is empty", "[is_empty]")
{
	// init
	stack<test_type> s(3);
	s.push(1);
	s.push(2);
	s.pop();
	s.pop();
	
	REQUIRE(s.is_empty());
}
