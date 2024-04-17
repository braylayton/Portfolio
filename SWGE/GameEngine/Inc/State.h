#pragma once

namespace SWGE {
namespace GameEngine {

template <typename AgentType>
class State
{
public:
	virtual ~State() {}
	virtual void Enter(AgentType& agent) = 0;
	virtual void Update(AgentType& agent, float deltaTime) = 0;
	virtual void Exit(AgentType& agent) = 0;
};

}
}