#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QHBoxLayout>
#include "StorageManager.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slotted events prototypes
    void onAddItemClicked();
    void onFindItemClicked();
    void onRemoveItemClicked();
    void duplicateItemMessage(const QString& message);

signals:
    // Signals prototypes
    void duplicateItemWarning(const QString& message);

private:
    // Declaring much of the QT widgets and objects that are in use
    QLabel *idLabel, *descLabel, *locLabel;
    QHBoxLayout *idBox, *descBox, *locBox;
    QLineEdit *idInput, *descInput, *locInput;
    QLineEdit *findIdInput, *removeIdInput;
    QListWidget *itemList;
    QPushButton *addButton, *findButton, *removeButton, *confirmButton;
    QMenu *fileMenu, *helpMenu;
    QAction *exitAction, *aboutAction;

    // Delcaring the StorageManager class
    StorageManager manager;

    // Counter intended for access to items on the list, as well as iterating through it.
    int itemCounter = 0;
};

#endif // MAINWINDOW_H
