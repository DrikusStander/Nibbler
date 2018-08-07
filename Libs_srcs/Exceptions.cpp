#include "Exceptions.hpp"

SDL_error::SDL_error( std::string error) : _error(error)
{
	return;
}

SDL_error::SDL_error(SDL_error const & src)
{
	this->_error = src._error;
	return;
}

SDL_error::~SDL_error( void ) throw()
{
	return;
}

SDL_error const & SDL_error::operator=(SDL_error const & rhs)
{
	this->_error = rhs._error;
	return(*this);
}

const char* SDL_error::what() const throw()
{
	return(this->_error.c_str());
}