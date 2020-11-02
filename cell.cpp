#include "cell.h"
#include "node.h"

Cell::Cell()
{
    setDirty();
    t = new Token();
    s.reset(new Node_Statement);
}

Cell::~Cell()
{
    delete t;
}


void Cell::setDirty()
{
    cacheIsDirty = true;
}

QTableWidgetItem *Cell::clone() const
{
    return new Cell(*this);
}

QVariant Cell::data(int role) const
{

        if(role ==Qt::DisplayRole)
        {
            QVariant res = this->getValue();
            if( res.isValid()){
                return res;

            } else {
                 return QVariant("Wrong Input");
                 }
        }
        return QTableWidgetItem::data(role);

}

void Cell::setData(int role, const QVariant &value)
{

    // s = new Node_Statement(Parser::parse(Lexer::Tokenize("1213 + 123")));
     //getValue();
    QTableWidgetItem::setData(role, value);


    if (role == Qt::EditRole)
        setDirty();
}

QVariant Cell::getValue() const
{
    return  QVariant(1000);
}
