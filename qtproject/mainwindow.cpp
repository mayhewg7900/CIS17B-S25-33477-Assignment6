#include "mainwindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMessageBox>
#include <QString>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Defining the horizontal box as well as the contents for the ID input
    idBox = new QHBoxLayout;
    idLabel = new QLabel("Enter Item ID: ", this);
    idInput = new QLineEdit(this);
    idBox->addWidget(idLabel);
    idBox->addWidget(idInput);

    // Defining the horizontal box for the description input
    descBox = new QHBoxLayout;
    descLabel = new QLabel("Enter Item Desc: ", this);
    descInput = new QLineEdit(this);
    descBox->addWidget(descLabel);
    descBox->addWidget(descInput);

    // Defining the horizontal box for the location input
    locBox = new QHBoxLayout;
    locLabel = new QLabel("Enter Item Location: ", this);
    locInput = new QLineEdit(this);
    locBox->addWidget(locLabel);
    locBox->addWidget(locInput);

    // Hiding all created labels until in use
    idLabel->hide();
    idInput->hide();

    descLabel->hide();
    descInput->hide();

    locLabel->hide();
    locInput->hide();


    // Set up central widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Test button
    QPushButton *button = new QPushButton("Click me", this);
    layout->addWidget(button);

    // Adding item button initialization
    addButton = new QPushButton("Add Item", this);
    layout->addWidget(addButton);

    // Adding confirm button initialization
    confirmButton = new QPushButton("Confirm", this);
    confirmButton->hide();
    layout->addWidget(confirmButton);

    // Adding to layout
    layout->addLayout(idBox);
    layout->addLayout(descBox);
    layout->addLayout(locBox);

    // Adding an item list widget
    itemList = new QListWidget(this);
    layout->addWidget(itemList);

    // Setting the central widget
    setCentralWidget(centralWidget);

    // Defining the "File" menu bar and assigning it the exitAction
    fileMenu = menuBar()->addMenu("File");
    exitAction = new QAction("Exit", this);
    fileMenu->addAction(exitAction);

    // Defining the "Help" menu bar and assigning it the aboutAction
    helpMenu = menuBar()->addMenu("Help");
    aboutAction = new QAction("About", this);
    helpMenu->addAction(aboutAction);

    // Specific to macOS, for debugging
    menuBar()->setNativeMenuBar(false);


    // Connecting the exit action upon file menu hover
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    // Optional: connect signals/slots
    connect(button, &QPushButton::clicked, this, []() {
        qDebug("Button clicked!");
    });

    // Adding the onAddItemClicked event upon addButton click
    connect(addButton, &QPushButton::clicked, this, [this]() {
        onAddItemClicked();
    });

    // Confirm button functionality on click, adding a new item
    connect(confirmButton, &QPushButton::clicked, this, [this]() {
        idLabel->hide();
        idInput->hide();

        descLabel->hide();
        descInput->hide();

        locLabel->hide();
        locInput->hide();

        confirmButton->hide();

        auto newItem_ptr = std::make_shared<StoredItem>(idInput->text().toStdString(),descInput->text().toStdString(),locInput->text().toStdString());
        manager.addItem(newItem_ptr);

        itemList->addItem(idInput->text());
        QListWidgetItem *item = itemList->item(itemCounter);
        itemCounter++;
        item->setText(idInput->text());
    });

    // About action, displaying a message box
    connect(aboutAction, &QAction::triggered, this, []() {
        QMessageBox::about(nullptr, "About", "Made by Matthew Garamone for CIS-17B");
    });
}

// Main window deconstructor
MainWindow::~MainWindow()
{
}

// Added item click event
void MainWindow::onAddItemClicked() {
    // Your logic here
    qDebug("Add Item clicked");
    idLabel->show();
    idInput->show();

    descLabel->show();
    descInput->show();

    locLabel->show();
    locInput->show();

    confirmButton->show();
}

// Find item click event
void MainWindow::onFindItemClicked() {
    // Your logic here
    qDebug("Find Item clicked");
}

// Remove item click event
void MainWindow::onRemoveItemClicked() {
    // Your logic here
    qDebug("Remove Item clicked");
}

// Message for duplicate item detection, not yet implemented
void MainWindow::duplicateItemMessage(const QString& message) {
    QMessageBox::warning(this, "Duplicate Item Detected", message);
}
