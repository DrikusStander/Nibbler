
#ifndef DRAW_HPP
#define DRAW_HPP

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <sstream>
#include <string>


class Draw : public Fl_Widget 
{
	private:
		Fl_Offscreen _buff;
		int _xmax;
		int _ymax;
	public:
		Draw(int X, int Y, int W, int H);
		Draw(Draw const & src);
		~Draw(void);
		Draw const & operator=(Draw const & rhs);
		void clear();
		void update(int x, int y, int w);
		void draw();
		void updateBorder(int scoreArea, int score);
		void twoPGameover(int score, int opscore, int scoreArea);

};

#endif