#include "application.h"

void application::ApplicationManager::CreateApplication( /*insert constructor args*/ )
{
	apps.emplace_back(Application( /* insert constructor args */ ));
}

void application::ApplicationManager::ProgressApplications()
{
	for (Application app : apps) {
		app.Progress();
	}
}
