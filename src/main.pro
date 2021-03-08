QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 \
  release \
  static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    Navigator.cpp \
    Welcome.cpp \
    "supported_db/master-widget/TableWidget_Master.cpp" \
    "supported_db/master-widget/Overview_Master.cpp" \
    "supported_db/SQLITE3/TableWidget_SQLITE3.cpp" \
    "supported_db/SQLITE3/Overview_SQLITE3.cpp"

HEADERS += \
    Navigator.h \
    Welcome.h \
    "supported_db/master-widget/TableWidget_Master.h" \
    "supported_db/master-widget/Overview_Master.h" \
    "supported_db/SQLITE3/TableWidget_SQLITE3.h" \
    "supported_db/SQLITE3/Overview_SQLITE3.h"

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
