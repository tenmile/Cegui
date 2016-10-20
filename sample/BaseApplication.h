#pragma once

#include <stdlib.h>
#include <limits.h>

class Sample;

class BaseApplication
{
public:
	BaseApplication(): d_quitting(false) {}
	virtual ~BaseApplication() {}

	virtual bool excute(Sample *smapleApp) = 0;
	virtual void cleanup() = 0;

	virtual void setQuitting(bool quit=true) {d_quitting = quit;}
	virtual bool isQuitting() const {return d_quitting;}

protected:
	virtual void initialiseResourceGroupDirectories();
	virtual void initialiseDefaultResourceGroups();

	const char* getDataPathPrefix() const;
	static const char DATAPATH_VAR_NAME[];
	bool d_quitting;
};