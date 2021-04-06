#include "error_handling.h"

#include <QMessageLogContext>
#include <QString>
#include <QDateTime>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
   Q_UNUSED(context);

   QString dt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
   QString txt = QString("[%1] ").arg(dt);

   switch (type)
   {

    case QtDebugMsg:
       txt += QString("{Debug} \t\t %1").arg(msg);
       break;
    case QtWarningMsg:
       txt += QString("{Warning} \t %1").arg(msg);
       break;
    case QtCriticalMsg:
       txt += QString("{Critical} \t %1").arg(msg);
       break;
    case QtFatalMsg:
       txt += QString("{Fatal} \t\t %1").arg(msg);
       abort();
       break;
    case QtInfoMsg:
      txt+= QString("{Info} \t\t %1").arg(msg);
      break;
    default:
      txt+= QString("Unhandeled message");
      break;
   }

   QFile outFile("debug.log");
   outFile.open(QIODevice::WriteOnly | QIODevice::Append);

   QTextStream textStream(&outFile);
   textStream << txt << Qt::endl;
}
