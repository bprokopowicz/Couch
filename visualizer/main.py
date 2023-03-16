from PyQt5 import QtWidgets
from pyqtgraph import PlotWidget, plot
from numpy import arange
import numpy
import pyqtgraph as pg
import sys 
import os
import time

def f(n):
    return numpy.abs(n)

class MainWindow(QtWidgets.QMainWindow):

    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)
        self.graphWidget = pg.PlotWidget()
        self.setCentralWidget(self.graphWidget)

    def showHalls(self):
        leftTopXs=[-2,1]
        leftTopYs=[1,1]
        leftBottomXs=[-2,0]
        leftBottomYs=[0,0]
        lowerLeftXs=[0,0]
        lowerLeftYs=[0,-2]
        lowerRightXs=[1,1]
        lowerRightYs=[1,-2]
        self.graphWidget.plot(leftTopXs, leftTopYs, pen=pg.mkPen('r', width=3))
        self.graphWidget.plot(leftBottomXs, leftBottomYs, pen=pg.mkPen('r', width=3))
        self.graphWidget.plot(lowerLeftXs, lowerLeftYs, pen=pg.mkPen('r', width=3))
        self.graphWidget.plot(lowerRightXs, lowerRightYs, pen=pg.mkPen('r', width=3))

    def showShape(self, xs, ys):
        xs.append(xs[0])
        ys.append(ys[0])
        self.graphWidget.plot(xs, ys)

def main():
    app = QtWidgets.QApplication(sys.argv)
    main = MainWindow()
    main.showHalls()
    main.show()

    for line in sys.stdin:
    # x1,x2,x3,x4:y1,y2,y3,y4
        xsAndYs = line.split(":")
        xs = list(map(float,xsAndYs[0].split(",")))
        ys = list(map(float,xsAndYs[1].split(",")))
        main.showShape(xs, ys)
        main.show()

    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
