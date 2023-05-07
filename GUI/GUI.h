#pragma once

#include <qwidget.h>
#include "../Service/Service.h"
#include "../Service/UserService.h"
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qvboxlayout>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <qmodelindex>
#include <qlabel.h>
#include <qmessagebox.h>
#include <qshortcut>
#include "../TrenchTableModel.h"
//#include "../TableViewWidget.h"
#include <QHeaderView>
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif
#include <QtCharts/qchart.h>

class GUI : public QWidget
{
private:
	Service& service;
	UserService& userService;

	QListWidget* trenchCoatsWidget;
	QListWidget* shoppingBasketWidget;
	QListWidget* addToBasketWidget;

	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QPushButton* undoButton;
	QPushButton* redoButton;
	QShortcut* undoShortcut;
	QShortcut* redoShortcut;


	QPushButton* addToBasketButton;

	QPushButton* accessButton;
	QPushButton* nextButton;

	QLineEdit* sizeWidget, * colorWidget, * quantityWidget, * priceWidget, * photographWidget;
	QLineEdit* filterLine;

	QLabel* basketPrice;

	QPushButton* tableButton;
	TrenchModel* model;

	void bindGUI();
	void populate();
	void populateShoppingBasket();
	void initFields();
	int getSelectedIndex();
	void connectSignalsWithSlots();
	void showInformation(const string& info);
	void showError(const string& err);

	void addTrenchCoat();
	void deleteTrenchCoat();
	void updateTrenchCoat();
	void addToBasket();
	void accessPhoto();
	void nextTrenchCoat();
	void filterPrice();

	void undo();
	void redo();
	void displayTable();
public:
	GUI(Service& service, UserService& userService);
};