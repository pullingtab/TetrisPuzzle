#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T19:14:32
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = TetrisPuzzle
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    piece.cpp \
    squigglepiece.cpp \
    utility.cpp \
    puzzlepad.cpp \
    reversesquigglepiece.cpp \
    lpiece.cpp \
    reverselpiece.cpp \
    squarepiece.cpp \
    linepiece.cpp \
    tpiece.cpp \
    DisduplicateDecorator.cpp

HEADERS += \
    piece.h \
    squigglepiece.h \
    utility.h \
    puzzlepad.h \
    reversesquigglepiece.h \
    lpiece.h \
    reverselpiece.h \
    squarepiece.h \
    linepiece.h \
    tpiece.h \
	DisduplicateDecorator.h \

CONFIG += C++11
