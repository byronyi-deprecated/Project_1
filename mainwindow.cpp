#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createToolBars();
    createMenus();
    createStatusBar();

    readSettings();

    setWindowIcon(QIcon(":/images/icon.png"));
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
    if(okToContinue())
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
       if(curFile.isEmpty()) return saveAs();
       else
            return saveFile(curFile);
}

bool MainWindow::saveAs()
{
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
//left to do
void MainWindow::unDo()
{

}
//left to do
void MainWindow::reDo()
{

}
//left to do
void MainWindow::clearAll()
{

}
//left to do
void MainWindow::resize()
{

}
//left to do
void MainWindow::zoomIn()
{

}
//left to do
void MainWindow::zoomOut()
{

}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::createActions()
{
    //File menu
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new image"));
    connect(newAction, SIGNAL(triggered()),
            this, SLOT(newFile()));

    openAction = new QAction(tr("&Open..."), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a image"));
    connect(openAction, SIGNAL(triggered()),
            this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the current image"));
    connect(saveAction, SIGNAL(triggered()),
            this, SLOT(save()));

    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setIcon(QIcon(":/images/saveAs.png"));
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

    closeAction = new QAction(tr("&Close"), this);
    closeAction->setStatusTip(tr("To be implemented"));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    //Edit Menu
    unDoAction = new QAction(tr("&Undo"), this);
    unDoAction->setIcon(QIcon(":/images/unDo.png"));
    unDoAction->setShortcut(QKeySequence::Undo);
    unDoAction->setStatusTip(tr("Undo the last modification"));
    connect(unDoAction, SIGNAL(triggered()),
            this, SLOT(unDo()));

    reDoAction = new QAction(tr("&Redo"), this);
    reDoAction->setIcon(QIcon(":/images/reDo.png"));
    reDoAction->setShortcut(QKeySequence::Redo);
    reDoAction->setStatusTip(tr("Redo the last modification undone"));
    connect(reDoAction, SIGNAL(triggered()),
            this, SLOT(reDo()));

    clearAllAction = new QAction(tr("Clear All"), this);
    clearAllAction->setIcon(QIcon(":/images/clearAll.png"));
    clearAllAction->setStatusTip(tr("Clear the image"));
    connect(clearAllAction, SIGNAL(triggered()),
            this, SLOT(clearAll()));

    resizeAction = new QAction(tr("Resize"), this);
    resizeAction->setIcon(QIcon(":/images/resize.png"));
    resizeAction->setStatusTip(tr("Resize the image"));
    connect(resizeAction, SIGNAL(triggered()),
            this, SLOT(resize()));

    //View Menu
    zoomInAction = new QAction(tr("Zoom in"), this);
    zoomInAction->setIcon(QIcon(":/images/zoomIn.png"));
    zoomInAction->setStatusTip(tr("Zoom in the image"));
    connect(zoomInAction, SIGNAL(triggered()),
            this, SLOT(zoomIn()));

    zoomOutAction = new QAction(tr("Zoom out"), this);
    zoomOutAction->setIcon(QIcon(":/images/zoomOut.png"));
    zoomOutAction->setStatusTip(tr("Zoom out the image"));
    connect(zoomOutAction, SIGNAL(triggered()),
            this, SLOT(zoomOut()));


    //Help Menu
    aboutAction = new QAction(tr("About"), this);
    connect(aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setIcon(QIcon(":/images/qt.png"));
    connect(aboutQtAction, SIGNAL(triggered()),
            this, SLOT(aboutQt()));

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
}
//left to do
void MainWindow::createStatusBar()
{
    locationLabel = new QLabel("w999");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    statusBar()->addWidget(locationLabel);
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
