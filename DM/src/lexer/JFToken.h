//
// Created by Dima Halych on 18.06.2021.
//

#ifndef _JFTOKEN_H_
#define _JFTOKEN_H_

#include "Token.h"


class JFToken : public Token
{
  public:
	JFToken();
	unsigned int jumpToIdx;
	std::string toString() override;
};

#endif //_JFTOKEN_H_
