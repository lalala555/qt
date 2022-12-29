#include "CheckBoxHeaderView.h"

CheckBoxHeaderView::CheckBoxHeaderView(int checkColumnIndex, QPoint topLeft, QSize size, Qt::Orientation orientation, QWidget * parent) : QHeaderView(orientation, parent)
	
{
	m_checkColIndex = checkColumnIndex;
	m_topLeft = topLeft;
	m_checkSize = size;
	m_isChecked = false;
	m_bPressed = false;
	m_bTristate = false;
	m_bNoChange = false;
    m_bMoving = false;
	setHighlightSections(false);
	setMouseTracking(true);
	// 响应鼠标
	setSectionsClickable(true);
}

CheckBoxHeaderView::~CheckBoxHeaderView()
{
}

void CheckBoxHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    //第一种方式，使用 option.state来指定复选框的状态
       painter->save();
       QHeaderView::paintSection(painter, rect, logicalIndex);
       painter->restore();

       if (logicalIndex == 0)
       {
           QStyleOptionButton option;
           option.initFrom(this);

           if (m_isChecked)
               option.state |= QStyle::State_NoChange; //未完全选中状态

           if (!m_isChecked)
               option.state |= QStyle::State_Off;  //未选中状态

           if (m_bTristate && m_bNoChange)
               option.state |= QStyle::State_NoChange;//未完全选中状态
           else
               option.state |= m_isChecked ? QStyle::State_On : QStyle::State_Off; //选中状态
           //变色可屏蔽 if (！m_bMoving)
//           if (testAttribute(Qt::WA_Hover) && underMouse()) {
//               if (m_bMoving)
//                   option.state |= QStyle::State_MouseOver;
//               else
//                   option.state &= ~QStyle::State_MouseOver;
//           }

           QCheckBox checkBox;
           option.iconSize = QSize(20, 20);
           option.rect = rect;
           style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter, &checkBox);
           //style()->drawItemPixmap(painter, rect, Qt::AlignCenter, QPixmap(":/images/checkBoxChecked"));
           //style()->drawControl(QStyle::CE_CheckBox, &option, painter, this);
       }
       //第二种方式，使用图片来绘制复选框
#if 0
       painter->save();
          QHeaderView::paintSection(painter, rect, logicalIndex);
          painter->restore();
          if (0 == logicalIndex)
          {
              QStyleOptionButton option;
              QPixmap pix;

              if (m_isChecked  && !m_bTristate)
              {
                  //图片需要在资源里添加
                  pix.load(":/homepage/footleft-icon1-1.png");//选中
                  option.state = QStyle::State_On;
              }
              else if (!m_isChecked && !m_bTristate)
              {
                 pix.load(":/homepage/footleft-icon2-1.png");//未选中
                  option.state = QStyle::State_Off;
              }
              else if (m_bTristate)
              {
                 // option.state = QStyle::State_NoChange;
                pix.load(":/homepage/footleft-icon3-1.png");//未完全选中
              }

              style()->drawItemPixmap(painter, rect, Qt::AlignCenter, pix);
          }
#endif

}

void CheckBoxHeaderView::mousePressEvent(QMouseEvent *event)
{
    //press与release结合
//    if (visualIndexAt(event->pos().x()) == m_checkColIndex)
//    {
//        m_isChecked = !m_isChecked;
//        this->updateSection(m_checkColIndex);
//        //update();
//        emit checkStatusChange(m_isChecked);
//    }

    QHeaderView::mousePressEvent(event);
    int nColumn = logicalIndexAt(event->pos());
        if ((event->buttons() & Qt::LeftButton) && (nColumn == 0))
        {
            m_bPressed = true;
            this->updateSection(m_checkColIndex);
        }
        else
        {
            QHeaderView::mousePressEvent(event);
        }

}

void CheckBoxHeaderView::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_bPressed)
    {
        if (m_bTristate && m_bNoChange)
        {
            m_isChecked = true;
            m_bNoChange = false;
        }
        else
        {
            m_isChecked = !m_isChecked;
        }

         update();
        Qt::CheckState state;
        state = m_isChecked ? Qt::Checked : Qt::Unchecked;

        emit checkStatusChange(state);
    }
    else
    {
        QHeaderView::mouseReleaseEvent(event);
    }

    m_bPressed = false;
}

 //鼠标滑过、离开，更新复选框状态
bool CheckBoxHeaderView::event(QEvent *event)
{
    if (event->type() == QEvent::Enter || event->type() == QEvent::Leave)
    {
        QMouseEvent *pEvent = static_cast<QMouseEvent *>(event);
        int nColumn = logicalIndexAt(pEvent->x());
        if (nColumn == 0)
        {
            m_bMoving = (event->type() == QEvent::Enter);
            update();
            return true;
        }
    }
   return QHeaderView::event(event);
}

void CheckBoxHeaderView::checkstate(int value)
{
    //value = 0;全选，value = 1,半选，value = 2，不选
    if (value == 1) {
           m_bTristate = true;
           m_bNoChange = true;
       } else {
           m_bNoChange = false;
          // m_bTristate = false;
       }

       m_isChecked = (value != 2);
       this->updateSection(m_checkColIndex);
       update();


}
