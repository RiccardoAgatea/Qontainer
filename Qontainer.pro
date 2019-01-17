#-------------------------------------------------
#
# Project created by QtCreator 2018-12-06T14:46:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qontainer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
	main.cpp \
	InvalidIterator.cpp \
	EmptyContainer.cpp \
	MenuItem.cpp \
	Bevanda.cpp \
	BevandaAlcolica.cpp \
	Liquore.cpp \
	Cocktail.cpp \
	Pietanza.cpp

HEADERS += \
	Container.h \
	DeepPtr.h \
	InvalidIterator.h \
	CustomExceptions.h \
	EmptyContainer.h \
	MenuItem.h \
	Bevanda.h \
	BevandaAlcolica.h \
	Liquore.h \
	Cocktail.h \
	Pietanza.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
	- Delete before submitting \
	- Delete before submitting
