#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "linked_list.cpp"

/*
 * Note about CATCH: for each SECTION, the TEST_CASE is executed from the
 * beginning. The function calls within each SECTION do not affect anything in
 * a different SECTION. When moving to another SECTION, the initial part of the
 * TEST_CASE is re-run. The purpose of this is to start with the same scenario
 * for each section, without having to copy-and-paste the code.
 *
 * Make sure "catch.hpp" and "linked_list.h" is included in the same directory
 * as this file.
 *
 * If you come up with more (or better) unit tests, please send them to me so
 * that I can share with everyone and we all benefit.
 *
 * Compile:
 * $ g++ -o unit_tests unit_tests.cpp
 *
 * Run all tests:
 * $ ./unit_tests
 *
 * Run only the tests for the item_at() method:
 * $ ./unit_tests [item_at]
 *
 * Run only the tests for the size() method:
 * $ ./unit_tests [size]
 *
 * Run only the tests for the insert() method:
 * $ ./unit_tests [insert]
 *
 * Run only the tests for the remove() method:
 * $ ./unit_tests [remove]
 */

typedef int test_type; // change this to test other types

TEST_CASE("item_at method", "[item_at]")
{
	linked_list<test_type> l;

	SECTION("when list is empty")
	{
		REQUIRE_THROWS(l.item_at(0));
		REQUIRE_THROWS(l.item_at(5));
		REQUIRE_THROWS(l.item_at(-1));
	}

	SECTION("existing list")
	{
		l.insert(0, 1);
		l.insert(1, 2);
		l.insert(2, 3);
		l.insert(3, 4);

		REQUIRE(l.item_at(0) == 1);
		REQUIRE(l.item_at(1) == 2);
		REQUIRE(l.item_at(2) == 3);
		REQUIRE(l.item_at(3) == 4);

		REQUIRE_THROWS(l.item_at(4));
		REQUIRE_THROWS(l.item_at(-1));
	}
}

TEST_CASE("size method", "[size]")
{
	linked_list<test_type> l;

	SECTION("when list is empty")
	{
		REQUIRE(l.size() == 0);
	}

	SECTION("existing list")
	{
		l.insert(0, 10);
		REQUIRE(l.size() == 1);

		l.insert(1, 20);
		REQUIRE(l.size() == 2);

		l.insert(2, 30);
		REQUIRE(l.size() == 3);
	}
}

TEST_CASE("insertion into empty list", "[insert]")
{
	linked_list<test_type> l;

	SECTION("at position 0")
	{
		l.insert(0, 8);

		REQUIRE(l.item_at(0) == 8);
		REQUIRE(l.size() == 1);
	}

	SECTION("at invalid position > 0")
	{
		REQUIRE_THROWS(l.insert(1, 8));
	}

	SECTION("at invalid position < 0")
	{
		REQUIRE_THROWS(l.insert(-1, 8));
	}
}

TEST_CASE("insertion into existing list", "[insert]")
{
	linked_list<test_type> l;
	l.insert(0, 8);
	l.insert(1, 9);
	l.insert(2, 10);
	l.insert(3, 11);
	l.insert(4, 12);

	SECTION("insertions at end of list")
	{
		REQUIRE(l.size() == 5);
		REQUIRE(l.item_at(0) == 8);
		REQUIRE(l.item_at(1) == 9);
		REQUIRE(l.item_at(2) == 10);
		REQUIRE(l.item_at(3) == 11);
		REQUIRE(l.item_at(4) == 12);
	}

	SECTION("insertions into middle of list")
	{
		l.insert(3, 3);
		REQUIRE(l.size() == 6);
		REQUIRE(l.item_at(0) == 8);
		REQUIRE(l.item_at(1) == 9);
		REQUIRE(l.item_at(2) == 10);
		REQUIRE(l.item_at(3) == 3);
		REQUIRE(l.item_at(4) == 11);
		REQUIRE(l.item_at(5) == 12);
	}

	SECTION("insertions at beginning of list")
	{
		l.insert(0, 0);
		REQUIRE(l.size() == 6);
		REQUIRE(l.item_at(0) == 0);
		REQUIRE(l.item_at(1) == 8);
		REQUIRE(l.item_at(2) == 9);
		REQUIRE(l.item_at(3) == 10);
		REQUIRE(l.item_at(4) == 11);
		REQUIRE(l.item_at(5) == 12);
	}

	SECTION("at invalid position > size")
	{
		REQUIRE_THROWS(l.insert(6, 5));
	}

	SECTION("at invalid position < 0")
	{
		REQUIRE_THROWS(l.insert(-1, 8));
	}
}

TEST_CASE("removal from existing list", "[remove]")
{
	linked_list<test_type> l;
	l.insert(0, 8);
	l.insert(1, 9);
	l.insert(2, 10);
	l.insert(3, 11);
	l.insert(4, 12);

	SECTION("removal from end of list")
	{
		REQUIRE(l.remove(4) == 12);
		REQUIRE(l.size() == 4);
		REQUIRE(l.item_at(0) == 8);
		REQUIRE(l.item_at(1) == 9);
		REQUIRE(l.item_at(2) == 10);
		REQUIRE(l.item_at(3) == 11);
	}

	SECTION("removal from middle of list")
	{
		REQUIRE(l.remove(2) == 10);
		REQUIRE(l.size() == 4);
		REQUIRE(l.item_at(0) == 8);
		REQUIRE(l.item_at(1) == 9);
		REQUIRE(l.item_at(2) == 11);
		REQUIRE(l.item_at(3) == 12);
	}

	SECTION("removal from beginning of list")
	{
		REQUIRE(l.remove(0) == 8);
		REQUIRE(l.size() == 4);
		REQUIRE(l.item_at(0) == 9);
		REQUIRE(l.item_at(1) == 10);
		REQUIRE(l.item_at(2) == 11);
		REQUIRE(l.item_at(3) == 12);
	}

	SECTION("at invalid position > (size - 1)")
	{
		REQUIRE_THROWS(l.remove(5));
	}

	SECTION("at invalid position < 0")
	{
		REQUIRE_THROWS(l.remove(-1));
	}
}
