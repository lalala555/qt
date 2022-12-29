#pragma once


#ifndef CHECKBOXHEADERVIEW_H
#define CHECKBOXHEADERVIEW_H

#include <QtGui>
#include <QPainter>
#include <QHeaderView>
#include <QStyleOptionButton>
#include <QStyle>
#include <QCheckBox>
#include <QObject>

class CheckBoxHeaderView : public QHeaderView
{
	Q_OBJECT

public:
	explicit CheckBoxHeaderView(int checkColumnIndex,QPoint topLeft,QSize size,Qt::Orientation orientation,QWidget * parent = nullptr);
	~CheckBoxHeaderView();

    //rect:复选框的位置和大小 ，logicalIndex：第几列
	void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

	void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    bool event(QEvent *event);

signals:
	void checkStatusChange(bool value);

public slots:
    void  checkstate(int value);
private:
	int     m_checkColIndex;    //列下标
	QPoint  m_topLeft;          //勾选框起始坐标
	QSize   m_checkSize;        //勾选框大小
	bool    m_isChecked;        //勾选框状态
	bool    m_bPressed;
    bool	m_bTristate;   //未完全选中状态
	bool	m_bNoChange;
	bool    m_bMoving;


};
#endif
