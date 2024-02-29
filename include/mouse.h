#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Location.h"
#include "io.h"
#include <conio.h>
#include <cstdlib> // for std::system()
class Cat;

class Mouse
{
public:
	Mouse(); //constructor

	void get_starting_location(std::vector<std::string> map);
	Location get_current_location() const;
	void moveMouse(std::vector <std::string> &map, Cat* &cat, int &cat_amount, bool &check);
	void handleSpecialKey(std::vector <std::string> &map, Cat* &cat, int &cat_amount, bool &check);
	void moveUp(std::vector <std::string> &map, Cat* &cat, int &cat_amount, bool& check);
	void moveDown(std::vector <std::string> &map, Cat* &cat, int &cat_amount, bool& check);
	void moveLeft(std::vector <std::string> &map, Cat* &cat, int &cat_amount, bool& check);
	void moveRight(std::vector <std::string> &map, Cat* &cat, int &cat_amount, bool &check);
	void reset_cheese_amount();
	int get_cheese_amount() const;
	void update_score(int starting_cats);
	int getLives() const;
	int getScore() const;
	int getKeys() const;
	void reset_mouse_location();
	void kill_cat(Cat *&cat, int& cat_amount);

private:
	int m_lives,
	    m_cur_cheese_amount,
		m_keys,
		m_score;

	Location m_curr_location;
	Location m_spawn_point;
};