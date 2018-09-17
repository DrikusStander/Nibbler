#include "Draw.hpp"

Draw::Draw(int X, int Y, int W, int H) : Fl_Widget(0,0,X,Y,0)
{
	this->_xmax = X;
	this->_ymax = Y;
	this->_buff = fl_create_offscreen(X, Y);
	return;
}

Draw::Draw(Draw const & src) : Fl_Widget(0,0, src._xmax, src._ymax, 0)
{
	this->_xmax = src._xmax;
	this->_ymax = src._ymax;
	this->_buff = src._buff;
	return;
}

Draw::~Draw(void)
{
	return;
}

Draw const & Draw::operator=(Draw const & rhs)
{
	this->_xmax = rhs._xmax;
	this->_ymax = rhs._ymax;
	this->_buff = rhs._buff;
	return(*this);
}

void Draw::clear()
{
	fl_begin_offscreen(this->_buff);
	fl_color(FL_BLACK);
	fl_rectf(0, 0, Fl::w(), Fl::h());
	fl_end_offscreen();
}

void Draw::updateBorder(int scoreArea, int score)
{
	
	std::stringstream sstr;
	sstr << score;
	std::string str = "Score: " + sstr.str();
	fl_begin_offscreen(this->_buff);
	fl_color(FL_RED);
	fl_rect(0, 0, this->_xmax, this->_ymax - scoreArea);
	fl_rect(0, this->_ymax - scoreArea, this->_xmax, scoreArea);
	fl_draw(str.c_str(), 8, (this->_ymax - scoreArea) + 15);
	fl_end_offscreen();
}

void Draw::update(int x, int y, int w)
{
	fl_begin_offscreen(this->_buff);
	fl_rectf(x, y, w, w);
	fl_end_offscreen();
}

void Draw::twoPGameover(int score, int opscore, int scoreArea)
{
	Fl_Font font = fl_font();
	Fl_Fontsize size = fl_size();
	this->clear();
	this->updateBorder(scoreArea, score);
	std::stringstream opsstr;
	opsstr << opscore;
	std::string opstr = "Opponent Score: " + opsstr.str();
	fl_begin_offscreen(this->_buff);
	fl_font(font, 72);
	fl_draw("GAME OVER", this->_xmax / 4, (this->_ymax - scoreArea) / 2);
	fl_font(font, size);
	if (opscore != -22)
		fl_draw(opstr.c_str(), (this->_xmax - 130), (this->_ymax - scoreArea) + 15);
	fl_end_offscreen();
}

void Draw::draw()
{
	fl_copy_offscreen(0, 0, Fl::w(), Fl::h(), this->_buff, 0, 0);
}