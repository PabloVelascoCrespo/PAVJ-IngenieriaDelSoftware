#include <iostream>
#include "StateMachine.h"

Transitions ducking(EState::DUCKING, EState::STANDING, EInput::A);
Transitions standingA(EState::STANDING, EState::DUCKING, EInput::A);
Transitions standingB(EState::STANDING, EState::JUMPING, EInput::B);
Transitions jumping(EState::JUMPING, EState::DIVING, EInput::A);

int main()
{
  StateMachine stateMachine();
}
