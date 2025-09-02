#include <QMainWindow>
class QTextEdit;
class QWidget;
class QFrame;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QTabWidget;
class QFile;
class QLabel;
class QRegularExpression;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private:
    QWidget *contentWidget;
    QTextEdit *pageEdit;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *tabLayout;
    QVBoxLayout *mainLayout;
    QTabWidget *tabWidget;
    QWidget *statusBar;
    QLabel *statusLabel;
    QWidget *currentTab;
    // Buttons

    QPushButton *newButton;
    QPushButton *saveButton;
    QPushButton *loadButton;

    void createTab();
    void saveCurrentTabContent();
    void loadNoteFromFile(const QString &filePath);
    void statusBarMessage(const QString &message);
    void updateWordCount(QTextEdit *editor);
};
