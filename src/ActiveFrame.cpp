/*
 * ActiveFrame.cpp
 *
 *  Created on: 2012-11-29
 *      Author: Travis Redpath
 */

#include <string.h>
#include <stdio.h>

#include "ActiveFrame.hpp"
#include "ATI85/TI85.h"

extern bool isPhysicalKeyboardDevice;

ActiveFrame::ActiveFrame()
	: SceneCover(this)
{
	qml = QmlDocument::create("asset:///active_frame.qml")
		.parent(this);

	mMainContainer = qml->createRootObject<Container>();
	setContent(mMainContainer);
	m_label = NULL;

	QObject::connect(Application::instance(), SIGNAL(thumbnail()), this, SLOT(thumbnail()));
}

ActiveFrame::~ActiveFrame()
{
}

void ActiveFrame::thumbnail()
{
	m_label = mMainContainer->findChild<Label*>("label2");
	if (!m_label && !isPhysicalKeyboardDevice)
	{
		m_label = new bb::cascades::Label(mMainContainer);
		m_label->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Center);
		m_label->setVerticalAlignment(bb::cascades::VerticalAlignment::Center);
		m_label->textStyle()->setFontSizeValue(20);
		m_label->textStyle()->setColor(bb::cascades::Color::White);
		m_label->setObjectName("label1");
		mMainContainer->add(m_label);
		m_label = new bb::cascades::Label(mMainContainer);
		m_label->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Center);
		m_label->setVerticalAlignment(bb::cascades::VerticalAlignment::Center);
		m_label->textStyle()->setFontSizeValue(20);
		m_label->textStyle()->setColor(bb::cascades::Color::White);
		m_label->setObjectName("label2");
	}
	if (m_label)
	{
		char temp[10];
		strcpy(temp, TIFilename);
		char* temp2 = strrchr(temp, (int)'.');
		if (temp2)
			*temp2 = '\0';
		QString upper(temp);
		if (upper.isEmpty())
			return;
		upper = upper.left(2) + QString("-") + upper.right(upper.length() - 2);
		upper = upper.toUpper();
		upper = upper.replace('P', '+');

		m_label->setText(upper);
		mMainContainer->add(m_label);
	}
}



