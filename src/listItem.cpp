#include "listItem.h"

#include <bb/cascades/DockLayout>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/StackLayout>
#include <bb/cascades/StackLayoutProperties>
#include <bb/cascades/SystemDefaults>

listItem::listItem(Container *parent)
			    	:CustomControl(parent)
{
	/*itemImage = ImageView::create().image(Image(QUrl(QString("asset:///") + imageName)));
	itemImage->setPreferredSize(120.0f, 100.0f);//.layoutProperties(StackLayoutProperties::create().vertical(VerticalAlignment::Top));
	itemLabel = Label::create(labelName);
	itemLabel->textStyle()->setBase(SystemDefaults::TextStyles::titleText());*/

	// Dock layout with margins inside.
	Container *itemContainer = new Container();
	DockLayout *itemLayout = new DockLayout();
	itemContainer->setLayout(itemLayout);
	itemContainer->setPreferredWidth(768.0f);

	// A background Container that will hold the item content Container.
	Container *backgroundContainer = new Container();
	DockLayout *backgroundLayout = new DockLayout();
	backgroundContainer->setLayout(backgroundLayout);
	backgroundContainer->setLayoutProperties(
			DockLayoutProperties::create().horizontal(HorizontalAlignment::Center));

	// Content Container, Image + text with padding to get alignment on background image.
	Container *contentContainer = new Container();
	StackLayout *contentLayout = new StackLayout();
	contentLayout->setLayoutDirection(LayoutDirection::LeftToRight);
	contentContainer->setLayout(contentLayout);

	itemImage =
	            ImageView::create("asset:///images/white_photo.png").preferredSize(250.0f, 168.0f).layoutProperties(
	                    StackLayoutProperties::create().vertical(VerticalAlignment::Top));

	itemLabel = Label::create().text(" ").layoutProperties(
	    StackLayoutProperties::create().vertical(VerticalAlignment::Center)).leftMargin(30.0f);

	// Add the Image and Label to the content.
	contentContainer->add(itemImage);
	contentContainer->add(itemLabel);

	// Add the content to the full item container.
	backgroundContainer->add(contentContainer);

	// Finally add the background Container to the item Container.
	itemContainer->add(backgroundContainer);

	setRoot(itemContainer);
}

void listItem::updateItem(const QString text, const QString imagePath)
{
    // Update image and text for the current item.
    itemImage->setImage(Image(imagePath));
    itemLabel->setText(text);
}

void listItem::select(bool select)
{
}

void listItem::reset(bool selected, bool activated)
{
    Q_UNUSED(activated);

    // Since items are recycled the reset function is where we have
    // to make sure that item state, defined by the arguments, is correct.
    select(selected);
}

void listItem::activate(bool activate)
{
    // There is no special activate state, select and activated looks the same.
    select(activate);
}
