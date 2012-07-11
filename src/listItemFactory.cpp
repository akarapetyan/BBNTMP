#include "listItemFactory.h"
#include "listItem.h"

using namespace bb::cascades;

listItemFactory::listItemFactory()
{
}

VisualNode* listItemFactory::createItem(ListView* list, const QString &type)
{
    //We only have one item type so we do not need to check the type variable.
    Q_UNUSED(type);
    Q_UNUSED(list);

    return new listItem();
}

void listItemFactory::updateItem(ListView* list, bb::cascades::VisualNode* node,
        const QString &type, const QVariantList &indexPath, const QVariant &data)
{
    Q_UNUSED(list);
    Q_UNUSED(indexPath);
    Q_UNUSED(type);

    // Update the control with correct data.
    QVariantMap map = data.value<QVariantMap>();
    listItem* item = static_cast<listItem *>(node);
    item->updateItem(map["title"].toString(), map["image"].toString());
}
