#include "StateMachine.h"
#include <stdio.h>
#include <iostream>

StateMachine::StateMachine(Transitions _state):
  state(_state)
{
  
}

void StateMachine::print()
{
  const char* StatesNames[] = { "DUCKING", "STANDING", "JUMPING", "DIVING" };

  printf("current state: %s\n", StatesNames[state.current]);
}

void StateMachine::Update(EInput input)
{
  if(state.transition == input)
  {
    state.current = state.to;
  }
}

Transitions::Transitions(EState _from, EState _to, EInput _transition)
{
  current = _from;
  to = _to;
  transition = _transition;
}
