#include "GUI.h"
#include <qlabel.h>
#include <qlineargradient>
#include <qcolor>
#include <qpalette.h>
#include <qkeysequence.h>
#include <QtCharts/qabstractaxis.h>
#include <qtableview.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/QBarSeries.h>
#include <QtCharts/QBarSet.h>
#include <QtCharts/QBarCategoryAxis.h>
#include <QtCharts/QValueAxis.h>

void GUI::bindGUI()
{
	trenchCoatsWidget = new QListWidget();
	shoppingBasketWidget = new QListWidget();
	addToBasketWidget = new QListWidget();

	QLinearGradient listGradient(0, 0, 0, trenchCoatsWidget->height());
	listGradient.setColorAt(0, QColor(227, 177, 206));
	listGradient.setColorAt(1, QColor(158, 219, 247));
	QPalette palette = trenchCoatsWidget->palette();
	palette.setBrush(QPalette::ColorRole::Base, QBrush(listGradient));
	trenchCoatsWidget->setPalette(palette);

	addButton = new QPushButton("Add");			// for administrator
	deleteButton = new QPushButton("Delete");
	updateButton = new QPushButton("Update");
	undoButton = new QPushButton("Undo");
	redoButton = new QPushButton("Redo");
	undoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
	redoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);

	addToBasketButton = new QPushButton(">");	// add to basket
	tableButton = new QPushButton("Table");

	accessButton = new QPushButton("Acces");
	nextButton = new QPushButton("Next");

	sizeWidget = new QLineEdit();				// input for trench coats
	colorWidget = new QLineEdit();
	priceWidget = new QLineEdit();
	quantityWidget = new QLineEdit();
	photographWidget = new QLineEdit();
	filterLine = new QLineEdit();
	basketPrice = new QLabel("Basket price: ");

	QHBoxLayout* mainLayout = new QHBoxLayout(this);
	QVBoxLayout* trenchCoatLayout = new QVBoxLayout(this);
	QVBoxLayout* shoppingBasketLayout = new QVBoxLayout(this);
	QVBoxLayout* addToBasketLayout = new QVBoxLayout(this);

	QLabel* label1 = new QLabel;
	label1->setText("Trench Coats");
	trenchCoatLayout->addWidget(label1);
	trenchCoatLayout->addWidget(trenchCoatsWidget);		//trench coat list

	QLabel* label2 = new QLabel;
	label2->setText("Shopping Basket");
	shoppingBasketLayout->addWidget(label2);
	shoppingBasketLayout->addWidget(shoppingBasketWidget);	// shopping basket list
	shoppingBasketLayout->addWidget(basketPrice);

	
	QFormLayout* adminFormLayout = new QFormLayout();
	adminFormLayout->addRow("Size", sizeWidget);			// form for input text for trench coat
	adminFormLayout->addRow("Color", colorWidget);
	adminFormLayout->addRow("Price", priceWidget);
	adminFormLayout->addRow("Quantity", quantityWidget);
	adminFormLayout->addRow("Photograph", photographWidget);
	trenchCoatLayout->addLayout(adminFormLayout);
	
	QGridLayout* adminGridLayout = new QGridLayout;		// grid for administrator buttons
	adminGridLayout->addWidget(addButton, 0, 0);
	adminGridLayout->addWidget(deleteButton, 0, 1);
	adminGridLayout->addWidget(updateButton, 0, 2);
	adminGridLayout->addWidget(undoButton, 1, 0);
	adminGridLayout->addWidget(redoButton, 1, 2);
	trenchCoatLayout->addLayout(adminGridLayout);
	
	QFormLayout* filterLayout = new QFormLayout();		// for the filtering
	filterLayout->addRow("Maximum price: ", filterLine);
	trenchCoatLayout->addLayout(filterLayout);
	

	QGridLayout* addToBasketButtonGrid = new QGridLayout;		// add to basket button
	addToBasketButtonGrid->addWidget(addToBasketButton, 0, 0);
	addToBasketButtonGrid->addWidget(tableButton, 1, 0);
	addToBasketLayout->addLayout(addToBasketButtonGrid);

	QGridLayout* userGridLayout = new QGridLayout;	// buttons for user
	userGridLayout->addWidget(accessButton, 0, 1);
	userGridLayout->addWidget(nextButton, 0, 2);
	shoppingBasketLayout->addLayout(userGridLayout);


	mainLayout->addLayout(trenchCoatLayout);
	mainLayout->addLayout(addToBasketLayout);
	mainLayout->addLayout(shoppingBasketLayout);
	model = new TrenchModel(userService);
	
}

void GUI::populate()
{
	vector<TrenchCoat> trenchCoats = service.getAllTrenchCoats();
	trenchCoatsWidget->clear();
	for (auto& t : trenchCoats)
	{
		trenchCoatsWidget->addItem(QString::fromStdString(t.getSize() + " / " + t.getColor()+" / ")+
			QString::number(t.getPrice(), 'f', 2) + QString::fromStdString(" / " + to_string(t.getQuantity()) + " / " + t.getPhotograph()));
	}
}

void GUI::populateShoppingBasket()
{
	vector<TrenchCoat> shoppingBasket = userService.getBasket();
	shoppingBasketWidget->clear();
	for (auto& t : shoppingBasket)
	{
		shoppingBasketWidget->addItem(QString::fromStdString(t.getSize() + " / " + t.getColor() + " / ") +
			QString::number(t.getPrice(), 'f', 2) + QString::fromStdString(" / " + to_string(t.getQuantity()) + " / " + t.getPhotograph()));
	}
}

void GUI::initFields()
{
	int index = getSelectedIndex();
	TrenchCoat t = service.getAllTrenchCoats()[index];

	sizeWidget->setText(QString::fromStdString(t.getSize()));
	colorWidget->setText(QString::fromStdString(t.getColor()));
	priceWidget->setText(QString::fromStdString(to_string(t.getPrice())));
	quantityWidget->setText(QString::fromStdString(to_string(t.getQuantity())));
	photographWidget->setText(QString::fromStdString(t.getPhotograph()));
}

int GUI::getSelectedIndex()
{
	QModelIndexList indexes = trenchCoatsWidget->selectionModel()->selectedIndexes();
	if (indexes.size() == 0)
		return -1;
	return indexes[0].row();
}

void GUI::connectSignalsWithSlots()
{
	QObject::connect(trenchCoatsWidget, &QListWidget::clicked, this, &GUI::initFields);
	QObject::connect(addButton, &QPushButton::clicked, this, &GUI::addTrenchCoat);
	QObject::connect(filterLine, &QLineEdit::textChanged, this, &GUI::filterPrice);
	QObject::connect(deleteButton, &QPushButton::clicked, this, &GUI::deleteTrenchCoat);
	QObject::connect(updateButton, &QPushButton::clicked, this, &GUI::updateTrenchCoat);
	QObject::connect(addToBasketButton, &QPushButton::clicked, this, &GUI::addToBasket);
	QObject::connect(accessButton, &QPushButton::clicked, this, &GUI::accessPhoto);
	QObject::connect(nextButton, &QPushButton::clicked, this, &GUI::nextTrenchCoat);
	QObject::connect(undoButton, &QPushButton::clicked, this, &GUI::undo);
	QObject::connect(redoButton, &QPushButton::clicked, this, &GUI::redo);
	QObject::connect(undoShortcut, &QShortcut::activated, this, &GUI::undo);
	QObject::connect(redoShortcut, &QShortcut::activated, this, &GUI::redo);
	QObject::connect(tableButton, &QPushButton::clicked, this, &GUI::displayTable);

}

void GUI::showInformation(const string& info)
{
	QMessageBox::information(this, "Information", QString::fromStdString(info));
}

void GUI::showError(const string& err)
{
	QMessageBox::critical(this, "Error", QString::fromStdString(err));
}

void GUI::addTrenchCoat()
{
	string size = sizeWidget->text().toStdString();
	string color = colorWidget->text().toStdString();
	string price = priceWidget->text().toStdString();
	string quantity = quantityWidget->text().toStdString();
	string photograph = photographWidget->text().toStdString();

	try {
		this->service.addService(size, color, price, quantity, photograph);
		this->populate();
		int lastElementIndex = this->service.getAllTrenchCoats().size() - 1;
		trenchCoatsWidget->setCurrentRow(lastElementIndex);
	}
	catch (RepositoryException& re)
	{
		this->showError(re.what());
	}
}

void GUI::deleteTrenchCoat()
{
	string size = sizeWidget->text().toStdString();
	string color = colorWidget->text().toStdString();
	string price = priceWidget->text().toStdString();
	string quantity = quantityWidget->text().toStdString();
	string photograph = photographWidget->text().toStdString();
	TrenchCoat t;
	t.setSize(size);
	t.setColor(color);
	t.setPrice(stod(price));
	t.setQuantity(stoi(quantity));
	t.setPhotograph(photograph);
	try {
		this->service.deleteService(t);
		this->populate();
	}
	catch (RepositoryException& re)
	{
		this->showError(re.what());
	}

}

void GUI::updateTrenchCoat()
{
	string size = sizeWidget->text().toStdString();
	string color = colorWidget->text().toStdString();
	string price = priceWidget->text().toStdString();
	string quantity = quantityWidget->text().toStdString();
	string photograph = photographWidget->text().toStdString();
	TrenchCoat t;
	t.setSize(size);
	t.setColor(color);
	t.setPrice(stod(price));
	t.setQuantity(stoi(quantity));
	t.setPhotograph(photograph);
	try {
		this->service.updateService(t, price, quantity, photograph);
		this->populate();
	}
	catch (RepositoryException& re)
	{
		this->showError(re.what());
	}

}

void GUI::addToBasket()
{
	string size = sizeWidget->text().toStdString();
	string color = colorWidget->text().toStdString();
	string price = priceWidget->text().toStdString();
	string quantity = quantityWidget->text().toStdString();
	string photograph = photographWidget->text().toStdString();
	TrenchCoat t;
	t.setSize(size);
	t.setColor(color);
	t.setPrice(stod(price));
	t.setQuantity(stoi(quantity));
	t.setPhotograph(photograph);
	this->userService.addTrenchToBasketService(t);
	this->populateShoppingBasket();

	double basket = userService.getBasketPrice();
	QString str = QString::fromStdString("Basket price:   ") + QString::number(basket, 'f', 2);
	basketPrice->setText(str);
}

void GUI::accessPhoto()
{
	string text = shoppingBasketWidget->currentItem()->text().toStdString();
	int pos;
	pos = text.find("www.");
	TrenchCoat t;
	text.erase(0, pos);
	t.setPhotograph(text);
	t.accessPhoto();
}

void GUI::nextTrenchCoat()
{	
	QModelIndexList indexes = shoppingBasketWidget->selectionModel()->selectedIndexes();
	int index =  indexes[0].row();
	if(index == userService.getBasket().size() - 1)
		shoppingBasketWidget->setCurrentRow(0);
	else
		shoppingBasketWidget->setCurrentRow(index + 1);
	accessPhoto();
}

void GUI::filterPrice()
{
	vector<TrenchCoat> trenchCoats = this->service.getAllTrenchCoats();
	int price = filterLine->text().toInt();
	if (price > 0) {
		trenchCoatsWidget->clear();
		for (auto& t : trenchCoats)
		{
			if (t.getPrice() <= price)
				trenchCoatsWidget->addItem(QString::fromStdString(t.getSize() + " / " + t.getColor() + " / ") +
					QString::number(t.getPrice(), 'f', 2) + QString::fromStdString(" / " + to_string(t.getQuantity()) + " / " + t.getPhotograph()));
		}
	}
	else
		populate();

}

void GUI::undo()
{
	try
	{
		service.undo();
		populate();
		this->showInformation("The last operation was undone successfully.");
	}
	catch (RepositoryException& re)
	{
		this->showError(re.what());
	}
}

void GUI::redo()
{
	try
	{
		this->service.redo();
		populate();
		this->showInformation("The last operation was redone successfully.");
	}
	catch (RepositoryException& re)
	{
		this->showError(re.what());
	}
}

void GUI::displayTable()
{
	auto* window = new QWidget;
	auto* tableView = new QTableView;
	tableView->setModel(model);
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	window->setMinimumWidth(tableView->width());
	auto* Vbox = new QVBoxLayout{ window };
	Vbox->addWidget(tableView);
	window->show();
	
}

GUI::GUI(Service& _service, UserService& _userService):service{_service}, userService{_userService}
{
	bindGUI();
	populate();
	connectSignalsWithSlots();
}