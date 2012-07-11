#ifndef WINDOW_HPP
#define WINDOW_HPP

/**
 * @file window.hpp
 * @brief Holder for UI widget implementation
 */

#include <bb/cascades/ImageView>
#include <bb/cascades/Slider>
#include <bb/cascades/Label>
#include <bb/cascades/ListView>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Page>
#include <bb/cascades/QListDataModel>

#include "player.hpp"

using namespace bb::cascades;

class Window : public QObject
{
    Q_OBJECT

public:

    Window(Player*);

private Q_SLOTS:

	void playPrevious(bb::cascades::TouchEvent *);
	void playNext(bb::cascades::TouchEvent *);
	void setImage(bb::cascades::TouchEvent *);
	void onSelectionChanged(const QVariantList indexPath, bool selected);
	void onTopChanged(bb::cascades::AbstractPane* pane);

private:

	Page*     createFileListPage();
	Page*     createPlayerPage();
	ListView* createFileListView();

private:

	NavigationPane* root;
	Page* 	    	playerPage;
	Container* 		contentContainer;
	ImageView* 		previous;
	ImageView* 		stop;
	ImageView* 		next;
	Slider*    		timeSlider;
	Slider*		    volumeSlider;
	bool       		isPlaying;
	Label*     		fullTime;
	Label*     		elapsedTime;

	Player*   		player;

	ListView*   	fileListView;

	QVariantListDataModel fileListModel;
};

#endif
