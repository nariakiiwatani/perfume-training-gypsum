/*!
*/

#pragma once

#include "ofTypes.h"
class Factor;
class FactorTask;


class Generator
{
public:
	Generator();
	~Generator();

	void setFactorGenFunc(Factor* func(string id, string type));
	void setTaskGenFunc(FactorTask* func(string id, string type));

	void generateFromXML(string file_name);
	void generateFromBVH(string file_name);

private:
	Factor*(*factor_func_)(string, string);
	FactorTask*(*task_func_)(string, string);
};

/* EOF */