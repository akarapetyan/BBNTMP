/**
 * @file window.cpp
 * @brief Contains the implementation of UI widget class used as a GUI in the Video Player application
 */

#include <bb/cascades/Application>
#include <bb/cascades/Color>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/ImageView>
#include <bb/cascades/Page>
#include <bb/cascades/Stacklayout>
#include <bb/cascades/StackLayoutProperties>

#include "window.hpp"


Window::Window()
{
	isPlaying = true;
	Container *appContainer = new Container();

	appContainer->setLayout(new DockLayout());
	appContainer->setBackground(Color::fromARGB(0xff262626));

	Container *contentContainer = new Container();
	contentContainer->setLayout(new StackLayout());
	contentContainer->setLayoutProperties(DockLayoutProperties::create()
	        .horizontal(HorizontalAlignment::Center)
	        .vertical(VerticalAlignment::Bottom));

	//TODO maybe we don't need this  container, it's for the future
	Container *imageContainer = new Container();
	imageContainer->setLayout(new DockLayout());
	imageContainer->setLayoutProperties(StackLayoutProperties::create()
	        .horizontal(HorizontalAlignment::Center));

	Container *sliderContainer = new Container();
	sliderContainer->setLayout(StackLayout::create()
	        .direction(LayoutDirection::LeftToRight));
	        //.left(20.0f).right(20.0f));
	sliderContainer->setLayoutProperties(StackLayoutProperties::create()
	        .horizontal(HorizontalAlignment::Center)
	        .vertical(VerticalAlignment::Center));

	opacitySlider = Slider::create()
	        .from(0.0f).to(0.5f)
	        .leftMargin(20.0f).rightMargin(20.0f);

	opacitySlider->setLayoutProperties(StackLayoutProperties::create()
	        .horizontal(HorizontalAlignment::Fill)
	        .spaceQuota(1.0f));

	/*ImageView* previous = ImageView::create("asset:///images/previous.png");
	previous->setLayoutProperties(StackLayoutProperties::create().vertical(VerticalAlignment::Center));*/

	previousButton = new Button();
	previousButton->setImage(Image(QUrl("asset:///images/previous")));
	previousButton->setPreferredWidth(0);
	previousButton->setPreferredHeight(0);
	previousButton->setLeftMargin(0);
	previousButton->setRightMargin(0);
	connect(previousButton, SIGNAL(clicked()), this, SLOT(playPrevious()));


	/*ImageView* stop = ImageView::create("asset:///images/stop.png");
	stop->setLayoutProperties(StackLayoutProperties::create().vertical(VerticalAlignment::Center));*/

	stopButton = new Button();
	stopButton->setImage(Image(QUrl("asset:///images/stop")));
	stopButton->setPreferredWidth(0);
	stopButton->setLeftMargin(0);
	stopButton->setRightMargin(0);
	connect(stopButton, SIGNAL(clicked()), this, SLOT(setImage()));

	/*ImageView* next = ImageView::create("asset:///images/next.png");
	next->setLayoutProperties(StackLayoutProperties::create().vertical(VerticalAlignment::Center));*/

	nextButton = new Button();
	nextButton->setImage(Image(QUrl("asset:///images/next")));
	nextButton->setPreferredWidth(0);
	nextButton->setLeftMargin(0);
	nextButton->setRightMargin(0);
	connect(nextButton, SIGNAL(clicked()), this, SLOT(playNext()));

	sliderContainer->add(previousButton);
	sliderContainer->add(stopButton);
	sliderContainer->add(nextButton);

	sliderContainer->add(opacitySlider);

	contentContainer->add(imageContainer);

	contentContainer->add(sliderContainer);
	appContainer->add(contentContainer);

	Page *page = new Page();
	page->setContent(appContainer);

	Application::setScene(page);
}

void Window::setImage()
{
	Image image = isPlaying ? Image(QUrl("asset:///images/play")) : Image(QUrl("asset:///images/stop"));
	stopButton->setImage(image);
	isPlaying = !isPlaying;
}
