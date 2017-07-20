#include "stdafx_test.h"
#include "catch.hpp"
#include "StateMachine.h"
#include "State.h"
#include "FooState.h"
#include "BarState.h"
#include "BazState.h"
#include "FooStackState.h"


std::shared_ptr<FooState> update(StateMachine<FooState>& machine) {
	machine.update(0.1f);
	return machine.getState();
}


std::shared_ptr<FooStackState> update(StateStackMachine<FooStackState>& machine) {
	machine.update(0.1f);
	return machine.getCurrentState();
}

TEST_CASE("State Machine", "[state][state machine]") {
	StateMachine<FooState> fooMachine;
	std::shared_ptr<FooState> state;
	SECTION("Adding and checking states"){
		REQUIRE(fooMachine.addState(1, std::make_shared<FooState>()));
		REQUIRE(fooMachine.addState(2, std::make_shared<BarState>()));

		SECTION("Add state") {
			// Cannot add state with already used id
			REQUIRE_FALSE(fooMachine.addState(1, std::make_shared<BarState>()));
			// Can add state of same type, with new id
			REQUIRE(fooMachine.addState(3, std::make_shared<FooState>()));
		}

		SECTION("Force and get state") {
			// No state returns nullptr
			REQUIRE_THROWS(fooMachine.forceState(7));
			fooMachine.forceState(1);
			REQUIRE(fooMachine.getState()->getValue() == 1);
			fooMachine.forceState(2);
			REQUIRE(fooMachine.getState()->getValue() == 10);
			update(fooMachine);
			REQUIRE(fooMachine.getState()->getValue() == 9);
			// Force move to same state does nothing
			fooMachine.forceState(2);
			REQUIRE(fooMachine.getState()->getValue() == 9);
		}
	}
	SECTION("Transitions") {
		std::shared_ptr<FooState> foo(new FooState());
		std::shared_ptr<BarState> bar(new BarState());
		fooMachine.addState(1, foo);
		fooMachine.addState(2, bar);
		SECTION("State transitions") {
			state = update(fooMachine);
			REQUIRE(state->getValue() == 2);
			REQUIRE_FALSE(foo->shouldTransition());
			state = update(fooMachine);
			state = update(fooMachine);
			SECTION("Check transition occurs") {
				state = update(fooMachine);
				// Transition to Bar state
				CHECK(state->getValue() == 10);
				REQUIRE(std::dynamic_pointer_cast<BarState>(state));
				// Check exit was called
				REQUIRE(foo->getValue() == 0);
				state = update(fooMachine);
				REQUIRE(state->getValue() == 9);
				REQUIRE_FALSE(bar->shouldTransition());
				state = update(fooMachine);
				state = update(fooMachine);
				// Transition back to Foo state
				CHECK(state->getValue() == 1);
				REQUIRE(std::dynamic_pointer_cast<FooState>(state));
			}
		}
	}
}

TEST_CASE("Stack State Machine", "[state][state machine][stack]") {
	StateStackMachine<FooStackState> fooMachine;
	std::shared_ptr<FooStackState> state;
	std::shared_ptr<FooStackState> foo(new FooStackState());
	std::shared_ptr<BarStackState> bar(new BarStackState());
	SECTION("Adding and checking states") {
		REQUIRE(fooMachine.addState(1, foo));
		REQUIRE(fooMachine.addState(2, bar));
		SECTION("Add state") {
			// Cannot add state with already used id
			REQUIRE_FALSE(fooMachine.addState(1, std::make_shared<BarStackState>()));
			// Can add state of same type, with new id
			REQUIRE(fooMachine.addState(3, std::make_shared<FooStackState>()));
		}
		SECTION("Force and get state") {
			REQUIRE_THROWS(fooMachine.forceState(7));
			fooMachine.forceState(1);
			REQUIRE(fooMachine.getCurrentState()->getValue() == 1);
			REQUIRE(std::dynamic_pointer_cast<FooStackState>(fooMachine.getCurrentState()));
			fooMachine.forceState(2);
			REQUIRE(fooMachine.getCurrentState()->getValue() == 100);
			REQUIRE(std::dynamic_pointer_cast<BarStackState>(fooMachine.getCurrentState()));
		}
		SECTION("Force push and pop") {
			update(fooMachine);
			// Popping bottom does nothing
			fooMachine.forcePopState();
			REQUIRE(std::dynamic_pointer_cast<FooStackState>(fooMachine.getCurrentState()));
			CHECK(fooMachine.getCurrentState()->getValue() == 12);
			// Pushing same state does nothing
			fooMachine.forcePushState(1);
			REQUIRE(std::dynamic_pointer_cast<FooStackState>(fooMachine.getCurrentState()));
			fooMachine.forcePushState(2);
			REQUIRE(std::dynamic_pointer_cast<BarStackState>(fooMachine.getCurrentState()));
			state = update(fooMachine);
			// Lower states lose focus
			REQUIRE(fooMachine.getState(fooMachine.getStateStack()->peek(1))->getValue() == 13);
			// Popping gets lower state and gives back focus to it
			fooMachine.forcePopState();
			REQUIRE(std::dynamic_pointer_cast<FooStackState>(fooMachine.getCurrentState()));
			state = update(fooMachine);
			REQUIRE(state->getValue() == 24);
			REQUIRE(fooMachine.getStateStack()->size() == 1);
			// Pushing lower state onto stack does nothing
			fooMachine.forcePushState(2);
			fooMachine.forcePushState(1);
			REQUIRE(fooMachine.getCurrentState()->getValue() == 100);
		}
	}
}