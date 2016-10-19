#pragma once

class BaseApplication;
class RendererSelector;

class Sample
{
public:
	Sample();
	virtual ~Sample();

	int run();

	virtual bool initialiseSample() = 0;
	virtual void cleanupSample() = 0;
protected:
	virtual bool initialise();
	virtual void cleanup();

	void outputExceptionMessage(const char *message) const;
	BaseApplication *d_sampleApp;
};