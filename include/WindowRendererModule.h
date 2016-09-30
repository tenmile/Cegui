#include "Base.h"
#include <vector>

namespace CEGUI
{

class CEGUIEXPORT WindowRendererModule
{
public:
	virtual ~WindowRendererModule();
	void registerFactory(const String &type_name);
	uint registerAllFactories();
	void unregisterFactory(const String &type);
	uint unregisterAllFactories();
protected:
	typedef std::vector<WRFactoryRegisterer*> FactoryRegisterer;
	FactoryRegisterer d_registery;
};

}