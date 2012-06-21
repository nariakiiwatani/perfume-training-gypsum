/*!
*/

#include "Generator.h"
#include "Factor.h"
#include "FactorTask.h"
#include "FactorManager.h"
#include "ofLog.h"
#include "ofxXmlSettings.h"


namespace {
}
Generator::Generator():
factor_func_(NULL)
,task_func_(NULL)
{
}

Generator::~Generator()
{
}

void Generator::setFactorGenFunc(Factor* func(string id, string type))
{
	factor_func_ = func;
}

void Generator::setTaskGenFunc(FactorTask* func(string id, string type))
{
	task_func_ = func;
}

void Generator::generateFromXML(string file_name)
{
	ofxXmlSettings xml(file_name);

	map<FactorTask*, string> parent_ids;

	if(xml.tagExists("Tasks")) {
		xml.pushTag("Tasks");
		for(int i = 0, max = xml.getNumTags("Task"); i < max; ++i) {
			FactorTask* task;
			if(task_func_) {
				task = task_func_(xml.getAttribute("Task", "id", "", i), xml.getAttribute("Task", "class", "", i));
			}
			if(!task) {
				task = new FactorTask(xml.getAttribute("Task", "id", "", i));
			}
			xml.pushTag("Task", i);
			if(xml.tagExists("Parent")) {
				parent_ids.insert(pair<FactorTask*, string>(task, xml.getValue("Parent", "")));
			}
			for(int j = 0; j < xml.getNumTags("Param"); ++j) {
				task->setParam(xml.getAttribute("Param", "id", "", j), xml.getValue("Param", "", j), xml.getAttribute("Param", "func", "", j));
			}
			/*
			for(int j = 0; j < xml.getNumTags("Animation"); ++j) {
				FactorTaskAnimation* animation = FactorManager::getCurrent()->getAnimation(xml.getAttribute("Animation", "id", "", j));
				xml.pushTag("Animation", j);
				vector<vector<string>> assigns;
				for(int k = 0; k < xml.getNumTags("Assign"); ++k) {
					xml.pushTag("Assign", k);
					vector<string> assign;
					assign.push_back(xml.getValue("SequenceID", ""));
					assign.push_back(xml.getValue("Target", ""));
					assign.push_back(xml.getValue("Func", ""));
					assigns.push_back(assign);
					xml.popTag();
				}
				task->addAnimation(	animation,
									xml.getValue("Start", 0),
									xml.getValue("Length", 0),
									xml.getValue("Times", 0),
									assigns);
				xml.popTag();
			}
			*/
			xml.popTag();
		}
		xml.popTag();
	}

	for(map<FactorTask*, string>::iterator it = parent_ids.begin(); it != parent_ids.end(); ++it) {
		(*it).first->setParent(FactorManager::getCurrent()->getTask((*it).second));
	}
	
	if(xml.tagExists("Factors")) {
		xml.pushTag("Factors");
		for(int i = 0, max = xml.getNumTags("Factor"); i < max; ++i) {
			Factor* factor;
			if(factor_func_) {
				factor = factor_func_(xml.getAttribute("Factor", "id", "", i), xml.getAttribute("Factor", "class", "", i));
			}
			if(!factor) {
				factor = new Factor(xml.getAttribute("Factor", "id", "", i));
			}
			xml.pushTag("Factor", i);
			for(int j = 0, jmax = xml.getNumTags("Bind"); j < jmax; ++j) {
				factor->bindTask(xml.getAttribute("Bind", "type", "", j), FactorManager::getCurrent()->getTask(xml.getValue("Bind", "", j)));
			}
			xml.popTag();
		}
		xml.popTag();
	}


	if(xml.tagExists("Animations")) {
		xml.pushTag("Animations");
		for(int i = 0, max = xml.getNumTags("Animation"); i < max; ++i) {
			FactorTaskAnimation* animation = new FactorTaskAnimation();
			animation->setLength(xml.getAttribute("Animation", "length", 0, i));
			int times = xml.getAttribute("Animation", "times", 0, i);
			xml.pushTag("Animation", i);
			for(int j = 0; j < xml.getNumTags("Sequence"); ++j) {
				FactorTaskAnimation::ValueType value_type;
				string bind = xml.getAttribute("Sequence", "bind", "", j);
				string target = xml.getAttribute("Sequence", "target", "", j);
				animation->beginSequence(bind+target, xml.getAttribute("Sequence", "type", "", j));
				xml.pushTag("Sequence", j);
				for(int k = 0; k < xml.getNumTags("Key"); ++k) {
					animation->addKey(xml, k);
				}
				xml.popTag();
				animation->endSequence();
				FactorManager::getCurrent()->getTask(bind)->addAnimation(
									animation, bind+target, target, times);
			}
			xml.popTag();
		}
		xml.popTag();
	}
}

/* EOF */