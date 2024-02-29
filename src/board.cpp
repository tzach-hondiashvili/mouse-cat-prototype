#include "board.h"
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std::chrono_literals;

Board::Board()
{
	m_board = {};
	m_max_cheese_amount = 0;
	m_mouse = {};
	m_level = 1;
	m_cat_count = 0;
}
void Board::print_board() const
{
	for (const auto& content : m_board)
	{
		std::cout << content << std::endl;
	}
	std::cout << "\n******SCOREBOARD******\n";
	std::cout << "Level: " << m_level << "\n";
	std::cout << "Lives: " << m_mouse.getLives() << "\n";
	std::cout << "Keys: " << m_mouse.getKeys() << "\n";
	std::cout << "Score: " << m_mouse.getScore() << "\n";
}
//*************************************************************
void Board::run_game(std::string fileName)
{
	std::ifstream file(fileName);
	bool is_cat_touched = false;
	int starting_level_cats = 0,
		changed_cats = 0;;
	
	if (file.is_open())
	{
		while (!file.eof())
		{
			update_Map(file);
			findCheeses(); //find jesus
			m_mouse.reset_cheese_amount();
			m_mouse.get_starting_location(m_board);
			count_cats();
			create_cats();
			for (int i = 0; i < m_cat_count; i++)
			{
				m_cat[i].get_starting_location(m_board, i);
			}
			//count how many cats in level
			starting_level_cats = m_cat_count;
			
			while (m_mouse.get_cheese_amount() < m_max_cheese_amount)//לא השגנו את כל הגבינות
			{
				if (m_mouse.getLives() == 0)
				{
					Screen::resetLocation();
					std::system("cls");
					std::cout << "YOU LOST!\n";
					exit(EXIT_SUCCESS);
				}
				print_board();
				changed_cats = m_cat_count;
				m_mouse.moveMouse(m_board, m_cat, changed_cats, is_cat_touched);
				m_cat_count = changed_cats;
				if (is_cat_touched)
				{
					is_cat_touched = false;
					Screen::resetLocation();
					continue;
				}
				Screen::resetLocation();

				for (int i = 0; i < m_cat_count;i++)
				{
					print_board();
					Screen::resetLocation();

					std::this_thread::sleep_for(50ms);
					m_cat[i].moveCat(m_board,m_mouse.get_current_location().row, m_mouse.get_current_location().col, m_cat, m_cat_count, m_mouse);

					print_board();	
					Screen::resetLocation();
					
				}
			}	
			delete_cats();
			m_mouse.update_score(starting_level_cats); //increase score by 25 and cats
			starting_level_cats = 0; //reset cats
			m_level++;
			std::system("cls");
		}
		std::cout << "YOU WON WITH: " << m_mouse.getScore()<< " POINTS!\n";
	}
	else
	{
		std::cerr << "error opening map file loser\n";
		exit(EXIT_FAILURE);
	}	
}
//*************************************************************
void Board::findCheeses()
{
	m_max_cheese_amount = 0;
	for (size_t row = 0; row < m_board.size(); ++row)//iterate vector
	{
		for (size_t col = 0; col < m_board[row].size(); ++col)//iterate string
		{
			if (m_board[row][col] == '*')//cheese
			{
				m_max_cheese_amount++;
			}
		}
	}
}
void Board::update_Map(std::ifstream &file)
{
	std::string line;

	m_board.clear();//erase old map

	while (std::getline(file, line) && !line.empty()) //read untill map ends
	{
		m_board.push_back(line);
	}
}
void Board::count_cats()
{
	m_cat_count = 0;
	for (size_t row = 0; row < m_board.size(); ++row)//iterate vector
	{
		for (size_t col = 0; col < m_board[row].size(); ++col)//iterate string
		{
			if (m_board[row][col] == '^')//cheese
			{
				m_cat_count++;
			}
		}
	}
}
void Board::create_cats()
{
	m_cat = new(std::nothrow) Cat[m_cat_count];
	if (!m_cat)
	{
		// Handle allocation failure
		std::cerr << "Failed to allocate memory for cats.\n";
		exit(EXIT_FAILURE);
	}
}
void Board::delete_cats()
{
		delete [] m_cat;	
}
