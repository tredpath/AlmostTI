// Default empty project template
#include "ATI85/TI85.h"
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include <QLocale>
#include <QTranslator>
#include "AlmostTIPb.hpp"
#include "ActiveFrame.hpp"

#include <sys/stat.h>

using namespace bb::cascades;

extern QThread* tiThread;

int main(int argc, char **argv)
{
    // this is where the server is started etc
    Application app(argc, argv);

    // localization support
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString( "AlmostTI_pb_%1" ).arg( locale_string );
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator( &translator );
    }

	mkdir("shared/misc/TI", 0777);
	mkdir("shared/misc/TI/ROM/", 0777);
	mkdir("shared/misc/TI/RAM/", 0777);

    app.setCover(new ActiveFrame());

    AlmostTIPb* tipb = new AlmostTIPb(&app);

    // we complete the transaction started in the app constructor and start the client event loop here
    int retval = Application::exec();

    fprintf(stderr, "Closing main thread\n");

    if (exitMutex.tryLock())
    {
    	ExitNow = 1;
    	delete tipb;
		if (!tiThread->wait(2500)) {
			app.extendTerminationTimeout();
			tiThread->quit();
			tiThread->wait();
		}
    }
    else
    	delete tipb;
    return retval;
    // when loop is exited the Application deletes the scene which deletes all its children (per qt rules for children)
}
