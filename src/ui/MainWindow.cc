#include "MainWindow.h"
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QApplication>
#include <QStyle>
#include <QLabel>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      contentWidget(new QWidget(this)),
      mainLayout(new QVBoxLayout(contentWidget))
{
    // Botones
    saveButton = new QPushButton("");
    saveButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton));
    saveButton->setToolTip("Save Note");

    loadButton = new QPushButton("");
    loadButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton));
    loadButton->setToolTip("Load Note");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(loadButton);
    mainLayout->addLayout(buttonLayout);

    // TabWidget
    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    mainLayout->addWidget(tabWidget);

    // Botón + en la esquina
    newButton = new QPushButton("+");
    newButton->setToolTip("New Note");
    newButton->setFixedSize(30, 30);
    QWidget *corner = new QWidget(this);
    QHBoxLayout *cornerLayout = new QHBoxLayout(corner);
    cornerLayout->setContentsMargins(0, 0, 0, 0);
    cornerLayout->setSpacing(0);
    cornerLayout->addWidget(newButton);
    tabWidget->setCornerWidget(corner);

    // Status bar
    statusBar = new QWidget(this);
    statusBar->setFixedHeight(20);
    statusLabel = new QLabel("0 words", statusBar);
    QHBoxLayout *statusLayout = new QHBoxLayout(statusBar);
    statusLayout->setContentsMargins(5, 0, 5, 0);
    statusLayout->addWidget(statusLabel);
    mainLayout->addWidget(statusBar);

    setCentralWidget(contentWidget);

    // Conexiones
    connect(newButton, &QPushButton::clicked, this, &MainWindow::createTab);
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, [this](int index)
            {
        QWidget *tab = tabWidget->widget(index);
        if (!tab) return;
        QTextEdit *editor = tab->findChild<QTextEdit*>();
        if (!editor) return;

        bool hasContent = !editor->toPlainText().isEmpty();
        tabWidget->removeTab(index);

        if (index == 0 && hasContent) createTab();
        if (tabWidget->count() == 0) createTab(); });

    connect(tabWidget, &QTabWidget::currentChanged, this, [this](int index)
            {
        QWidget *tab = tabWidget->widget(index);
        if (!tab) return;
        QTextEdit *editor = tab->findChild<QTextEdit*>();
        if (editor) updateWordCount(editor); });

    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveCurrentTabContent);
    connect(loadButton, &QPushButton::clicked, this, [this]()
            {
        QString fileName = QFileDialog::getOpenFileName(
            this, "Load Note", "notes/", "Text Files (*.txt);;doNote Files (*.doNote);;All Files (*)");
        if (!fileName.isEmpty()) loadNoteFromFile(fileName); });

    // Cargar notas existentes
    QDir dir("data/notes");
    if (!dir.exists())
        dir.mkpath(".");
    QStringList files = dir.entryList(QStringList() << "*.doNote" << "*.txt", QDir::Files);
    for (const QString &fileName : files)
        loadNoteFromFile(dir.filePath(fileName));

    if (tabWidget->count() == 0)
        createTab();
}

void MainWindow::createTab()
{
    QWidget *tab = new QWidget;
    QTextEdit *editor = new QTextEdit;
    editor->setPlaceholderText("Type your notes here...");

    // Conectar el editor al conteo de palabras
    connect(editor, &QTextEdit::textChanged, this, [this, editor]()
            { updateWordCount(editor); });

    QVBoxLayout *tabLayout = new QVBoxLayout(tab);
    tabLayout->addWidget(editor);

    int index = tabWidget->addTab(tab, QString("Tab %1").arg(tabWidget->count() + 1));
    tabWidget->setCurrentIndex(index);

    // Actualizar el conteo al crear
    updateWordCount(editor);
}

void MainWindow::saveCurrentTabContent()
{
    int currentIndex = tabWidget->currentIndex();
    if (currentIndex != -1)
    {
        currentTab = tabWidget->widget(currentIndex);
        QTextEdit *editor = currentTab->findChild<QTextEdit *>();
        if (editor)
        {
            QString content = editor->toPlainText();
            QString fileName = QFileDialog::getSaveFileName(
                this,
                "Save Note",
                "",
                "Text Files (*.txt);;doNote Files (*.doNote);;All Files (*)");

            if (fileName.isEmpty())
                return;
            QFile file(fileName);
            if (file.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream out(&file);
                out << content;
                file.close();
            }
        }
    }
}

void MainWindow::loadNoteFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.exists())
        return;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString content = in.readAll();
        file.close();

        createTab();

        QWidget *currentTab = tabWidget->currentWidget();
        if (currentTab)
        {
            QTextEdit *editor = currentTab->findChild<QTextEdit *>();
            if (editor)
            {
                editor->setPlainText(content);
            }
        }

        tabWidget->setTabText(tabWidget->currentIndex(), QFileInfo(filePath).fileName());
    }
}

void MainWindow::statusBarMessage(const QString &message)
{
    statusBar = new QWidget(this);
    statusBar->setFixedHeight(20);

    mainLayout->addWidget(statusBar);
}

void MainWindow::updateWordCount(QTextEdit *editor)
{
    if (!editor)
        return;

    QString text = editor->toPlainText();
    int wordCount = text.length();

    statusLabel->setText(QString("%1 words").arg(wordCount));
}
