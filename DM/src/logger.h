//
// Created by Dima Halych on 18.06.2021.
//

#ifndef _LOGGER_H_
#define _LOGGER_H_

std::ostream& log( const std::string& prefix = "" );

//class NulStreambuf : public std::streambuf
//{
//	char                dummyBuffer[ 64 ];
//  protected:
//	virtual int         overflow( int c )
//	{
//		setp( dummyBuffer, dummyBuffer + sizeof( dummyBuffer ) );
//		return (c == traits_type::eof()) ? '\0' : c;
//	}
//};
//class NulOStream : private NulStreambuf, public std::ostream
//{
//  public:
//	NulOStream() : std::ostream( this ) {}
//	const NulStreambuf* rdbuf() const { return this; }
//};

#endif //_LOGGER_H_
