#include "String.h"

namespace CEGUI
{

class CEGUIEXPORT WRFactoryRegisterer
{
public:
	~WRFactoryRegisterer();

	void registerFactory();
	const CEGUI::utf8 *d_type;
protected:
	WRFactoryRegisterer(const CEGUI::utf8 *type);

	virtual void doFactoryAdd() = 0;
};

}