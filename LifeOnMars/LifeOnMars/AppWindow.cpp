#include "stdafx.h"
#include "LifeOnMars.h"
#include "tinyfiledialogs.h"
#include "AppWindow.h"
#include <sstream>

namespace
{
const unsigned WINDOW_WIDTH = 800;
const unsigned WINDOW_HEIGHT = 600;
const unsigned MENU_BAR_HEIGHT = 20;
const unsigned WINDOW_STYLE = sf::Style::Titlebar | sf::Style::Close;
const int FRAME_SWITCH_INTERVAL = 1000;
}

CAppWindow::CAppWindow()
    : sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Life on Mars", WINDOW_STYLE)
{
    m_menu = std::make_unique<CAppMenu>("File");
    m_menu->SetFrame(sf::FloatRect(0, 0, float(WINDOW_WIDTH), float(MENU_BAR_HEIGHT)));
    m_openActionId = m_menu->AddAction("Open...", std::bind(&CAppWindow::AskOpenInput, this));
    m_saveActionId = m_menu->AddAction("Save...", std::bind(&CAppWindow::AskSaveOutput, this));

    setFramerateLimit(60);
    setVerticalSyncEnabled(true);
    SetState(State::WaitingInput);

    m_font.loadFromFile("TimesNewRomanRegular.ttf");
}

CAppWindow::~CAppWindow()
{
    m_menu.reset();
}

void CAppWindow::EnterLoop()
{
    while (isOpen())
    {
        sf::Event event;
        while (pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                close();
                return;
            }
            m_menu->OnEvent(event);
        }

        clear(sf::Color::Black);
        if (m_state != State::WaitingInput)
        {
            OnRunningDemo();
        }
        draw(*m_menu);
        display();
    }
}

void CAppWindow::SetState(CAppWindow::State state)
{
    m_state = state;
    m_menu->SetActionEnabled(m_openActionId, state != State::RunningDemo);
    m_menu->SetActionEnabled(m_saveActionId, state == State::WaitingOutput);
}

void CAppWindow::OnRunningDemo()
{
    if (m_state == State::RunningDemo && m_clock.getElapsedTime().asMilliseconds() >= FRAME_SWITCH_INTERVAL)
    {
        if (!SwitchNextFrame())
        {
            SetState(State::WaitingOutput);
        }
    }

	clear(sf::Color::White);

	for (size_t i = 0; i < m_graph->m_components.size(); i++)
	{	
		for (size_t j = 0; j < m_graph->m_components[i].size(); j++)
		{
			auto textShift = -10;
			auto currentColor = xoy.GetColor(i);
			xoy.circle.setFillColor(sf::Color(currentColor[0], currentColor[1], currentColor[2]));
			xoy.circle.setPosition(xoy.ConvertCoor(m_graph->m_verticies[m_graph->m_components[i][j]].x, m_graph->m_verticies[m_graph->m_components[i][j]].y));
			xoy.text.setString(std::to_string(m_graph->m_components[i][j]));
			xoy.text.setPosition(xoy.circle.getPosition().x + textShift, xoy.circle.getPosition().y + textShift);
			xoy.text.setColor(sf::Color(currentColor[0], currentColor[1], currentColor[2]));
			draw(xoy.circle);
			draw(xoy.text);
		}
	}

	for (size_t i = 0; i < m_graph->m_edges.size(); i++)
	{
		if (!m_graph->m_edges[i].isSetted)
		{
			continue;
		}
		size_t component = (m_graph->m_components[m_graph->m_edges[i].first].empty()) ? m_graph->m_edges[i].second : m_graph->m_edges[i].first;
		auto currentColor = xoy.GetColor(component);
		xoy.rectangle.setFillColor(sf::Color(currentColor[0], currentColor[1], currentColor[2]));
		auto firstVert = m_graph->m_verticies[m_graph->m_edges[i].first];
		auto secondVert = m_graph->m_verticies[m_graph->m_edges[i].second];
		sf::Vector2f lengths = { static_cast<float>(secondVert.x - firstVert.x), static_cast<float>(secondVert.y - firstVert.y) };
		xoy.rectangle.setSize({ hypotf(lengths.x, lengths.y) * xoy.UNIT, 2.f });
		xoy.rectangle.setRotation(atan(lengths.y / lengths.x) * 180 / 3.14159265);
		xoy.rectangle.setPosition(xoy.ConvertCoor(firstVert.x, firstVert.y));
		draw(xoy.rectangle);
	}

	xoy.ResetColor();
	/*sf::Text atext;
	atext.setFont(m_font);
	atext.setCharacterSize(20);
	atext.setStyle(sf::Text::Bold);
	atext.setColor(sf::Color::Black);
	atext.setPosition(100, 100);

	atext.setString(std::to_string(m_graph->m_count));
	draw(atext);
	atext.setString(std::to_string(m_graph->m_limit));
	atext.setPosition(200, 200);
	draw(atext);*/

    /*sf::Sprite sprite;

    const sf::Vector2f spriteSize = { float(sprite.getTextureRect().width), float(sprite.getTextureRect().height)};
    const sf::Vector2f windowSize = { float(getSize().x), float(getSize().y) };
    const float scale = std::min(windowSize.x / spriteSize.x, windowSize.y / spriteSize.y);
    sprite.setOrigin(spriteSize * 0.5f);
    sprite.setPosition(windowSize * 0.5f);
    sprite.setScale(scale, scale);

    draw(sprite);*/
}

void CAppWindow::RunAlgorithmDemo()
{
    /*m_pendingFramePaths.clear();
    m_graph->RunPrima();*/
    SetState(State::RunningDemo);
    //SwitchNextFrame();
}

bool CAppWindow::SwitchNextFrame()
{
    m_clock.restart();
    if (!m_graph->NextStep())
    {
        return false;
    }

    return true;
}

void CAppWindow::AskOpenInput()
{
    const char *filters[] = { "*.txt" };
    char const *result = tinyfd_openFileDialog("Select input file", "", 1, filters, "", false);
    // Пользователь отменил выбор файла.
    if (result == nullptr)
    {
        return;
    }
    m_graph = std::make_unique<CGraph>();

    std::ifstream in(result);
    if (!in.is_open())
    {
        tinyfd_messageBox("Error", "I/O error when reading input file", "ok", "error", 1);
    }
    else
    {
		m_graph->InitFromText(in);
		xoy.Reset(m_graph->m_minMaxX, m_graph->m_minMaxY, m_graph->m_count);
        RunAlgorithmDemo();
    }
}

void CAppWindow::AskSaveOutput()
{
    const char *filters[] = { "*.txt" };
    char const *result = tinyfd_saveFileDialog("Select output file", "", 1, filters, "");
    // Пользователь отменил выбор файла.
    if (result == nullptr)
    {
        return;
    }
    std::ofstream out(result);
    if (!out.is_open())
    {
        tinyfd_messageBox("Error", "I/O error when writing output file", "ok", "error", 1);
    }
    else
    {
		out << std::fixed << std::setprecision(2) << m_graph->GetResult() << std::endl;
        tinyfd_messageBox("Success", "File saved OK", "ok", "info", 1);
    }
}

XOY::XOY()
{
	UNIT = 0.f;
	WINDOW_START = { 0.f, 0.f };
	SOURCE_START = { 0.f, 0.f };
	m_font.loadFromFile("TimesNewRomanRegular.ttf");
	text.setFont(m_font);
	text.setCharacterSize(20);
	text.setColor(sf::Color::Black);

	circle.setRadius(RADIUS);
}

std::vector<int> XOY::GetColor(int number)
{
	int power = number / 3;
	for (size_t i = 0; i < currentColor.size(); i++)
	{
		currentColor[i] += power * COLOR_UNIT;
	}
	for (size_t i = 0; i < number % 3; i++)
	{
		currentColor[i] += COLOR_UNIT;
	}
	
	return currentColor;
}

sf::Vector2f XOY::ConvertCoor(int x, int y)
{
	return WINDOW_START + (sf::Vector2f(x, y) - SOURCE_START) * UNIT;
}

void XOY::ResetColor()
{
	currentColor = { 0, 0, 0 };
}

void XOY::Reset(const std::pair<int, int> & minMaxX, const std::pair<int, int> & minMaxY, int elementsCount)
{
	const sf::Vector2f SOURCE_SIZE = { static_cast<float>(minMaxX.second - minMaxX.first), static_cast<float>(minMaxY.second - minMaxY.first) };
	const sf::Vector2f WORK_SIZE = { WINDOW_WIDTH - BOUND * 2, WINDOW_HEIGHT - BOUND * 2 };
	const sf::Vector2f UNIT_X_Y = { WORK_SIZE.x / SOURCE_SIZE.x, WORK_SIZE.y / SOURCE_SIZE.y };
	UNIT = (UNIT_X_Y.x < UNIT_X_Y.y) ? UNIT_X_Y.x : UNIT_X_Y.y;
	const sf::Vector2f LENGTH = { WORK_SIZE.x / UNIT_X_Y.x * UNIT, WORK_SIZE.y / UNIT_X_Y.y * UNIT };
	WINDOW_START = { BOUND + (WORK_SIZE.x - LENGTH.x) / 2, BOUND + (WORK_SIZE.y - LENGTH.y) / 2 };
	SOURCE_START = { static_cast<float>(minMaxX.first), static_cast<float>(minMaxY.first) };
	
	std::cout << std::fixed << std::setprecision(2);
	/*std::cout << "UNIT " << std::fixed << std::setprecision(2) << UNIT << std::endl;
	std::cout << "UNIT_X_Y " << UNIT_X_Y.x << " " << UNIT_X_Y.y << std::endl;
	std::cout << "LENGTH " << LENGTH.x << " " << LENGTH.y << std::endl;
	std::cout << "WINDOW_START " << WINDOW_START.x << " " << WINDOW_START.y << std::endl;
	std::cout << "SOURCE_START " << SOURCE_START.x << " " << SOURCE_START.y << std::endl;
	std::cout << "COLOR_UNIT " << std::endl;*/

	COLOR_UNIT = static_cast<int> (256.f / (ceil(pow(static_cast<float>(elementsCount), 1.f / 3.f))));
	
	ResetColor();
}