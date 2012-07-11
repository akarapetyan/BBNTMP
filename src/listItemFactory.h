#ifndef LISTITEMFACTORY_H_
#define LISTITEMFACTORY_H_

#include <bb/cascades/ListItemManager>

using namespace bb::cascades;

namespace bb
{
    namespace cascades
    {
        class ListView;
    }
}

class listItemFactory: public bb::cascades::ListItemManager
{
public:
	listItemFactory();

    VisualNode * createItem(ListView* list, const QString &type);

    void updateItem(ListView* list, VisualNode *listItem, const QString &type,
    				const QVariantList &indexPath, const QVariant &data);
};

#endif /* LISTITEMFACTORY_H_ */
