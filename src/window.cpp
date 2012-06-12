#include <bb/cascades/Application>
#include <bb/cascades/Color>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/Page>
#include <bb/cascades/Slider>
#include <bb/cascades/Stacklayout>
#include <bb/cascades/StackLayoutProperties>

#include "window.hpp"

using namespace bb::cascades;

Window::Window()
{
	Container *appContainer = new Container();

	appContainer->setLayout(new DockLayout());
	appContainer->setBackground(Color::fromARGB(0xff262626));

	Container *contentContainer = new Container();
	contentContainer->setLayout(new StackLayout());
	contentContainer->setLayoutProperties(DockLayoutProperties::create()
	        .horizontal(HorizontalAlignment::Center)
	        .vertical(VerticalAlignment::Center));

	Container *imageContainer = new Container();
	imageContainer->setLayout(new DockLayout());
	imageContainer->setLayoutProperties(StackLayoutProperties::create()
	        .horizontal(HorizontalAlignment::Center));

	Container *sliderContainer = new Container();
	sliderContainer->setLayout(StackLayout::create()
	        .direction(LayoutDirection::LeftToRight)
	        .left(20.0f).right(20.0f));
	sliderContainer->setLayoutProperties(StackLayoutProperties::create()
	        .horizontal(HorizontalAlignment::Center));

	Slider *opacitySlider = Slider::create()
	        .from(0.0f).to(0.5f)
	        .leftMargin(20.0f).rightMargin(20.0f);

	opacitySlider->setLayoutProperties(StackLayoutProperties::create()
	        .horizontal(HorizontalAlignment::Fill)
	        .spaceQuota(1.0f));

	sliderContainer->add(opacitySlider);

	contentContainer->add(imageContainer);
	contentContainer->add(sliderContainer);
	appContainer->add(contentContainer);

	Page *page = new Page();
	page->setContent(appContainer);

	Application::setScene(page);

}
