#ifndef CELL_H
#define CELL_H
#include <QTableWidgetItem>
#include "token.h"
#include "spreadsheet.h"

class Tree;
class Node_Statement;

class Cell : public QTableWidgetItem
{
public:
    Cell(QTableWidget* parent);
    ~Cell();
    QTableWidgetItem *clone() const;

    void setData(int role, const QVariant &value);
   QVariant data(int role) const;
    void setFormula(const QString &formula);
    QString getFormula() const;
    void setDirty();
    bool getIsEmpty() const;
    QVariant getAnotherCellData(int row, int column) const;
    QTableWidget *getParent();
private:
    QTableWidget* parent;
    Tree* tree;
    //QSharedPointer<Node_Statement> s;
    QString formula;
    bool isEmpty;
    QString getValue() const ;
    mutable QVariant cachedValue;
    mutable bool cacheIsDirty;

};

#endif // CELL_H
