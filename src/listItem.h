#ifndef LISTITEM_H_
#define LISTITEM_H_

#include <bb/cascades/CustomControl>
#include <bb/cascades/Container>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>
#include <bb/cascades/ListItemListener>

using namespace bb::cascades;

class listItem : public bb::cascades::CustomControl, public ListItemListener
{
	Q_OBJECT

public:

	listItem(Container *parent = 0);

	//listItem(const QString& imageName, const QString& labelName);

	void updateItem(const QString text, const QString imagePath);
	void select(bool select);
	void reset(bool selected, bool activated);
	void activate(bool activate);

	private:
	    ImageView*  itemImage;
	    Label* 		itemLabel;

};

//Q_DECLARE_METATYPE(listItem *);

#endif /* LISTITEM_H_ */
