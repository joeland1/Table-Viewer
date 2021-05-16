QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 \
  release \
  static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#SOURCES += $$files(*.cpp, true)
#SOURCES += $$files(*.c, true)
#HEADERS += $$files(*.h, true)

SOURCES += \
    main.cpp \
    Navigator.cpp \
    Welcome.cpp \
    "supported_db/master-widget/TableWidget_Master.cpp" \
    "supported_db/master-widget/Overview_Master.cpp" \
    "supported_db/SQLITE3/TableWidget_SQLITE3.cpp" \
    "supported_db/SQLITE3/Overview_SQLITE3.cpp" \
    "error_handling.cpp"

SQLITE3_FILE = "libs/SQLITE3/sqlite3.c"
file.input = SQLITE3_FILE
file.dependency_type = TYPE_C
file.variable_out = OBJECTS
file.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
file.commands = $${QMAKE_CXX} $(CXXFLAGS) -O0 $(INCPATH) -c ${QMAKE_FILE_IN} -DSQLITE_ENABLE_UPDATE_DELETE_LIMIT -o ${QMAKE_FILE_OUT}  # Note the -O0
QMAKE_EXTRA_COMPILERS += file

HEADERS += \
    Navigator.h \
    Welcome.h \
    "supported_db/master-widget/TableWidget_Master.h" \
    "supported_db/master-widget/Overview_Master.h" \
    "supported_db/SQLITE3/TableWidget_SQLITE3.h" \
    "supported_db/SQLITE3/Overview_SQLITE3.h" \
    "libs/SQLITE3/sqlite3.h" \
    "error_handling.h"



FORMS +=


INCLUDEPATH +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

TARGET = "TableViewer"
