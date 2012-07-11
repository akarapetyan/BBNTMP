/**
 * @file window.cpp
 * @brief Contains the implementation of UI widget class used as a GUI in the Video Player application
 */

#include <bb/cascades/ActionItem>
#include <bb/cascades/Application>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/Color>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/NavigationPaneProperties>
#include <bb/cascades/Stacklayout>
#include <bb/cascades/StackLayoutProperties>
#include <bb/cascades/TouchEvent>

#include "listItemFactory.h"
#include "window.hpp"


Window::Window(Player* newPlayer)
{
	player = newPlayer;
	isPlaying = true;

	root = new NavigationPane();
	Q_ASSERT(connect(root, SIGNAL(topChanged(bb::cascades::AbstractPane* )),
					 this, SLOT(onTopChanged(bb::cascades::AbstractPane* ))));

	Page* fileListPage = createFileListPage();
	playerPage = createPlayerPage();

	root->push(fileListPage);

	Application::setScene(root);
}

Page* Window::createFileListPage()
{
	Page* fileListPage = new Page();

	Container* fileListContainer = new Container();
	DockLayout* fileListLayout = new DockLayout();
	fileListContainer->setLayout(fileListLayout);

	fileListContainer->setBackground(Color::fromARGB(0xff262626));

	ImageView* topDecorationImage =
			ImageView::create("asset:///images/red_cloth_edge_top.png").preferredHeight(15.0f).layoutProperties(
					DockLayoutProperties::create().vertical(VerticalAlignment::Top).horizontal(
							HorizontalAlignment::Fill));

	ImageView* bottomDecorationImage = ImageView::create(
			"images/red_cloth_edge_bottom.png").preferredHeight(15.0f).layoutProperties(
			DockLayoutProperties::create().vertical(VerticalAlignment::Bottom).horizontal(
					HorizontalAlignment::Fill));

	Container* contentContainer = new Container();
	DockLayout* contentLayout = new DockLayout();
	contentLayout->setTopPadding(15.0f);
	contentLayout->setBottomPadding(15.0f);
	contentContainer->setLayout(contentLayout);
	contentContainer->setLayoutProperties(DockLayoutProperties::create().horizontal(HorizontalAlignment::Fill));

	fileListView = createFileListView();
	fileListView->setLayoutProperties(DockLayoutProperties::create().horizontal(HorizontalAlignment::Fill));

	contentContainer->add(fileListView);

	fileListContainer->add(topDecorationImage);
	fileListContainer->add(contentContainer);
	fileListContainer->add(bottomDecorationImage);

	fileListPage->setContent(fileListContainer);

	return fileListPage;
}


Page* Window::createPlayerPage()
{
	Page* page = new Page();

	// We need an action on the ContentPage, so we can navigate back.
	ActionItem* backAction = ActionItem::create();
	Q_ASSERT(connect(backAction, SIGNAL(triggered()), root, SLOT(pop())));
	page->setPaneProperties(NavigationPaneProperties::create().backButton(backAction));

	contentContainer = new Container();
	contentContainer->setBackground(Color::fromARGB(0xff262626));
	contentContainer->setLayout(DockLayout::create());

	Container *sliderContainer = new Container();
	sliderContainer->setLayout(StackLayout::create()
			.direction(LayoutDirection::LeftToRight));
			//.left(20.0f).right(20.0f));
	sliderContainer->setLayoutProperties(StackLayoutProperties::create()
			.horizontal(HorizontalAlignment::Fill)
			.vertical(VerticalAlignment::Bottom));

	previous = ImageView::create("asset:///images/previous");
	previous->setLeftMargin(0);
	previous->setRightMargin(0);
	Q_ASSERT(connect(previous, SIGNAL(touch(bb::cascades::TouchEvent *)), this, SLOT(playPrevious(bb::cascades::TouchEvent *))));

	stop = ImageView::create("asset:///images/stop");
	stop->setLeftMargin(0);
	stop->setRightMargin(0);
	Q_ASSERT(connect(stop, SIGNAL(touch(bb::cascades::TouchEvent*)), this, SLOT(setImage(bb::cascades::TouchEvent*))));

	next = ImageView::create("asset:///images/next");
	next->setLeftMargin(0);
	next->setRightMargin(0);
	Q_ASSERT(connect(next, SIGNAL(touch(bb::cascades::TouchEvent *)), this, SLOT(playNext(bb::cascades::TouchEvent *))));

	elapsedTime = new Label();
	elapsedTime->setText("11.11.11");

	timeSlider = Slider::create().from(0.0f).to(0.5f).leftMargin(20.0f).rightMargin(20.0f);
	timeSlider->setLayoutProperties(StackLayoutProperties::create().spaceQuota(1.0f));

	fullTime = new Label();
	fullTime->setText("22.22.22");

	volumeSlider = Slider::create().from(0.0f).to(0.5f).leftMargin(20.0f).rightMargin(20.0f);
	volumeSlider->setLayoutProperties(StackLayoutProperties::create().spaceQuota(1.0f));

	sliderContainer->add(previous);
	sliderContainer->add(stop);
	sliderContainer->add(next);
	sliderContainer->add(elapsedTime);
	sliderContainer->add(timeSlider);
	sliderContainer->add(fullTime);
	sliderContainer->add(volumeSlider);

	contentContainer->add(sliderContainer);

	page->setContent(contentContainer);

	return page;
}

ListView* Window::createFileListView()
{
    // The list view and its item manager (where item are created and set up).
    ListView* fileListView = new ListView();
    listItemFactory* itemManager = new listItemFactory();

    QVariantMap map;
    QStringList result;
	QStringList filters;
	filters << "*.mp4";
	filters << "*.avi";
	/*if(utility::FileSystemUtility::getEntryListR("/", filters, result))
	{
		foreach(QString str, result)
		{*/
			map["title"] = QString("text1");
			map["image"] = QString("asset:///images/first.jpg");
			fileListModel << map;
			map["title"] = QString("text2");
			map["image"] = QString("asset:///images/second.jpg");
			fileListModel << map;
		/*}
	}*/

    fileListView->setDataModel(&fileListModel);
    fileListView->setListItemManager(itemManager);
    fileListView->setLayoutProperties(StackLayoutProperties::create().vertical(VerticalAlignment::Fill));

    Q_ASSERT(connect(fileListView, SIGNAL(selectionChanged(const QVariantList, bool)),
    		this,    	  SLOT(onSelectionChanged(const QVariantList, bool))));

    return fileListView;
}


void Window::onTopChanged(bb::cascades::AbstractPane* pane)
{
    if(pane != playerPage) {
        // Reset list selection when the top Container is not the Content Page.
    	fileListView->clearSelection();
    }
}


void Window::playNext(bb::cascades::TouchEvent *)
{
	qDebug("playNext");
	//player->playNext();
}

void Window::playPrevious(bb::cascades::TouchEvent *)
{
	qDebug("playPrevious");
	//player->playPrevious();
}

void Window::setImage(bb::cascades::TouchEvent * te)
{
	if (te->isDown())
	{
		Image image = isPlaying ? Image(QUrl("asset:///images/play")) : Image(QUrl("asset:///images/stop"));
		stop->setImage(image);
		isPlaying = !isPlaying;
	}
}

void Window::onSelectionChanged(const QVariantList indexPath, bool selected)
{
    if (selected)
    {
    	QVariantMap map = fileListModel.data(indexPath).toMap();
    	QString fileName = map.value("title").toString();
    	//TODO
    	//pass found fileName to player to be played.

    	/*Container *content = dynamic_cast<Container *>(mContentPage->content());
		content->removeAll();
		recipe->setLayoutProperties(
				DockLayoutProperties::create().horizontal(HorizontalAlignment::Center).vertical(
						VerticalAlignment::Center));
		content->add(recipe);*/

    	root->push(playerPage);
    }
}

