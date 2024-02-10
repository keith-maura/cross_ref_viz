#include "Chapter.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

// Constructor
Chapter::Chapter(int ch_bible, std::string bk_name, int bk_num, int ch_in_bk) {
	chapter_bible = ch_bible;
	book_name = bk_name;
	book_number = bk_num;
	chapter_in_book = ch_in_bk;
}

// Default destructor
Chapter::~Chapter() {
}
