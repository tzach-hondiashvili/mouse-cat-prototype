#include "cat.h"
#include <cmath>

Cat::Cat()
{
	m_curr_location.row = 0;
	m_curr_location.col = 0;
	m_spawn_point = m_curr_location;
	m_prevCell = ' ';
}
void Cat::get_starting_location(std::vector <std::string> map, int i)
{
	int index = 0;
	for (int row = 0; row < map.size(); ++row)//iterate vector
	{
		for (int col = 0; col < map[row].size(); ++col)//iterate string
		{
			if (map[row][col] == '^')
			{
				if (index == i)
				{
					m_curr_location.col = col;
					m_curr_location.row = row;
					m_spawn_point = m_curr_location;
					return;
				}
				index++;
			}
		}
	}
}
void Cat::moveCat(std::vector <std::string>& map, int y_mouse, int x_mouse,
	              Cat* m_cat, int m_cat_count, Mouse& m_mouse)
{
	int x_distance_from_mouse = 0,
		y_distance_from_mouse = 0;
	
	x_distance_from_mouse = distance(x_mouse, m_curr_location.col);
	y_distance_from_mouse = distance(y_mouse, m_curr_location.row);

	if (x_distance_from_mouse > y_distance_from_mouse)
	{
		
		if (is_mouse_to_the_right(x_mouse,m_curr_location.col))
		{	
			if (!blocked(map,m_curr_location.row, m_curr_location.col+1))//left or right 
			{
				if (m_prevCell != '^' && m_prevCell != '%')
				{
					map[m_curr_location.row][m_curr_location.col] = m_prevCell;
				}
				else
				{
					map[m_curr_location.row][m_curr_location.col] = ' ';
				}
				
				m_curr_location.col++;
				m_prevCell = map[m_curr_location.row][m_curr_location.col];
				if (map[m_curr_location.row][m_curr_location.col] == '%')
				{				
					m_mouse.reset_mouse_location();
					for (int i = 0; i < m_cat_count; i++)
					{
						if (m_prevCell != '%')
						{
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = m_cat[i].m_prevCell;
						}
						else
						{
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = ' ';
						}
						
						m_cat[i].reset_cat_location();
						map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = '^';
					}
					map[m_mouse.get_current_location().row][m_mouse.get_current_location().col] = '%';
				}
				map[m_curr_location.row][m_curr_location.col] = '^';
			}
			else//move y
			{
				if (is_mouse_above(y_mouse, m_curr_location.row) && !blocked(map, m_curr_location.row + 1, m_curr_location.col))
				{
					if (m_prevCell != '^' && m_prevCell != '%')
					{
						map[m_curr_location.row][m_curr_location.col] = m_prevCell;
					}
					else
					{
						map[m_curr_location.row][m_curr_location.col] = ' ';
					}
					m_curr_location.row--;
					m_prevCell = map[m_curr_location.row][m_curr_location.col];
					if (map[m_curr_location.row][m_curr_location.col] == '%')
					{
						
						m_mouse.reset_mouse_location();
						for (int i = 0; i < m_cat_count; i++)
						{
							if (m_prevCell != '%')
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = m_cat[i].m_prevCell;
							}
							else
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = ' ';
							}

							m_cat[i].reset_cat_location();
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = '^';
						}
						map[m_mouse.get_current_location().row][m_mouse.get_current_location().col] = '%';
					}
					map[m_curr_location.row][m_curr_location.col] = '^';
				}
				else if(!blocked(map, m_curr_location.row+1, m_curr_location.col))
				{
					if (m_prevCell != '^' && m_prevCell != '%')
					{
						map[m_curr_location.row][m_curr_location.col] = m_prevCell;
					}
					else
					{
						map[m_curr_location.row][m_curr_location.col] = ' ';
					}
					m_curr_location.row++;
					m_prevCell = map[m_curr_location.row][m_curr_location.col];
					if (map[m_curr_location.row][m_curr_location.col] == '%')
					{
						m_mouse.reset_mouse_location();
						for (int i = 0; i < m_cat_count; i++)
						{
							if (m_prevCell != '%')
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = m_cat[i].m_prevCell;
							}
							else
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = ' ';
							}

							m_cat[i].reset_cat_location();
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = '^';
						}
						map[m_mouse.get_current_location().row][m_mouse.get_current_location().col] = '%';
					}
					map[m_curr_location.row][m_curr_location.col] = '^';
				}
			}
		}
		else //left
		{
			if (!blocked(map, m_curr_location.row, m_curr_location.col - 1))
			{
				if (m_prevCell != '^' && m_prevCell != '%')
				{
					map[m_curr_location.row][m_curr_location.col] = m_prevCell;
				}
				else
				{
					map[m_curr_location.row][m_curr_location.col] = ' ';
				}
				m_curr_location.col--;
				m_prevCell = map[m_curr_location.row][m_curr_location.col];
				if (map[m_curr_location.row][m_curr_location.col] == '%')
				{
					m_mouse.reset_mouse_location();
					for (int i = 0; i < m_cat_count; i++)
					{
						if (m_prevCell != '%')
						{
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = m_cat[i].m_prevCell;
						}
						else
						{
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = ' ';
						}

						m_cat[i].reset_cat_location();
						map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = '^';
					}
					map[m_mouse.get_current_location().row][m_mouse.get_current_location().col] = '%';
				}
				map[m_curr_location.row][m_curr_location.col] = '^';
			}
			else//move y
			{
				if (is_mouse_above(y_mouse, m_curr_location.row) && !blocked(map, m_curr_location.row - 1, m_curr_location.col))
				{
					if (m_prevCell != '^' && m_prevCell != '%')
					{
						map[m_curr_location.row][m_curr_location.col] = m_prevCell;
					}
					else
					{
						map[m_curr_location.row][m_curr_location.col] = ' ';
					}
					m_curr_location.row--;
					m_prevCell = map[m_curr_location.row][m_curr_location.col];
					if (map[m_curr_location.row][m_curr_location.col] == '%')
					{
						m_mouse.reset_mouse_location();
						for (int i = 0; i < m_cat_count; i++)
						{
							if (m_prevCell != '%')
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = m_cat[i].m_prevCell;
							}
							else
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = ' ';
							}

							m_cat[i].reset_cat_location();
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = '^';
						}
						map[m_mouse.get_current_location().row][m_mouse.get_current_location().col] = '%';
					}
					map[m_curr_location.row][m_curr_location.col] = '^';

				}
				else if(!blocked(map, m_curr_location.row + 1, m_curr_location.col))
				{
					if (m_prevCell != '^' && m_prevCell != '%')
					{
						map[m_curr_location.row][m_curr_location.col] = m_prevCell;
					}
					else
					{
						map[m_curr_location.row][m_curr_location.col] = ' ';
					}
					m_curr_location.row++;
					m_prevCell = map[m_curr_location.row][m_curr_location.col];
					if (map[m_curr_location.row][m_curr_location.col] == '%')
					{
						m_mouse.reset_mouse_location();
						for (int i = 0; i < m_cat_count; i++)
						{
							if (m_prevCell != '%')
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = m_cat[i].m_prevCell;
							}
							else
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = ' ';
							}

							m_cat[i].reset_cat_location();
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = '^';
						}
						map[m_mouse.get_current_location().row][m_mouse.get_current_location().col] = '%';
					}
					map[m_curr_location.row][m_curr_location.col] = '^';
				}
			}
		}
		
		
	}
	else// up or down
	{
		if (is_mouse_above(y_mouse, m_curr_location.row))
		{
			if (!blocked(map, m_curr_location.row-1, m_curr_location.col))//up 
			{
				if (m_prevCell != '^' && m_prevCell != '%')
				{
					map[m_curr_location.row][m_curr_location.col] = m_prevCell;
				}
				else
				{
					map[m_curr_location.row][m_curr_location.col] = ' ';
				}
				m_curr_location.row--;
				m_prevCell = map[m_curr_location.row][m_curr_location.col];
				if (map[m_curr_location.row][m_curr_location.col] == '%')
				{
					m_mouse.reset_mouse_location();
					for (int i = 0; i < m_cat_count; i++)
					{
						if (m_prevCell != '%')
						{
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = m_cat[i].m_prevCell;
						}
						else
						{
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = ' ';
						}

						m_cat[i].reset_cat_location();
						map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = '^';
					}
					map[m_mouse.get_current_location().row][m_mouse.get_current_location().col] = '%';
				}
				map[m_curr_location.row][m_curr_location.col] = '^';
			}
			else//move x
			{
				if (is_mouse_to_the_right(x_mouse, m_curr_location.col) && !blocked(map, m_curr_location.row, m_curr_location.col + 1))
				{
					if (m_prevCell != '^' && m_prevCell != '%')
					{
						map[m_curr_location.row][m_curr_location.col] = m_prevCell;
					}
					else
					{
						map[m_curr_location.row][m_curr_location.col] = ' ';
					}
					m_curr_location.col++;
					m_prevCell = map[m_curr_location.row][m_curr_location.col];
					if (map[m_curr_location.row][m_curr_location.col] == '%')
					{
						m_mouse.reset_mouse_location();
						for (int i = 0; i < m_cat_count; i++)
						{
							if (m_prevCell != '%')
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = m_cat[i].m_prevCell;
							}
							else
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = ' ';
							}

							m_cat[i].reset_cat_location();
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = '^';
						}
						map[m_mouse.get_current_location().row][m_mouse.get_current_location().col] = '%';
					}
					map[m_curr_location.row][m_curr_location.col] = '^';
				}
				else if(!blocked(map, m_curr_location.row, m_curr_location.col - 1))
				{
					if (m_prevCell != '^' && m_prevCell != '%')
					{
						map[m_curr_location.row][m_curr_location.col] = m_prevCell;
					}
					else
					{
						map[m_curr_location.row][m_curr_location.col] = ' ';
					}
					m_curr_location.col--;
					m_prevCell = map[m_curr_location.row][m_curr_location.col];
					if (map[m_curr_location.row][m_curr_location.col] == '%')
					{
						m_mouse.reset_mouse_location();
						for (int i = 0; i < m_cat_count; i++)
						{
							if (m_prevCell != '%')
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = m_cat[i].m_prevCell;
							}
							else
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = ' ';
							}

							m_cat[i].reset_cat_location();
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = '^';
						}
						map[m_mouse.get_current_location().row][m_mouse.get_current_location().col] = '%';
					}
					map[m_curr_location.row][m_curr_location.col] = '^';
				}
			}
		}
		else //down
		{
			if (!blocked(map,m_curr_location.row+1, m_curr_location.col))
			{
				if (m_prevCell != '^' && m_prevCell != '%')
				{
					map[m_curr_location.row][m_curr_location.col] = m_prevCell;
				}
				else
				{
					map[m_curr_location.row][m_curr_location.col] = ' ';
				}
				m_curr_location.row++;
				m_prevCell = map[m_curr_location.row][m_curr_location.col];
				if (map[m_curr_location.row][m_curr_location.col] == '%')
				{
					m_mouse.reset_mouse_location();
					for (int i = 0; i < m_cat_count; i++)
					{
						if (m_prevCell != '%')
						{
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = m_cat[i].m_prevCell;
						}
						else
						{
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = ' ';
						}

						m_cat[i].reset_cat_location();
						map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = '^';
					}
					map[m_mouse.get_current_location().row][m_mouse.get_current_location().col] = '%';
				}
				map[m_curr_location.row][m_curr_location.col] = '^';
			}
			else//move x
			{
				if (is_mouse_to_the_right(x_mouse, m_curr_location.col) && !blocked(map, m_curr_location.row, m_curr_location.col + 1))
				{
					if (m_prevCell != '^' && m_prevCell != '%')
					{
						map[m_curr_location.row][m_curr_location.col] = m_prevCell;
					}
					else
					{
						map[m_curr_location.row][m_curr_location.col] = ' ';
					}
					m_curr_location.col++;
					m_prevCell = map[m_curr_location.row][m_curr_location.col];
					if (map[m_curr_location.row][m_curr_location.col] == '%')
					{
						m_mouse.reset_mouse_location();
						for (int i = 0; i < m_cat_count; i++)
						{
							if (m_prevCell != '%')
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = m_cat[i].m_prevCell;
							}
							else
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = ' ';
							}

							m_cat[i].reset_cat_location();
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = '^';
						}
						map[m_mouse.get_current_location().row][m_mouse.get_current_location().col] = '%';
					}
					map[m_curr_location.row][m_curr_location.col] = '^';
				}
				else if(!blocked(map, m_curr_location.row, m_curr_location.col - 1))
				{
					if (m_prevCell != '^' && m_prevCell != '%')
					{
						map[m_curr_location.row][m_curr_location.col] = m_prevCell;
					}
					else
					{
						map[m_curr_location.row][m_curr_location.col] = ' ';
					}
					m_curr_location.col--;
					m_prevCell = map[m_curr_location.row][m_curr_location.col];
					if (map[m_curr_location.row][m_curr_location.col] == '%')
					{
						m_mouse.reset_mouse_location();
						for (int i = 0; i < m_cat_count; i++)
						{
							if (m_prevCell != '%')
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = m_cat[i].m_prevCell;
							}
							else
							{
								map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = ' ';
							}

							m_cat[i].reset_cat_location();
							map[m_cat[i].m_curr_location.row][m_cat[i].m_curr_location.col] = '^';
						}
						map[m_mouse.get_current_location().row][m_mouse.get_current_location().col] = '%';
					}
					map[m_curr_location.row][m_curr_location.col] = '^';
				}
			}
		}
	}

}
int Cat::distance(int mouse, int cat) const
{
	return abs(mouse - cat);
}
bool Cat::blocked(std::vector <std::string> map, int y, int x) const
{
	return (map[y][x] == '#' || map[y][x] == 'D' || y > map.size() || x < 0 || x > map[y].size() || y < 0);
}
bool Cat::is_mouse_to_the_right(int x_mouse, int x_cat) const
{
	return (x_mouse > x_cat);
}
bool Cat::is_mouse_above(int y_mouse, int y_cat) const
{
	return (y_mouse < y_cat);
} 
void Cat::reset_cat_location() 
{
	m_prevCell = ' ';
	m_curr_location = m_spawn_point;
}
char Cat::get_prev_cell() const
{
	return m_prevCell;
}
int Cat::get_cat_row() const
{
	return m_curr_location.row;
}
int Cat::get_cat_col() const
{
	return m_curr_location.col;
}
