#pragma once
#include <memory>
#include <stack>
#include "state.hpp"

namespace Deus{
	typedef std::unique_ptr<State> StateRef; //typedef gives an alias unlike define that writes out code for you

	class StateMachine {
	public:
		StateMachine();
		~StateMachine();


		void AddState(StateRef newState, bool isReplacing = true);
		void RemoveState();
		void ProcessStateChanges();
		void pause();

		StateRef& GetActiveState();

	private:
		std::stack<StateRef>_states;
		StateRef _newState;

		bool _isRemoving;
		bool _isAdding;
		bool _isReplacing;
	};
}