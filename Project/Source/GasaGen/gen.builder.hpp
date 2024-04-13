// This file was generated automatially by gencpp's bootstrap.cpp (See: https://github.com/Ed94/gencpp)

#pragma once

#include "gen.hpp"

GEN_NS_BEGIN

struct Builder
{
	FileInfo File;
	String   Buffer;

	static Builder open( char const* path );

	void pad_lines( s32 num );

	void print( Code );
	void print_fmt( char const* fmt, ... );

	void write();
};

GEN_NS_END
