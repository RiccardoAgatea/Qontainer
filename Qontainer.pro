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
    Order.cpp \
    Drink.cpp \
    Food.cpp \
    MeatBased.cpp \
    Steak.cpp \
    Hamburger.cpp \
    Sandwich.cpp \
    Appetizer.cpp \
    Model.cpp \
    Dessert.cpp \
    Analcoholic.cpp \
    Coffee.cpp \
    Alcoholic.cpp \
    Liquor.cpp \
    Beer.cpp \
    Wine.cpp \
    Cocktail.cpp \
    UnavailableFile.cpp \
    UnknownType.cpp \
	OrderWidget.cpp \
	NullPtrExcept.cpp \
	AddOrderDialog.cpp \
    View.cpp \
    EditOrderDialog.cpp \
    SearchDialog.cpp \
	SearchView.cpp \
    InvalidFile.cpp

HEADERS += \
	Container.h \
	DeepPtr.h \
	InvalidIterator.h \
	EmptyContainer.h \
    Order.h \
    Drink.h \
    Food.h \
    MeatBased.h \
    Steak.h \
    Hamburger.h \
    Sandwich.h \
    Appetizer.h \
    Model.h \
    Dessert.h \
    Analcoholic.h \
    Coffee.h \
    Alcoholic.h \
    Liquor.h \
    Beer.h \
    Wine.h \
    Cocktail.h \
    ContainerExceptions.h \
    UnavailableFile.h \
    UnknownType.h \
	OrderWidget.h \
	NullPtrExcept.h \
    UniformInterface.h \
	AddOrderDialog.h \
    View.h \
    EditOrderDialog.h \
    SearchDialog.h \
	SearchView.h \
    InvalidFile.h

RESOURCES += \
    Media.qrc
