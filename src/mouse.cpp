#include "mouse.h"
#include "cat.h"


Mouse::Mouse()
{
	m_lives = 3;
	m_curr_location.col = 0;
	m_curr_location.row = 0;
	m_cur_cheese_amount = 0;
	m_keys = 0,
	m_score = 0;
	m_spawn_point = m_curr_location;
}
void Mouse::get_starting_location(std::vector<std::string> map)
{
	for (int row = 0; row < map.size(); ++row)//iterate vector
	{
		for (int col = 0; col < map[row].size(); ++col)//iterate string
		{
			if (map[row][col] == '%')
			{
				m_curr_location.col = col;
				m_curr_location.row = row;
				m_spawn_point = m_curr_location;
				return;
			}
		}
	}
}
void Mouse::moveMouse(std::vector <std::string> &map, Cat* &cat, int &cat_amount, bool &check)
{
	const auto c = _getch();
	switch (c)
	{
	case 0:
	case Keys::SPECIAL_KEY:
		handleSpecialKey(map, cat, cat_amount, check);
		break;
	case Keys::SPACE:
		return;
	case Keys::ESCAPE:
		std::system("cls");
		std::cout << "Escape pressed, exiting game..\n";
		exit(EXIT_SUCCESS);
	default: 
		break;
	}
}
void Mouse::handleSpecialKey(std::vector <std::string> &map, Cat*& cat, int &cat_amount, bool &check)
{
	const auto c = _getch();
	switch (c)
	{
	case SpecialKeys::UP:
		moveUp(map, cat, cat_amount, check);
		break;
	case SpecialKeys::DOWN:
		moveDown(map, cat, cat_amount, check);
		break;
	case SpecialKeys::LEFT:
		moveLeft(map, cat, cat_amount, check);
		break;
	case SpecialKeys::RIGHT:
		moveRight(map, cat, cat_amount, check);
		break;
	default:
		std::cout << "Unknown special key pressed (code = " << c << ")\n";
		break;
	}
}
void Mouse::moveUp(std::vector <std::string> &map, Cat *& cat, int &cat_amount, bool &check)
{
	if (m_curr_location.row > 0 && map[m_curr_location.row-1][m_curr_location.col] != '#'
		&& map[m_curr_location.row - 1][m_curr_location.col] != '\0')
	{
		if (map[m_curr_location.row - 1][m_curr_location.col] == 'D')
		{
			if (m_keys > 0)
			{
				m_keys--;
				m_score += 2;
			}
			else
			{
				return;
			}
		}
		m_curr_location.row--;
		if (map[m_curr_location.row][m_curr_location.col] == '*')
		{
			m_cur_cheese_amount++;
			m_score += 10;
		}
		if (map[m_curr_location.row][m_curr_location.col] == 'F')
		{
			m_keys++;
		}
		if (map[m_curr_location.row][m_curr_location.col] == '$' && cat_amount > 0)
		{
			map[cat[cat_amount - 1].get_cat_row()][cat[cat_amount - 1].get_cat_col()] = ' ';
			kill_cat(cat, cat_amount);
			m_score += 5;
		}
		if (map[m_curr_location.row][m_curr_location.col] == '^')
		{
			map[m_curr_location.row][m_curr_location.col] = ' ';
			map[m_curr_location.row + 1][m_curr_location.col] = ' ';
			reset_mouse_location();
			for (int i=0;i<cat_amount;i++)
			{
				if (cat[i].get_prev_cell() != '%')
				{
					map[cat[i].get_cat_row()][cat[i].get_cat_col()] = cat[i].get_prev_cell();
					cat[i].reset_cat_location();
					map[cat[i].get_cat_row()][cat[i].get_cat_col()] = '^';
					check = true;
				}	
			}
			map[m_curr_location.row][m_curr_location.col] = '%';
			return;
		}

		map[m_curr_location.row+1][m_curr_location.col] = ' ';
		
		map[m_curr_location.row][m_curr_location.col] = '%';
	}
}
void Mouse::moveDown(std::vector <std::string> &map, Cat*& cat, int &cat_amount, bool& check)
{
	if (m_curr_location.row < map.size() - 1)
	{
		if (map[m_curr_location.row + 1][m_curr_location.col] != '#'
			&& map[m_curr_location.row + 1][m_curr_location.col] != '\0')
		{
			if (map[m_curr_location.row + 1][m_curr_location.col] == 'D')
			{
				if (m_keys > 0)
				{
					m_keys--;
					m_score += 2;
				}
				else
				{
					return;
				}
			}
			m_curr_location.row++;
			if (map[m_curr_location.row][m_curr_location.col] == '*')
			{
				m_cur_cheese_amount++;
				m_score += 10;
			}
			if (map[m_curr_location.row][m_curr_location.col] == 'F')
			{
				m_keys++;
			}
			if (map[m_curr_location.row][m_curr_location.col] == '$' && cat_amount > 0)
			{
				map[cat[cat_amount - 1].get_cat_row()][cat[cat_amount - 1].get_cat_col()] = ' ';
				kill_cat(cat, cat_amount);
				m_score += 5;
			}
			if (map[m_curr_location.row][m_curr_location.col] == '^')
			{
				map[m_curr_location.row][m_curr_location.col] = ' ';
				map[m_curr_location.row - 1][m_curr_location.col] = ' ';
				reset_mouse_location();
				for (int i = 0; i < cat_amount; i++)
				{
					if (cat[i].get_prev_cell() != '%')
					{
						map[cat[i].get_cat_row()][cat[i].get_cat_col()] = cat[i].get_prev_cell();
						cat[i].reset_cat_location();
						map[cat[i].get_cat_row()][cat[i].get_cat_col()] = '^';
						check = true;
					}
				}
				map[m_curr_location.row][m_curr_location.col] = '%';
				return;
			}
			map[m_curr_location.row - 1][m_curr_location.col] = ' ';
			
			map[m_curr_location.row][m_curr_location.col] = '%';
		}
	}
}
void Mouse::moveLeft(std::vector <std::string> &map, Cat*& cat, int &cat_amount, bool& check)
{
	if (m_curr_location.col > 0)
	{
		if (m_curr_location.row > 0 && map[m_curr_location.row][m_curr_location.col - 1] != '#'
			&& map[m_curr_location.row][m_curr_location.col - 1] != '\0')
		{
			if (map[m_curr_location.row][m_curr_location.col - 1] == 'D')
			{
				if (m_keys > 0)
				{
					m_keys--;
					m_score += 2;
				}
				else
				{
					return;
				}
			}
			m_curr_location.col--;
			if (map[m_curr_location.row][m_curr_location.col] == '*')
			{
				m_cur_cheese_amount++;
				m_score += 10;
			}
			if (map[m_curr_location.row][m_curr_location.col] == 'F')
			{
				m_keys++;
			}
			if (map[m_curr_location.row][m_curr_location.col] == '$' && cat_amount > 0)
			{
				map[cat[cat_amount - 1].get_cat_row()][cat[cat_amount - 1].get_cat_col()] = ' ';
				kill_cat(cat, cat_amount);
				m_score += 5;
			}
			if (map[m_curr_location.row][m_curr_location.col] == '^')
			{
				map[m_curr_location.row][m_curr_location.col] = ' ';
				map[m_curr_location.row][m_curr_location.col+1] = ' ';
				reset_mouse_location();
				for (int i = 0; i < cat_amount; i++)
				{
					if (cat[i].get_prev_cell() != '%')
					{
						map[cat[i].get_cat_row()][cat[i].get_cat_col()] = cat[i].get_prev_cell();
						cat[i].reset_cat_location();
						map[cat[i].get_cat_row()][cat[i].get_cat_col()] = '^';
						check = true;
					}
				}
				map[m_curr_location.row][m_curr_location.col] = '%';
				return;
			}
			map[m_curr_location.row][m_curr_location.col + 1] = ' ';
			
			map[m_curr_location.row][m_curr_location.col] = '%';
		}
	}
}
void Mouse::moveRight(std::vector <std::string> &map, Cat*& cat, int &cat_amount, bool& check)
{
	if (m_curr_location.col < map[m_curr_location.row].size())
	{
		if (m_curr_location.row > 0 && map[m_curr_location.row][m_curr_location.col + 1] != '#'
			&& map[m_curr_location.row][m_curr_location.col + 1] != '\0')
		{
			if (map[m_curr_location.row][m_curr_location.col + 1] == 'D')
			{
				if (m_keys > 0)
				{
					m_keys--;
					m_score += 2;
				}
				else
				{
					return;
				}
			}
			m_curr_location.col++;
			if (map[m_curr_location.row][m_curr_location.col] == '*')
			{
				m_cur_cheese_amount++;
				m_score += 10;
			}
			if (map[m_curr_location.row][m_curr_location.col] == 'F')
			{
				m_keys++;
			}
			if (map[m_curr_location.row][m_curr_location.col] == '$' && cat_amount > 0)
			{
				map[cat[cat_amount - 1].get_cat_row()][cat[cat_amount - 1].get_cat_col()] = ' ';
				kill_cat(cat, cat_amount);
				m_score += 5;
			}
			if (map[m_curr_location.row][m_curr_location.col] == '^')
			{
				map[m_curr_location.row][m_curr_location.col] = ' ';
				map[m_curr_location.row][m_curr_location.col-1] = ' ';
				reset_mouse_location();
				for (int i = 0; i < cat_amount; i++)
				{
					if (cat[i].get_prev_cell() != '%')
					{
						map[cat[i].get_cat_row()][cat[i].get_cat_col()] = cat[i].get_prev_cell();
						cat[i].reset_cat_location();
						map[cat[i].get_cat_row()][cat[i].get_cat_col()] = '^';
						check = true;
					}
				}
				map[m_curr_location.row][m_curr_location.col] = '%';
				return;
			}
			map[m_curr_location.row][m_curr_location.col - 1] = ' ';
			
			map[m_curr_location.row][m_curr_location.col] = '%';
		}
	}
}
void Mouse::reset_cheese_amount()
{
	m_cur_cheese_amount = 0;
}
int Mouse::get_cheese_amount() const
{
	return m_cur_cheese_amount;
}
void Mouse::update_score(int starting_cats)
{
	m_score += 25;
	m_score = starting_cats * 5 + m_score;
} 
int Mouse::getLives() const
{
	return m_lives;
}
int Mouse::getScore() const
{
	return m_score;
}
int Mouse::getKeys() const
{
	return m_keys;
}
Location Mouse::get_current_location() const
{
	return m_curr_location;
}
void Mouse::reset_mouse_location() 
{
	m_lives--;
	m_curr_location = m_spawn_point;
}
void Mouse::kill_cat(Cat *&cat,int &cat_amount) 
{
	cat_amount--;
	Cat* temp = new(std::nothrow) Cat [cat_amount];
	if (temp == NULL)
	{
		std::cerr << "memory alocation failed\n";
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < cat_amount; i++)
	{
		temp[i] = cat[i];
	}
	delete[] cat;
	cat = nullptr;
	cat = temp;
}