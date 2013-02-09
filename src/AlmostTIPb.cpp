// Default empty project template
#include "AlmostTIPb.hpp"
#include "EMULib/QNX/LibQNX.h"
#include "EMULib/EMULib.h"
#include "ATI85/TI85.h"
#include "ActiveFrame.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/Page>
#include <bb/cascades/Container>
#include <bb/cascades/AbsoluteLayout>
#include <bb/cascades/ListView>
#include <bb/cascades/Sheet>
#include <bb/cascades/DockLayout>
#include <bb/cascades/Divider>
#include <bb/cascades/Header>
#include <bb/system/SystemToast>
#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>
#include <bb/system/InvokeReply>
#include <bb/system/InvokeTargetReply>
#include <bb/device/HardwareInfo>
#include <bps/navigator.h>
#include <bps/deviceinfo.h>
#include <QThread>
#include <QFile>
#include <QList>

#include <unistd.h>

using namespace bb::cascades;
using namespace bb::system;

QString windowGroups;
QString windowIds;
QByteArray groupArr;
QByteArray idArr;
const char* windowGroup;
int windowIdLength;
const char* windowId;

extern int almostti_main(char*);
extern byte ExitNow;
extern char* ProgDir;
extern int paused;
QThread *tiThread = 0;
TIWorker* tiWorker = 0;

char romname[256];
QMutex exitMutex;

bool isPhysicalKeyboardDevice = false;

void TIWorker::doWork()
{
	almostti_main(romname);
	emit finished();
}

AlmostTIPb::AlmostTIPb(bb::cascades::Application *app)
: QObject(app),
  m_yourFiles(NULL),
  m_fw(NULL),
  m_listView(NULL),
  m_settings(NULL),
  m_recentlist(NULL),
  m_listModel(NULL),
  m_recentModel(NULL)
{
    m_qml = QmlDocument::create("asset:///main.qml");
	m_qml->setContextProperty("cs", this);
	m_fb = new FolderBrowser(this);
	m_qml->setContextProperty("fb", m_fb);

	bb::device::HardwareInfo info(this);
	isPhysicalKeyboardDevice = info.isPhysicalKeyboardDevice();

    m_root = m_qml->createRootObject<AbstractPane>();

    m_settings = new QSettings("shared/misc/TI/settings.ini", QSettings::IniFormat, 0);
    m_fb->setCurrentPath(m_settings->value(ROM_PATH_SETTING, ROM_PATH_DEFAULT).value<QString>());

	Application::instance()->setScene(m_root);

	for (int rec = 0; rec < 10; rec++)
	{
		QString fl = m_settings->value(QString("recent/") + QString::number(rec, 10), "").value<QString>();
		if (QString::compare(fl, "") == 0)
			break;
		else
			m_recentStrings << fl;
	}
	if (m_recentlist)
		setRecentSelector(m_recentlist);
	if (m_listView)
		setRomSelector(m_listView);

	connect(Application::instance(), SIGNAL(thumbnail()), this, SLOT(thumbnail()));
	connect(Application::instance(), SIGNAL(fullscreen()), this, SLOT(fullscreen()));
	connect(Application::instance(), SIGNAL(aboutToQuit()), this, SLOT(aboutToQuit()));
	connect(m_fb, SIGNAL(ROMDirectoryUpdated(QString)), this, SLOT(ROMDirectoryUpdated(QString)));

	m_pane = 0;

	exitMutex.lock();
}

AlmostTIPb::~AlmostTIPb()
{
	fprintf(stderr, "Cleaning up\n");
	for (int rec = 0; rec < m_recentStrings.size() && rec < 10; rec++)
		m_settings->setValue(QString("recent/") + QString::number(rec, 10), m_recentStrings[rec]);

	if (m_settings)
		delete m_settings;
	if (m_fb)
		delete m_fb;
	if (ProgDir)
		delete ProgDir;
	/*if (m_listener)
		delete m_listener;*/
}

void AlmostTIPb::setForeignWindow(ForeignWindowControl* ctrl)
{
	m_fw = ctrl;
	if (m_fw)
	{
		windowGroups = m_fw->windowGroup();
		windowIds = m_fw->windowId();
		groupArr = windowGroups.toAscii();
		idArr = windowIds.toAscii();
		windowGroup = groupArr.constData();
		windowIdLength = idArr.length();
		windowId = idArr.constData();
	}
}

void AlmostTIPb::setPage(bb::cascades::Page *d)
{
	/*m_listener = KeyListener::create()
		.onKeyPressed(this, SLOT(onKeyPressed(bb::cascades::KeyEvent*)))
		.onKeyReleased(this, SLOT(onKeyReleased(bb::cascades::KeyEvent*)));
	d->addKeyListener(m_listener);*/
}

/*void AlmostTIPb::onKeyPressed(bb::cascades::KeyEvent* event)
{
	(*KeyHandler)(event->key(), 1);
}

void AlmostTIPb::onKeyReleased(bb::cascades::KeyEvent* event)
{
	(*KeyHandler)(event->key(), 0);
}*/

void AlmostTIPb::press(int key)
{
	(*KeyHandler)(key, 1);
}

void AlmostTIPb::unpress(int key)
{
	(*KeyHandler)(key, 0);
}

void AlmostTIPb::setYourFileContainer(Control* ctrl)
{
	m_yourFiles = static_cast<Container*>(ctrl);

	if (m_yourFiles)
	{
		//UpdateRomList(0);
		//std::vector<std::string> list = getList();
		QString path = m_settings->value(ROM_PATH_SETTING, ROM_PATH_DEFAULT).value<QString>();
		QDir dir(path);
		QStringList filters;
		filters << "ti85.rom" << "ti86.rom" << "ti82.rom" << "ti83.rom" << "ti83p.rom";
		dir.setNameFilters(filters);
		QStringList stringList = dir.entryList();
		if (stringList.size() > 0)
		{
			m_yourFiles->removeAll();
			Header *head = new Header();
			head->setParent(m_yourFiles);
			head->setTitle(QString("Your Files"));
			head->setTopMargin(10.0);
			m_yourFiles->add(head);
			Container *cnt = new Container(m_yourFiles);
			cnt->setLayout(new DockLayout());
			cnt->setHorizontalAlignment(HorizontalAlignment::Fill);
			cnt->setTopMargin(10.0);
			Label *lb1 = new Label(cnt);
			lb1->setText(QString("ROM File"));
			cnt->add(lb1);
			lb1 = new Label(cnt);
			lb1->setText(QString("File Size"));
			lb1->setHorizontalAlignment(HorizontalAlignment::Right);
			cnt->add(lb1);
			m_yourFiles->add(cnt);
			m_yourFiles->add(new Divider(m_yourFiles));
			for (unsigned int i = 0; i < stringList.size(); i++)
			{
				QString text(stringList[i]);
				Container* cont = new Container(m_yourFiles);
				cont->setLayout(new DockLayout());
				cont->setHorizontalAlignment(HorizontalAlignment::Fill);
				cont->setTopMargin(10.0);
				Label *lbl1 = new Label(cont);
				lbl1->setText(text);
				cont->add(lbl1);
				Label *lbl2 = new Label(cont);
				QFile fl(path + "/" + text);
				quint64 s = fl.size();
				lbl2->setText(QString::number(s, 10) + QString(" Bytes"));
				lbl2->setHorizontalAlignment(HorizontalAlignment::Right);
				cont->add(lbl2);
				m_yourFiles->add(cont);
			}
		}
	}
}

void AlmostTIPb::selectionChanged(QVariantList indexPath)
{
	if (!m_pane)
		m_pane = Application::instance()->findChild<NavigationPane*>("navigationPane");
	if (indexPath.at(0).type() == QVariant::Int)
	{
		int c = indexPath.at(0).toInt();
		//std::vector<std::string> list = getList();
		QVariantList ls;
		ls << c;
		QString file = m_listView->dataModel()->data(ls).value<QString>();
		QString path = m_settings->value(ROM_PATH_SETTING, ROM_PATH_DEFAULT).value<QString>();
		QFileInfo fi(path + "/" + file);
		if (!fi.exists())
			return;
		openROM(file);
		if (m_pane)
			m_pane->pop();
	}
}

void AlmostTIPb::openRecent(QVariantList indexPath)
{
	if (!m_pane)
		m_pane = Application::instance()->findChild<NavigationPane*>("navigationPane");
	if (indexPath.at(0).type() == QVariant::Int)
	{
		int c = indexPath.at(0).toInt();
		if (c >= 0 && c < m_recentStrings.size())
		{
			QFileInfo info(m_recentStrings[c]);
			if (!info.exists())
			{
				m_recentStrings.removeAt(c);
				setRecentSelector(m_recentlist);
				bb::system::SystemToast *toast = new bb::system::SystemToast(this);
				toast->setBody("File does not exist.");
				toast->show();
				return;
			}
			openROM(info.fileName(), info.path());
			if (m_pane)
				m_pane->pop();
		}
	}
}

void AlmostTIPb::clearRecent()
{
	m_recentStrings.clear();
	for (int i = 0; i < 10; i++)
	{
		QString temp = m_settings->value("recent/" + QString::number(i, 10), "").value<QString>();
		if (QString::compare(temp, "") == 0)
			break;
		m_settings->remove("recent/" + QString::number(i, 10));
	}
	setRecentSelector(m_recentlist);
}

void AlmostTIPb::setRomSelector(Control *d)
{
	if (m_listView != d)
	{
		m_listView = static_cast<ListView*>(d);
		m_listModel = 0;
	}
	if (m_listView && m_settings)
	{
		//UpdateRomList(0);
		//std::vector<std::string> list = getList();
		QString path = m_settings->value(ROM_PATH_SETTING, ROM_PATH_DEFAULT).value<QString>();
		QDir dir(path);
		QStringList filters;
		filters << "ti85.rom" << "ti86.rom" << "ti82.rom" << "ti83.rom" << "ti83p.rom";
		dir.setNameFilters(filters);
		QStringList stringList = dir.entryList();
		if (stringList.size() > 0)
		{
			m_listView->setVisible(true);
			if (m_listModel)
			{
				m_listModel->clear();
				m_listModel->append(stringList);
			}
			else
			{
				m_listModel = new QListDataModel<QString>(stringList);
				m_listView->setDataModel(m_listModel);
				connect(m_listView, SIGNAL(triggered(QVariantList)), this, SLOT(selectionChanged(QVariantList)));
			}
		}
		else
		{
			m_listView->setVisible(false);
			/*m_cont->removeAll();
			Label *lbl = new Label(m_cont);
			lbl->setText(QString("No ROMs Found"));
			lbl->setHorizontalAlignment(HorizontalAlignment::Center);
			m_cont->add(lbl);*/
		}
	}
	/*if (m_cont)
	{
		m_cont->removeAll();
		if (m_yourFiles)
		{
			m_yourFiles->removeAll();
			Header *head = new Header();
			head->setParent(m_yourFiles);
			head->setTitle(QString("Your Files"));
			head->setTopMargin(10.0);
			m_yourFiles->add(head);
			Container *cnt = new Container(m_yourFiles);
			cnt->setLayout(new DockLayout());
			cnt->setHorizontalAlignment(HorizontalAlignment::Fill);
			cnt->setTopMargin(10.0);
			Label *lb1 = new Label(cnt);
			lb1->setText(QString("ROM File"));
			cnt->add(lb1);
			lb1 = new Label(cnt);
			lb1->setText(QString("File Size"));
			lb1->setHorizontalAlignment(HorizontalAlignment::Right);
			cnt->add(lb1);
			m_yourFiles->add(cnt);
			m_yourFiles->add(new Divider(m_yourFiles));
		}
		UpdateRomList(1);
		std::vector<std::string> list = getList();
		if (list.size() > 0)
		{
			for (int i = 0; i < list.size(); i++)
			{
				QString text(list.at(i).c_str());
				m_cont->add(Option::create().text(text));
				if (m_yourFiles)
				{
					Container* cont = new Container(m_yourFiles);
					cont->setLayout(new DockLayout());
					cont->setHorizontalAlignment(HorizontalAlignment::Fill);
					cont->setTopMargin(10.0);
					Label *lbl1 = new Label(cont);
					lbl1->setText(QString(text));
					cont->add(lbl1);
					Label *lbl2 = new Label(cont);
					QFile fl(QString("shared/misc/TI/ROM/") + QString(text));
					quint64 s = fl.size();
					lbl2->setText(QString::number(s, 10) + QString(" Bytes"));
					lbl2->setHorizontalAlignment(HorizontalAlignment::Right);
					cont->add(lbl2);
					m_yourFiles->add(cont);
				}
			}
		}
	}*/
}

void AlmostTIPb::setRecentSelector(bb::cascades::Control *d)
{
	if (m_recentlist != d)
	{
		m_recentlist = static_cast<ListView*>(d);
		m_recentModel = 0;
	}
	if (m_recentlist)
	{
		if (m_recentStrings.size() > 0)
		{
			m_recentlist->setVisible(true);
			QStringList filenames;
			for (int i = 0; i < m_recentStrings.size(); i++)
			{
				QFileInfo info(m_recentStrings[i]);
				filenames << info.fileName();
			}
			if (m_recentModel)
			{
				m_recentModel->clear();
				m_recentModel->append(filenames);
			}
			else
			{
				m_recentModel = new QListDataModel<QString>(filenames);
				m_recentlist->setDataModel(m_recentModel);
				connect(m_recentlist, SIGNAL(triggered(QVariantList)), this, SLOT(openRecent(QVariantList)));
			}
		}
		else
		{
			m_recentlist->setVisible(false);
		}
	}
}

void AlmostTIPb::ROMDirectoryUpdated(const QString& path)
{
	m_settings->setValue(ROM_PATH_SETTING, path);
	setRomSelector(m_listView);
}

void AlmostTIPb::clearRAM()
{
	QString tiname(TIFilename);
	tiname = tiname.toUpper();
	if (!tiname.isEmpty())
	{
		tiname.replace(QString("ROM"), QString("RAM"));
		tiname = QString("shared/misc/TI/RAM/") + tiname;
		QFile::remove(tiname);
		saveRAM = 0;
		loadROM = 1;
	}
}

int AlmostTIPb::inRecentList(QString path, QString filename)
{
	QString fullpath = path + "/" + filename;
	for (int rec = 0; rec < m_recentStrings.size(); rec++)
	{
		if (QString::compare(fullpath, m_recentStrings[rec], Qt::CaseInsensitive) == 0)
			return rec;
	}
	return -1;
}

void AlmostTIPb::openROM(const QString& rom, const QString& path)
{
	QString ppath;
	if (path == "")
		ppath = m_settings->value(ROM_PATH_SETTING, ROM_PATH_DEFAULT).value<QString>();
	else
		ppath = QString(path);
	int pos = -1;
	if ((pos = inRecentList(ppath, rom)) < 0)
		m_recentStrings.insert(0, ppath + "/" + rom);
	else if (pos > 0)
		m_recentStrings.move(pos, 0);
	if (tiThread)
	{
		strcpy(ProgDir, ppath.toStdString().c_str());
		strcpy(TIFilename, rom.toStdString().c_str());
		loadROM = 1;
	}
	else
	{
		if (!ProgDir)
			ProgDir = new char[256];
		strcpy(ProgDir, ppath.toStdString().c_str());
		strcpy(romname, rom.toStdString().c_str());
		tiThread = new QThread;
		tiWorker = new TIWorker;
		tiWorker->moveToThread(tiThread);
		connect(tiThread, SIGNAL(started()), tiWorker, SLOT(doWork()));
		connect(tiWorker, SIGNAL(finished()), tiThread, SLOT(quit()));
		connect(tiWorker, SIGNAL(finished()), tiWorker, SLOT(deleteLater()));
		connect(tiThread, SIGNAL(finished()), tiThread, SLOT(deleteLater()));
		connect(tiThread, SIGNAL(finished()), this, SLOT(finished()));
		tiThread->start();
		exitMutex.unlock();
	}
}

void AlmostTIPb::finished()
{
	if (tiThread)
		delete tiThread;
	if (exitMutex.tryLock())
	{
		Application::instance()->exit();
	}
}

void AlmostTIPb::thumbnail()
{
	paused = 1;
}

void AlmostTIPb::fullscreen()
{
	paused = 0;
}

void AlmostTIPb::aboutToQuit()
{
	ExitNow = 1;
	paused = 0;
}

void AlmostTIPb::toggleFrameRate()
{
	BPSToggleEffects(0x100);
}

void AlmostTIPb::toggleScanlines()
{
	BPSToggleEffects(0x004);
}

void AlmostTIPb::toggleSoften()
{
	BPSToggleEffects(0x002);
}

void AlmostTIPb::touch(int x, int y)
{
	(*MouseHandler)(x, y, 1);
}

void AlmostTIPb::unTouch(int x, int y)
{
	(*MouseHandler)(x, y, 0);
}

int getROMType(const char* path, int &M)
{
	QString str(path);
	QFileInfo fi(str);
	str = fi.fileName();
	if (QString::compare(str, "TI85.ROM", Qt::CaseInsensitive) == 0)
	{
		M = 0;
		return 0x0;
	}
	if (QString::compare(str, "TI86.ROM", Qt::CaseInsensitive) == 0)
	{
		M = 1;
		return 0x100;
	}
	if (QString::compare(str, "TI82.ROM", Qt::CaseInsensitive) == 0)
	{
		M = 2;
		return 0x200;
	}
	if (QString::compare(str, "TI83.ROM", Qt::CaseInsensitive) == 0)
	{
		M = 3;
		return 0x400;
	}
	if (QString::compare(str, "TI83P.ROM", Qt::CaseInsensitive) == 0)
	{
		M = 4;
		return 0x800;
	}
	return -1;
}

