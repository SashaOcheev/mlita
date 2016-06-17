#pragma once
#include "stdafx.h"
#include "AppMenu.h"

class CGraph;

struct XOY
{
	float UNIT;
	sf::Vector2f WINDOW_START;
	sf::Vector2f SOURCE_START;
	float COLOR_UNIT;
	sf::CircleShape circle;
	sf::Text text;
	sf::RectangleShape rectangle;

	XOY();
	std::vector<int> GetColor(int number);
	void Reset(const std::pair<int, int> & minMaxX, const std::pair<int, int> & minMaxY, int elementsCount);
	sf::Vector2f ConvertCoor(int x, int y);
	void ResetColor();
	const float RADIUS = 10.0;
	const float THICKNESS = 2.0;
private:
	sf::Font m_font;
	std::vector<int> currentColor;
	const float BOUND = 50.f;
	const int TEXT_SIZE = 20;
};

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
	XOY xoy;
    sf::Clock m_clock;
    sf::Font m_font;
    std::unique_ptr<CGraph> m_graph;
    std::unique_ptr<CAppMenu> m_menu;
    size_t m_openActionId = 0;
    size_t m_saveActionId = 0;
};
