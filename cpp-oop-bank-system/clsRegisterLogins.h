#pragma once
#include "clsUser.h"
#include "clsDate.h"

class clsRegisterLogins
{
	clsUser CurrentUser;
	clsDate CurrentDate;

public:
	clsRegisterLogins(clsUser User, clsDate Date) :
		CurrentUser(User),
		CurrentDate(Date)
	{
	}

};

