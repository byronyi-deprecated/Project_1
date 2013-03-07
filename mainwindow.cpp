#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    painter = new Painter(this);
    setCentralWidget(painter);
    createActions();
    createToolBars();
    createMenus();
    createStatusBar();
    createRightButtonSettings();

    readSettings();

    setWindowIcon(QIcon(":/images/icon.jpg"));
    setCurrentFile("");
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(okToContinue())
    {
        writeSettings();
        event->accept();
    }
    else event->ignore();
}

void MainWindow::newFile()
{
    if(okToContinue() && resize())
    {
        painter->clear();
        setCurrentFile("");
    }
}

void MainWindow::open()
{
      if(okToContinue())
      {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open image"), ".",
                                                        tr("bitmap (*.bmp)"));
        if(!fileName.isEmpty())
            loadFile(fileName);
      }
}

bool MainWindow::save()
{
    if(painter->isNull()) return true;
    if(curFile.isEmpty()) return saveAs();
    return saveFile(curFile);
}

bool MainWindow::saveAs()
{
    if(painter->isNull()) return true;
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save image"), ".",
                                                    tr("bitmap (*.bmp)"));
    if(fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Painter"),
                    tr("<h2>Painter 1.0</h2>"
                    "<p>Copyright &copy; Byron 2013"
                    "<p>Painter is a small course"
                    "<p>project of COMP2012H."));
}

void MainWindow::openRecentFile()
{
    if(okToContinue())
    {
        QAction *action = qobject_cast<QAction *>(sender());
        if(action)
            loadFile(action->data().toString());
    }
}

void MainWindow::clearAll()
{
    if(painter->isNull()) return;
    int r = QMessageBox::warning(this, tr("Painter"), tr("Do you want to clear the image\n"
                                                         "with the background color?"),
                                 QMessageBox::Yes | QMessageBox::Cancel);
    if(r == QMessageBox::Yes) painter->clear();
    if(r == QMessageBox::Cancel) return;
}

bool MainWindow::resize()
{
    bool ok;
    int width = QInputDialog::getInt(this, tr("Painter"),
                                         tr("Please enter the width"
                                            "(less than 1024)"),
                                     painter->curSize().width(), 0,
                                     1024, 1, &ok);
    if(!ok) return ok;
    int height = QInputDialog::getInt(this, tr("Painter"),
                                         tr("Please enter the height"
                                            "(less than 1024)"),
                                      painter->curSize().height(), 0,
                                      1024, 1, &ok);
    if(!ok) return ok;
    setWindowModified(painter->setSize(QSize(width, height)));
    return ok;
}

void MainWindow::zoomIn()
{
    double zoomFactor = painter->curZoomFactor() * 1.25;
    painter->setZoomFactor(zoomFactor);
}

void MainWindow::zoomOut()
{
    double zoomFactor = painter->curZoomFactor() * 0.8;
    painter->setZoomFactor(zoomFactor);
}

void MainWindow::changeFColor()
{
    painter->setFColor(QColorDialog::getColor(painter->curFColor(), this,
                                              tr("Choose the foreground color"),
                                              QColorDialog::ShowAlphaChannel));
}

void MainWindow::changeBColor()
{
    painter->setBColor(QColorDialog::getColor(painter->curBColor(), this,
                                              tr("Choose the background color"),
                                              QColorDialog::ShowAlphaChannel));
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::createActions()
{
    //File menu
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new_icon.bmp"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new image"));
    connect(newAction, SIGNAL(triggered()),
            this, SLOT(newFile()));

    openAction = new QAction(tr("&Open..."), this);
    openAction->setIcon(QIcon(":/images/open_icon.bmp"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a image"));
    connect(openAction, SIGNAL(triggered()),
            this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save_icon.bmp"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the current image"));
    connect(saveAction, SIGNAL(triggered()),
            this, SLOT(save()));

    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setIcon(QIcon(":/images/save_icon.bmp"));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save the current image as..."));
    connect(saveAsAction, SIGNAL(triggered()),
            this, SLOT(saveAs()));

    for(unsigned int i = 0; i < MaxRecentFiles; ++i)
    {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()),
                this, SLOT(openRecentFile()));
    }

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    //Edit Menu
    unDoAction = new QAction(tr("&Undo"), this);
    unDoAction->setIcon(QIcon(":/images/undo_icon.bmp"));
    unDoAction->setShortcut(QKeySequence::Undo);
    unDoAction->setStatusTip(tr("Undo the last modification"));
    connect(unDoAction, SIGNAL(triggered()),
            painter, SLOT(unDo()));

    reDoAction = new QAction(tr("&Redo"), this);
    reDoAction->setIcon(QIcon(":/images/redo_icon.bmp"));
    reDoAction->setShortcut(QKeySequence::Redo);
    reDoAction->setStatusTip(tr("Redo the last modification undone"));
    connect(reDoAction, SIGNAL(triggered()),
            painter, SLOT(reDo()));

    clearAllAction = new QAction(tr("Clear All"), this);
    clearAllAction->setIcon(QIcon(":/images/clearall_icon.bmp"));
    clearAllAction->setStatusTip(tr("Clear the image"));
    connect(clearAllAction, SIGNAL(triggered()),
            this, SLOT(clearAll()));

    resizeAction = new QAction(tr("Resize"), this);
    resizeAction->setIcon(QIcon(":/images/resize_icon.bmp"));
    resizeAction->setStatusTip(tr("Resize the image"));
    connect(resizeAction, SIGNAL(triggered()),
            this, SLOT(resize()));

    //View Menu
    zoomInAction = new QAction(tr("Zoom in"), this);
    zoomInAction->setStatusTip(tr("Zoom in the image"));
    connect(zoomInAction, SIGNAL(triggered()),
            this, SLOT(zoomIn()));

    zoomOutAction = new QAction(tr("Zoom out"), this);
    zoomOutAction->setStatusTip(tr("Zoom out the image"));
    connect(zoomOutAction, SIGNAL(triggered()),
            this, SLOT(zoomOut()));

    //Help Menu
    aboutAction = new QAction(tr("About"), this);
    connect(aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()),
            this, SLOT(aboutQt()));

    //Toolbar buttons
    changeFColorAction = new QAction(QIcon(":/images/fcolor_icon.bmp"),
                            tr(""), this);
    changeFColorAction->setStatusTip(tr("Set Foreground Color"));
    connect(changeFColorAction, SIGNAL(triggered()),
            this, SLOT(changeFColor()));

    changeBColorAction = new QAction(QIcon(":/images/bcolor_icon.bmp"),
                            tr(""), this);
    changeBColorAction->setStatusTip(tr("Set Background Color"));
    connect(changeBColorAction, SIGNAL(triggered()),
            this, SLOT(changeBColor()));

    setPen = new QToolButton;
    setPen->setIcon(QIcon(":/images/pen_icon.bmp"));
    setPen->setStatusTip(tr("Pen"));
    setPen->setCheckable(true);

    setLine = new QToolButton;
    setLine->setIcon(QIcon(":/images/line_icon.bmp"));
    setLine->setStatusTip(tr("Line"));
    setLine->setCheckable(true);

    setRect = new QToolButton;
    setRect->setIcon(QIcon(":/images/rect_icon.bmp"));
    setRect->setStatusTip(tr("Rectangle"));
    setRect->setCheckable(true);

    setEraser = new QToolButton;
    setEraser->setIcon(QIcon(":/images/eraser_icon.bmp"));
    setEraser->setStatusTip(tr("Eraser"));
    setEraser->setCheckable(true);

    setPaintTool = new QButtonGroup(this);
    setPaintTool->addButton(setPen, 1);
    setPaintTool->addButton(setLine, 2);
    setPaintTool->addButton(setRect, 3);
    setPaintTool->addButton(setEraser, 4);
    setPaintTool->setExclusive(true);
    connect(setPaintTool, SIGNAL(buttonClicked(int)),
            painter, SLOT(setTool(int)));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    separatorAction = fileMenu->addSeparator();
    for(int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(unDoAction);
    editMenu->addAction(reDoAction);
    editMenu->addAction(clearAllAction);
    editMenu->addAction(resizeAction);

    viewMenu = menuBar()->addMenu(tr("&View"));
    toolBar->toggleViewAction()->setText(tr("&Tool Bar"));
    viewMenu->addAction(toolBar->toggleViewAction());
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
    toolBar = new QToolBar;
    addToolBar(toolBar);
    toolBar->addAction(newAction);
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addSeparator();
    toolBar->addAction(unDoAction);
    toolBar->addAction(reDoAction);
    toolBar->addAction(clearAllAction);
    toolBar->addAction(resizeAction);
    toolBar->addSeparator();
    toolBar->addAction(changeFColorAction);
    toolBar->addAction(changeBColorAction);
    toolBar->addSeparator();
    toolBar->addWidget(setPen);
    toolBar->addWidget(setLine);
    toolBar->addWidget(setRect);
    toolBar->addWidget(setEraser);
}

void MainWindow::createStatusBar()
{
    locationLabel = new QLabel("0, 0");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    zoomFactorLabel = new QLabel(tr("Zoom factor") + ": 1.0");

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(zoomFactorLabel);
    connect(painter, SIGNAL(cursorChanged()),
            this, SLOT(updateStatusBar()));
    connect(painter, SIGNAL(zoomFactorChanged()),
            this, SLOT(updateStatusBar()));
    updateStatusBar();
}

void MainWindow::createRightButtonSettings()
{
    connect(painter, SIGNAL(penSettings()),
            this, SLOT(penSettings()));
    connect(painter, SIGNAL(lineSettings()),
            this, SLOT(lineSettings()));
    connect(painter, SIGNAL(rectSettings()),
            this, SLOT(rectSettings()));
    connect(painter, SIGNAL(eraserSettings()),
            this, SLOT(eraserSettings()));
}

void MainWindow::updateStatusBar()
{
    QString pos = tr("Cursor location: ");
    pos += QString::number(painter->curXPos());
    pos += ", ";
    pos += QString::number(painter->curYPos());
    locationLabel->setText(pos);

    QString zoomFactor = tr("Zoom factor =");
    zoomFactor += QString::number(painter->curZoomFactor());
    zoomFactorLabel->setText(zoomFactor);
}

void MainWindow::readSettings()
{
    QSettings settings("Byron", "Painter");
    restoreGeometry(settings.value("geometry").toByteArray());
    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();
}

void MainWindow::writeSettings()
{
    QSettings settings("Byron", "Painter");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", recentFiles);
}

bool MainWindow::okToContinue()
{
    if(isWindowModified())
    {
        int r = QMessageBox::warning(this, tr("Painter"), tr("This image has been modified.\n"
                                                             "Do you want to save your changes?"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(r == QMessageBox::Yes) return save();
        if(r == QMessageBox::Cancel) return false;
    }
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    if(!painter->readFile(fileName))
    {
        statusBar()->showMessage(tr("Loading cancelled"), 2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("Image loaded"), 2000);
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
    if(!painter->writeFile(fileName))
    {
        statusBar()->showMessage(tr("Saving cancelled"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);
    QString shownName = tr("Untitled");
    if(!curFile.isEmpty())
    {
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Painter")));
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);
    while(i.hasNext())
    {
        if(!QFile::exists(i.next()))
            i.remove();
    }
    for(int j = 0; j < MaxRecentFiles; ++j)
    {
        if(j < recentFiles.count())
        {
            QString text = tr("&%1 %2")
                    .arg(j+1).arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }
        else
            recentFileActions[j]->setVisible(false);
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::penSettings()
{
    PenDialog penDialog(this);

    connect(&penDialog, SIGNAL(penSettings(int,Qt::PenCapStyle)),
            painter, SLOT(penSettings(int,Qt::PenCapStyle)));

    penDialog.exec();
}

void MainWindow::lineSettings()
{
    LineDialog lineDialog(this);

    connect(&lineDialog, SIGNAL(lineSettings(Qt::PenStyle,Qt::PenCapStyle,bool,int)),
            painter, SLOT(lineSettings(Qt::PenStyle,Qt::PenCapStyle,bool,int)));

    lineDialog.exec();
}

void MainWindow::rectSettings()
{
      RectDialog rectDialog(this);

      connect(&rectDialog, SIGNAL(rectSettings(int,Qt::BrushStyle,Qt::PenStyle,Qt::PenJoinStyle,bool,int)),
              painter, SLOT(rectSettings(int,Qt::BrushStyle,Qt::PenStyle,Qt::PenJoinStyle,bool,int)));

      rectDialog.exec();
}

void MainWindow::eraserSettings()
{
    EraserDialog eraserDialog(this);

    connect(&eraserDialog, SIGNAL(eraserSettings(int)),
            painter, SLOT(eraserSettings(int)));

    eraserDialog.exec();
}
