#pragma once

enum class EInput : int
{
  A,
  B
};

enum class EState : int
{
  DUCKING,
  STANDING,
  JUMPING,
  DIVING
};

struct Transitions
{
  Transitions(EState _from, EState _to, EInput _transition);
  EState from;
  EState to;
  EInput transition;
};



struct StateMachine
{
  StateMachine(Transitions _state);

  Transitions state;
  EState Update(EInput input);
};

//
//
//#include <windows.h>
//#pragma comment(lib, "user32")
//#define GetKey(X) (!!(GetAsyncKeyState(0[#X)&0x8000))
//