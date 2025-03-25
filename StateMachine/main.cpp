#include <iostream>
#include <vector>
#include <windows.h>

#pragma comment(lib, "user32")
#define GetKeyDown(X) ((GetAsyncKeyState(X) & 0x8001) == 0x8001)

// Definición de inputs y estados
enum class EInput { A, B };
enum class EState { DUCKING, STANDING, JUMPING, DIVING };

// Estructura para definir transiciones
struct Transition 
{
  EState from;
  EState to;
  EInput input;
};

// Máquina de estados
class StateMachine 
{
public:
  StateMachine(EState initialState) : currentState(initialState) {}

  void addTransition(EState from, EState to, EInput input) 
  {
    transitions.push_back({ from, to, input });
  }

  void update(EInput input) 
  {
    for (const auto& t : transitions) 
    {
      if (t.from == currentState && t.input == input) 
      {
        currentState = t.to;
        return;
      }
    }
  }

  void print() 
  {
    const char* states[] = { "DUCKING", "STANDING", "JUMPING", "DIVING" };
    std::cout << "Current State: " << states[static_cast<int>(currentState)] << std::endl;
  }

private:
  EState currentState;
  std::vector<Transition> transitions;
};

// Main
int main() 
{
  StateMachine player(EState::STANDING);

  // Definir transiciones
  player.addTransition(EState::STANDING, EState::DUCKING, EInput::A);
  player.addTransition(EState::DUCKING, EState::STANDING, EInput::A);
  player.addTransition(EState::STANDING, EState::JUMPING, EInput::B);
  player.addTransition(EState::JUMPING, EState::DIVING, EInput::A);

  player.print();

  while (true)
  {
    if (GetKeyDown('A'))
    {
      player.print();
      player.update(EInput::A);
      player.print();
    }
    if (GetKeyDown('B'))
    {
      player.print();
      player.update(EInput::B);
      player.print();
    }
  }

  return 0;
}
