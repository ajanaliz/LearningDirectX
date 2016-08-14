#include "pch.h"


// include common name spaces for code simplification
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
		Window->PointerPressed += ref new TypedEventHandler<CoreWindow ^, PointerEventArgs ^>(this, &App::PointerPressed);
		Window->PointerWheelChanged += ref new TypedEventHandler<CoreWindow ^,PointerEventArgs ^>(this, &App::OnPointerWheelChanged);
		Window->KeyDown += ref new TypedEventHandler<CoreWindow ^, KeyEventArgs ^>(this, &App::OnKeyDown);
	}

	virtual void Load(String ^EntryPoint)
	{

	}

	virtual void Run()
	{
		// obtain a pointer to the window
		CoreWindow^ Window = CoreWindow::GetForCurrentThread();

		// run ProcessEvents() to dispatch events
		Window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
		
	}

	virtual void Uninitialize()
	{

	}


	// an event that is called when the application windows is ready to be activated
	void OnActivated(CoreApplicationView ^sender, IActivatedEventArgs ^args) 
	{
		// obtain a pointer to the window
		CoreWindow ^Window = CoreWindow::GetForCurrentThread();
		
		// activate the window
		Window->Activate();
	}

	// input event handlers
	void PointerPressed(CoreWindow ^Window, PointerEventArgs ^Args)
	{
		MessageDialog Dialog("", "");
		Dialog.Content = "X: " + Args->CurrentPoint->Position.X.ToString() + " Y: " + Args->CurrentPoint->Position.Y.ToString();
		Dialog.Title = "Notice!";
		Dialog.ShowAsync();

	}

	void OnPointerWheelChanged(CoreWindow ^Window, PointerEventArgs ^Args)
	{
		int wheel = Args->CurrentPoint->Properties->MouseWheelDelta;

		MessageDialog Dialog("", " Mouse Wheel Event");
		Dialog.Content = wheel.ToString();
		Dialog.ShowAsync();
	}

	void OnKeyDown(CoreWindow ^Window, KeyEventArgs ^Args)
	{
		MessageDialog Dialog("", "");
		if (Args->VirtualKey == VirtualKey::W)
		{
			Dialog.Content = "Move Forward";
			Dialog.Title = "W Pressed";
			Dialog.ShowAsync();
		}else if (Args->VirtualKey == VirtualKey::A)
		{
			Dialog.Content = "Strafe Left";
			Dialog.Title = "A Pressed";
			Dialog.ShowAsync();
		}
		else if (Args->VirtualKey == VirtualKey::S)
		{
			Dialog.Content = "Move Back";
			Dialog.Title = "S Pressed";
			Dialog.ShowAsync();
		}
		else if (Args->VirtualKey == VirtualKey::D)
		{
			Dialog.Content = "Strafe Right";
			Dialog.Title = "D Pressed";
			Dialog.ShowAsync();
		}
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