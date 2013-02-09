// Default empty project template
#ifndef AlmostTIPb_HPP_
#define AlmostTIPb_HPP_

#include <QObject>
#include <QMutex>
#include <bb/cascades/ForeignWindowControl>
#include <bb/cascades/Control>
#include <bb/cascades/QListDataModel>
#include <bb/cascades/ListView>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/DropDown>
#include <bb/cascades/TouchEvent>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/NavigationPane>
/*#include <bb/cascades/KeyListener>
#include <bb/cascades/KeyEvent>*/
#include <bb/ProcessState>

#include "Browser/FolderBrowser.hpp"

namespace bb { namespace cascades { class Application; }}

#define ROM_PATH_SETTING "ROMPATH"
#define ROM_PATH_DEFAULT "shared/misc/TI/ROM"

extern QMutex exitMutex;

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class AlmostTIPb : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void setForeignWindow(bb::cascades::ForeignWindowControl* ctrl);
    Q_INVOKABLE void setRomSelector(bb::cascades::Control *d);
    Q_INVOKABLE void setRecentSelector(bb::cascades::Control *d);
    Q_INVOKABLE void setPage(bb::cascades::Page *d);
    Q_INVOKABLE void clearRecent();
    Q_INVOKABLE void clearRAM();
    Q_INVOKABLE void toggleScanlines();
    Q_INVOKABLE void toggleFrameRate();
    Q_INVOKABLE void toggleSoften();
    Q_INVOKABLE void touch(int x, int y);
    Q_INVOKABLE void unTouch(int x, int y);
    Q_INVOKABLE void press(int key);
    Q_INVOKABLE void unpress(int key);
    Q_INVOKABLE void setYourFileContainer(bb::cascades::Control* ctrl);

public:
    AlmostTIPb(bb::cascades::Application *app);
    virtual ~AlmostTIPb();

public slots:
    void finished();
    void thumbnail();
    void fullscreen();
    void aboutToQuit();
    void selectionChanged(QVariantList indexPath);
    void openRecent(QVariantList indexPath);
    void ROMDirectoryUpdated(const QString& path);
    /*void onKeyPressed(bb::cascades::KeyEvent* event);
    void onKeyReleased(bb::cascades::KeyEvent* event);*/

private:
    int inRecentList(QString path, QString filename);
    void openROM(const QString& rom, const QString& path = "");

private:
    bb::cascades::ForeignWindowControl* m_fw;
    bb::cascades::QListDataModel<QString> m_romData;
    bb::cascades::QVariantListDataModel m_varList;
    bb::cascades::QmlDocument *m_qml;
    bb::cascades::Container *m_yourFiles;
    bb::cascades::ListView *m_listView;
    bb::cascades::ListView *m_recentlist;
    bb::cascades::AbstractPane *m_root;
    bb::cascades::NavigationPane *m_pane;
    FolderBrowser* m_fb;
    QSettings* m_settings;
    QStringList m_recentStrings;
    bb::cascades::QListDataModel<QString>* m_recentModel;
    bb::cascades::QListDataModel<QString>* m_listModel;
    //bb::cascades::KeyListener* m_listener;
};

class TIWorker : public QObject
{
	Q_OBJECT

public slots:
	void doWork();

signals:
	void finished();
};


#endif /* AlmostTIPb_HPP_ */
