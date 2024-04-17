#pragma once

#include "State.h"

namespace SWGE {
namespace GameEngine {

template <typename AgentType>
class StateMachine
{
public:
	using StateType = State<AgentType>;

	StateMachine(AgentType& agent);
	~StateMachine();

	template <typename NewStateType>
	void AddState();

	void Purge();

	void Update(float deltaTime);
	void ChangeState(uint32_t index);
private:
	StateType* mCurrentState;
	std::vector<std::unique_ptr<StateType>> mStates;
	AgentType& mAgent;
};

template<typename AgentType>
StateMachine<AgentType>::StateMachine(AgentType& agent)
	: mAgent(agent)
	, mCurrentState(nullptr)
{
}

template<typename AgentType>
StateMachine<AgentType>::~StateMachine()
{
	ASSERT(mStates.empty(), "[StateMachine] Purge must be called before destruction");
}

template<typename AgentType>
template<typename NewStateType>
void StateMachine<AgentType>::AddState()
{
	static_assert(std::is_base_of<StateType, NewStateType>::value, "[StateMachine] can only add state for AgentType");
	mStates.emplace_back(std::make_unique<NewStateType>());
}

template<typename AgentType>
void StateMachine<AgentType>::Purge()
{
	mStates.clear();
}

template<typename AgentType>
void StateMachine<AgentType>::Update(float deltaTime)
{
	ASSERT(mCurrentState != nullptr, "[StateMachine] mCurrentState is null");
	mCurrentState->Update(mAgent, deltaTime);
}

template <typename AgentType>
void StateMachine<AgentType>::ChangeState(uint32_t index)
{
	ASSERT(index < (uint32_t)mStates.size(), "[StateMachine] invalid index %d", index);
	if (mCurrentState)
	{
		mCurrentState->Exit(mAgent);
	}
	mCurrentState = mStates[index].get();
	mCurrentState->Enter(mAgent);
}

}
}