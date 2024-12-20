// This file was generated automatially by gencpp's unreal.cpp (See: https://github.com/Ed94/gencpp)

#ifdef __clang__
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wunused-const-variable"
#	pragma clang diagnostic ignored "-Wunused-but-set-variable"
#	pragma clang diagnostic ignored "-Wswitch"
#	pragma clang diagnostic ignored "-Wunused-variable"
#   pragma clang diagnostic ignored "-Wunknown-pragmas"
#	pragma clang diagnostic ignored "-Wvarargs"
#	pragma clang diagnostic ignored "-Wunused-function"
#endif

#ifdef __GNUC__
#	pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wunknown-pragmas"
#	pragma GCC diagnostic ignored "-Wcomment"
#	pragma GCC diagnostic ignored "-Wswitch"
#	pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#include "gen.builder.hpp"

GEN_NS_BEGIN

Builder Builder::open( char const* path )
{
	Builder result;

	FileError error = file_open_mode( & result.File, EFileMode_WRITE, path );
	if ( error != EFileError_NONE )
	{
		log_failure( "gen::File::open - Could not open file: %s", path);
		return result;
	}

	result.Buffer = String::make_reserve( GlobalAllocator, Builder_StrBufferReserve );

	// log_fmt("$Builder - Opened file: %s\n", result.File.filename );
	return result;
}

void Builder::pad_lines( s32 num )
{
	Buffer.append( "\n" );
}

void Builder::print( Code code )
{
	String   str = code->to_string();
	// const ssize len = str.length();
	// log_fmt( "%s - print: %.*s\n", File.filename, len > 80 ? 80 : len, str.Data );
	Buffer.append( str );
}

void Builder::print_fmt( char const* fmt, ... )
{
	ssize   res;
	char buf[ GEN_PRINTF_MAXLEN ] = { 0 };

	va_list va;
	va_start( va, fmt );
	res = str_fmt_va( buf, count_of( buf ) - 1, fmt, va ) - 1;
	va_end( va );

	// log_fmt( "$%s - print_fmt: %.*s\n", File.filename, res > 80 ? 80 : res, buf );
	Buffer.append( buf, res );
}

void Builder::write()
{
	b32 result = file_write( & File, Buffer, Buffer.length() );

	if ( result == false )
		log_failure("gen::File::write - Failed to write to file: %s\n", file_name( & File ) );

	log_fmt( "Generated: %s\n", File.filename );
	file_close( & File );
	Buffer.free();
}

GEN_NS_END

#ifdef __clang__
#	pragma clang diagnostic pop
#endif

#ifdef __GNUC__
#	pragma GCC diagnostic pop
#endif
