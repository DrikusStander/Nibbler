#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>
#include <iostream>
#include <exception>

class SDL_error : public std::exception
{
	private:
		std::string _error;
	public:
		SDL_error( std::string error);
		SDL_error(SDL_error const & src);
		~SDL_error( void ) throw();
		SDL_error const & operator=(SDL_error const & rhs);
		const char* what() const throw();
};

#endif