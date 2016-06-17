#pragma once
#include "stdafx.h"
#include "AppMenu.h"

class CGraph;

class CAppWindow : public sf::RenderWindow
{
public:
    CAppWindow();
    ~CAppWindow();

    void EnterLoop();

private:
    enum class State
    {
        WaitingInput,
        RunningDemo,
        WaitingOutput,
    };

    void SetState(State state);
    void OnRunningDemo();
    void RunAlgorithmDemo();
    bool SwitchNextFrame();
    void AskOpenInput();
    void AskSaveOutput();

    State m_state = State::WaitingInput;
    sf::Clock m_clock;
    sf::Font m_font;
    std::unique_ptr<CGraph> m_graph;
    std::unique_ptr<CAppMenu> m_menu;
    size_t m_openActionId = 0;
    size_t m_saveActionId = 0;
};
