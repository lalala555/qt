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
	// ��Ӧ���
	setSectionsClickable(true);
}

CheckBoxHeaderView::~CheckBoxHeaderView()
{
}

void CheckBoxHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    //��һ�ַ�ʽ��ʹ�� option.state��ָ����ѡ���״̬
       painter->save();
       QHeaderView::paintSection(painter, rect, logicalIndex);
       painter->restore();

       if (logicalIndex == 0)
       {
           QStyleOptionButton option;
           option.initFrom(this);

           if (m_isChecked)
               option.state |= QStyle::State_NoChange; //δ��ȫѡ��״̬

           if (!m_isChecked)
               option.state |= QStyle::State_Off;  //δѡ��״̬

           if (m_bTristate && m_bNoChange)
               option.state |= QStyle::State_NoChange;//δ��ȫѡ��״̬
           else
               option.state |= m_isChecked ? QStyle::State_On : QStyle::State_Off; //ѡ��״̬
           //��ɫ������ if (��m_bMoving)
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
       //�ڶ��ַ�ʽ��ʹ��ͼƬ�����Ƹ�ѡ��
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
                  //ͼƬ��Ҫ����Դ�����
                  pix.load(":/homepage/footleft-icon1-1.png");//ѡ��
                  option.state = QStyle::State_On;
              }
              else if (!m_isChecked && !m_bTristate)
              {
                 pix.load(":/homepage/footleft-icon2-1.png");//δѡ��
                  option.state = QStyle::State_Off;
              }
              else if (m_bTristate)
              {
                 // option.state = QStyle::State_NoChange;
                pix.load(":/homepage/footleft-icon3-1.png");//δ��ȫѡ��
              }

              style()->drawItemPixmap(painter, rect, Qt::AlignCenter, pix);
          }
#endif

}

void CheckBoxHeaderView::mousePressEvent(QMouseEvent *event)
{
    //press��release���
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

 //��껬�����뿪�����¸�ѡ��״̬
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
    //value = 0;ȫѡ��value = 1,��ѡ��value = 2����ѡ
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
