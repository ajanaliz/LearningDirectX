#include "pch.h"


// include common namespaces for code simplification
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Platform;


// class definition for the core framework of the app
ref class App sealed : public IFrameworkView
{
public:
	virtual void Initialize(CoreApplicationView^ appView)
	{
		// subscribe the OnActivated function to handle the Activated 'event'
		appView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &App::OnActivated);


	}

	virtual void SetWindow(CoreWindow ^Window)
	{

	}

	virtual void Load(String ^EntryPoint)
	{

	}

	virtual void Run()
	{

	}

	virtual void Uninitialize()
	{

	}


	// an event that is called when the application windows is ready to be activated
	void OnActivated(CoreApplicationView ^sender, IActivatedEventArgs ^args) 
	{
		CoreWindow ^Window = CoreWindow::GetForCurrentThread();
		Window->Activate();
	}
};


// the class definition that creates an instance of our core framework class
ref class AppSource sealed : IFrameworkViewSource
{
public:
	virtual IFrameworkView^ CreateView()
	{
		return ref new App();
	}
};

[MTAThreadAttribute] // define main() as a multi-threaded-apartment function

//the starting point of the app
int main(Array<String^>^ args)
{
	CoreApplication::Run(ref new AppSource());
	return 0;
}