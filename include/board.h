#pragma once
#include <fstream>
#include "mouse.h"
#include "cat.h"

class Board {

public:
	Board();
	void run_game(std::string fileName);
	void print_board() const;
	void update_Map(std::ifstream &file);
	void count_cats();
	void create_cats();
	void delete_cats();

private:
	std::vector<std::string> m_board;

	Mouse m_mouse;

	Cat *m_cat;

	int m_max_cheese_amount,
		m_level,
		m_cat_count;
	
	void findCheeses();
};