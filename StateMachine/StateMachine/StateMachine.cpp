#include "StateMachine.h"

EState StateMachine::Update(EInput input)
{
  if(state.transition == input)
  {
    return state.to;
  }
  return state.from;
}

Transitions::Transitions(EState _from, EState _to, EInput _transition)
{
  from = _from;
  to = _to;
  transition = _transition;
}
