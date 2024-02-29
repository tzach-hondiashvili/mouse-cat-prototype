#pragma once
#include<iostream>
#include <vector>
#include <string>
#include "Location.h"
#include "mouse.h"
#include "io.h"
#include <conio.h>
#include <cstdlib> // for std::system()

class Cat
{
public:
	Cat();
	void get_starting_location(std::vector <std::string> map, int i);
	void moveCat(std::vector <std::string> &map, int x_mouse, int y_mouse, Cat *m_cat,int m_cat_count,Mouse &m_mouse);
	int distance(int mouse, int cat) const;
	bool blocked(std::vector <std::string> map, int x, int y) const;
	bool is_mouse_to_the_right(int x_mouse, int x_cat) const;
	bool is_mouse_above(int y_mouse, int y_cat) const;
	void reset_cat_location();
	char get_prev_cell() const;
	int get_cat_row() const;
	int get_cat_col() const;

private:
	char m_prevCell;

	Location m_curr_location;
	Location m_spawn_point;
};