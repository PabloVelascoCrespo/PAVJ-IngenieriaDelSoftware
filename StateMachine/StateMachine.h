#pragma once

enum EInput : int
{
  A,
  B
};

enum EState : int
{
  DUCKING,
  STANDING,
  JUMPING,
  DIVING,
  STATES_COUNT // TOTAL NUMBER OF ELEMNTS
};

struct Transitions
{
  Transitions(EState _current, EState _to, EInput _transition);
  EState current;
  EState to;
  EInput transition;
};

struct StateMachine
{
  StateMachine(Transitions _state);
  void print();
  void Update(EInput input);

  Transitions state;
};
