/*
 * ActiveFrame.hpp
 *
 *  Created on: 2012-11-29
 *      Author: Travis Redpath
 */

#ifndef ACTIVEFRAME_HPP_
#define ACTIVEFRAME_HPP_

#include <bb/cascades/SceneCover>
#include <bb/cascades/Container>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/Label>

using namespace bb::cascades;

class ActiveFrame : public SceneCover
{
	Q_OBJECT

public:
	ActiveFrame();
	virtual ~ActiveFrame();

public slots:
	void thumbnail();

private:
	Container* mMainContainer;
	QmlDocument* qml;
	Label* m_label;
};


#endif /* ACTIVEFRAME_HPP_ */
