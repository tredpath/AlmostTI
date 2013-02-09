/*
 * filebrowser.h
 *
 *  Created on: 2012-08-03
 *      Author: Travis Redpath
 */

#ifndef FILEBROWSER_H_
#define FILEBROWSER_H_

#include <QObject>
#include <bb/cascades/QListDataModel>
#include <bb/cascades/Header>
#include <bb/cascades/Container>
#include <bb/cascades/ListView>
#include <bb/cascades/Label>

class FolderBrowser : public QObject
{
    Q_OBJECT
public:
    explicit FolderBrowser(QObject *parent = 0);
    ~FolderBrowser();

    Q_INVOKABLE void setFolderDialog(bb::cascades::Control *d);
    Q_INVOKABLE void setFolderLabel(bb::cascades::Label *d);
    Q_INVOKABLE void set();
    Q_INVOKABLE void setDefault();
    Q_INVOKABLE void setSDCard();
    Q_INVOKABLE void cancel();

    inline QString getCurrentPath() { return m_currentPath; }
    inline void setCurrentPath(const QString& path) { m_currentPath = QString(path); m_startPath = m_currentPath; refreshPath(); }
    inline void setCurrentPath(const char* path) { m_currentPath = QString(path); m_startPath = m_currentPath; refreshPath(); }

public slots:
    void selectionChanged(QVariantList indexPath);

signals:
	void ROMDirectoryUpdated(const QString& path);
	void ROMSelected(const QString& romname);

private:
    void refreshPath();
    void getFolders();
    void go(const QString& path);

private:
    bb::cascades::Label* m_head;
    QString m_currentPath;
    QString m_startPath;
    QStringList m_currentFolders;
    bb::cascades::ListView *m_listView;
    bb::cascades::QListDataModel<QString>* m_listModel;
    bool isSaving;
};

#endif /* FILEBROWSER_H_ */
