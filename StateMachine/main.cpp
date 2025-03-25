#include <iostream>
#include "StateMachine.h"
#include <windows.h>

#pragma comment(lib, "user32")
#define GetKeyDown(X) ((GetAsyncKeyState(X) & 0x8001) == 0x8001)


Transitions ducking(EState::DUCKING, EState::STANDING, EInput::A);
Transitions standingA(EState::STANDING, EState::DUCKING, EInput::A);
Transitions standingB(EState::STANDING, EState::JUMPING, EInput::B);
Transitions jumping(EState::JUMPING, EState::DIVING, EInput::A);

int main()
{
  StateMachine playerstates(ducking);
  while (true)
  {
    if (GetKeyDown('A'))
    {
      playerstates.print();
      playerstates.Update(EInput::A);
      playerstates.print();
    }
    if (GetKeyDown('B'))
    {
      playerstates.print();
      playerstates.Update(EInput::B);
      playerstates.print();
    }
  }

}
