#pragma once

#include "IETThread.h"
class IconLoader :    public IETThread
{
private:
	typedef std::string String;
public:
	IconLoader(String path);
	~IconLoader();

private:
	void run() override;

	String path;

};

