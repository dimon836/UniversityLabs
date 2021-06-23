//
// Created by Dima Halych on 18.06.2021.
//

#ifndef _JUMPTOKEN_H_
#define _JUMPTOKEN_H_

#include "Token.h"


class JUMPToken : public Token
{
  public:
	JUMPToken();
	unsigned int jumpToIdx;
	std::string toString() override;
};

#endif //_JUMPTOKEN_H_
