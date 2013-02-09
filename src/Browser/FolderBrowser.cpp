/*
 * filebrowser.cpp
 *
 *  Created on: 2012-08-03
 *      Author: Travis Redpath
 */

#include <bps/bps.h>
#include <bps/dialog.h>
#include <bps/event.h>

#include <QStringList>
#include <QDir>

#include "folderbrowser.hpp"

using namespace bb::cascades;

FolderBrowser::FolderBrowser(QObject *parent) :
    QObject(parent),
    m_head(NULL),
    m_listView(NULL),
    m_listModel(NULL)
{
    setCurrentPath("shared/misc/TI/ROM");
}

FolderBrowser::~FolderBrowser()
{
	if (m_listModel)
		delete m_listModel;
}

void FolderBrowser::setFolderDialog(bb::cascades::Control *d)
{
	if (m_listView != d)
	{
		m_listView = static_cast<bb::cascades::ListView*>(d);
		m_listModel = 0;
	}
	refreshPath();
}

void FolderBrowser::setFolderLabel(bb::cascades::Label *d)
{
	m_head = d;
	m_head->setText(m_currentPath);
}

void FolderBrowser::go(const QString &path)
{
	QString newPath;
	if (path == "..")
		newPath = m_currentPath;
	else
		newPath = m_currentPath + "/" + path;
	QFileInfo fi(newPath);
	if (fi.isFile())
	{
		emit ROMDirectoryUpdated(fi.path());
		emit ROMSelected(fi.fileName());
		return;
	}
    QDir p(newPath);
    if (path == "..")
    	p.cdUp();
    if (!p.exists())
    	return;
    m_currentPath = p.path();
    refreshPath();
}

void FolderBrowser::cancel()
{
	m_currentPath = m_startPath;
	refreshPath();
}

void FolderBrowser::getFolders()
{
	QDir dir(m_currentPath);
	dir.setFilter(QDir::AllDirs | QDir::Files);
	QStringList filters;
	filters << "ti85.rom" << "ti86.rom" << "ti82.rom" << "ti83.rom" << "ti83p.rom";
	dir.setNameFilters(filters);
	m_currentFolders = dir.entryList(QDir::NoFilter, QDir::Name);
	while (m_currentPath.at(m_currentPath.length() - 1) == '/')
		m_currentPath = m_currentPath.left(m_currentPath.length() - 1);
	if (m_currentFolders.count() == 0)
		m_currentFolders.insert(0, "..");
	else
	{
		m_currentFolders.removeAt(0);
		int index = m_currentPath.lastIndexOf('/');
		if (index <= 0)
			m_currentFolders.removeAt(0);
	}
}

void FolderBrowser::selectionChanged(QVariantList indexPath)
{
	if (indexPath.at(0).type() == QVariant::Int)
	{
		int c = indexPath.at(0).toInt();
		go(m_currentFolders[c]);
	}
}

void FolderBrowser::set()
{
	m_startPath = m_currentPath;
	emit ROMDirectoryUpdated(m_currentPath);
}

void FolderBrowser::setDefault()
{
	m_currentPath = "shared/misc/TI/ROM";
	m_startPath = m_currentPath;
	refreshPath();
	emit ROMDirectoryUpdated(m_currentPath);
}

void FolderBrowser::setSDCard()
{
	m_currentPath = "/sdcard2";
	m_startPath = m_currentPath;
	refreshPath();
	emit ROMDirectoryUpdated(m_currentPath);
}

void FolderBrowser::refreshPath()
{
	if (!m_listView)
		return;
	getFolders();
    if (m_head)
    	m_head->setText(m_currentPath);
	if (!m_listModel) {
		connect(m_listView, SIGNAL(triggered(QVariantList)), this, SLOT(selectionChanged(QVariantList)));
		m_listModel = new QListDataModel<QString>(m_currentFolders);
		m_listModel->setParent(this);
		m_listView->setDataModel(m_listModel);
	}
	else
	{
		m_listModel->clear();
		m_listModel->append(m_currentFolders);
	}
}


