#pragma once
#include <fstream>
#include "Windows.h"
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <msclr\marshal_cppstd.h>
#include <windows.h>

#include <iostream>

// Grade structure
struct Grade {
	std::string name = "";
	double grade = -1;
	double weight = -1;
	double runningPercent = 0;

	std::vector<Grade> sections;
	Grade() {  }



	// Set Functions:
	void reset() { name = ""; grade = -1; weight = -1; sections.clear(); runningPercent = 0; }
	void addSection(std::string sName, double nWeight, int subs) {
		Grade sendingGrade;
		sendingGrade.name = sName;
		sendingGrade.weight = nWeight;
		sendingGrade.addSectionByCount(subs);
		sections.push_back(sendingGrade);
	}
	void addSectionByCount(int count) {
		Grade temp;
		for (int i = 0; i < count; i++) {
			temp.name = "Assingnment #" + std::to_string(i+1);
			sections.push_back(temp);
		}

	}
	void removeSection(int target) {
		runningPercent -= sections[target].weight;
		sections.erase(sections.begin() + target);
	}
	void refreshGrade() {
		if (sections.size() == 0)                    // Grade should be set through the set grade screen
			return;
		double fullSum = 0;
		for (int i = 0; i < sections.size(); i++){   // Going through all the sections
			if (sections[i].grade == -1) {           // Grade is not ready to be set, set *this grade to -1 and return
				grade = -1;
				return;
			}
			fullSum += (sections[i].grade * (sections[i].weight / 100.00));
		}

		// If it did not return, then all grades are inputted --> Update *this's grade
		grade = fullSum;
	}

	
	// Get Functions:
	int numOfSections() const { return sections.size(); }


	// Indicator Updating: 
	bool allWeightsInputted() {
		// loop through all sections
		for (int i = 0; i < sections.size(); i++){
			// if any section has -1 weight
			if (sections[i].weight == -1)
				return false;
			// if the sections of this class has subs
			if (sections[i].numOfSections() != 0) {
				// loop through all subsections
				for (int j = 0; j < sections[i].numOfSections(); j++){
					// if the subsection has -1 weight
					if (sections[i].sections[j].weight == -1)
						return false;
				}
			}
		}
		return true;
	}
	bool weightsAddUp() {
		if (!allWeightsInputted())
			return false;

		double classSum = 0, subSum = 0;
		for (int i = 0; i < sections.size(); i++) {
			classSum += sections[i].weight;
			if (sections[i].numOfSections() != 0) {
				subSum = 0;
				for (int j = 0; j < sections[i].numOfSections(); j++) {
					subSum += sections[i].sections[j].weight;
				}
				if (subSum != 100)
					return false;
			}
		}
		if (classSum != 100)
			return false;
		return true;
	}
	bool allSectionsNamed() {
		// loop through all sections
		for (int i = 0; i < sections.size(); i++) {
			// if any section has "" name
			if (sections[i].name == "") {
				return false;
			}
			// if the sections of this class has subs
			if (sections[i].numOfSections() != 0) {
				// loop through all subsections
				for (int j = 0; j < sections[i].numOfSections(); j++) {
					// if the subsection has "" name
					if (sections[i].sections[j].name == "") {
						
						return false;
					}
				}
			}
		}
		return true;
	}
	void updateWeight() {
		runningPercent = 0;
		for (int i = 0; i < sections.size(); i++) {
			if (sections[i].weight != -1)
				runningPercent += sections[i].weight;
		}
	}

	

	// File Saving Functions
	void SaveFile() {
		bool fileExisted;
		std::ifstream testOpening(name + ".txt");
		fileExisted = testOpening.is_open();
		if (testOpening) {
			testOpening.close();
		}
		// If it did not open, this file has not existed yet --> save false into bool and continue


		std::ofstream outputFile(name + ".txt");
		outputFile << numOfSections() << std::endl;
		for (int i = 0; i < numOfSections(); i++) {
			outputFile << sections[i].name << std::endl;
			outputFile << sections[i].weight << std::endl;
			outputFile << sections[i].grade << std::endl;
			outputFile << sections[i].numOfSections() << std::endl;
			if (sections[i].numOfSections() != 0) {
				for (int j = 0; j < sections[i].numOfSections(); j++) {
					outputFile << sections[i].sections[j].name << std::endl;
					outputFile << sections[i].sections[j].weight << std::endl;
					outputFile << sections[i].sections[j].grade << std::endl;
				}
			}
		}
		outputFile << "<><><>";
		outputFile.close();



		// If file did not exist yet, save it also into the allClases text
		if (!fileExisted) {
			std::ofstream allClassesOutput("_allClasses_.txt", std::ios::app);
			allClassesOutput << (name + ".txt") << std::endl;
			allClassesOutput.close();
		}
	}
	

};

// All Grades vector and temp Grade variable
std::vector<Grade> allClasses;
Grade newClass;





namespace GradeCalculator {

#pragma region Class Namespaces / Constructor / Destructor
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	public ref class form : public System::Windows::Forms::Form
	{
	public:form(void){InitializeComponent();}
	protected:~form(){if (components){delete components;}}
#pragma endregion

#pragma region Private Functions for class
	private:
	System::Windows::Forms::TabControl^ tabControl;
	System::Windows::Forms::TabPage^ tab1;
	System::Windows::Forms::Label^ addText16;
	System::Windows::Forms::Panel^ addClassPanel4;
	System::Windows::Forms::ListBox^ sectionNamesDisplay;
	System::Windows::Forms::Label^ addText10;
	System::Windows::Forms::Label^ addText9;
	System::Windows::Forms::Label^ addText8;
	System::Windows::Forms::Panel^ addClassPanel2;
	System::Windows::Forms::Button^ button1;

	System::Windows::Forms::Label^ amountSubText;

	System::Windows::Forms::Label^ percentText;
	System::Windows::Forms::TextBox^ sectionNameInput;
	System::Windows::Forms::Label^ sectionNameText;
	System::Windows::Forms::Label^ addText2;
	System::Windows::Forms::Panel^ classNamePanel;
	System::Windows::Forms::TextBox^ classNameInput;	
	System::Windows::Forms::Label^ addText1;
	System::Windows::Forms::Panel^ addClassPanel5;
	System::Windows::Forms::ListBox^ sectionSubDisplay;
	System::Windows::Forms::Label^ addText14;
	System::Windows::Forms::Label^ addText15;
	System::Windows::Forms::Label^ addText12;
	System::Windows::Forms::Button^ button4;
	System::Windows::Forms::Panel^ addClassPanel3;
	System::Windows::Forms::Button^ button2;
	System::Windows::Forms::Label^ addText3;
	System::Windows::Forms::Label^ summaryClassName;
	System::Windows::Forms::Label^ addText4;
	System::Windows::Forms::TextBox^ subSectionInputWeight;
	System::Windows::Forms::Label^ addText6;
	System::Windows::Forms::Label^ addText5;
	System::Windows::Forms::Label^ summaryWeightDisplay;
	System::Windows::Forms::Label^ summarySumsDisplay;
	System::Windows::Forms::Label^ sectionPercentSum;
	System::Windows::Forms::Label^ subSectionPercentSum;
	System::Windows::Forms::Label^ addText13;
	System::Windows::Forms::Label^ addText11;
	System::Windows::Forms::Label^ summaryAllSectionsNamed;
	System::Windows::Forms::Label^ addText7;
	System::Windows::Forms::TabPage^ tab2;
	System::Windows::Forms::Panel^ changeGradesPanel4;
	System::Windows::Forms::Label^ classesSavedIndicator;
	System::Windows::Forms::Button^ CGSaveGradesButton;
	System::Windows::Forms::Label^ changeGradeText8;
	System::Windows::Forms::Panel^ changeGradesPanel3;
	System::Windows::Forms::Button^ CGChangeGradeButton;
	System::Windows::Forms::TextBox^ CHChangeGradeInput;
	System::Windows::Forms::Label^ changeGradeText7;
	System::Windows::Forms::Label^ changeGradeText6;
	System::Windows::Forms::Panel^ changeGradesPanel2;
	System::Windows::Forms::Label^ changeGradeText5;
	System::Windows::Forms::ListBox^ CGsubSectionDisplay;
	System::Windows::Forms::Label^ changeGradeText4;
	System::Windows::Forms::ListBox^ CGSectionDisplay;
	System::Windows::Forms::Panel^ changeGradesPanel1;
	System::Windows::Forms::Label^ changeGradeText3;
	System::Windows::Forms::Label^ changeGradeText2;
	System::Windows::Forms::ListBox^ chooseClassDisplay;
	System::Windows::Forms::Label^ changeGradeText1;
	private: System::Windows::Forms::TabPage^ tab4;


	System::Windows::Forms::Button^ settingsMakeExampleFile;
	System::Windows::Forms::Label^ settingsText1;
	System::Windows::Forms::Label^ grabbingGradesFailureMessage;
	System::Windows::Forms::Panel^ settingsPanel1;
	System::Windows::Forms::Label^ settingsText3;
	System::Windows::Forms::Label^ settingsFileStatus;
	System::Windows::Forms::Label^ settingsText2;
	System::Windows::Forms::Label^ settingsCouldNotOpen;
	System::Windows::Forms::Panel^ settingsPanel2;
	System::Windows::Forms::Label^ settingsText4;
	System::Windows::Forms::ColorDialog^ backColor;
	System::Windows::Forms::Button^ button9;
	System::Windows::Forms::Button^ settingForeColorButton;
	System::Windows::Forms::ColorDialog^ foreColor;
	System::Windows::Forms::Label^ settingsText5;
	System::Windows::Forms::Panel^ settingsBackColorDisplay;
	System::Windows::Forms::Panel^ settingsForeColorDisplay;
	System::Windows::Forms::Label^ settingsText6;
	System::Windows::Forms::Button^ button10;
	System::Windows::Forms::Label^ settingsText7;
	System::Windows::Forms::ColorDialog^ textColor;
	System::Windows::Forms::Panel^ settingsTextColorDisplay;
	System::Windows::Forms::Panel^ preset1Box;
	System::Windows::Forms::Panel^ preset4Box;
	private: System::Windows::Forms::Label^ preset4Label;


	System::Windows::Forms::Panel^ preset3Box;
	System::Windows::Forms::Label^ preset3Label;
	System::Windows::Forms::Panel^ preset2Box;
	System::Windows::Forms::Label^ preset2Label;
	System::Windows::Forms::Label^ preset1Label;
	System::Windows::Forms::Button^ CGResetGradeButton;
	System::Windows::Forms::TabPage^ tab3;
	System::Windows::Forms::Panel^ TSPanel1;
	System::Windows::Forms::Label^ TSText2;
	System::Windows::Forms::Label^ TSText1;
	System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	System::Windows::Forms::Panel^ TSPanel2;
	System::Windows::Forms::ComboBox^ TSChooseClassBox;
	System::Windows::Forms::Label^ TSText3;
	System::Windows::Forms::Panel^ TSPanel3;
	System::Windows::Forms::Label^ TSText4;
	System::Windows::Forms::Panel^ TSPanel4;
	System::Windows::Forms::Label^ TSDisplayGradeTop;
	System::Windows::Forms::ListBox^ TSSubSectionsDisplay;
	System::Windows::Forms::ListBox^ TSSectionsDisplay;
	System::Windows::Forms::Label^ TSText6;
	System::Windows::Forms::Label^ TSText5;
	System::Windows::Forms::TrackBar^ changeGradeTrack;
	System::Windows::Forms::Label^ TSText7;
	System::Windows::Forms::Panel^ TSPanel5;
	System::Windows::Forms::Label^ TSDisplayGradeBottom;
	System::Windows::Forms::Button^ TSResetAllGradesButton;
	System::Windows::Forms::Button^ TSSaveThisClassButton;
	System::Windows::Forms::Panel^ TSPanel6;
	System::Windows::Forms::Label^ addText17;
	System::Windows::Forms::Label^ addText18;
	System::Windows::Forms::Label^ summaryHasSections;
	System::Windows::Forms::Button^ saveSubSectionButotn;
	System::Windows::Forms::TextBox^ subSectionInputName;
	System::Windows::Forms::Label^ addText20;
	System::Windows::Forms::Label^ addText19;

	System::Windows::Forms::Label^ addText21;
	System::Windows::Forms::Button^ CGDeleteClass;


	System::Windows::Forms::Timer^ messageTimer;
	System::Windows::Forms::Panel^ deletingClassMessage;
	System::Windows::Forms::Label^ label1;
	System::Windows::Forms::Panel^ settingsPanel3;
	System::Windows::Forms::Button^ settingsOpenAllClassFIle;
	System::Windows::Forms::Label^ label6;
	System::Windows::Forms::Label^ settingsStatusOutput;
	System::Windows::Forms::Button^ settingsAdminButton;
	System::Windows::Forms::ListBox^ settingsDisplayClasses;
	System::Windows::Forms::Label^ label2;
	System::Windows::Forms::Button^ settingsOpenChosenClassFile;
	System::Windows::Forms::Button^ settingsOpenExplorer;
	System::Windows::Forms::Panel^ settingsHider2;
	System::Windows::Forms::Panel^ settingsHider1;
	System::Windows::Forms::Label^ settingsText8;
	System::Windows::Forms::PictureBox^ pictureBox10;
	System::Windows::Forms::PictureBox^ pictureBox9;
	System::Windows::Forms::PictureBox^ pictureBox8;
	System::Windows::Forms::PictureBox^ pictureBox7;
	System::Windows::Forms::PictureBox^ pictureBox6;
	System::Windows::Forms::PictureBox^ pictureBox5;
	System::Windows::Forms::PictureBox^ pictureBox4;
	System::Windows::Forms::PictureBox^ pictureBox3;
	System::Windows::Forms::PictureBox^ pictureBox2;
	System::Windows::Forms::PictureBox^ pictureBox1;
	System::Windows::Forms::Label^ settingsCorruptedIconText;
	System::Windows::Forms::Label^ settingsText9;
	System::Windows::Forms::TextBox^ settingsSetFormNameInput;
	System::Windows::Forms::Button^ settingsSetFormNameButton;
	System::Windows::Forms::Label^ settingsCorruptNameText;
private: System::Windows::Forms::Timer^ adminPageAnimation;
private: System::Windows::Forms::Button^ button3;
private: System::Windows::Forms::Label^ settingsCorruptThemeText;
private: System::Windows::Forms::Label^ changingGradeDisplayText;
private: System::Windows::Forms::Label^ changeGradeText9;


private: System::Windows::Forms::Panel^ messagePanel;
private: System::Windows::Forms::Label^ messageText;
private: System::Windows::Forms::TextBox^ percentInput;
private: System::Windows::Forms::TextBox^ amountSubInput;









	   System::ComponentModel::IContainer^ components;


#pragma endregion
#pragma region Windows Form Designer generated code
		//System::ComponentModel::ComponentResourceManager^ resourcesPublic;
		// add this: resourcesPublic = resources;
		// add all images from icons into the icon resources
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(form::typeid));
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tab1 = (gcnew System::Windows::Forms::TabPage());
			this->messagePanel = (gcnew System::Windows::Forms::Panel());
			this->messageText = (gcnew System::Windows::Forms::Label());
			this->grabbingGradesFailureMessage = (gcnew System::Windows::Forms::Label());
			this->addClassPanel3 = (gcnew System::Windows::Forms::Panel());
			this->summaryHasSections = (gcnew System::Windows::Forms::Label());
			this->addText18 = (gcnew System::Windows::Forms::Label());
			this->summaryAllSectionsNamed = (gcnew System::Windows::Forms::Label());
			this->addText7 = (gcnew System::Windows::Forms::Label());
			this->summarySumsDisplay = (gcnew System::Windows::Forms::Label());
			this->summaryWeightDisplay = (gcnew System::Windows::Forms::Label());
			this->addText6 = (gcnew System::Windows::Forms::Label());
			this->addText5 = (gcnew System::Windows::Forms::Label());
			this->summaryClassName = (gcnew System::Windows::Forms::Label());
			this->addText4 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->addText3 = (gcnew System::Windows::Forms::Label());
			this->addClassPanel5 = (gcnew System::Windows::Forms::Panel());
			this->addText20 = (gcnew System::Windows::Forms::Label());
			this->addText19 = (gcnew System::Windows::Forms::Label());
			this->saveSubSectionButotn = (gcnew System::Windows::Forms::Button());
			this->subSectionInputName = (gcnew System::Windows::Forms::TextBox());
			this->subSectionPercentSum = (gcnew System::Windows::Forms::Label());
			this->addText13 = (gcnew System::Windows::Forms::Label());
			this->subSectionInputWeight = (gcnew System::Windows::Forms::TextBox());
			this->sectionSubDisplay = (gcnew System::Windows::Forms::ListBox());
			this->addText14 = (gcnew System::Windows::Forms::Label());
			this->addText15 = (gcnew System::Windows::Forms::Label());
			this->addText12 = (gcnew System::Windows::Forms::Label());
			this->addText16 = (gcnew System::Windows::Forms::Label());
			this->addClassPanel4 = (gcnew System::Windows::Forms::Panel());
			this->sectionPercentSum = (gcnew System::Windows::Forms::Label());
			this->addText11 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->sectionNamesDisplay = (gcnew System::Windows::Forms::ListBox());
			this->addText10 = (gcnew System::Windows::Forms::Label());
			this->addText9 = (gcnew System::Windows::Forms::Label());
			this->addText8 = (gcnew System::Windows::Forms::Label());
			this->addClassPanel2 = (gcnew System::Windows::Forms::Panel());
			this->amountSubInput = (gcnew System::Windows::Forms::TextBox());
			this->percentInput = (gcnew System::Windows::Forms::TextBox());
			this->addText21 = (gcnew System::Windows::Forms::Label());
			this->addText17 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->amountSubText = (gcnew System::Windows::Forms::Label());
			this->percentText = (gcnew System::Windows::Forms::Label());
			this->sectionNameInput = (gcnew System::Windows::Forms::TextBox());
			this->sectionNameText = (gcnew System::Windows::Forms::Label());
			this->addText2 = (gcnew System::Windows::Forms::Label());
			this->classNamePanel = (gcnew System::Windows::Forms::Panel());
			this->classNameInput = (gcnew System::Windows::Forms::TextBox());
			this->addText1 = (gcnew System::Windows::Forms::Label());
			this->tab2 = (gcnew System::Windows::Forms::TabPage());
			this->deletingClassMessage = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->changeGradesPanel4 = (gcnew System::Windows::Forms::Panel());
			this->classesSavedIndicator = (gcnew System::Windows::Forms::Label());
			this->CGSaveGradesButton = (gcnew System::Windows::Forms::Button());
			this->changeGradeText8 = (gcnew System::Windows::Forms::Label());
			this->changeGradesPanel3 = (gcnew System::Windows::Forms::Panel());
			this->CGResetGradeButton = (gcnew System::Windows::Forms::Button());
			this->CGChangeGradeButton = (gcnew System::Windows::Forms::Button());
			this->CHChangeGradeInput = (gcnew System::Windows::Forms::TextBox());
			this->changeGradeText7 = (gcnew System::Windows::Forms::Label());
			this->changeGradeText6 = (gcnew System::Windows::Forms::Label());
			this->changeGradesPanel2 = (gcnew System::Windows::Forms::Panel());
			this->changingGradeDisplayText = (gcnew System::Windows::Forms::Label());
			this->changeGradeText9 = (gcnew System::Windows::Forms::Label());
			this->changeGradeText5 = (gcnew System::Windows::Forms::Label());
			this->CGsubSectionDisplay = (gcnew System::Windows::Forms::ListBox());
			this->changeGradeText4 = (gcnew System::Windows::Forms::Label());
			this->CGSectionDisplay = (gcnew System::Windows::Forms::ListBox());
			this->changeGradesPanel1 = (gcnew System::Windows::Forms::Panel());
			this->CGDeleteClass = (gcnew System::Windows::Forms::Button());
			this->changeGradeText3 = (gcnew System::Windows::Forms::Label());
			this->changeGradeText2 = (gcnew System::Windows::Forms::Label());
			this->chooseClassDisplay = (gcnew System::Windows::Forms::ListBox());
			this->changeGradeText1 = (gcnew System::Windows::Forms::Label());
			this->tab3 = (gcnew System::Windows::Forms::TabPage());
			this->TSPanel6 = (gcnew System::Windows::Forms::Panel());
			this->TSSaveThisClassButton = (gcnew System::Windows::Forms::Button());
			this->TSResetAllGradesButton = (gcnew System::Windows::Forms::Button());
			this->TSPanel3 = (gcnew System::Windows::Forms::Panel());
			this->TSPanel5 = (gcnew System::Windows::Forms::Panel());
			this->TSDisplayGradeBottom = (gcnew System::Windows::Forms::Label());
			this->changeGradeTrack = (gcnew System::Windows::Forms::TrackBar());
			this->TSText7 = (gcnew System::Windows::Forms::Label());
			this->TSSubSectionsDisplay = (gcnew System::Windows::Forms::ListBox());
			this->TSSectionsDisplay = (gcnew System::Windows::Forms::ListBox());
			this->TSPanel4 = (gcnew System::Windows::Forms::Panel());
			this->TSDisplayGradeTop = (gcnew System::Windows::Forms::Label());
			this->TSText6 = (gcnew System::Windows::Forms::Label());
			this->TSText4 = (gcnew System::Windows::Forms::Label());
			this->TSText5 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->TSPanel1 = (gcnew System::Windows::Forms::Panel());
			this->TSText2 = (gcnew System::Windows::Forms::Label());
			this->TSPanel2 = (gcnew System::Windows::Forms::Panel());
			this->TSChooseClassBox = (gcnew System::Windows::Forms::ComboBox());
			this->TSText3 = (gcnew System::Windows::Forms::Label());
			this->TSText1 = (gcnew System::Windows::Forms::Label());
			this->tab4 = (gcnew System::Windows::Forms::TabPage());
			this->settingsAdminButton = (gcnew System::Windows::Forms::Button());
			this->settingsPanel3 = (gcnew System::Windows::Forms::Panel());
			this->settingsHider2 = (gcnew System::Windows::Forms::Panel());
			this->settingsCorruptNameText = (gcnew System::Windows::Forms::Label());
			this->settingsSetFormNameButton = (gcnew System::Windows::Forms::Button());
			this->settingsSetFormNameInput = (gcnew System::Windows::Forms::TextBox());
			this->settingsText9 = (gcnew System::Windows::Forms::Label());
			this->settingsOpenExplorer = (gcnew System::Windows::Forms::Button());
			this->settingsOpenChosenClassFile = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->settingsDisplayClasses = (gcnew System::Windows::Forms::ListBox());
			this->settingsStatusOutput = (gcnew System::Windows::Forms::Label());
			this->settingsOpenAllClassFIle = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->settingsPanel2 = (gcnew System::Windows::Forms::Panel());
			this->settingsCorruptThemeText = (gcnew System::Windows::Forms::Label());
			this->preset4Box = (gcnew System::Windows::Forms::Panel());
			this->preset4Label = (gcnew System::Windows::Forms::Label());
			this->preset3Box = (gcnew System::Windows::Forms::Panel());
			this->preset3Label = (gcnew System::Windows::Forms::Label());
			this->preset2Box = (gcnew System::Windows::Forms::Panel());
			this->preset2Label = (gcnew System::Windows::Forms::Label());
			this->preset1Box = (gcnew System::Windows::Forms::Panel());
			this->preset1Label = (gcnew System::Windows::Forms::Label());
			this->settingsTextColorDisplay = (gcnew System::Windows::Forms::Panel());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->settingsText7 = (gcnew System::Windows::Forms::Label());
			this->settingsForeColorDisplay = (gcnew System::Windows::Forms::Panel());
			this->settingsText6 = (gcnew System::Windows::Forms::Label());
			this->settingsBackColorDisplay = (gcnew System::Windows::Forms::Panel());
			this->settingsText5 = (gcnew System::Windows::Forms::Label());
			this->settingForeColorButton = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->settingsText4 = (gcnew System::Windows::Forms::Label());
			this->settingsPanel1 = (gcnew System::Windows::Forms::Panel());
			this->settingsHider1 = (gcnew System::Windows::Forms::Panel());
			this->settingsCorruptedIconText = (gcnew System::Windows::Forms::Label());
			this->settingsText8 = (gcnew System::Windows::Forms::Label());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->settingsFileStatus = (gcnew System::Windows::Forms::Label());
			this->settingsMakeExampleFile = (gcnew System::Windows::Forms::Button());
			this->settingsText2 = (gcnew System::Windows::Forms::Label());
			this->settingsCouldNotOpen = (gcnew System::Windows::Forms::Label());
			this->settingsText3 = (gcnew System::Windows::Forms::Label());
			this->settingsText1 = (gcnew System::Windows::Forms::Label());
			this->backColor = (gcnew System::Windows::Forms::ColorDialog());
			this->foreColor = (gcnew System::Windows::Forms::ColorDialog());
			this->textColor = (gcnew System::Windows::Forms::ColorDialog());
			this->messageTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->adminPageAnimation = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabControl->SuspendLayout();
			this->tab1->SuspendLayout();
			this->messagePanel->SuspendLayout();
			this->addClassPanel3->SuspendLayout();
			this->addClassPanel5->SuspendLayout();
			this->addClassPanel4->SuspendLayout();
			this->addClassPanel2->SuspendLayout();
			this->classNamePanel->SuspendLayout();
			this->tab2->SuspendLayout();
			this->deletingClassMessage->SuspendLayout();
			this->changeGradesPanel4->SuspendLayout();
			this->changeGradesPanel3->SuspendLayout();
			this->changeGradesPanel2->SuspendLayout();
			this->changeGradesPanel1->SuspendLayout();
			this->tab3->SuspendLayout();
			this->TSPanel6->SuspendLayout();
			this->TSPanel3->SuspendLayout();
			this->TSPanel5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->changeGradeTrack))->BeginInit();
			this->TSPanel4->SuspendLayout();
			this->TSPanel1->SuspendLayout();
			this->TSPanel2->SuspendLayout();
			this->tab4->SuspendLayout();
			this->settingsPanel3->SuspendLayout();
			this->settingsHider2->SuspendLayout();
			this->settingsPanel2->SuspendLayout();
			this->preset4Box->SuspendLayout();
			this->preset3Box->SuspendLayout();
			this->preset2Box->SuspendLayout();
			this->preset1Box->SuspendLayout();
			this->settingsPanel1->SuspendLayout();
			this->settingsHider1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Alignment = System::Windows::Forms::TabAlignment::Bottom;
			this->tabControl->Controls->Add(this->tab1);
			this->tabControl->Controls->Add(this->tab2);
			this->tabControl->Controls->Add(this->tab3);
			this->tabControl->Controls->Add(this->tab4);
			this->tabControl->ItemSize = System::Drawing::Size(190, 31);
			this->tabControl->Location = System::Drawing::Point(-11, -12);
			this->tabControl->Multiline = true;
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(1718, 1089);
			this->tabControl->TabIndex = 6;
			// 
			// tab1
			// 
			this->tab1->BackColor = System::Drawing::Color::Tan;
			this->tab1->Controls->Add(this->messagePanel);
			this->tab1->Controls->Add(this->grabbingGradesFailureMessage);
			this->tab1->Controls->Add(this->addClassPanel3);
			this->tab1->Controls->Add(this->addClassPanel5);
			this->tab1->Controls->Add(this->addText16);
			this->tab1->Controls->Add(this->addClassPanel4);
			this->tab1->Controls->Add(this->addClassPanel2);
			this->tab1->Controls->Add(this->classNamePanel);
			this->tab1->Location = System::Drawing::Point(8, 8);
			this->tab1->Margin = System::Windows::Forms::Padding(0);
			this->tab1->Name = L"tab1";
			this->tab1->Size = System::Drawing::Size(1702, 1042);
			this->tab1->TabIndex = 0;
			this->tab1->Text = L"Set up New Class";
			this->tab1->Enter += gcnew System::EventHandler(this, &form::cleanAddClassPage);
			// 
			// messagePanel
			// 
			this->messagePanel->BackColor = System::Drawing::Color::Green;
			this->messagePanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->messagePanel->Controls->Add(this->messageText);
			this->messagePanel->ForeColor = System::Drawing::Color::White;
			this->messagePanel->Location = System::Drawing::Point(3, 10);
			this->messagePanel->Name = L"messagePanel";
			this->messagePanel->Size = System::Drawing::Size(1628, 80);
			this->messagePanel->TabIndex = 11;
			this->messagePanel->Visible = false;
			// 
			// messageText
			// 
			this->messageText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->messageText->Location = System::Drawing::Point(39, -2);
			this->messageText->Name = L"messageText";
			this->messageText->Size = System::Drawing::Size(1526, 83);
			this->messageText->TabIndex = 0;
			this->messageText->Text = L"Class has been added";
			this->messageText->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// grabbingGradesFailureMessage
			// 
			this->grabbingGradesFailureMessage->BackColor = System::Drawing::Color::Red;
			this->grabbingGradesFailureMessage->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->grabbingGradesFailureMessage->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->grabbingGradesFailureMessage->ForeColor = System::Drawing::Color::White;
			this->grabbingGradesFailureMessage->Location = System::Drawing::Point(404, 566);
			this->grabbingGradesFailureMessage->Name = L"grabbingGradesFailureMessage";
			this->grabbingGradesFailureMessage->Size = System::Drawing::Size(752, 67);
			this->grabbingGradesFailureMessage->TabIndex = 13;
			this->grabbingGradesFailureMessage->Text = L"Corrupted Files, please find corruption!";
			this->grabbingGradesFailureMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->grabbingGradesFailureMessage->Visible = false;
			// 
			// addClassPanel3
			// 
			this->addClassPanel3->BackColor = System::Drawing::Color::Bisque;
			this->addClassPanel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->addClassPanel3->Controls->Add(this->summaryHasSections);
			this->addClassPanel3->Controls->Add(this->addText18);
			this->addClassPanel3->Controls->Add(this->summaryAllSectionsNamed);
			this->addClassPanel3->Controls->Add(this->addText7);
			this->addClassPanel3->Controls->Add(this->summarySumsDisplay);
			this->addClassPanel3->Controls->Add(this->summaryWeightDisplay);
			this->addClassPanel3->Controls->Add(this->addText6);
			this->addClassPanel3->Controls->Add(this->addText5);
			this->addClassPanel3->Controls->Add(this->summaryClassName);
			this->addClassPanel3->Controls->Add(this->addText4);
			this->addClassPanel3->Controls->Add(this->button2);
			this->addClassPanel3->Controls->Add(this->addText3);
			this->addClassPanel3->Location = System::Drawing::Point(24, 631);
			this->addClassPanel3->Name = L"addClassPanel3";
			this->addClassPanel3->Size = System::Drawing::Size(774, 372);
			this->addClassPanel3->TabIndex = 11;
			// 
			// summaryHasSections
			// 
			this->summaryHasSections->BackColor = System::Drawing::Color::Green;
			this->summaryHasSections->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->summaryHasSections->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.875F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->summaryHasSections->ForeColor = System::Drawing::Color::White;
			this->summaryHasSections->Location = System::Drawing::Point(407, 229);
			this->summaryHasSections->Name = L"summaryHasSections";
			this->summaryHasSections->Size = System::Drawing::Size(212, 43);
			this->summaryHasSections->TabIndex = 10;
			this->summaryHasSections->Text = L"Ready!";
			this->summaryHasSections->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// addText18
			// 
			this->addText18->BackColor = System::Drawing::Color::Transparent;
			this->addText18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText18->Location = System::Drawing::Point(37, 225);
			this->addText18->Name = L"addText18";
			this->addText18->Size = System::Drawing::Size(312, 45);
			this->addText18->TabIndex = 9;
			this->addText18->Text = L"Has Sections:";
			this->addText18->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// summaryAllSectionsNamed
			// 
			this->summaryAllSectionsNamed->BackColor = System::Drawing::Color::Green;
			this->summaryAllSectionsNamed->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->summaryAllSectionsNamed->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.875F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->summaryAllSectionsNamed->ForeColor = System::Drawing::Color::White;
			this->summaryAllSectionsNamed->Location = System::Drawing::Point(407, 184);
			this->summaryAllSectionsNamed->Name = L"summaryAllSectionsNamed";
			this->summaryAllSectionsNamed->Size = System::Drawing::Size(212, 43);
			this->summaryAllSectionsNamed->TabIndex = 8;
			this->summaryAllSectionsNamed->Text = L"Ready!";
			this->summaryAllSectionsNamed->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// addText7
			// 
			this->addText7->BackColor = System::Drawing::Color::Transparent;
			this->addText7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText7->Location = System::Drawing::Point(37, 180);
			this->addText7->Name = L"addText7";
			this->addText7->Size = System::Drawing::Size(312, 45);
			this->addText7->TabIndex = 7;
			this->addText7->Text = L"All Sections named:";
			this->addText7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// summarySumsDisplay
			// 
			this->summarySumsDisplay->BackColor = System::Drawing::Color::Green;
			this->summarySumsDisplay->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->summarySumsDisplay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.875F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->summarySumsDisplay->ForeColor = System::Drawing::Color::White;
			this->summarySumsDisplay->Location = System::Drawing::Point(407, 139);
			this->summarySumsDisplay->Name = L"summarySumsDisplay";
			this->summarySumsDisplay->Size = System::Drawing::Size(212, 43);
			this->summarySumsDisplay->TabIndex = 6;
			this->summarySumsDisplay->Text = L"Ready!";
			this->summarySumsDisplay->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// summaryWeightDisplay
			// 
			this->summaryWeightDisplay->BackColor = System::Drawing::Color::Red;
			this->summaryWeightDisplay->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->summaryWeightDisplay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.875F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->summaryWeightDisplay->ForeColor = System::Drawing::Color::White;
			this->summaryWeightDisplay->Location = System::Drawing::Point(407, 94);
			this->summaryWeightDisplay->Name = L"summaryWeightDisplay";
			this->summaryWeightDisplay->Size = System::Drawing::Size(212, 43);
			this->summaryWeightDisplay->TabIndex = 0;
			this->summaryWeightDisplay->Text = L"Needs Attention!";
			this->summaryWeightDisplay->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// addText6
			// 
			this->addText6->BackColor = System::Drawing::Color::Transparent;
			this->addText6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText6->Location = System::Drawing::Point(37, 135);
			this->addText6->Name = L"addText6";
			this->addText6->Size = System::Drawing::Size(271, 45);
			this->addText6->TabIndex = 5;
			this->addText6->Text = L"Weights Sums:";
			this->addText6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// addText5
			// 
			this->addText5->BackColor = System::Drawing::Color::Transparent;
			this->addText5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText5->Location = System::Drawing::Point(37, 90);
			this->addText5->Name = L"addText5";
			this->addText5->Size = System::Drawing::Size(271, 45);
			this->addText5->TabIndex = 4;
			this->addText5->Text = L"Weights Inputted:";
			this->addText5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// summaryClassName
			// 
			this->summaryClassName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->summaryClassName->Location = System::Drawing::Point(307, 45);
			this->summaryClassName->Name = L"summaryClassName";
			this->summaryClassName->Size = System::Drawing::Size(417, 45);
			this->summaryClassName->TabIndex = 3;
			this->summaryClassName->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// addText4
			// 
			this->addText4->BackColor = System::Drawing::Color::Transparent;
			this->addText4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText4->Location = System::Drawing::Point(37, 45);
			this->addText4->Name = L"addText4";
			this->addText4->Size = System::Drawing::Size(212, 45);
			this->addText4->TabIndex = 2;
			this->addText4->Text = L"Class Name:";
			this->addText4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(29, 286);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(695, 76);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Add Class";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &form::addClasButton);
			// 
			// addText3
			// 
			this->addText3->BackColor = System::Drawing::Color::Transparent;
			this->addText3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText3->Location = System::Drawing::Point(3, 0);
			this->addText3->Name = L"addText3";
			this->addText3->Size = System::Drawing::Size(769, 45);
			this->addText3->TabIndex = 0;
			this->addText3->Text = L"Class Adding Requirements:";
			this->addText3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// addClassPanel5
			// 
			this->addClassPanel5->BackColor = System::Drawing::Color::Bisque;
			this->addClassPanel5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->addClassPanel5->Controls->Add(this->addText20);
			this->addClassPanel5->Controls->Add(this->addText19);
			this->addClassPanel5->Controls->Add(this->saveSubSectionButotn);
			this->addClassPanel5->Controls->Add(this->subSectionInputName);
			this->addClassPanel5->Controls->Add(this->subSectionPercentSum);
			this->addClassPanel5->Controls->Add(this->addText13);
			this->addClassPanel5->Controls->Add(this->subSectionInputWeight);
			this->addClassPanel5->Controls->Add(this->sectionSubDisplay);
			this->addClassPanel5->Controls->Add(this->addText14);
			this->addClassPanel5->Controls->Add(this->addText15);
			this->addClassPanel5->Controls->Add(this->addText12);
			this->addClassPanel5->Location = System::Drawing::Point(820, 631);
			this->addClassPanel5->Name = L"addClassPanel5";
			this->addClassPanel5->Size = System::Drawing::Size(774, 370);
			this->addClassPanel5->TabIndex = 10;
			// 
			// addText20
			// 
			this->addText20->BackColor = System::Drawing::Color::Transparent;
			this->addText20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText20->Location = System::Drawing::Point(3, 303);
			this->addText20->Name = L"addText20";
			this->addText20->Size = System::Drawing::Size(78, 44);
			this->addText20->TabIndex = 25;
			this->addText20->Text = L"Weight:";
			this->addText20->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// addText19
			// 
			this->addText19->BackColor = System::Drawing::Color::Transparent;
			this->addText19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText19->Location = System::Drawing::Point(3, 244);
			this->addText19->Name = L"addText19";
			this->addText19->Size = System::Drawing::Size(78, 44);
			this->addText19->TabIndex = 24;
			this->addText19->Text = L"Name:";
			this->addText19->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// saveSubSectionButotn
			// 
			this->saveSubSectionButotn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->saveSubSectionButotn->Location = System::Drawing::Point(534, 242);
			this->saveSubSectionButotn->Name = L"saveSubSectionButotn";
			this->saveSubSectionButotn->Size = System::Drawing::Size(194, 105);
			this->saveSubSectionButotn->TabIndex = 23;
			this->saveSubSectionButotn->Text = L"Save Sub Section";
			this->saveSubSectionButotn->UseVisualStyleBackColor = true;
			this->saveSubSectionButotn->Click += gcnew System::EventHandler(this, &form::saveSubSectionButotn_Click);
			// 
			// subSectionInputName
			// 
			this->subSectionInputName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->subSectionInputName->Location = System::Drawing::Point(87, 242);
			this->subSectionInputName->Name = L"subSectionInputName";
			this->subSectionInputName->Size = System::Drawing::Size(423, 44);
			this->subSectionInputName->TabIndex = 21;
			this->subSectionInputName->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// subSectionPercentSum
			// 
			this->subSectionPercentSum->BackColor = System::Drawing::Color::Transparent;
			this->subSectionPercentSum->Location = System::Drawing::Point(689, 11);
			this->subSectionPercentSum->Name = L"subSectionPercentSum";
			this->subSectionPercentSum->Size = System::Drawing::Size(80, 27);
			this->subSectionPercentSum->TabIndex = 19;
			this->subSectionPercentSum->Text = L"100.00";
			this->subSectionPercentSum->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// addText13
			// 
			this->addText13->BackColor = System::Drawing::Color::Transparent;
			this->addText13->Location = System::Drawing::Point(552, 11);
			this->addText13->Name = L"addText13";
			this->addText13->Size = System::Drawing::Size(143, 29);
			this->addText13->TabIndex = 20;
			this->addText13->Text = L"Total Weight:";
			// 
			// subSectionInputWeight
			// 
			this->subSectionInputWeight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->subSectionInputWeight->Location = System::Drawing::Point(87, 303);
			this->subSectionInputWeight->Name = L"subSectionInputWeight";
			this->subSectionInputWeight->Size = System::Drawing::Size(423, 44);
			this->subSectionInputWeight->TabIndex = 22;
			this->subSectionInputWeight->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// sectionSubDisplay
			// 
			this->sectionSubDisplay->Cursor = System::Windows::Forms::Cursors::Hand;
			this->sectionSubDisplay->Font = (gcnew System::Drawing::Font(L"Courier New", 10.125F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sectionSubDisplay->FormattingEnabled = true;
			this->sectionSubDisplay->ItemHeight = 30;
			this->sectionSubDisplay->Location = System::Drawing::Point(44, 68);
			this->sectionSubDisplay->Name = L"sectionSubDisplay";
			this->sectionSubDisplay->Size = System::Drawing::Size(684, 184);
			this->sectionSubDisplay->TabIndex = 14;
			this->sectionSubDisplay->SelectedIndexChanged += gcnew System::EventHandler(this, &form::sectionSubDisplay_SelectedIndexChanged);
			// 
			// addText14
			// 
			this->addText14->BackColor = System::Drawing::Color::Transparent;
			this->addText14->Location = System::Drawing::Point(633, 40);
			this->addText14->Name = L"addText14";
			this->addText14->Size = System::Drawing::Size(95, 25);
			this->addText14->TabIndex = 13;
			this->addText14->Text = L"Weight:";
			// 
			// addText15
			// 
			this->addText15->BackColor = System::Drawing::Color::Transparent;
			this->addText15->Location = System::Drawing::Point(39, 40);
			this->addText15->Name = L"addText15";
			this->addText15->Size = System::Drawing::Size(203, 25);
			this->addText15->TabIndex = 12;
			this->addText15->Text = L"Section Name:";
			// 
			// addText12
			// 
			this->addText12->BackColor = System::Drawing::Color::Transparent;
			this->addText12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText12->Location = System::Drawing::Point(172, 0);
			this->addText12->Name = L"addText12";
			this->addText12->Size = System::Drawing::Size(439, 45);
			this->addText12->TabIndex = 0;
			this->addText12->Text = L"Section Sub Grades";
			this->addText12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// addText16
			// 
			this->addText16->BackColor = System::Drawing::Color::Bisque;
			this->addText16->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->addText16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText16->Location = System::Drawing::Point(24, 13);
			this->addText16->Name = L"addText16";
			this->addText16->Size = System::Drawing::Size(1570, 67);
			this->addText16->TabIndex = 9;
			this->addText16->Text = L"Adding a New Class";
			this->addText16->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// addClassPanel4
			// 
			this->addClassPanel4->BackColor = System::Drawing::Color::Bisque;
			this->addClassPanel4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->addClassPanel4->Controls->Add(this->sectionPercentSum);
			this->addClassPanel4->Controls->Add(this->addText11);
			this->addClassPanel4->Controls->Add(this->button4);
			this->addClassPanel4->Controls->Add(this->sectionNamesDisplay);
			this->addClassPanel4->Controls->Add(this->addText10);
			this->addClassPanel4->Controls->Add(this->addText9);
			this->addClassPanel4->Controls->Add(this->addText8);
			this->addClassPanel4->Location = System::Drawing::Point(820, 96);
			this->addClassPanel4->Name = L"addClassPanel4";
			this->addClassPanel4->Size = System::Drawing::Size(774, 519);
			this->addClassPanel4->TabIndex = 8;
			// 
			// sectionPercentSum
			// 
			this->sectionPercentSum->BackColor = System::Drawing::Color::Transparent;
			this->sectionPercentSum->Location = System::Drawing::Point(687, 20);
			this->sectionPercentSum->Name = L"sectionPercentSum";
			this->sectionPercentSum->Size = System::Drawing::Size(80, 27);
			this->sectionPercentSum->TabIndex = 16;
			this->sectionPercentSum->Text = L"100.00";
			this->sectionPercentSum->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// addText11
			// 
			this->addText11->BackColor = System::Drawing::Color::Transparent;
			this->addText11->Location = System::Drawing::Point(552, 20);
			this->addText11->Name = L"addText11";
			this->addText11->Size = System::Drawing::Size(143, 25);
			this->addText11->TabIndex = 21;
			this->addText11->Text = L"Total Weight:";
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(44, 430);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(684, 69);
			this->button4->TabIndex = 15;
			this->button4->Text = L"Delete Section";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &form::deleteSectionButton);
			// 
			// sectionNamesDisplay
			// 
			this->sectionNamesDisplay->Cursor = System::Windows::Forms::Cursors::Hand;
			this->sectionNamesDisplay->Font = (gcnew System::Drawing::Font(L"Courier New", 10.125F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sectionNamesDisplay->FormattingEnabled = true;
			this->sectionNamesDisplay->ItemHeight = 30;
			this->sectionNamesDisplay->Location = System::Drawing::Point(44, 90);
			this->sectionNamesDisplay->Name = L"sectionNamesDisplay";
			this->sectionNamesDisplay->Size = System::Drawing::Size(684, 334);
			this->sectionNamesDisplay->TabIndex = 14;
			this->sectionNamesDisplay->SelectedIndexChanged += gcnew System::EventHandler(this, &form::sectionNamesDisplay_SelectedIndexChanged);
			// 
			// addText10
			// 
			this->addText10->BackColor = System::Drawing::Color::Transparent;
			this->addText10->Location = System::Drawing::Point(633, 62);
			this->addText10->Name = L"addText10";
			this->addText10->Size = System::Drawing::Size(95, 25);
			this->addText10->TabIndex = 13;
			this->addText10->Text = L"Weight:";
			// 
			// addText9
			// 
			this->addText9->BackColor = System::Drawing::Color::Transparent;
			this->addText9->Location = System::Drawing::Point(39, 62);
			this->addText9->Name = L"addText9";
			this->addText9->Size = System::Drawing::Size(203, 25);
			this->addText9->TabIndex = 12;
			this->addText9->Text = L"Section Name:";
			// 
			// addText8
			// 
			this->addText8->BackColor = System::Drawing::Color::Transparent;
			this->addText8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText8->Location = System::Drawing::Point(172, 18);
			this->addText8->Name = L"addText8";
			this->addText8->Size = System::Drawing::Size(439, 45);
			this->addText8->TabIndex = 0;
			this->addText8->Text = L"Sections of Class";
			this->addText8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// addClassPanel2
			// 
			this->addClassPanel2->BackColor = System::Drawing::Color::Bisque;
			this->addClassPanel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->addClassPanel2->Controls->Add(this->amountSubInput);
			this->addClassPanel2->Controls->Add(this->percentInput);
			this->addClassPanel2->Controls->Add(this->addText21);
			this->addClassPanel2->Controls->Add(this->addText17);
			this->addClassPanel2->Controls->Add(this->button1);
			this->addClassPanel2->Controls->Add(this->amountSubText);
			this->addClassPanel2->Controls->Add(this->percentText);
			this->addClassPanel2->Controls->Add(this->sectionNameInput);
			this->addClassPanel2->Controls->Add(this->sectionNameText);
			this->addClassPanel2->Controls->Add(this->addText2);
			this->addClassPanel2->Location = System::Drawing::Point(24, 226);
			this->addClassPanel2->Name = L"addClassPanel2";
			this->addClassPanel2->Size = System::Drawing::Size(774, 389);
			this->addClassPanel2->TabIndex = 7;
			// 
			// amountSubInput
			// 
			this->amountSubInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->amountSubInput->Location = System::Drawing::Point(482, 233);
			this->amountSubInput->Name = L"amountSubInput";
			this->amountSubInput->Size = System::Drawing::Size(137, 44);
			this->amountSubInput->TabIndex = 4;
			this->amountSubInput->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// percentInput
			// 
			this->percentInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->percentInput->Location = System::Drawing::Point(112, 228);
			this->percentInput->Name = L"percentInput";
			this->percentInput->Size = System::Drawing::Size(137, 44);
			this->percentInput->TabIndex = 3;
			this->percentInput->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// addText21
			// 
			this->addText21->BackColor = System::Drawing::Color::Transparent;
			this->addText21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText21->Location = System::Drawing::Point(625, 216);
			this->addText21->Name = L"addText21";
			this->addText21->Size = System::Drawing::Size(138, 74);
			this->addText21->TabIndex = 10;
			this->addText21->Text = L"Amount cannot be 1";
			this->addText21->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// addText17
			// 
			this->addText17->BackColor = System::Drawing::Color::Transparent;
			this->addText17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText17->Location = System::Drawing::Point(270, 226);
			this->addText17->Name = L"addText17";
			this->addText17->Size = System::Drawing::Size(67, 56);
			this->addText17->TabIndex = 9;
			this->addText17->Text = L"%";
			this->addText17->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(29, 295);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(695, 69);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Add Section";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &form::addSectionButton);
			// 
			// amountSubText
			// 
			this->amountSubText->BackColor = System::Drawing::Color::Transparent;
			this->amountSubText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->amountSubText->Location = System::Drawing::Point(437, 129);
			this->amountSubText->Name = L"amountSubText";
			this->amountSubText->Size = System::Drawing::Size(225, 93);
			this->amountSubText->TabIndex = 7;
			this->amountSubText->Text = L"Amount of Sub Grades:";
			this->amountSubText->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// percentText
			// 
			this->percentText->BackColor = System::Drawing::Color::Transparent;
			this->percentText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->percentText->Location = System::Drawing::Point(44, 129);
			this->percentText->Name = L"percentText";
			this->percentText->Size = System::Drawing::Size(293, 93);
			this->percentText->TabIndex = 5;
			this->percentText->Text = L"Percentage of Class Grade:";
			this->percentText->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// sectionNameInput
			// 
			this->sectionNameInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sectionNameInput->Location = System::Drawing::Point(255, 70);
			this->sectionNameInput->Name = L"sectionNameInput";
			this->sectionNameInput->Size = System::Drawing::Size(469, 44);
			this->sectionNameInput->TabIndex = 2;
			this->sectionNameInput->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->sectionNameInput->TextChanged += gcnew System::EventHandler(this, &form::sectionNameInput_TextChanged);
			// 
			// sectionNameText
			// 
			this->sectionNameText->BackColor = System::Drawing::Color::Transparent;
			this->sectionNameText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->sectionNameText->Location = System::Drawing::Point(22, 68);
			this->sectionNameText->Name = L"sectionNameText";
			this->sectionNameText->Size = System::Drawing::Size(227, 46);
			this->sectionNameText->TabIndex = 3;
			this->sectionNameText->Text = L"Section Name:";
			this->sectionNameText->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// addText2
			// 
			this->addText2->BackColor = System::Drawing::Color::Transparent;
			this->addText2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText2->Location = System::Drawing::Point(3, 0);
			this->addText2->Name = L"addText2";
			this->addText2->Size = System::Drawing::Size(769, 45);
			this->addText2->TabIndex = 0;
			this->addText2->Text = L"Add New Section";
			this->addText2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// classNamePanel
			// 
			this->classNamePanel->BackColor = System::Drawing::Color::Bisque;
			this->classNamePanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->classNamePanel->Controls->Add(this->classNameInput);
			this->classNamePanel->Controls->Add(this->addText1);
			this->classNamePanel->Location = System::Drawing::Point(24, 96);
			this->classNamePanel->Name = L"classNamePanel";
			this->classNamePanel->Size = System::Drawing::Size(774, 114);
			this->classNamePanel->TabIndex = 6;
			// 
			// classNameInput
			// 
			this->classNameInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->classNameInput->Location = System::Drawing::Point(255, 35);
			this->classNameInput->Name = L"classNameInput";
			this->classNameInput->Size = System::Drawing::Size(469, 44);
			this->classNameInput->TabIndex = 0;
			this->classNameInput->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->classNameInput->TextChanged += gcnew System::EventHandler(this, &form::summaryUpdateName);
			// 
			// addText1
			// 
			this->addText1->BackColor = System::Drawing::Color::Transparent;
			this->addText1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addText1->Location = System::Drawing::Point(22, 33);
			this->addText1->Name = L"addText1";
			this->addText1->Size = System::Drawing::Size(206, 46);
			this->addText1->TabIndex = 1;
			this->addText1->Text = L"Class Name:";
			this->addText1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// tab2
			// 
			this->tab2->BackColor = System::Drawing::Color::Tan;
			this->tab2->Controls->Add(this->deletingClassMessage);
			this->tab2->Controls->Add(this->changeGradesPanel4);
			this->tab2->Controls->Add(this->changeGradesPanel3);
			this->tab2->Controls->Add(this->changeGradesPanel2);
			this->tab2->Controls->Add(this->changeGradesPanel1);
			this->tab2->Location = System::Drawing::Point(8, 8);
			this->tab2->Name = L"tab2";
			this->tab2->Size = System::Drawing::Size(1702, 1042);
			this->tab2->TabIndex = 2;
			this->tab2->Text = L"Change Grades";
			this->tab2->Enter += gcnew System::EventHandler(this, &form::tabPage3_Enter);
			// 
			// deletingClassMessage
			// 
			this->deletingClassMessage->BackColor = System::Drawing::Color::Green;
			this->deletingClassMessage->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->deletingClassMessage->Controls->Add(this->label1);
			this->deletingClassMessage->Location = System::Drawing::Point(62, 350);
			this->deletingClassMessage->Name = L"deletingClassMessage";
			this->deletingClassMessage->Size = System::Drawing::Size(1500, 79);
			this->deletingClassMessage->TabIndex = 4;
			this->deletingClassMessage->Visible = false;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(-2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(1480, 70);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Deleting class, please wait...";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// changeGradesPanel4
			// 
			this->changeGradesPanel4->BackColor = System::Drawing::Color::Bisque;
			this->changeGradesPanel4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->changeGradesPanel4->Controls->Add(this->classesSavedIndicator);
			this->changeGradesPanel4->Controls->Add(this->CGSaveGradesButton);
			this->changeGradesPanel4->Controls->Add(this->changeGradeText8);
			this->changeGradesPanel4->Location = System::Drawing::Point(943, 738);
			this->changeGradesPanel4->Name = L"changeGradesPanel4";
			this->changeGradesPanel4->Size = System::Drawing::Size(619, 262);
			this->changeGradesPanel4->TabIndex = 4;
			// 
			// classesSavedIndicator
			// 
			this->classesSavedIndicator->BackColor = System::Drawing::Color::Green;
			this->classesSavedIndicator->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->classesSavedIndicator->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->classesSavedIndicator->ForeColor = System::Drawing::Color::White;
			this->classesSavedIndicator->Location = System::Drawing::Point(20, 72);
			this->classesSavedIndicator->Name = L"classesSavedIndicator";
			this->classesSavedIndicator->Size = System::Drawing::Size(577, 81);
			this->classesSavedIndicator->TabIndex = 7;
			this->classesSavedIndicator->Text = L"Saved!";
			this->classesSavedIndicator->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// CGSaveGradesButton
			// 
			this->CGSaveGradesButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CGSaveGradesButton->Location = System::Drawing::Point(14, 168);
			this->CGSaveGradesButton->Name = L"CGSaveGradesButton";
			this->CGSaveGradesButton->Size = System::Drawing::Size(583, 64);
			this->CGSaveGradesButton->TabIndex = 6;
			this->CGSaveGradesButton->Text = L"Save Grades";
			this->CGSaveGradesButton->UseVisualStyleBackColor = true;
			this->CGSaveGradesButton->Click += gcnew System::EventHandler(this, &form::CGSaveGradesButton_Click);
			// 
			// changeGradeText8
			// 
			this->changeGradeText8->BackColor = System::Drawing::Color::Transparent;
			this->changeGradeText8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->changeGradeText8->Location = System::Drawing::Point(-2, 19);
			this->changeGradeText8->Name = L"changeGradeText8";
			this->changeGradeText8->Size = System::Drawing::Size(619, 37);
			this->changeGradeText8->TabIndex = 1;
			this->changeGradeText8->Text = L"Save All Classes";
			this->changeGradeText8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// changeGradesPanel3
			// 
			this->changeGradesPanel3->BackColor = System::Drawing::Color::Bisque;
			this->changeGradesPanel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->changeGradesPanel3->Controls->Add(this->CGResetGradeButton);
			this->changeGradesPanel3->Controls->Add(this->CGChangeGradeButton);
			this->changeGradesPanel3->Controls->Add(this->CHChangeGradeInput);
			this->changeGradesPanel3->Controls->Add(this->changeGradeText7);
			this->changeGradesPanel3->Controls->Add(this->changeGradeText6);
			this->changeGradesPanel3->Location = System::Drawing::Point(943, 451);
			this->changeGradesPanel3->Name = L"changeGradesPanel3";
			this->changeGradesPanel3->Size = System::Drawing::Size(619, 266);
			this->changeGradesPanel3->TabIndex = 3;
			// 
			// CGResetGradeButton
			// 
			this->CGResetGradeButton->Location = System::Drawing::Point(447, 59);
			this->CGResetGradeButton->Name = L"CGResetGradeButton";
			this->CGResetGradeButton->Size = System::Drawing::Size(150, 37);
			this->CGResetGradeButton->TabIndex = 6;
			this->CGResetGradeButton->Text = L"Reset Grade";
			this->CGResetGradeButton->UseVisualStyleBackColor = true;
			this->CGResetGradeButton->Click += gcnew System::EventHandler(this, &form::CGChangeGrade);
			// 
			// CGChangeGradeButton
			// 
			this->CGChangeGradeButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->CGChangeGradeButton->Location = System::Drawing::Point(20, 167);
			this->CGChangeGradeButton->Name = L"CGChangeGradeButton";
			this->CGChangeGradeButton->Size = System::Drawing::Size(577, 64);
			this->CGChangeGradeButton->TabIndex = 5;
			this->CGChangeGradeButton->Text = L"Change Grade";
			this->CGChangeGradeButton->UseVisualStyleBackColor = true;
			this->CGChangeGradeButton->Click += gcnew System::EventHandler(this, &form::CGChangeGrade);
			// 
			// CHChangeGradeInput
			// 
			this->CHChangeGradeInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->CHChangeGradeInput->Location = System::Drawing::Point(275, 108);
			this->CHChangeGradeInput->Name = L"CHChangeGradeInput";
			this->CHChangeGradeInput->Size = System::Drawing::Size(322, 44);
			this->CHChangeGradeInput->TabIndex = 4;
			this->CHChangeGradeInput->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// changeGradeText7
			// 
			this->changeGradeText7->BackColor = System::Drawing::Color::Transparent;
			this->changeGradeText7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->changeGradeText7->Location = System::Drawing::Point(13, 97);
			this->changeGradeText7->Name = L"changeGradeText7";
			this->changeGradeText7->Size = System::Drawing::Size(256, 64);
			this->changeGradeText7->TabIndex = 2;
			this->changeGradeText7->Text = L"Change Grade:";
			this->changeGradeText7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// changeGradeText6
			// 
			this->changeGradeText6->BackColor = System::Drawing::Color::Transparent;
			this->changeGradeText6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->changeGradeText6->Location = System::Drawing::Point(-2, 19);
			this->changeGradeText6->Name = L"changeGradeText6";
			this->changeGradeText6->Size = System::Drawing::Size(619, 37);
			this->changeGradeText6->TabIndex = 1;
			this->changeGradeText6->Text = L"Edit Selected Grade";
			this->changeGradeText6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// changeGradesPanel2
			// 
			this->changeGradesPanel2->BackColor = System::Drawing::Color::Bisque;
			this->changeGradesPanel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->changeGradesPanel2->Controls->Add(this->changingGradeDisplayText);
			this->changeGradesPanel2->Controls->Add(this->changeGradeText9);
			this->changeGradesPanel2->Controls->Add(this->changeGradeText5);
			this->changeGradesPanel2->Controls->Add(this->CGsubSectionDisplay);
			this->changeGradesPanel2->Controls->Add(this->changeGradeText4);
			this->changeGradesPanel2->Controls->Add(this->CGSectionDisplay);
			this->changeGradesPanel2->Location = System::Drawing::Point(62, 451);
			this->changeGradesPanel2->Name = L"changeGradesPanel2";
			this->changeGradesPanel2->Size = System::Drawing::Size(862, 549);
			this->changeGradesPanel2->TabIndex = 2;
			// 
			// changingGradeDisplayText
			// 
			this->changingGradeDisplayText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->changingGradeDisplayText->ForeColor = System::Drawing::Color::Black;
			this->changingGradeDisplayText->Location = System::Drawing::Point(398, 500);
			this->changingGradeDisplayText->Name = L"changingGradeDisplayText";
			this->changingGradeDisplayText->Size = System::Drawing::Size(437, 45);
			this->changingGradeDisplayText->TabIndex = 5;
			this->changingGradeDisplayText->Text = L"Name of target";
			this->changingGradeDisplayText->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// changeGradeText9
			// 
			this->changeGradeText9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->changeGradeText9->ForeColor = System::Drawing::Color::Black;
			this->changeGradeText9->Location = System::Drawing::Point(69, 500);
			this->changeGradeText9->Name = L"changeGradeText9";
			this->changeGradeText9->Size = System::Drawing::Size(323, 45);
			this->changeGradeText9->TabIndex = 4;
			this->changeGradeText9->Text = L"Changing Grade for:";
			this->changeGradeText9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// changeGradeText5
			// 
			this->changeGradeText5->BackColor = System::Drawing::Color::Transparent;
			this->changeGradeText5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->changeGradeText5->Location = System::Drawing::Point(437, 10);
			this->changeGradeText5->Name = L"changeGradeText5";
			this->changeGradeText5->Size = System::Drawing::Size(398, 37);
			this->changeGradeText5->TabIndex = 3;
			this->changeGradeText5->Text = L"Subs of Sections";
			this->changeGradeText5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// CGsubSectionDisplay
			// 
			this->CGsubSectionDisplay->Font = (gcnew System::Drawing::Font(L"Courier New", 12));
			this->CGsubSectionDisplay->FormattingEnabled = true;
			this->CGsubSectionDisplay->ItemHeight = 36;
			this->CGsubSectionDisplay->Location = System::Drawing::Point(437, 61);
			this->CGsubSectionDisplay->Name = L"CGsubSectionDisplay";
			this->CGsubSectionDisplay->Size = System::Drawing::Size(398, 436);
			this->CGsubSectionDisplay->TabIndex = 2;
			this->CGsubSectionDisplay->SelectedIndexChanged += gcnew System::EventHandler(this, &form::CGsubSectionDisplay_SelectedIndexChanged);
			// 
			// changeGradeText4
			// 
			this->changeGradeText4->BackColor = System::Drawing::Color::Transparent;
			this->changeGradeText4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->changeGradeText4->Location = System::Drawing::Point(19, 10);
			this->changeGradeText4->Name = L"changeGradeText4";
			this->changeGradeText4->Size = System::Drawing::Size(390, 37);
			this->changeGradeText4->TabIndex = 1;
			this->changeGradeText4->Text = L"Sections of Class";
			this->changeGradeText4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// CGSectionDisplay
			// 
			this->CGSectionDisplay->Font = (gcnew System::Drawing::Font(L"Courier New", 12));
			this->CGSectionDisplay->FormattingEnabled = true;
			this->CGSectionDisplay->ItemHeight = 36;
			this->CGSectionDisplay->Location = System::Drawing::Point(19, 61);
			this->CGSectionDisplay->Name = L"CGSectionDisplay";
			this->CGSectionDisplay->Size = System::Drawing::Size(412, 436);
			this->CGSectionDisplay->TabIndex = 0;
			this->CGSectionDisplay->SelectedIndexChanged += gcnew System::EventHandler(this, &form::CGSectionDisplay_SelectedIndexChanged);
			// 
			// changeGradesPanel1
			// 
			this->changeGradesPanel1->BackColor = System::Drawing::Color::Bisque;
			this->changeGradesPanel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->changeGradesPanel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->changeGradesPanel1->Controls->Add(this->CGDeleteClass);
			this->changeGradesPanel1->Controls->Add(this->changeGradeText3);
			this->changeGradesPanel1->Controls->Add(this->changeGradeText2);
			this->changeGradesPanel1->Controls->Add(this->chooseClassDisplay);
			this->changeGradesPanel1->Controls->Add(this->changeGradeText1);
			this->changeGradesPanel1->Location = System::Drawing::Point(62, 45);
			this->changeGradesPanel1->Name = L"changeGradesPanel1";
			this->changeGradesPanel1->Size = System::Drawing::Size(1500, 384);
			this->changeGradesPanel1->TabIndex = 1;
			// 
			// CGDeleteClass
			// 
			this->CGDeleteClass->Location = System::Drawing::Point(1271, 319);
			this->CGDeleteClass->Name = L"CGDeleteClass";
			this->CGDeleteClass->Size = System::Drawing::Size(207, 52);
			this->CGDeleteClass->TabIndex = 3;
			this->CGDeleteClass->Text = L"Delete Class";
			this->CGDeleteClass->UseVisualStyleBackColor = true;
			this->CGDeleteClass->Click += gcnew System::EventHandler(this, &form::CGDeleteClass_Click);
			// 
			// changeGradeText3
			// 
			this->changeGradeText3->BackColor = System::Drawing::Color::Transparent;
			this->changeGradeText3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->changeGradeText3->Location = System::Drawing::Point(1269, 55);
			this->changeGradeText3->Name = L"changeGradeText3";
			this->changeGradeText3->Size = System::Drawing::Size(209, 35);
			this->changeGradeText3->TabIndex = 2;
			this->changeGradeText3->Text = L"Class Grade:";
			// 
			// changeGradeText2
			// 
			this->changeGradeText2->BackColor = System::Drawing::Color::Transparent;
			this->changeGradeText2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->changeGradeText2->Location = System::Drawing::Point(13, 55);
			this->changeGradeText2->Name = L"changeGradeText2";
			this->changeGradeText2->Size = System::Drawing::Size(234, 35);
			this->changeGradeText2->TabIndex = 1;
			this->changeGradeText2->Text = L"Class Name:";
			// 
			// chooseClassDisplay
			// 
			this->chooseClassDisplay->Font = (gcnew System::Drawing::Font(L"Courier New", 12));
			this->chooseClassDisplay->FormattingEnabled = true;
			this->chooseClassDisplay->ItemHeight = 36;
			this->chooseClassDisplay->Location = System::Drawing::Point(20, 93);
			this->chooseClassDisplay->Name = L"chooseClassDisplay";
			this->chooseClassDisplay->Size = System::Drawing::Size(1458, 220);
			this->chooseClassDisplay->TabIndex = 0;
			this->chooseClassDisplay->SelectedIndexChanged += gcnew System::EventHandler(this, &form::chooseClassDisplay_SelectedIndexChanged);
			// 
			// changeGradeText1
			// 
			this->changeGradeText1->BackColor = System::Drawing::Color::Transparent;
			this->changeGradeText1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->changeGradeText1->Location = System::Drawing::Point(531, 18);
			this->changeGradeText1->Name = L"changeGradeText1";
			this->changeGradeText1->Size = System::Drawing::Size(389, 58);
			this->changeGradeText1->TabIndex = 0;
			this->changeGradeText1->Text = L"Choose class to edit:";
			this->changeGradeText1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tab3
			// 
			this->tab3->BackColor = System::Drawing::Color::Tan;
			this->tab3->Controls->Add(this->TSPanel6);
			this->tab3->Controls->Add(this->TSPanel3);
			this->tab3->Controls->Add(this->flowLayoutPanel1);
			this->tab3->Controls->Add(this->TSPanel1);
			this->tab3->Location = System::Drawing::Point(8, 8);
			this->tab3->Name = L"tab3";
			this->tab3->Padding = System::Windows::Forms::Padding(3);
			this->tab3->Size = System::Drawing::Size(1702, 1042);
			this->tab3->TabIndex = 1;
			this->tab3->Text = L"Test Scenarios";
			this->tab3->Enter += gcnew System::EventHandler(this, &form::tab3_Enter);
			this->tab3->Leave += gcnew System::EventHandler(this, &form::tab3_Leave);
			// 
			// TSPanel6
			// 
			this->TSPanel6->BackColor = System::Drawing::Color::Bisque;
			this->TSPanel6->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->TSPanel6->Controls->Add(this->TSSaveThisClassButton);
			this->TSPanel6->Controls->Add(this->TSResetAllGradesButton);
			this->TSPanel6->Location = System::Drawing::Point(63, 861);
			this->TSPanel6->Name = L"TSPanel6";
			this->TSPanel6->Size = System::Drawing::Size(1499, 142);
			this->TSPanel6->TabIndex = 12;
			// 
			// TSSaveThisClassButton
			// 
			this->TSSaveThisClassButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->TSSaveThisClassButton->Location = System::Drawing::Point(758, 25);
			this->TSSaveThisClassButton->Name = L"TSSaveThisClassButton";
			this->TSSaveThisClassButton->Size = System::Drawing::Size(711, 98);
			this->TSSaveThisClassButton->TabIndex = 10;
			this->TSSaveThisClassButton->Text = L"Save Class Grades";
			this->TSSaveThisClassButton->UseVisualStyleBackColor = true;
			this->TSSaveThisClassButton->Click += gcnew System::EventHandler(this, &form::TSSaveThisClassButton_Click);
			// 
			// TSResetAllGradesButton
			// 
			this->TSResetAllGradesButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->TSResetAllGradesButton->Location = System::Drawing::Point(25, 25);
			this->TSResetAllGradesButton->Name = L"TSResetAllGradesButton";
			this->TSResetAllGradesButton->Size = System::Drawing::Size(694, 98);
			this->TSResetAllGradesButton->TabIndex = 9;
			this->TSResetAllGradesButton->Text = L"Reset Test Scenarios";
			this->TSResetAllGradesButton->UseVisualStyleBackColor = true;
			this->TSResetAllGradesButton->Click += gcnew System::EventHandler(this, &form::TSResetAllGradesButton_Click);
			// 
			// TSPanel3
			// 
			this->TSPanel3->BackColor = System::Drawing::Color::Bisque;
			this->TSPanel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->TSPanel3->Controls->Add(this->TSPanel5);
			this->TSPanel3->Controls->Add(this->TSSubSectionsDisplay);
			this->TSPanel3->Controls->Add(this->TSSectionsDisplay);
			this->TSPanel3->Controls->Add(this->TSPanel4);
			this->TSPanel3->Location = System::Drawing::Point(27, 236);
			this->TSPanel3->Name = L"TSPanel3";
			this->TSPanel3->Size = System::Drawing::Size(1565, 585);
			this->TSPanel3->TabIndex = 4;
			// 
			// TSPanel5
			// 
			this->TSPanel5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->TSPanel5->Controls->Add(this->TSDisplayGradeBottom);
			this->TSPanel5->Controls->Add(this->changeGradeTrack);
			this->TSPanel5->Controls->Add(this->TSText7);
			this->TSPanel5->Location = System::Drawing::Point(34, 420);
			this->TSPanel5->Name = L"TSPanel5";
			this->TSPanel5->Size = System::Drawing::Size(1499, 133);
			this->TSPanel5->TabIndex = 8;
			// 
			// TSDisplayGradeBottom
			// 
			this->TSDisplayGradeBottom->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->TSDisplayGradeBottom->Location = System::Drawing::Point(1353, 17);
			this->TSDisplayGradeBottom->Name = L"TSDisplayGradeBottom";
			this->TSDisplayGradeBottom->Size = System::Drawing::Size(118, 100);
			this->TSDisplayGradeBottom->TabIndex = 8;
			this->TSDisplayGradeBottom->Text = L"100.00";
			this->TSDisplayGradeBottom->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// changeGradeTrack
			// 
			this->changeGradeTrack->Location = System::Drawing::Point(325, 27);
			this->changeGradeTrack->Maximum = 100;
			this->changeGradeTrack->Name = L"changeGradeTrack";
			this->changeGradeTrack->Size = System::Drawing::Size(1012, 90);
			this->changeGradeTrack->TabIndex = 6;
			this->changeGradeTrack->Value = 50;
			this->changeGradeTrack->Scroll += gcnew System::EventHandler(this, &form::changeGradeTrack_Scroll);
			// 
			// TSText7
			// 
			this->TSText7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TSText7->Location = System::Drawing::Point(22, 17);
			this->TSText7->Name = L"TSText7";
			this->TSText7->Size = System::Drawing::Size(275, 100);
			this->TSText7->TabIndex = 7;
			this->TSText7->Text = L"Change Grade:";
			this->TSText7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TSSubSectionsDisplay
			// 
			this->TSSubSectionsDisplay->Font = (gcnew System::Drawing::Font(L"Courier New", 12));
			this->TSSubSectionsDisplay->FormattingEnabled = true;
			this->TSSubSectionsDisplay->ItemHeight = 36;
			this->TSSubSectionsDisplay->Location = System::Drawing::Point(794, 185);
			this->TSSubSectionsDisplay->Name = L"TSSubSectionsDisplay";
			this->TSSubSectionsDisplay->Size = System::Drawing::Size(739, 220);
			this->TSSubSectionsDisplay->TabIndex = 3;
			this->TSSubSectionsDisplay->SelectedIndexChanged += gcnew System::EventHandler(this, &form::TSSubSectionsDisplay_SelectedIndexChanged);
			// 
			// TSSectionsDisplay
			// 
			this->TSSectionsDisplay->Font = (gcnew System::Drawing::Font(L"Courier New", 12));
			this->TSSectionsDisplay->FormattingEnabled = true;
			this->TSSectionsDisplay->ItemHeight = 36;
			this->TSSectionsDisplay->Location = System::Drawing::Point(34, 182);
			this->TSSectionsDisplay->Name = L"TSSectionsDisplay";
			this->TSSectionsDisplay->Size = System::Drawing::Size(721, 220);
			this->TSSectionsDisplay->TabIndex = 2;
			this->TSSectionsDisplay->SelectedIndexChanged += gcnew System::EventHandler(this, &form::TSSectionsDisplay_SelectedIndexChanged);
			// 
			// TSPanel4
			// 
			this->TSPanel4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->TSPanel4->Controls->Add(this->TSDisplayGradeTop);
			this->TSPanel4->Controls->Add(this->TSText6);
			this->TSPanel4->Controls->Add(this->TSText4);
			this->TSPanel4->Controls->Add(this->TSText5);
			this->TSPanel4->Location = System::Drawing::Point(34, 21);
			this->TSPanel4->Name = L"TSPanel4";
			this->TSPanel4->Size = System::Drawing::Size(1499, 144);
			this->TSPanel4->TabIndex = 1;
			// 
			// TSDisplayGradeTop
			// 
			this->TSDisplayGradeTop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TSDisplayGradeTop->Location = System::Drawing::Point(792, 18);
			this->TSDisplayGradeTop->Name = L"TSDisplayGradeTop";
			this->TSDisplayGradeTop->Size = System::Drawing::Size(178, 52);
			this->TSDisplayGradeTop->TabIndex = 1;
			this->TSDisplayGradeTop->Text = L"100.00";
			this->TSDisplayGradeTop->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TSText6
			// 
			this->TSText6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TSText6->Location = System::Drawing::Point(771, 85);
			this->TSText6->Name = L"TSText6";
			this->TSText6->Size = System::Drawing::Size(721, 55);
			this->TSText6->TabIndex = 5;
			this->TSText6->Text = L"Sub Sections:";
			this->TSText6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TSText4
			// 
			this->TSText4->BackColor = System::Drawing::Color::Transparent;
			this->TSText4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TSText4->Location = System::Drawing::Point(474, 0);
			this->TSText4->Name = L"TSText4";
			this->TSText4->Size = System::Drawing::Size(267, 89);
			this->TSText4->TabIndex = 0;
			this->TSText4->Text = L"Class Grade:";
			this->TSText4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TSText5
			// 
			this->TSText5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TSText5->Location = System::Drawing::Point(-2, 85);
			this->TSText5->Name = L"TSText5";
			this->TSText5->Size = System::Drawing::Size(721, 55);
			this->TSText5->TabIndex = 4;
			this->TSText5->Text = L"Sections:";
			this->TSText5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Location = System::Drawing::Point(1198, 409);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(8, 8);
			this->flowLayoutPanel1->TabIndex = 3;
			// 
			// TSPanel1
			// 
			this->TSPanel1->BackColor = System::Drawing::Color::Bisque;
			this->TSPanel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->TSPanel1->Controls->Add(this->TSText2);
			this->TSPanel1->Controls->Add(this->TSPanel2);
			this->TSPanel1->Controls->Add(this->TSText1);
			this->TSPanel1->Location = System::Drawing::Point(27, 31);
			this->TSPanel1->Name = L"TSPanel1";
			this->TSPanel1->Size = System::Drawing::Size(1565, 171);
			this->TSPanel1->TabIndex = 1;
			// 
			// TSText2
			// 
			this->TSText2->BackColor = System::Drawing::Color::Transparent;
			this->TSText2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TSText2->Location = System::Drawing::Point(-2, 82);
			this->TSText2->Name = L"TSText2";
			this->TSText2->Size = System::Drawing::Size(706, 58);
			this->TSText2->TabIndex = 1;
			this->TSText2->Text = L"Note: Any chages made here are not saved";
			this->TSText2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TSPanel2
			// 
			this->TSPanel2->BackColor = System::Drawing::Color::Transparent;
			this->TSPanel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->TSPanel2->Controls->Add(this->TSChooseClassBox);
			this->TSPanel2->Controls->Add(this->TSText3);
			this->TSPanel2->Location = System::Drawing::Point(761, 30);
			this->TSPanel2->Name = L"TSPanel2";
			this->TSPanel2->Size = System::Drawing::Size(772, 110);
			this->TSPanel2->TabIndex = 2;
			// 
			// TSChooseClassBox
			// 
			this->TSChooseClassBox->BackColor = System::Drawing::SystemColors::Window;
			this->TSChooseClassBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TSChooseClassBox->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->TSChooseClassBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TSChooseClassBox->FormattingEnabled = true;
			this->TSChooseClassBox->Location = System::Drawing::Point(249, 32);
			this->TSChooseClassBox->Name = L"TSChooseClassBox";
			this->TSChooseClassBox->Size = System::Drawing::Size(493, 45);
			this->TSChooseClassBox->TabIndex = 7;
			this->TSChooseClassBox->SelectedIndexChanged += gcnew System::EventHandler(this, &form::TSChooseClassBox_SelectedIndexChanged);
			// 
			// TSText3
			// 
			this->TSText3->BackColor = System::Drawing::Color::Transparent;
			this->TSText3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TSText3->Location = System::Drawing::Point(3, 30);
			this->TSText3->Name = L"TSText3";
			this->TSText3->Size = System::Drawing::Size(240, 47);
			this->TSText3->TabIndex = 0;
			this->TSText3->Text = L"Choose Class:";
			this->TSText3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// TSText1
			// 
			this->TSText1->BackColor = System::Drawing::Color::Transparent;
			this->TSText1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->TSText1->Location = System::Drawing::Point(-2, 0);
			this->TSText1->Name = L"TSText1";
			this->TSText1->Size = System::Drawing::Size(706, 82);
			this->TSText1->TabIndex = 0;
			this->TSText1->Text = L"Test Scenarios";
			this->TSText1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// tab4
			// 
			this->tab4->BackColor = System::Drawing::Color::Tan;
			this->tab4->Controls->Add(this->settingsAdminButton);
			this->tab4->Controls->Add(this->settingsPanel3);
			this->tab4->Controls->Add(this->settingsPanel2);
			this->tab4->Controls->Add(this->settingsPanel1);
			this->tab4->Location = System::Drawing::Point(8, 8);
			this->tab4->Name = L"tab4";
			this->tab4->Size = System::Drawing::Size(1702, 1042);
			this->tab4->TabIndex = 3;
			this->tab4->Text = L"Settings";
			this->tab4->Enter += gcnew System::EventHandler(this, &form::tabPage3_Click);
			// 
			// settingsAdminButton
			// 
			this->settingsAdminButton->Location = System::Drawing::Point(1421, 34);
			this->settingsAdminButton->Name = L"settingsAdminButton";
			this->settingsAdminButton->Size = System::Drawing::Size(200, 93);
			this->settingsAdminButton->TabIndex = 5;
			this->settingsAdminButton->Text = L"Open Admin";
			this->settingsAdminButton->UseVisualStyleBackColor = true;
			this->settingsAdminButton->Click += gcnew System::EventHandler(this, &form::settingsAdminButton_Click);
			// 
			// settingsPanel3
			// 
			this->settingsPanel3->BackColor = System::Drawing::Color::Bisque;
			this->settingsPanel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->settingsPanel3->Controls->Add(this->settingsHider2);
			this->settingsPanel3->Controls->Add(this->settingsOpenExplorer);
			this->settingsPanel3->Controls->Add(this->settingsOpenChosenClassFile);
			this->settingsPanel3->Controls->Add(this->label2);
			this->settingsPanel3->Controls->Add(this->settingsDisplayClasses);
			this->settingsPanel3->Controls->Add(this->settingsStatusOutput);
			this->settingsPanel3->Controls->Add(this->settingsOpenAllClassFIle);
			this->settingsPanel3->Controls->Add(this->label6);
			this->settingsPanel3->Controls->Add(this->button3);
			this->settingsPanel3->Location = System::Drawing::Point(732, 34);
			this->settingsPanel3->Name = L"settingsPanel3";
			this->settingsPanel3->Size = System::Drawing::Size(671, 876);
			this->settingsPanel3->TabIndex = 4;
			// 
			// settingsHider2
			// 
			this->settingsHider2->Controls->Add(this->settingsCorruptNameText);
			this->settingsHider2->Controls->Add(this->settingsSetFormNameButton);
			this->settingsHider2->Controls->Add(this->settingsSetFormNameInput);
			this->settingsHider2->Controls->Add(this->settingsText9);
			this->settingsHider2->Location = System::Drawing::Point(3, 3);
			this->settingsHider2->Name = L"settingsHider2";
			this->settingsHider2->Size = System::Drawing::Size(661, 866);
			this->settingsHider2->TabIndex = 8;
			// 
			// settingsCorruptNameText
			// 
			this->settingsCorruptNameText->AutoSize = true;
			this->settingsCorruptNameText->BackColor = System::Drawing::Color::Red;
			this->settingsCorruptNameText->ForeColor = System::Drawing::Color::White;
			this->settingsCorruptNameText->Location = System::Drawing::Point(157, 7);
			this->settingsCorruptNameText->Name = L"settingsCorruptNameText";
			this->settingsCorruptNameText->Size = System::Drawing::Size(356, 25);
			this->settingsCorruptNameText->TabIndex = 13;
			this->settingsCorruptNameText->Text = L"Corruption at customFormName file!";
			this->settingsCorruptNameText->Visible = false;
			// 
			// settingsSetFormNameButton
			// 
			this->settingsSetFormNameButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->settingsSetFormNameButton->Location = System::Drawing::Point(82, 167);
			this->settingsSetFormNameButton->Name = L"settingsSetFormNameButton";
			this->settingsSetFormNameButton->Size = System::Drawing::Size(492, 47);
			this->settingsSetFormNameButton->TabIndex = 2;
			this->settingsSetFormNameButton->Text = L"Save Name";
			this->settingsSetFormNameButton->UseVisualStyleBackColor = true;
			this->settingsSetFormNameButton->Click += gcnew System::EventHandler(this, &form::settingsSetFormNameButton_Click);
			// 
			// settingsSetFormNameInput
			// 
			this->settingsSetFormNameInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->settingsSetFormNameInput->Location = System::Drawing::Point(82, 108);
			this->settingsSetFormNameInput->Name = L"settingsSetFormNameInput";
			this->settingsSetFormNameInput->Size = System::Drawing::Size(492, 44);
			this->settingsSetFormNameInput->TabIndex = 1;
			this->settingsSetFormNameInput->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// settingsText9
			// 
			this->settingsText9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->settingsText9->Location = System::Drawing::Point(7, 26);
			this->settingsText9->Name = L"settingsText9";
			this->settingsText9->Size = System::Drawing::Size(643, 48);
			this->settingsText9->TabIndex = 0;
			this->settingsText9->Text = L"Change Top Left Name";
			this->settingsText9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// settingsOpenExplorer
			// 
			this->settingsOpenExplorer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->settingsOpenExplorer->Location = System::Drawing::Point(10, 548);
			this->settingsOpenExplorer->Name = L"settingsOpenExplorer";
			this->settingsOpenExplorer->Size = System::Drawing::Size(643, 61);
			this->settingsOpenExplorer->TabIndex = 7;
			this->settingsOpenExplorer->Text = L"Open File Explorer at location";
			this->settingsOpenExplorer->UseVisualStyleBackColor = true;
			this->settingsOpenExplorer->Click += gcnew System::EventHandler(this, &form::settingsOpenExplorer_Click);
			// 
			// settingsOpenChosenClassFile
			// 
			this->settingsOpenChosenClassFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->settingsOpenChosenClassFile->Location = System::Drawing::Point(10, 481);
			this->settingsOpenChosenClassFile->Name = L"settingsOpenChosenClassFile";
			this->settingsOpenChosenClassFile->Size = System::Drawing::Size(643, 61);
			this->settingsOpenChosenClassFile->TabIndex = 6;
			this->settingsOpenChosenClassFile->Text = L"Open Chosen Class File";
			this->settingsOpenChosenClassFile->UseVisualStyleBackColor = true;
			this->settingsOpenChosenClassFile->Click += gcnew System::EventHandler(this, &form::settingsOpenChosenClassFile_Click);
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(5, 161);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(448, 32);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Refresh by closing and opening admin";
			// 
			// settingsDisplayClasses
			// 
			this->settingsDisplayClasses->FormattingEnabled = true;
			this->settingsDisplayClasses->ItemHeight = 25;
			this->settingsDisplayClasses->Location = System::Drawing::Point(10, 196);
			this->settingsDisplayClasses->Name = L"settingsDisplayClasses";
			this->settingsDisplayClasses->Size = System::Drawing::Size(643, 279);
			this->settingsDisplayClasses->TabIndex = 4;
			// 
			// settingsStatusOutput
			// 
			this->settingsStatusOutput->BackColor = System::Drawing::Color::Transparent;
			this->settingsStatusOutput->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->settingsStatusOutput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->settingsStatusOutput->Location = System::Drawing::Point(332, 70);
			this->settingsStatusOutput->Name = L"settingsStatusOutput";
			this->settingsStatusOutput->Size = System::Drawing::Size(321, 71);
			this->settingsStatusOutput->TabIndex = 3;
			this->settingsStatusOutput->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// settingsOpenAllClassFIle
			// 
			this->settingsOpenAllClassFIle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->settingsOpenAllClassFIle->Location = System::Drawing::Point(10, 70);
			this->settingsOpenAllClassFIle->Name = L"settingsOpenAllClassFIle";
			this->settingsOpenAllClassFIle->Size = System::Drawing::Size(316, 73);
			this->settingsOpenAllClassFIle->TabIndex = 2;
			this->settingsOpenAllClassFIle->Text = L"Open All Class File";
			this->settingsOpenAllClassFIle->UseVisualStyleBackColor = true;
			this->settingsOpenAllClassFIle->Click += gcnew System::EventHandler(this, &form::settingsOpenAllClassFIle_Click);
			// 
			// label6
			// 
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(3, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(665, 42);
			this->label6->TabIndex = 1;
			this->label6->Text = L"File Explorer";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(482, 152);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(151, 42);
			this->button3->TabIndex = 9;
			this->button3->Text = L"Refresh";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &form::button3_Click);
			// 
			// settingsPanel2
			// 
			this->settingsPanel2->BackColor = System::Drawing::Color::Bisque;
			this->settingsPanel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->settingsPanel2->Controls->Add(this->settingsCorruptThemeText);
			this->settingsPanel2->Controls->Add(this->preset4Box);
			this->settingsPanel2->Controls->Add(this->preset3Box);
			this->settingsPanel2->Controls->Add(this->preset2Box);
			this->settingsPanel2->Controls->Add(this->preset1Box);
			this->settingsPanel2->Controls->Add(this->settingsTextColorDisplay);
			this->settingsPanel2->Controls->Add(this->button10);
			this->settingsPanel2->Controls->Add(this->settingsText7);
			this->settingsPanel2->Controls->Add(this->settingsForeColorDisplay);
			this->settingsPanel2->Controls->Add(this->settingsText6);
			this->settingsPanel2->Controls->Add(this->settingsBackColorDisplay);
			this->settingsPanel2->Controls->Add(this->settingsText5);
			this->settingsPanel2->Controls->Add(this->settingForeColorButton);
			this->settingsPanel2->Controls->Add(this->button9);
			this->settingsPanel2->Controls->Add(this->settingsText4);
			this->settingsPanel2->Location = System::Drawing::Point(20, 411);
			this->settingsPanel2->Name = L"settingsPanel2";
			this->settingsPanel2->Size = System::Drawing::Size(671, 499);
			this->settingsPanel2->TabIndex = 3;
			// 
			// settingsCorruptThemeText
			// 
			this->settingsCorruptThemeText->AutoSize = true;
			this->settingsCorruptThemeText->BackColor = System::Drawing::Color::Red;
			this->settingsCorruptThemeText->ForeColor = System::Drawing::Color::White;
			this->settingsCorruptThemeText->Location = System::Drawing::Point(196, 9);
			this->settingsCorruptThemeText->Name = L"settingsCorruptThemeText";
			this->settingsCorruptThemeText->Size = System::Drawing::Size(277, 25);
			this->settingsCorruptThemeText->TabIndex = 16;
			this->settingsCorruptThemeText->Text = L"Corruption at customTheme";
			this->settingsCorruptThemeText->Visible = false;
			// 
			// preset4Box
			// 
			this->preset4Box->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->preset4Box->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->preset4Box->Controls->Add(this->preset4Label);
			this->preset4Box->Cursor = System::Windows::Forms::Cursors::Default;
			this->preset4Box->Location = System::Drawing::Point(506, 381);
			this->preset4Box->Name = L"preset4Box";
			this->preset4Box->Size = System::Drawing::Size(144, 97);
			this->preset4Box->TabIndex = 15;
			// 
			// preset4Label
			// 
			this->preset4Label->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->preset4Label->Cursor = System::Windows::Forms::Cursors::Hand;
			this->preset4Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->preset4Label->ForeColor = System::Drawing::Color::White;
			this->preset4Label->Location = System::Drawing::Point(12, 12);
			this->preset4Label->Name = L"preset4Label";
			this->preset4Label->Size = System::Drawing::Size(115, 66);
			this->preset4Label->TabIndex = 13;
			this->preset4Label->Text = L"Preset 4";
			this->preset4Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->preset4Label->Click += gcnew System::EventHandler(this, &form::presetClicked);
			// 
			// preset3Box
			// 
			this->preset3Box->BackColor = System::Drawing::Color::DarkSeaGreen;
			this->preset3Box->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->preset3Box->Controls->Add(this->preset3Label);
			this->preset3Box->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->preset3Box->Location = System::Drawing::Point(347, 381);
			this->preset3Box->Name = L"preset3Box";
			this->preset3Box->Size = System::Drawing::Size(144, 97);
			this->preset3Box->TabIndex = 14;
			// 
			// preset3Label
			// 
			this->preset3Label->BackColor = System::Drawing::Color::DarkSlateGray;
			this->preset3Label->Cursor = System::Windows::Forms::Cursors::Hand;
			this->preset3Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->preset3Label->ForeColor = System::Drawing::Color::White;
			this->preset3Label->Location = System::Drawing::Point(12, 12);
			this->preset3Label->Name = L"preset3Label";
			this->preset3Label->Size = System::Drawing::Size(115, 66);
			this->preset3Label->TabIndex = 13;
			this->preset3Label->Text = L"Preset 3";
			this->preset3Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->preset3Label->Click += gcnew System::EventHandler(this, &form::presetClicked);
			// 
			// preset2Box
			// 
			this->preset2Box->BackColor = System::Drawing::Color::LightSlateGray;
			this->preset2Box->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->preset2Box->Controls->Add(this->preset2Label);
			this->preset2Box->Cursor = System::Windows::Forms::Cursors::Default;
			this->preset2Box->Location = System::Drawing::Point(186, 381);
			this->preset2Box->Name = L"preset2Box";
			this->preset2Box->Size = System::Drawing::Size(144, 97);
			this->preset2Box->TabIndex = 13;
			// 
			// preset2Label
			// 
			this->preset2Label->BackColor = System::Drawing::Color::Silver;
			this->preset2Label->Cursor = System::Windows::Forms::Cursors::Hand;
			this->preset2Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->preset2Label->Location = System::Drawing::Point(12, 12);
			this->preset2Label->Name = L"preset2Label";
			this->preset2Label->Size = System::Drawing::Size(115, 66);
			this->preset2Label->TabIndex = 13;
			this->preset2Label->Text = L"Preset 2";
			this->preset2Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->preset2Label->Click += gcnew System::EventHandler(this, &form::presetClicked);
			// 
			// preset1Box
			// 
			this->preset1Box->BackColor = System::Drawing::Color::Tan;
			this->preset1Box->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->preset1Box->Controls->Add(this->preset1Label);
			this->preset1Box->Cursor = System::Windows::Forms::Cursors::Default;
			this->preset1Box->Location = System::Drawing::Point(20, 381);
			this->preset1Box->Name = L"preset1Box";
			this->preset1Box->Size = System::Drawing::Size(144, 97);
			this->preset1Box->TabIndex = 12;
			// 
			// preset1Label
			// 
			this->preset1Label->BackColor = System::Drawing::Color::Bisque;
			this->preset1Label->Cursor = System::Windows::Forms::Cursors::Hand;
			this->preset1Label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->preset1Label->Location = System::Drawing::Point(12, 12);
			this->preset1Label->Name = L"preset1Label";
			this->preset1Label->Size = System::Drawing::Size(115, 66);
			this->preset1Label->TabIndex = 13;
			this->preset1Label->Text = L"Preset 1";
			this->preset1Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->preset1Label->Click += gcnew System::EventHandler(this, &form::presetClicked);
			// 
			// settingsTextColorDisplay
			// 
			this->settingsTextColorDisplay->AccessibleDescription = L"";
			this->settingsTextColorDisplay->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->settingsTextColorDisplay->Location = System::Drawing::Point(263, 277);
			this->settingsTextColorDisplay->Name = L"settingsTextColorDisplay";
			this->settingsTextColorDisplay->Size = System::Drawing::Size(182, 73);
			this->settingsTextColorDisplay->TabIndex = 11;
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(462, 277);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(166, 73);
			this->button10->TabIndex = 10;
			this->button10->Text = L"Edit";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &form::settingsTextColorButton_Click);
			// 
			// settingsText7
			// 
			this->settingsText7->BackColor = System::Drawing::Color::Transparent;
			this->settingsText7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->settingsText7->Location = System::Drawing::Point(59, 277);
			this->settingsText7->Name = L"settingsText7";
			this->settingsText7->Size = System::Drawing::Size(187, 73);
			this->settingsText7->TabIndex = 8;
			this->settingsText7->Text = L"Text Color:";
			this->settingsText7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// settingsForeColorDisplay
			// 
			this->settingsForeColorDisplay->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->settingsForeColorDisplay->Location = System::Drawing::Point(263, 187);
			this->settingsForeColorDisplay->Name = L"settingsForeColorDisplay";
			this->settingsForeColorDisplay->Size = System::Drawing::Size(182, 73);
			this->settingsForeColorDisplay->TabIndex = 7;
			// 
			// settingsText6
			// 
			this->settingsText6->BackColor = System::Drawing::Color::Transparent;
			this->settingsText6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->settingsText6->Location = System::Drawing::Point(59, 184);
			this->settingsText6->Name = L"settingsText6";
			this->settingsText6->Size = System::Drawing::Size(187, 73);
			this->settingsText6->TabIndex = 6;
			this->settingsText6->Text = L"Fore Color:";
			this->settingsText6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// settingsBackColorDisplay
			// 
			this->settingsBackColorDisplay->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->settingsBackColorDisplay->Location = System::Drawing::Point(263, 92);
			this->settingsBackColorDisplay->Name = L"settingsBackColorDisplay";
			this->settingsBackColorDisplay->Size = System::Drawing::Size(182, 73);
			this->settingsBackColorDisplay->TabIndex = 5;
			// 
			// settingsText5
			// 
			this->settingsText5->BackColor = System::Drawing::Color::Transparent;
			this->settingsText5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->settingsText5->Location = System::Drawing::Point(59, 92);
			this->settingsText5->Name = L"settingsText5";
			this->settingsText5->Size = System::Drawing::Size(187, 73);
			this->settingsText5->TabIndex = 4;
			this->settingsText5->Text = L"Back Color:";
			this->settingsText5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// settingForeColorButton
			// 
			this->settingForeColorButton->Location = System::Drawing::Point(462, 187);
			this->settingForeColorButton->Name = L"settingForeColorButton";
			this->settingForeColorButton->Size = System::Drawing::Size(166, 73);
			this->settingForeColorButton->TabIndex = 3;
			this->settingForeColorButton->Text = L"Edit";
			this->settingForeColorButton->UseVisualStyleBackColor = true;
			this->settingForeColorButton->Click += gcnew System::EventHandler(this, &form::settingForeColorButton_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(462, 92);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(166, 73);
			this->button9->TabIndex = 2;
			this->button9->Text = L"Edit";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &form::settingBackColorButton);
			// 
			// settingsText4
			// 
			this->settingsText4->BackColor = System::Drawing::Color::Transparent;
			this->settingsText4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->settingsText4->Location = System::Drawing::Point(3, 34);
			this->settingsText4->Name = L"settingsText4";
			this->settingsText4->Size = System::Drawing::Size(665, 42);
			this->settingsText4->TabIndex = 1;
			this->settingsText4->Text = L"Change Theme";
			this->settingsText4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// settingsPanel1
			// 
			this->settingsPanel1->BackColor = System::Drawing::Color::Bisque;
			this->settingsPanel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->settingsPanel1->Controls->Add(this->settingsHider1);
			this->settingsPanel1->Controls->Add(this->settingsFileStatus);
			this->settingsPanel1->Controls->Add(this->settingsMakeExampleFile);
			this->settingsPanel1->Controls->Add(this->settingsText2);
			this->settingsPanel1->Controls->Add(this->settingsCouldNotOpen);
			this->settingsPanel1->Controls->Add(this->settingsText3);
			this->settingsPanel1->Controls->Add(this->settingsText1);
			this->settingsPanel1->Location = System::Drawing::Point(20, 32);
			this->settingsPanel1->Name = L"settingsPanel1";
			this->settingsPanel1->Size = System::Drawing::Size(671, 357);
			this->settingsPanel1->TabIndex = 2;
			// 
			// settingsHider1
			// 
			this->settingsHider1->Controls->Add(this->settingsCorruptedIconText);
			this->settingsHider1->Controls->Add(this->settingsText8);
			this->settingsHider1->Controls->Add(this->pictureBox10);
			this->settingsHider1->Controls->Add(this->pictureBox9);
			this->settingsHider1->Controls->Add(this->pictureBox8);
			this->settingsHider1->Controls->Add(this->pictureBox7);
			this->settingsHider1->Controls->Add(this->pictureBox6);
			this->settingsHider1->Controls->Add(this->pictureBox5);
			this->settingsHider1->Controls->Add(this->pictureBox4);
			this->settingsHider1->Controls->Add(this->pictureBox3);
			this->settingsHider1->Controls->Add(this->pictureBox2);
			this->settingsHider1->Controls->Add(this->pictureBox1);
			this->settingsHider1->Location = System::Drawing::Point(3, 3);
			this->settingsHider1->Name = L"settingsHider1";
			this->settingsHider1->Size = System::Drawing::Size(661, 347);
			this->settingsHider1->TabIndex = 6;
			// 
			// settingsCorruptedIconText
			// 
			this->settingsCorruptedIconText->AutoSize = true;
			this->settingsCorruptedIconText->BackColor = System::Drawing::Color::Red;
			this->settingsCorruptedIconText->ForeColor = System::Drawing::Color::White;
			this->settingsCorruptedIconText->Location = System::Drawing::Point(182, 11);
			this->settingsCorruptedIconText->Name = L"settingsCorruptedIconText";
			this->settingsCorruptedIconText->Size = System::Drawing::Size(291, 25);
			this->settingsCorruptedIconText->TabIndex = 12;
			this->settingsCorruptedIconText->Text = L"Corruption at customIcon file!";
			this->settingsCorruptedIconText->Visible = false;
			// 
			// settingsText8
			// 
			this->settingsText8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->settingsText8->Location = System::Drawing::Point(48, 28);
			this->settingsText8->Name = L"settingsText8";
			this->settingsText8->Size = System::Drawing::Size(558, 62);
			this->settingsText8->TabIndex = 11;
			this->settingsText8->Text = L"Change Top Left Icon";
			this->settingsText8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pictureBox10
			// 
			this->pictureBox10->AccessibleName = L"9";
			this->pictureBox10->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox10->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox10->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox10.Image")));
			this->pictureBox10->Location = System::Drawing::Point(514, 228);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(90, 82);
			this->pictureBox10->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox10->TabIndex = 10;
			this->pictureBox10->TabStop = false;
			this->pictureBox10->Click += gcnew System::EventHandler(this, &form::IconClicked);
			// 
			// pictureBox9
			// 
			this->pictureBox9->AccessibleName = L"8";
			this->pictureBox9->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox9.Image")));
			this->pictureBox9->Location = System::Drawing::Point(394, 228);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(90, 82);
			this->pictureBox9->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox9->TabIndex = 9;
			this->pictureBox9->TabStop = false;
			this->pictureBox9->Click += gcnew System::EventHandler(this, &form::IconClicked);
			// 
			// pictureBox8
			// 
			this->pictureBox8->AccessibleName = L"7";
			this->pictureBox8->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox8.Image")));
			this->pictureBox8->Location = System::Drawing::Point(282, 228);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(90, 82);
			this->pictureBox8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox8->TabIndex = 8;
			this->pictureBox8->TabStop = false;
			this->pictureBox8->Click += gcnew System::EventHandler(this, &form::IconClicked);
			// 
			// pictureBox7
			// 
			this->pictureBox7->AccessibleName = L"6";
			this->pictureBox7->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.Image")));
			this->pictureBox7->Location = System::Drawing::Point(164, 228);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(90, 82);
			this->pictureBox7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox7->TabIndex = 7;
			this->pictureBox7->TabStop = false;
			this->pictureBox7->Click += gcnew System::EventHandler(this, &form::IconClicked);
			// 
			// pictureBox6
			// 
			this->pictureBox6->AccessibleName = L"5";
			this->pictureBox6->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox6.Image")));
			this->pictureBox6->Location = System::Drawing::Point(46, 228);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(90, 82);
			this->pictureBox6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox6->TabIndex = 6;
			this->pictureBox6->TabStop = false;
			this->pictureBox6->Click += gcnew System::EventHandler(this, &form::IconClicked);
			// 
			// pictureBox5
			// 
			this->pictureBox5->AccessibleName = L"4";
			this->pictureBox5->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.Image")));
			this->pictureBox5->Location = System::Drawing::Point(514, 128);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(90, 82);
			this->pictureBox5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox5->TabIndex = 5;
			this->pictureBox5->TabStop = false;
			this->pictureBox5->Click += gcnew System::EventHandler(this, &form::IconClicked);
			// 
			// pictureBox4
			// 
			this->pictureBox4->AccessibleName = L"3";
			this->pictureBox4->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(394, 128);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(90, 82);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox4->TabIndex = 4;
			this->pictureBox4->TabStop = false;
			this->pictureBox4->Click += gcnew System::EventHandler(this, &form::IconClicked);
			// 
			// pictureBox3
			// 
			this->pictureBox3->AccessibleName = L"2";
			this->pictureBox3->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(282, 128);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(90, 82);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 3;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &form::IconClicked);
			// 
			// pictureBox2
			// 
			this->pictureBox2->AccessibleName = L"1";
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(164, 128);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(90, 82);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &form::IconClicked);
			// 
			// pictureBox1
			// 
			this->pictureBox1->AccessibleDescription = L"";
			this->pictureBox1->AccessibleName = L"0";
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(46, 128);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(90, 82);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &form::IconClicked);
			// 
			// settingsFileStatus
			// 
			this->settingsFileStatus->BackColor = System::Drawing::Color::White;
			this->settingsFileStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->settingsFileStatus->Location = System::Drawing::Point(285, 72);
			this->settingsFileStatus->Name = L"settingsFileStatus";
			this->settingsFileStatus->Size = System::Drawing::Size(353, 56);
			this->settingsFileStatus->TabIndex = 5;
			this->settingsFileStatus->Text = L"---------";
			this->settingsFileStatus->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// settingsMakeExampleFile
			// 
			this->settingsMakeExampleFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->settingsMakeExampleFile->Location = System::Drawing::Point(38, 238);
			this->settingsMakeExampleFile->Name = L"settingsMakeExampleFile";
			this->settingsMakeExampleFile->Size = System::Drawing::Size(600, 88);
			this->settingsMakeExampleFile->TabIndex = 0;
			this->settingsMakeExampleFile->Text = L"Make Example File";
			this->settingsMakeExampleFile->UseVisualStyleBackColor = true;
			this->settingsMakeExampleFile->Click += gcnew System::EventHandler(this, &form::settingsMakeExampleFile_Click);
			// 
			// settingsText2
			// 
			this->settingsText2->BackColor = System::Drawing::Color::Transparent;
			this->settingsText2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->settingsText2->Location = System::Drawing::Point(31, 72);
			this->settingsText2->Name = L"settingsText2";
			this->settingsText2->Size = System::Drawing::Size(248, 56);
			this->settingsText2->TabIndex = 4;
			this->settingsText2->Text = L"All Class File:";
			this->settingsText2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// settingsCouldNotOpen
			// 
			this->settingsCouldNotOpen->BackColor = System::Drawing::Color::White;
			this->settingsCouldNotOpen->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->settingsCouldNotOpen->Location = System::Drawing::Point(285, 144);
			this->settingsCouldNotOpen->Name = L"settingsCouldNotOpen";
			this->settingsCouldNotOpen->Size = System::Drawing::Size(353, 56);
			this->settingsCouldNotOpen->TabIndex = 3;
			this->settingsCouldNotOpen->Text = L"------------------";
			this->settingsCouldNotOpen->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// settingsText3
			// 
			this->settingsText3->BackColor = System::Drawing::Color::Transparent;
			this->settingsText3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->settingsText3->Location = System::Drawing::Point(31, 144);
			this->settingsText3->Name = L"settingsText3";
			this->settingsText3->Size = System::Drawing::Size(254, 56);
			this->settingsText3->TabIndex = 2;
			this->settingsText3->Text = L"Could not Open:";
			this->settingsText3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// settingsText1
			// 
			this->settingsText1->BackColor = System::Drawing::Color::Transparent;
			this->settingsText1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->settingsText1->Location = System::Drawing::Point(3, 0);
			this->settingsText1->Name = L"settingsText1";
			this->settingsText1->Size = System::Drawing::Size(665, 42);
			this->settingsText1->TabIndex = 1;
			this->settingsText1->Text = L"Indicators for files";
			this->settingsText1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// backColor
			// 
			this->backColor->Color = System::Drawing::Color::Tan;
			// 
			// foreColor
			// 
			this->foreColor->Color = System::Drawing::Color::Bisque;
			// 
			// messageTimer
			// 
			this->messageTimer->Interval = 2000;
			this->messageTimer->Tick += gcnew System::EventHandler(this, &form::messageTimer_Tick);
			// 
			// adminPageAnimation
			// 
			this->adminPageAnimation->Tick += gcnew System::EventHandler(this, &form::adminPageAnimation_Tick);
			// 
			// form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Tan;
			this->ClientSize = System::Drawing::Size(1630, 1127);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"form";
			this->Text = L"Grade Calculator";
			this->Load += gcnew System::EventHandler(this, &form::form_Load);
			this->tabControl->ResumeLayout(false);
			this->tab1->ResumeLayout(false);
			this->messagePanel->ResumeLayout(false);
			this->addClassPanel3->ResumeLayout(false);
			this->addClassPanel5->ResumeLayout(false);
			this->addClassPanel5->PerformLayout();
			this->addClassPanel4->ResumeLayout(false);
			this->addClassPanel2->ResumeLayout(false);
			this->addClassPanel2->PerformLayout();
			this->classNamePanel->ResumeLayout(false);
			this->classNamePanel->PerformLayout();
			this->tab2->ResumeLayout(false);
			this->deletingClassMessage->ResumeLayout(false);
			this->changeGradesPanel4->ResumeLayout(false);
			this->changeGradesPanel3->ResumeLayout(false);
			this->changeGradesPanel3->PerformLayout();
			this->changeGradesPanel2->ResumeLayout(false);
			this->changeGradesPanel1->ResumeLayout(false);
			this->tab3->ResumeLayout(false);
			this->TSPanel6->ResumeLayout(false);
			this->TSPanel3->ResumeLayout(false);
			this->TSPanel5->ResumeLayout(false);
			this->TSPanel5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->changeGradeTrack))->EndInit();
			this->TSPanel4->ResumeLayout(false);
			this->TSPanel1->ResumeLayout(false);
			this->TSPanel2->ResumeLayout(false);
			this->tab4->ResumeLayout(false);
			this->settingsPanel3->ResumeLayout(false);
			this->settingsHider2->ResumeLayout(false);
			this->settingsHider2->PerformLayout();
			this->settingsPanel2->ResumeLayout(false);
			this->settingsPanel2->PerformLayout();
			this->preset4Box->ResumeLayout(false);
			this->preset3Box->ResumeLayout(false);
			this->preset2Box->ResumeLayout(false);
			this->preset1Box->ResumeLayout(false);
			this->settingsPanel1->ResumeLayout(false);
			this->settingsHider1->ResumeLayout(false);
			this->settingsHider1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion



//  ===========================================================================
//	==																		 ==
//	====					Helper functions             		           ====
//	==																		 ==
//  ===========================================================================
bool isDigits(string target) {
	int dotCount = 0;
	for (int i = 0; i < target.length(); i++) {
		if (!isdigit(target[i])) {
			if (target[i] == '.') {
				dotCount += 1;
				if (dotCount > 1) {
					return false;
				}
				continue;
			}
			return false;
		}
	}
	return true;
}
bool isOnlySpaces(string target) {
	for (int i = 0; i < target.length(); i++){
		if (target[i] != ' ')
			return false;
	}
	return true;
}


void resetAddingColors() {
	classNamePanel->BackColor == backColor->Color;
	sectionNameText->BackColor = Color::Transparent;
	amountSubText->BackColor = Color::Transparent;
	percentText->BackColor = Color::Transparent;
}


string hToString(String^ target) {
	string rValue = msclr::interop::marshal_as<std::string>(target);
	return rValue;
}
String^ stringToH(string target) {
	String^ rValue = msclr::interop::marshal_as<String^>(target);
	return rValue;
}


string cleanSectionName(string target) {
	return target.substr(0, target.find('.'));
}

void refreshTheme() {
	// Settings up the back colors:
	tab1->BackColor = backColor->Color;
	tab2->BackColor = backColor->Color;
	tab3->BackColor = backColor->Color;
	tab4->BackColor = backColor->Color;
	



	// Settings up the BAKCGROUND colors:
	classNamePanel->BackColor = foreColor->Color;
	addClassPanel2->BackColor = foreColor->Color;
	addClassPanel3->BackColor = foreColor->Color;
	addClassPanel4->BackColor = foreColor->Color;
	addClassPanel5->BackColor = foreColor->Color;
	addText16->BackColor = foreColor->Color;

	changeGradesPanel1->BackColor = foreColor->Color;
	changeGradesPanel2->BackColor = foreColor->Color;
	changeGradesPanel3->BackColor = foreColor->Color;
	changeGradesPanel4->BackColor = foreColor->Color;

	TSPanel1->BackColor = foreColor->Color; TSPanel4->BackColor = foreColor->Color;
	TSPanel2->BackColor = foreColor->Color; TSPanel5->BackColor = foreColor->Color;
	TSPanel3->BackColor = foreColor->Color; TSPanel6->BackColor = foreColor->Color;

	settingsPanel1->BackColor = foreColor->Color;
	settingsPanel2->BackColor = foreColor->Color;
	settingsPanel3->BackColor = foreColor->Color;
	settingsHider1->BackColor = foreColor->Color;
	settingsHider2->BackColor = foreColor->Color;




	// Setting up the TEXT colors:
	sectionNameText->ForeColor = textColor->Color;
	percentText->ForeColor = textColor->Color;
	amountSubText->ForeColor = textColor->Color;
	sectionPercentSum->ForeColor = textColor->Color;
	subSectionPercentSum->ForeColor = textColor->Color;
	addText1->ForeColor = textColor->Color; addText7->ForeColor = textColor->Color;  addText13->ForeColor = textColor->Color;
	addText2->ForeColor = textColor->Color;	addText8->ForeColor = textColor->Color;	 addText14->ForeColor = textColor->Color;
	addText3->ForeColor = textColor->Color;	addText9->ForeColor = textColor->Color;	 addText15->ForeColor = textColor->Color;
	addText4->ForeColor = textColor->Color;	addText10->ForeColor = textColor->Color; addText16->ForeColor = textColor->Color;
	addText5->ForeColor = textColor->Color;	addText11->ForeColor = textColor->Color; addText17->ForeColor = textColor->Color;
	addText6->ForeColor = textColor->Color;	addText12->ForeColor = textColor->Color; addText18->ForeColor = textColor->Color;
	addText19->ForeColor = textColor->Color; addText20->ForeColor = textColor->Color; addText21->ForeColor = textColor->Color;

	changeGradeText1->ForeColor = textColor->Color; changeGradeText5->ForeColor = textColor->Color;
	changeGradeText2->ForeColor = textColor->Color; changeGradeText6->ForeColor = textColor->Color;
	changeGradeText3->ForeColor = textColor->Color; changeGradeText7->ForeColor = textColor->Color;
	changeGradeText4->ForeColor = textColor->Color; changeGradeText8->ForeColor = textColor->Color;
	changeGradeText9->ForeColor = textColor->Color;


	TSText1->ForeColor = textColor->Color; TSText5->ForeColor = textColor->Color;
	TSText2->ForeColor = textColor->Color; TSText6->ForeColor = textColor->Color;
	TSText3->ForeColor = textColor->Color; TSText7->ForeColor = textColor->Color;
	TSText4->ForeColor = textColor->Color; 
	TSDisplayGradeTop->ForeColor = textColor->Color;
	TSDisplayGradeBottom->ForeColor = textColor->Color;

	settingsText1->ForeColor = textColor->Color; settingsText5->ForeColor = textColor->Color;
	settingsText2->ForeColor = textColor->Color; settingsText6->ForeColor = textColor->Color;
	settingsText3->ForeColor = textColor->Color; settingsText7->ForeColor = textColor->Color;
	settingsText4->ForeColor = textColor->Color; settingsText8->ForeColor = textColor->Color;
	settingsText9->ForeColor = textColor->Color;


	// Setting up the form background
	this->BackColor = backColor->Color;


	// Setting the change theme displays
	settingsBackColorDisplay->BackColor = backColor->Color;
	settingsTextColorDisplay->BackColor = textColor->Color;
	settingsForeColorDisplay->BackColor = foreColor->Color;
}

void refreshAllGrades() {
	for (int i = 0; i < allClasses.size(); i++){                              // Through all classes
		if (allClasses[i].numOfSections() != 0) {							  // If class has sections - it should but yk 
			for (int j = 0; j < allClasses[i].numOfSections(); j++){		  // Going through all the sections
				if (allClasses[i].sections[j].numOfSections() != 0) {		  // If section has subSections
					allClasses[i].sections[j].refreshGrade();                 // Update that sections grades
				}
			}
			allClasses[i].refreshGrade();                                     // Update this section grades
		}
	}
}




//  ===========================================================================
//	==																		 ==
//	====					Starting up program functions		           ====
//	==																		 ==
//  ===========================================================================
void grabbingGradesFailure(string fileFailure) {
	grabbingGradesFailureMessage->Visible = true;
	settingsCouldNotOpen->Text = stringToH(fileFailure);
}


void grabClassesFromFiles() {
	allClasses.clear();
	vector<string> allFileNames;
	ifstream namesFile("_allClasses_.txt");

	// Checking if there are any files previously saved
	if (!namesFile) {
		settingsFileStatus->Text = "Could not find any.";
		return;
	}
	else
		settingsFileStatus->Text = "Found Files";


	// Adding all names from the file to the allFileNames Vector, then closing the file
	string tempString = "";
	while (!namesFile.eof()) {
		getline(namesFile, tempString);
		if (!tempString.empty())
			allFileNames.push_back(tempString.substr(0, tempString.length() - 4));
	}
	namesFile.close();



	// Using the allFileNames vector to grab information from all of the class files
	tempString = "";
	string tempName;
	double tempWeight;
	double tempGrade;
	int tempClassSections;
	int tempSubSections;

	Grade currentClass;
	currentClass.reset();

	ifstream currClassFile;
	for (int i = 0; i < allFileNames.size(); i++) {                                // For each name in allFileNames
		currClassFile.open(allFileNames[i] + ".txt");                              // Opens this file and starts reading
		
		if (!currClassFile) {
			grabbingGradesFailure(allFileNames[i]);
			currClassFile.close();
			return;
		}

		// grab the information from the class text and make it into a class then add into the class vector!!
		currentClass.name = allFileNames[i]; // Grabs the name from the list file name
		getline(currClassFile, tempString);                                       // Grabbing how many sections this class has 
		if (!isDigits(tempString)) {                                              // | |
			grabbingGradesFailure(allFileNames[i]);								  // | |
			currClassFile.close();
			return;																  // | |
		}																		  //  V
		tempClassSections = stoi(tempString);                                     // Doing class section count conversion (INT)


		for (int sectionIter = 0; sectionIter < tempClassSections; sectionIter++) {
			getline(currClassFile, tempName);                                     // Grabbing this section NAME



			getline(currClassFile, tempString);                                   // Grabbing this section WEIGHT
			if (!isDigits(tempString)) {			                              //   | |
				grabbingGradesFailure(allFileNames[i]);			                  //   | |
				currClassFile.close();
				return;								                              //   | |
			}										                              //    V
			tempWeight = stod(tempString);                                        // Doing section weight conversion (DOUBLE)



			getline(currClassFile, tempString);                                   // Grabbing this section GRADE
			if (tempString != "-1") {                                             // -1 will automatically skip checking if is digit to convert
				if (!isDigits(tempString)) {                                      //  | |
					grabbingGradesFailure(allFileNames[i]);		                  //  | |
					currClassFile.close();
					return;							                              //  | |
				}									                              //  | |
			}										                              //   V
			tempGrade = stod(tempString);                                         // Doing section subSections conversion (DOUBLE)


			getline(currClassFile, tempString);                                   // Grabbing this sections SUBSECTIONS
			if (tempString != "-1") {                                             //  | |
				if (!isDigits(tempString)) {                                      //  | |
					grabbingGradesFailure(allFileNames[i]);		                  //  | |
					currClassFile.close();
					return;							                              //  | |
				}									                              //  | |
			}										                              //   V
			tempSubSections = stoi(tempString);                                   // Doing section subSections conversion (INT)




			// Adding section to this current class
			currentClass.addSection(tempName, tempWeight, tempSubSections);                  // Adding this section to this currentClass
			currentClass.sections[sectionIter].grade = tempGrade;                            // Changing the grade of this section


			if (tempSubSections != 0) {                                                      // Checking if we need to set up sub sections
				for (int subSectionIter = 0; subSectionIter < tempSubSections; subSectionIter++) {
					getline(currClassFile, tempName);                                        // Grabbing this subSection NAME


					getline(currClassFile, tempString);                                      // Grabbing this subSection WEIGHT
					if (!isDigits(tempString)) {			                                 //   | |
						grabbingGradesFailure(allFileNames[i]);			                     //   | |
						currClassFile.close();
						return;								                                 //   | |
					}										                                 //    V
					tempWeight = stod(tempString);                                           // Doing section weight conversion (DOUBLE)


					getline(currClassFile, tempString);                                      // Grabbing this subSection grade
					if (tempString != "-1") {                                                // -1 will automatically skip checking if is digit to convert
						if (!isDigits(tempString)) {                                         //  | |
							grabbingGradesFailure(allFileNames[i]);		                     //  | |
							currClassFile.close();
							return;							                                 //  | |
						}									                                 //  | |
					}										                                 //   V
					tempGrade = stod(tempString);                                            // Doing section grade conversion (DOUBLE)




					// Adding the subSection to this current section
					currentClass.sections[sectionIter].sections[subSectionIter].name = tempName;
					currentClass.sections[sectionIter].sections[subSectionIter].weight = tempWeight;
					currentClass.sections[sectionIter].sections[subSectionIter].grade = tempGrade;
					currentClass.sections[sectionIter].sections[subSectionIter].grade = tempGrade;
				}
			}
		}


		// Checking if the last line in file is the dedicated limiter
		getline(currClassFile, tempString);
		if (tempString != "<><><>") {
			grabbingGradesFailure(allFileNames[i]);
			currClassFile.close();
			return;
		}

		// Class has been set up -> saving this into the class vector
		allClasses.push_back(currentClass);
		currentClass.reset();

		// Closes this file when finished and ready to reopen another file
		currClassFile.close();

		// Refreshing all Grades
		refreshAllGrades();
	}
}

void setIcon() {
	ifstream customLogoFile("_customIcon_.txt");
	if (!customLogoFile) {
		return;
	}
	string tempString;
	getline(customLogoFile, tempString);
	if (tempString.empty() || !isDigits(tempString)) {
		customLogoFile.close();
		settingsCorruptedIconText->Visible = true;
		return;
	}
	if (stoi(tempString) > 9 || stoi(tempString) < 0) {
		settingsCorruptedIconText->Visible = true;
		customLogoFile.close();
		return;
	}

	int imageIndex = stoi(tempString);

	System::ComponentModel::ComponentResourceManager^ resourcesPublic = (gcnew System::ComponentModel::ComponentResourceManager(form::typeid));

	
	if (imageIndex == 0) {
		// regular og icon
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resourcesPublic->GetObject(L"$this.Icon")));
	}
	else if (imageIndex == 1) {
		// pink bow
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resourcesPublic->GetObject(L"pinkBowIcon")));
	}
	else if (imageIndex == 2) {
		// cow
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resourcesPublic->GetObject(L"cowIcon")));
	}
	else if (imageIndex == 3) {
		//dog
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resourcesPublic->GetObject(L"dogIcon")));
	}
	else if (imageIndex == 4) {
		//heart
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resourcesPublic->GetObject(L"heartIcon")));
	}
	else if (imageIndex == 5) {
		//grade2
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resourcesPublic->GetObject(L"anotherGradeIcon")));
	}
	else if (imageIndex == 6) {
		//school
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resourcesPublic->GetObject(L"schoolIcon")));
	}
	else if (imageIndex == 7) {
		//nurse
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resourcesPublic->GetObject(L"nurseIcon")));
	}
	else if (imageIndex == 8) {
		//medicine
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resourcesPublic->GetObject(L"medicineIcon")));
	}
	else if (imageIndex == 9) {
		//bow2
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resourcesPublic->GetObject(L"bow2")));
	}
	else {
		settingsCorruptedIconText->Visible = true;
		customLogoFile.close();
		return;
	}
	customLogoFile.close();
}

void setFormName() {
	ifstream setFormNameFile("_customFormName_.txt");
	if (!setFormNameFile)
		return;
	string tempString;
	getline(setFormNameFile, tempString);
	if (tempString.empty() || isOnlySpaces(tempString)) {
		setFormNameFile.close();
		settingsCorruptNameText->Visible = true;
		return;
	}

	this->Text = stringToH(tempString);
	settingsSetFormNameInput->Text = "";
	setFormNameFile.close();
}

void setTheme() {
	ifstream customThemeFile("_customTheme_.txt");
	if (!customThemeFile)
		return;

	string tempString;
	getline(customThemeFile, tempString);
	if (!isDigits(tempString)) {
		customThemeFile.close();
		settingsCorruptThemeText->Visible = true;
		return;
	}
	int tempInt = stoi(tempString);
	if (tempInt > 4 || tempInt < 1) {
		customThemeFile.close();
		settingsCorruptThemeText->Visible = true;
		return;
	}

	if (tempInt == 1) {
		presetClicked(preset1Label, nullptr);
	}
	else if (tempInt == 2) {
		presetClicked(preset2Label, nullptr);
	}
	else if (tempInt == 3) {
		presetClicked(preset3Label, nullptr);
	}
	else if (tempInt == 4) {
		presetClicked(preset4Label, nullptr);
	}
	else {
		customThemeFile.close();
		settingsCorruptThemeText->Visible = true;
		return;
	}
	

	customThemeFile.close();
}

private: System::Void form_Load(System::Object^ sender, System::EventArgs^ e) {
	grabClassesFromFiles();  // Loads the files from the computer into the all classes vector
	setIcon();
	setFormName();
	setTheme();
}







// ==========================================================================




#pragma region Add Class Tab Functions

// Refresh the display screens functions ====================================

void refreshSectionDisplay() {
	sectionNamesDisplay->Items->Clear();
	if (newClass.numOfSections() == 0) {
		sectionPercentSum->Text = "0.00";
		return;
	}

	
	String^ sending;
	ostringstream settingString;
	double sum = 0;
	for (int i = 0; i < newClass.numOfSections(); i++){
		settingString << setw(36) << left << setfill('.') << newClass.sections[i].name 
			<< right << setw(5) << fixed << setprecision(2) << newClass.sections[i].weight;
		sending = stringToH(settingString.str());
		sectionNamesDisplay->Items->Add(sending);
		settingString.str("");

		if (newClass.sections[i].weight != -1) {
			sum += newClass.sections[i].weight;
		}
	}

	// Setting the sum number on the bottom right
	settingString << fixed << setprecision(2) << sum;
	sending = stringToH(settingString.str());
	sectionPercentSum->Text = sending;

}

void refreshSubSectionDisplay() {
	sectionSubDisplay->Items->Clear();
	if (newClass.numOfSections() == 0) {
		subSectionPercentSum->Text = "0.00";
		return;
	}

	if (sectionNamesDisplay->SelectedIndex == -1) {
		return;
	}

	String^ sending;
	ostringstream settingString;
	Grade* currSection = &newClass.sections[sectionNamesDisplay->SelectedIndex];
	double sum = 0;

	string subSectionName = "";
	for (int i = 0; i < currSection->numOfSections(); i++) {
		if (currSection->sections[i].name == "")
			subSectionName = "<No Name Yet>";
		else
			subSectionName = currSection->sections[i].name;

		settingString << setw(36) << left << setfill('.') << subSectionName
			<< right << setw(5) << fixed << setprecision(2) << currSection->sections[i].weight;
		sending = stringToH(settingString.str());
		sectionSubDisplay->Items->Add(sending);
		settingString.str("");

		if (currSection->sections[i].weight != -1) {
			sum += currSection->sections[i].weight;
		}
	}

	// Setting the sum number on the bottom right
	settingString << fixed << setprecision(2) << sum;
	sending = stringToH(settingString.str());
	subSectionPercentSum->Text = sending;
}

void refreshSummaryIndicators() {
	// Updates the Weights inputted indicator
	if (!newClass.allWeightsInputted() || (newClass.numOfSections() == 0)) {  // Weights ARE NOT all inputted
		summaryWeightDisplay->Text = "Needs Attention!";
		summaryWeightDisplay->BackColor = Color::Red;
	}
	else {                                                                    // Weights ARE all inputted
		summaryWeightDisplay->Text = "Ready!";
		summaryWeightDisplay->BackColor = Color::Green;
	}

	// Updates the weights sums indicator
	if (!newClass.weightsAddUp() || (newClass.numOfSections() == 0)) {        // Weights DO NOT add up
		summarySumsDisplay->Text = "Needs Attention!";
		summarySumsDisplay->BackColor = Color::Red;
	}
	else {                                                                    // Weights DO add up
		summarySumsDisplay->Text = "Ready!";
		summarySumsDisplay->BackColor = Color::Green;
	}

	// Updates the all sections named indicators
	if (!newClass.allSectionsNamed() || (newClass.numOfSections() == 0)) {
		summaryAllSectionsNamed->Text = "Needs Attention!";
		summaryAllSectionsNamed->BackColor = Color::Red;
	}
	else {
		summaryAllSectionsNamed->Text = "Ready!";
		summaryAllSectionsNamed->BackColor = Color::Green;
	}


	if (newClass.numOfSections() == 0) {
		summaryHasSections->BackColor = Color::Red;
		summaryHasSections->Text = "Needs Attention!";
	}
	else {
		summaryHasSections->BackColor = Color::Green;
		summaryHasSections->Text = "Ready!";
	}

	
}

private: System::Void sectionNamesDisplay_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	sectionSubDisplay->Items->Clear();
	if (sectionNamesDisplay->SelectedIndex == -1) {
		return;
	}
	refreshSubSectionDisplay();
}

private: System::Void sectionSubDisplay_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	subSectionInputName->Focus();
}



private: System::Void sectionNameInput_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	sectionNameText->BackColor = Color::Transparent;
}
private: System::Void percentInput_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	percentText->BackColor = Color::Transparent;
}
private: System::Void amountSubInput_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	amountSubText->BackColor = Color::Transparent;
}

// ==========================================================================


// Show Message =============================================================
 

void showMessage(string message, string context) {
	// Set the message and make visible
	messageText->Text = stringToH(message);
	if (context == "good")
		messagePanel->BackColor = Color::Green;
	else
		messagePanel->BackColor = Color::Red;
	messagePanel->Visible = true;

	// Start timer
	messageTimer->Start();
}
private: System::Void messageTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
	// Stop timer and make message invisible
	messageTimer->Stop();
	messagePanel->Visible = false;
	deletingClassMessage->Visible = false;
}



// ==========================================================================



// Clicking Button Functions ================================================

private: System::Void addSectionButton(System::Object^ sender, System::EventArgs^ e) {
	resetAddingColors();
	if (sectionNameInput->Text == "") {
		sectionNameText->BackColor = Color::Red;
		return;
	}

	
	string sendingName = hToString(sectionNameInput->Text);
	string sendingPercentString = hToString(percentInput->Text);
	string sendingAmountString = hToString(amountSubInput->Text);
	// Making sure the percent is not Empty
	if (sendingPercentString == "" || isOnlySpaces(sendingPercentString)) {
		showMessage("Percent is missing.", "bad");
		percentText->BackColor = Color::Red;
		return;
	}

	// Making sure percent is ONLY digits
	if (!isDigits(sendingPercentString)) {
		showMessage("Percent is not all digits.", "bad");
		percentText->BackColor = Color::Red;
		return;
	}


	// Making sure sub sections is not empty
	if (sendingAmountString == "" || isOnlySpaces(sendingAmountString)) {
		showMessage("Amount of Sub Grades is missing.", "bad");
		amountSubText->BackColor = Color::Red;
		return;
	}

	// making sure sub sections is ONLY digits
	if (!isDigits(sendingAmountString)) {
		showMessage("Amount of Sub Grades is not all digits.", "bad");
		amountSubText->BackColor = Color::Red;
		return;
	}

	// Converting both percentage and Amount of sub grades
	double sendingPercent = stod(sendingPercentString);
	int sendingAmount = stoi(sendingAmountString);


	// Making sure the subSections is not equal to 1
	if (sendingAmount == 1) {
		showMessage("Amount of subs cannot be 1", "bad");
		amountSubText->BackColor = Color::Red;
		return;
	}
	
	// Making sure the percent is not 0 
	if (sendingPercent == 0) {
		showMessage("Percent would put grade over 100.", "bad");
		percentText->BackColor = Color::Red;
		return;
	}

	//  Making sure the percentage is not over 100 when adding this 
	if ((newClass.runningPercent + sendingPercent) > 100) {
		percentText->BackColor = Color::Red;
		showMessage("Percent would put grade over 100.", "bad");
		return;
	}
	
	

	// Passed all catches, newclass is ready to be made (really its a section that is being made)
	newClass.runningPercent += sendingPercent;
	newClass.addSection(sendingName, sendingPercent, sendingAmount);
	

	// If this section has subSections, then split the weight of the subSections
	if (sendingAmount != 0) {
		Grade* currSection = &newClass.sections[newClass.sections.size() - 1];


		double splitAmount = (100.00 / currSection->numOfSections());
		if ((100 % currSection->numOfSections()) != 0) {                                     // If there subSections are NOT able to split evenly
			string tempString = to_string(splitAmount);
			splitAmount = stod(tempString.substr(0, tempString.find('.') + 3));
			double difference = 100 - (splitAmount * (currSection->numOfSections() - 1));
			for (int i = 0; i < currSection->numOfSections() - 1; i++) {
				currSection->sections[i].weight = splitAmount;
			}
			currSection->sections[currSection->numOfSections() - 1].weight = difference;     // Makes the last subsection have the difference
		}
		else {                                                                               // If the subSections ARE able to split evenly
			for (int i = 0; i < currSection->numOfSections(); i++) {
				currSection->sections[i].weight = splitAmount;
			}
		}
	}


	
	
	
	// Clearing Adding Section Smaller SCreen
	sectionNameInput->Text = "";
	percentInput->Text = "";
	amountSubInput->Text = "";

	// Refreshing screen functions
	refreshSectionDisplay();
	resetAddingColors();
	sectionSubDisplay->Items->Clear();
	refreshSummaryIndicators();
}

private: System::Void deleteSectionButton(System::Object^ sender, System::EventArgs^ e) {
	if (sectionNamesDisplay->SelectedIndex == -1)
		return;
	
	

	newClass.removeSection(sectionNamesDisplay->SelectedIndex);
	refreshSectionDisplay();
	sectionSubDisplay->Items->Clear();
	refreshSummaryIndicators();
}

private: System::Void subSectionChangeName() {
	if (sectionSubDisplay->SelectedIndex == -1) {
		return;
	}
	
	// Making sure that we do not set any file names to spaces
	if (isOnlySpaces(hToString(subSectionInputName->Text))) {
		subSectionInputName->Text = "";
		return;
	}

	Grade* currSection = &newClass.sections[sectionNamesDisplay->SelectedIndex];

	
	currSection->sections[sectionSubDisplay->SelectedIndex].name = hToString(subSectionInputName->Text);
	subSectionInputName->Text = "";
	int savingIndex = sectionSubDisplay->SelectedIndex;
	refreshSubSectionDisplay();
	sectionSubDisplay->SelectedIndex = savingIndex;
	refreshSummaryIndicators();
}
private: System::Void subSectionChangeWeight() {
	if ((sectionSubDisplay->SelectedIndex == -1) ||
		(subSectionInputWeight->Text == "")) {
		return;
	}

	Grade* currSection = &newClass.sections[sectionNamesDisplay->SelectedIndex];

	string tempString = hToString(subSectionInputWeight->Text);
	if (!isDigits(tempString)) {
		return;
	}
	double sendingWeight = stod(tempString);
	double previousRunningPercent = currSection->runningPercent;
	Grade* currSubSection = &currSection->sections[sectionSubDisplay->SelectedIndex];
	
	if (currSubSection->weight != -1) {
		currSection->runningPercent -= currSubSection->weight;
	}

	if ((sendingWeight + currSection->runningPercent) > 100) {
		currSection->runningPercent = previousRunningPercent;
		return;
	}

	currSection->sections[sectionSubDisplay->SelectedIndex].weight = sendingWeight;
	currSection->updateWeight();
	subSectionInputWeight->Text = "";
	refreshSubSectionDisplay();
	refreshSummaryIndicators();
}
private: System::Void saveSubSectionButotn_Click(System::Object^ sender, System::EventArgs^ e) {
	subSectionChangeName();
	subSectionChangeWeight();
}

private: System::Void splitGradesButtons_Click(System::Object^ sender, System::EventArgs^ e) {
	// Setting all of the subSections of this section to an even distribution
	if (sectionNamesDisplay->SelectedIndex == -1)
		return;
	if (newClass.sections[sectionNamesDisplay->SelectedIndex].numOfSections() == 0)
		return;


	Grade* currSection = &newClass.sections[sectionNamesDisplay->SelectedIndex];


	double splitAmount = (100.00 / currSection->numOfSections());
	if ((100 % currSection->numOfSections()) != 0) {                                     // If there subSections are NOT able to split evenly
		string tempString = to_string(splitAmount);
		splitAmount = stod(tempString.substr(0, tempString.find('.') + 3));
		double difference = 100 - (splitAmount * (currSection->numOfSections() - 1));
		for (int i = 0; i < currSection->numOfSections() - 1; i++) {
			currSection->sections[i].weight = splitAmount;
		}
		currSection->sections[currSection->numOfSections() - 1].weight = difference;     // Makes the last subsection have the difference
	}
	else {                                                                               // If the subSections ARE able to split evenly
		for (int i = 0; i < currSection->numOfSections(); i++) {
			currSection->sections[i].weight = splitAmount;
		}
	}

	refreshSubSectionDisplay();
}



private: System::Void addClasButton(System::Object^ sender, System::EventArgs^ e) {
	resetAddingColors();
	if (summaryClassName->Text == "") {
		classNamePanel->BackColor = Color::Red;
		showMessage("Class has no name.", "bad");
		return;
	}

	ifstream testingFile(newClass.name + ".txt");
	if (testingFile) {  // if open
		classNamePanel->BackColor = Color::Red;
		testingFile.close();
		showMessage("Class Name is already used.", "bad");
		return;
	}

	if (summaryHasSections->BackColor == Color::Red) {
		showMessage("Class does not have sections", "bad");
		return;
	}


	if (summaryWeightDisplay->BackColor == Color::Red) {
		showMessage("Not all weights are inputted.", "bad");
		return;
	}
	if (summarySumsDisplay->BackColor == Color::Red) {
		showMessage("Weights do not add to 100.00.", "bad");
		return;
	}
	if (summaryAllSectionsNamed->BackColor == Color::Red) {
		showMessage("Not all sections are named.","bad");
		return;
	}
	

	
	// Saving into vector of classes for visual
	allClasses.push_back(newClass);


	// Saving class to the files for memory
	newClass.SaveFile();

	// Resetting everything 
	cleanAddClassPage(nullptr, nullptr);


	// Showing message that name has been added
	showMessage("Class has been added", "good");
}

// ==========================================================================





// Helper Functions: ========================================================
private: System::Void cleanAddClassPage(System::Object^ sender, System::EventArgs^ e) {
	classNameInput->Text = "";
	amountSubInput->Text = "";
	summaryClassName->Text = "";
	subSectionInputName->Text = "";
	subSectionInputWeight->Text = "";
	percentInput->Text = "";
	amountSubInput->Text = "";

	resetAddingColors();

	sectionNamesDisplay->Items->Clear();
	sectionSubDisplay->Items->Clear();
	sectionPercentSum->Text = "0.00";
	subSectionPercentSum->Text = "0.00";
	refreshSummaryIndicators();
	newClass.reset();
	refreshSummaryIndicators();



}

private: System::Void summaryUpdateName(System::Object^ sender, System::EventArgs^ e) {
	if (summaryClassName->Text != "") {
		classNamePanel->BackColor = foreColor->Color;
	}
	summaryClassName->Text = classNameInput->Text;
	newClass.reset();
	newClass.name = hToString(classNameInput->Text);
}

// ==========================================================================
#pragma endregion





#pragma region Change Grades Tab Functions

// ===================================
// Refreshing Screens: 
void refreshCGChooseClassDisplay() {
	chooseClassDisplay->Items->Clear();
	ostringstream tempStream;
	for (int i = 0; i < allClasses.size(); i++){
		tempStream << left << setfill('.') << setw(66) << allClasses[i].name;
		tempStream << right << setw(6) << fixed << setprecision(2) << allClasses[i].grade;
		chooseClassDisplay->Items->Add(stringToH(tempStream.str()));
		tempStream.str("");
	}
}

void refreshCGSections() {
	CGSectionDisplay->Items->Clear();
	ostringstream tempStream;
	Grade* currClass = &allClasses[chooseClassDisplay->SelectedIndex];
	string adjustedName = "";
	for (int i = 0; i < currClass->numOfSections() ; i++) {
		if (currClass->sections[i].name.length() > 10)
			adjustedName = currClass->sections[i].name.substr(0, 10);
		else
			adjustedName = currClass->sections[i].name;
		tempStream << left << setfill('.') << setw(12) << adjustedName;
		tempStream << right << setw(7) << fixed << setprecision(2) << currClass->sections[i].grade;
		CGSectionDisplay->Items->Add(stringToH(tempStream.str()));
		tempStream.str("");
	}
}

void refreshCGSubSections() {
	CGsubSectionDisplay->Items->Clear();
	ostringstream tempStream;
	if (allClasses[chooseClassDisplay->SelectedIndex].sections[CGSectionDisplay->SelectedIndex].numOfSections() == 0) {
		return;
	}

	string adjustedName = "";
	Grade* currSection = &allClasses[chooseClassDisplay->SelectedIndex].sections[CGSectionDisplay->SelectedIndex];
	for (int i = 0; i < currSection->numOfSections(); i++) {
		if (currSection->sections[i].name.length() > 10)
			adjustedName = currSection->sections[i].name.substr(0, 10);
		else
			adjustedName = currSection->sections[i].name;
		tempStream << left << setfill('.') << setw(12) << adjustedName;
		tempStream << right << setw(7) << fixed << setprecision(2) << currSection->sections[i].grade;
		CGsubSectionDisplay->Items->Add(stringToH(tempStream.str()));
		tempStream.str("");
	}
}
// ===================================



// ===================================
// Loads Edit Present tab: 
private: System::Void tabPage3_Enter(System::Object^ sender, System::EventArgs^ e) {
	// Clearing the 3 display screens
	chooseClassDisplay->Items->Clear();
	CGSectionDisplay->Items->Clear();
	CGsubSectionDisplay->Items->Clear();

	// Showing all of the classes in all classes vector
	refreshCGChooseClassDisplay();

	// Resetting the all information saved button
	classesSavedIndicator->BackColor = Color::Green;
	classesSavedIndicator->Text = "Saved!";

	// Removing any text that was in the change grade
	CHChangeGradeInput->Text = "";
	changingGradeDisplayText->Text = "N/A";

	
}
// ===================================






// ===================================
// ChooseClass index changes: 
private: System::Void chooseClassDisplay_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	CGSectionDisplay->Items->Clear();
	CGsubSectionDisplay->Items->Clear();
	if (chooseClassDisplay->SelectedIndex == -1) {
		return;
	}
	refreshCGSections();
	changingGradeDisplayText->Text = "N/A";
}
// ===================================

// ===================================
// Section index changes: 
private: System::Void CGSectionDisplay_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	CGsubSectionDisplay->Items->Clear();
	if (CGSectionDisplay->SelectedIndex == -1) {
		return;
	}
	refreshCGSubSections();
	if (allClasses[chooseClassDisplay->SelectedIndex].sections[CGSectionDisplay->SelectedIndex].numOfSections() == 0) {
		CHChangeGradeInput->Focus();
		changingGradeDisplayText->Text = stringToH(allClasses[chooseClassDisplay->SelectedIndex].sections[CGSectionDisplay->SelectedIndex].name);
	}
	else {
		changingGradeDisplayText->Text = "N/A";
	}
		
}
// ===================================

// ===================================
// subSectionDisplay index changes: 
private: System::Void CGsubSectionDisplay_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	if (CHChangeGradeInput->Text != "")
		return;
	CHChangeGradeInput->Focus();
	changingGradeDisplayText->Text = 
		stringToH(allClasses[chooseClassDisplay->SelectedIndex].sections[CGSectionDisplay->SelectedIndex].sections[CGsubSectionDisplay->SelectedIndex].name);
}
// ===================================




// ===================================
// Change Grade Button:
private: System::Void CGChangeGrade(System::Object^ sender, System::EventArgs^ e) {

	// If there is not a class selected OR if there is not a section selected, <return>
	if (chooseClassDisplay->SelectedIndex == -1 ||
		CGSectionDisplay->SelectedIndex == -1) {
		return;
	}

	// If a class and section are selected, BUT the section selected has sub sections and one is not selected, <return>
	if ((allClasses[chooseClassDisplay->SelectedIndex].sections[CGSectionDisplay->SelectedIndex].numOfSections() > 0) &&
		(CGsubSectionDisplay->SelectedIndex == -1)) {
		return;
	}



	double newGrade;
	Button^ clickedButton = safe_cast<Button^>(sender);

	if (hToString(clickedButton->Text).substr(0, 1) == "R") {    // If the reset grade button was clicked instead of the Change Grade button
		newGrade = -1;
	}
	else {
		// If input is empty, <return>
		if (CHChangeGradeInput->Text == "") {
			return;
		}

		// Making sure input is a double
		string tempString = hToString(CHChangeGradeInput->Text);
		if (!isDigits(tempString))
			return;
		newGrade = stod(tempString);

		// Making sure input is not negative
		if (newGrade < 0 || newGrade > 100)
			return;

	}

	// ======[ !! PASSES ALL CATCHES !! ]======

	


	// Changing Indicator so user knows that there is unsaved data
	classesSavedIndicator->BackColor = Color::Red;
	classesSavedIndicator->Text = "Not Saved!";

	// Saving the index of the sectionDisplay so that it can be rechosen
	int sectionDisplayIndexSaver = CGSectionDisplay->SelectedIndex;
	int chosenClassDisplayIndexSaver = chooseClassDisplay->SelectedIndex;

	
	// Enter here if the selected section has sub sections    --> Changing the chosen SUBSECTION grade
	if (allClasses[chooseClassDisplay->SelectedIndex].sections[CGSectionDisplay->SelectedIndex].numOfSections() > 0) {
		allClasses[chooseClassDisplay->SelectedIndex].sections[CGSectionDisplay->SelectedIndex].sections[CGsubSectionDisplay->SelectedIndex].grade = (newGrade);
	}
	// Enter here if the selected section has NO sub sections --> Changing the chosen SECTION grade
	else {
		allClasses[chooseClassDisplay->SelectedIndex].sections[CGSectionDisplay->SelectedIndex].grade = (newGrade);
		
	}

	// Refreshing all the grades of all the classes
	refreshAllGrades();

	// Refreshing all 3 displays 
	refreshCGChooseClassDisplay();
	chooseClassDisplay->SelectedIndex = chosenClassDisplayIndexSaver;
	refreshCGSections();
	CGSectionDisplay->SelectedIndex = sectionDisplayIndexSaver;
	refreshCGSubSections();

	// Erasing what was in the input to get ready for next input
	CHChangeGradeInput->Text = "";
}
// ===================================


// ===================================
// Save this grade button:
private: System::Void CGSaveGradesButton_Click(System::Object^ sender, System::EventArgs^ e) {
	for (int i = 0; i < allClasses.size(); i++){
		allClasses[i].SaveFile();
	}
	classesSavedIndicator->BackColor = Color::Green;
	classesSavedIndicator->Text = "Saved!";
}
// ===================================


// ===================================
// Delete this class
private: System::Void CGDeleteClass_Click(System::Object^ sender, System::EventArgs^ e) {
	if (chooseClassDisplay->SelectedIndex == -1)
		return;

	// Starting timer to hide the deleting button
	deletingClassMessage->Visible = true;
	messageTimer->Start();

	// Deleting the file with this name
	string fileName = allClasses[chooseClassDisplay->SelectedIndex].name + ".txt";
	string sendingCode = "del " + fileName;
	system(sendingCode.c_str());

	// Deleting the name from _allClasses_
	sendingCode = "ren _allClasses_.txt previousVersion__.txt";
	system(sendingCode.c_str());

	ifstream previousVersion("previousVersion__.txt");
	ofstream newVersion("_allClasses_.txt");
	
	string tempString;
	while (!previousVersion.eof()) {
		getline(previousVersion, tempString);
		if (!tempString.empty() && (tempString != fileName)) {
			newVersion << tempString << endl;
		}
	}
	previousVersion.close();
	newVersion.close();
	
	system("del previousVersion__.txt");
	


	// Removing from the array of allClasses
	allClasses.erase(allClasses.begin() + chooseClassDisplay->SelectedIndex);
	
	
	
	tabPage3_Enter(nullptr, nullptr);
}
// ===================================
#pragma endregion





#pragma region Settings Tab Functions

// Makes a file of the example class in case there is an error someday
private: System::Void settingsMakeExampleFile_Click(System::Object^ sender, System::EventArgs^ e) {
	ofstream exampleFile("000_ExampleFile_000.txt");
	exampleFile << "2      <- number of SECTIONS         " << endl;
	exampleFile << "Exam      <- Section Name            " << endl;
	exampleFile << "50        <- Section Weight	         " << endl;
	exampleFile << "-1        <- Section Grade           " << endl;
	exampleFile << "0         <- has sub sections	     " << endl;
	exampleFile << "Homeworks <- Section Name            " << endl;
	exampleFile << "50        <- Section Weight          " << endl;
	exampleFile << "-1        <- Section Grade           " << endl;
	exampleFile << "2         <- has sub sections	     " << endl;
	exampleFile << "HW1           <- Sub Section Name	 " << endl;
	exampleFile << "50            <- Sub Section Weight  " << endl;
	exampleFile << "-1            <- Sub Section Grade   " << endl;
	exampleFile << "HW2           <- Sub Section Name    " << endl;
	exampleFile << "50            <- Sub Section Weight  " << endl;
	exampleFile << "-1            <- Sub Section Grade   " << endl;
	exampleFile << "<><><>					             " << endl;
	exampleFile.close();

}


// Changing the theme of the application
private: System::Void settingBackColorButton(System::Object^ sender, System::EventArgs^ e) {
	backColor->ShowDialog();
	settingsBackColorDisplay->BackColor = backColor->Color;
	refreshTheme();
}
private: System::Void settingForeColorButton_Click(System::Object^ sender, System::EventArgs^ e) {
	foreColor->ShowDialog();
	settingsForeColorDisplay->BackColor = foreColor->Color;
	refreshTheme();
}
private: System::Void settingsTextColorButton_Click(System::Object^ sender, System::EventArgs^ e) {
	textColor->ShowDialog();
	settingsTextColorDisplay->BackColor = textColor->Color;
	refreshTheme();
}

// Entering the settings page
private: System::Void tabPage3_Click(System::Object^ sender, System::EventArgs^ e) {
	settingsBackColorDisplay->BackColor = backColor->Color;
	settingsForeColorDisplay->BackColor = foreColor->Color;
	settingsTextColorDisplay->BackColor = textColor->Color;
}

// A preset is clicked
private: System::Void presetClicked(System::Object^ sender, System::EventArgs^ e) {
	
	Label^ chosen = safe_cast<Label^>(sender);
	if (hToString(chosen->Name).substr(0, 7) == "preset1") {
		backColor->Color = preset1Box->BackColor;
		foreColor->Color = preset1Label->BackColor;
		textColor->Color = preset1Label->ForeColor;
	}
	else if (hToString(chosen->Name).substr(0, 7) == "preset2") {
		backColor->Color = preset2Box->BackColor;
		foreColor->Color = preset2Label->BackColor;
		textColor->Color = preset2Label->ForeColor;
	}
	else if (hToString(chosen->Name).substr(0, 7) == "preset3") {
		backColor->Color = preset3Box->BackColor;
		foreColor->Color = preset3Label->BackColor;
		textColor->Color = preset3Label->ForeColor;
	}
	else if (hToString(chosen->Name).substr(0, 7) == "preset4") {
		backColor->Color = preset4Box->BackColor;
		foreColor->Color = preset4Label->BackColor;
		textColor->Color = preset4Label->ForeColor;
	}
	refreshTheme();



	// Saving the custom theme
	ofstream customThemeFile("_customTheme_.txt");
	customThemeFile << hToString(chosen->Name).substr(6, 1) << endl;
	customThemeFile.close();

}





// Open all class file button is clicked
private: System::Void settingsOpenAllClassFIle_Click(System::Object^ sender, System::EventArgs^ e) {
	ifstream testFileOpen("_allClasses_.txt");
	if (!testFileOpen) {
		settingsStatusOutput->Text = "Could not open.";
		return;
	}
	testFileOpen.close();
	settingsStatusOutput->Text = "Opened File.";

	system("_allClasses_.txt");
}




//  Bool that holds if the admin page is active (opening/opened already)
bool adminPageActive = false;
int incrementAmount = 10;
int tickAmount = 5;

// Admin Page Animation TIMER TICK
private: System::Void adminPageAnimation_Tick(System::Object^ sender, System::EventArgs^ e) {

	if (adminPageActive) {   // Open the admin page, [OPENING] ANIMATION
		if ((settingsHider1->Location.X < -630) && (settingsHider2->Location.Y > 650))
			adminPageAnimation->Stop();
		if (settingsHider1->Location.X > -630)
			settingsHider1->Location = Point(settingsHider1->Location.X - incrementAmount, settingsHider1->Location.Y);
		if (settingsHider2->Location.Y < 650)
			settingsHider2->Location = Point(settingsHider2->Location.X, settingsHider2->Location.Y + incrementAmount);
	}
	else {                   // Close the admin page, [CLOSE] ANIMATION
		if ((settingsHider1->Location.X > 4) && (settingsHider2->Location.Y < 9))
			adminPageAnimation->Stop();
		if (settingsHider1->Location.X < 4)
			settingsHider1->Location = Point(settingsHider1->Location.X + incrementAmount, settingsHider1->Location.Y);
		if (settingsHider2->Location.Y > 9)
			settingsHider2->Location = Point(settingsHider2->Location.X, settingsHider2->Location.Y - incrementAmount);
	}
}

void refreshSettingsDisplay() {
	ifstream allClassesFile("_allClasses_.txt");
	if (!allClassesFile)
		return;
	string tempString;
	ifstream currClassFile;
	settingsDisplayClasses->Items->Clear();
	while (!allClassesFile.eof()) {
		getline(allClassesFile, tempString);
		if (tempString.empty())
			continue;
		currClassFile.open(tempString);
		if (!currClassFile)
			continue;
		settingsDisplayClasses->Items->Add(stringToH(tempString));
		currClassFile.close();
	}

	allClassesFile.close();
}

private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	refreshSectionDisplay();
}


// Admin mode button is clicked
private: System::Void settingsAdminButton_Click(System::Object^ sender, System::EventArgs^ e) {
	adminPageAnimation->Interval = tickAmount;
	adminPageAnimation->Stop();
	adminPageAnimation->Start();
	adminPageActive = !adminPageActive;

	if (adminPageActive) {
		settingsAdminButton->Text = "Close Admin";
	}
	else {                                              
		settingsAdminButton->Text = "Open Admin";
	}
	if (!adminPageActive) 
		return;

	refreshSettingsDisplay();

}

// Open chosen class button is clicked
private: System::Void settingsOpenChosenClassFile_Click(System::Object^ sender, System::EventArgs^ e) {
	if (settingsDisplayClasses->SelectedIndex == -1)
		return;
	string temp = hToString(settingsDisplayClasses->Items[0]->ToString());
	settingsDisplayClasses->SelectedIndex = -1;

	system(temp.c_str());
}

// Open Explorer button clicked
private: System::Void settingsOpenExplorer_Click(System::Object^ sender, System::EventArgs^ e) {
	system("start .");
}

// Icon Clicked
private: System::Void IconClicked(System::Object^ sender, System::EventArgs^ e) {
	PictureBox^ currBox = safe_cast<PictureBox^>(sender);
	ofstream customIconFile("_customIcon_.txt");
	customIconFile << hToString(currBox->AccessibleName) << endl;
	customIconFile.close();
	setIcon();
}

// Save form name button
private: System::Void settingsSetFormNameButton_Click(System::Object^ sender, System::EventArgs^ e) {
	if (settingsSetFormNameInput->Text == "") {
		return;
	}
	ofstream customFormNameFile("_customFormName_.txt");
	customFormNameFile << hToString(settingsSetFormNameInput->Text) << endl;
	customFormNameFile.close();
	setFormName();
}





#pragma endregion





#pragma region Test Scenarios Functions
void makeMissingGradesZero() {
	for (int i = 0; i < allClasses.size(); i++){										 // Going through all classes
		if (allClasses[i].numOfSections() != 0) {										 // If classes have sections which they should
			for (int j = 0; j < allClasses[i].numOfSections(); j++){					 // Going through all sections of class
				if (allClasses[i].sections[j].numOfSections() != 0) {					 // If section has subSections
					for (int k = 0; k < allClasses[i].sections[j].numOfSections(); k++){ // Going through all subSections of section
						if (allClasses[i].sections[j].sections[k].grade == -1)           // If this subSection is -1, make 0
							allClasses[i].sections[j].sections[k].grade = 0;
					}
				}
				else {                                                                   // If it does NOT have sub sections
					if (allClasses[i].sections[j].grade == -1)                           // If this section is -1, make 0
						allClasses[i].sections[j].grade = 0;
				}
			}
		}
	}
}

private: System::Void tab3_Enter(System::Object^ sender, System::EventArgs^ e) {
	TSChooseClassBox->Items->Clear();
	TSSectionsDisplay->Items->Clear();
	TSSubSectionsDisplay->Items->Clear();
	for (int i = 0; i < allClasses.size(); i++){
		TSChooseClassBox->Items->Add(stringToH(allClasses[i].name));
	}
	changeGradeTrack->Value = 0;
	TSDisplayGradeBottom->Text = "0";
	TSDisplayGradeTop->Text = "N/A";
	makeMissingGradesZero();
	refreshAllGrades();
}

private: System::Void tab3_Leave(System::Object^ sender, System::EventArgs^ e) {
	grabClassesFromFiles();
}



void refreshTSSectionDisplay() {
	Grade* currClass = &allClasses[TSChooseClassBox->SelectedIndex];
	String^ tempString;
	ostringstream tempStream;
	for (int i = 0; i < currClass->numOfSections(); i++){
		tempStream << left << setfill('.') << setw(29) << currClass->sections[i].name;
		tempStream << right << setw(6) << fixed << setprecision(2) << currClass->sections[i].grade;
		tempString = stringToH(tempStream.str());
		TSSectionsDisplay->Items->Add(tempString);
		tempStream.str("");
	}

}
void refreshTSSubSectionDisplay() {
	Grade* currSection = &allClasses[TSChooseClassBox->SelectedIndex].sections[TSSectionsDisplay->SelectedIndex];
	String^ tempString;
	ostringstream tempStream;
	for (int i = 0; i < currSection->numOfSections(); i++) {
		tempStream << left << setfill('.') << setw(29) << currSection->sections[i].name;
		tempStream << right << setw(6) << fixed << setprecision(2) << currSection->sections[i].grade;
		tempString = stringToH(tempStream.str());
		TSSubSectionsDisplay->Items->Add(tempString);
		tempStream.str("");
	}
}

bool movingTrack = false;
// Chosen class is changed
private: System::Void TSChooseClassBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	TSSectionsDisplay->Items->Clear();
	TSSubSectionsDisplay->Items->Clear();

	if (TSChooseClassBox->SelectedIndex == -1) 
		return;

	refreshTSSectionDisplay();
	double tempDouble = allClasses[TSChooseClassBox->SelectedIndex].grade;
	TSDisplayGradeTop->Text = stringToH(to_string(tempDouble));
}

// Chosen section is changed
private: System::Void TSSectionsDisplay_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	

	TSSubSectionsDisplay->Items->Clear();
	if ((TSSectionsDisplay->SelectedIndex == -1) || (TSChooseClassBox->SelectedIndex == -1))
		return;
	refreshTSSubSectionDisplay();

	if (movingTrack)
		return;

	// If it does not have sub sections
	if (allClasses[TSChooseClassBox->SelectedIndex].sections[TSSectionsDisplay->SelectedIndex].numOfSections() == 0) {
		int tempInt = allClasses[TSChooseClassBox->SelectedIndex].sections[TSSectionsDisplay->SelectedIndex].grade;
		changeGradeTrack->Value = tempInt;
		TSDisplayGradeBottom->Text = stringToH(to_string(tempInt));
	}
}


private: System::Void TSSubSectionsDisplay_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	if (movingTrack)
		return;

	int tempInt = allClasses[TSChooseClassBox->SelectedIndex].sections[TSSectionsDisplay->SelectedIndex].grade;
	changeGradeTrack->Value = tempInt;
	TSDisplayGradeBottom->Text = stringToH(to_string(tempInt));

}

private: System::Void changeGradeTrack_Scroll(System::Object^ sender, System::EventArgs^ e) {
	// Changing the display grade as the track changes
	int tempInt = changeGradeTrack->Value;
	TSDisplayGradeBottom->Text = stringToH(to_string(tempInt));

	// If nothing is selected, do nothing
	if ((TSSectionsDisplay->SelectedIndex == -1) || (TSChooseClassBox->SelectedIndex == -1))
		return;

	// If the section selected has not subsections, we are changing that sections grade
	if (allClasses[TSChooseClassBox->SelectedIndex].sections[TSSectionsDisplay->SelectedIndex].numOfSections() == 0) {
		allClasses[TSChooseClassBox->SelectedIndex].sections[TSSectionsDisplay->SelectedIndex].grade = tempInt;
		int savingSectionDisplayIndex = TSSectionsDisplay->SelectedIndex;
		TSSectionsDisplay->Items->Clear();		
		refreshTSSectionDisplay();
		TSSectionsDisplay->SelectedIndex = savingSectionDisplayIndex;
		refreshAllGrades();
		String^ sendingGrade;
		if (allClasses[TSChooseClassBox->SelectedIndex].grade == -1)
			sendingGrade = "N/A";
		else
			sendingGrade = stringToH(to_string(allClasses[TSChooseClassBox->SelectedIndex].grade));
		TSDisplayGradeTop->Text = sendingGrade;
		return;
	}
	
	// If this section has subsections, make sure that subsection is selected, if not --> do nothing
	if (TSSubSectionsDisplay->SelectedIndex == -1) {
		return;
	}

	// Change the grade of this subsection
	movingTrack = true;
	allClasses[TSChooseClassBox->SelectedIndex].sections[TSSectionsDisplay->SelectedIndex].sections[TSSubSectionsDisplay->SelectedIndex].grade = tempInt;
	int savingSectionDisplayIndex = TSSectionsDisplay->SelectedIndex;
	int savingSubSectionDisplayIndex = TSSubSectionsDisplay->SelectedIndex;

	TSSectionsDisplay->Items->Clear();
	refreshTSSectionDisplay();
	TSSectionsDisplay->SelectedIndex = savingSectionDisplayIndex;

	TSSubSectionsDisplay->Items->Clear();
	refreshTSSubSectionDisplay();
	TSSubSectionsDisplay->SelectedIndex = savingSubSectionDisplayIndex;

	refreshAllGrades();
	TSDisplayGradeTop->Text = stringToH(to_string(allClasses[TSChooseClassBox->SelectedIndex].grade));
	movingTrack = false;
	return;
}


private: System::Void TSResetAllGradesButton_Click(System::Object^ sender, System::EventArgs^ e) {
	if (TSChooseClassBox->SelectedIndex == -1)
		return;
	tab3_Leave(nullptr, nullptr);
	tab3_Enter(nullptr, nullptr);

}
private: System::Void TSSaveThisClassButton_Click(System::Object^ sender, System::EventArgs^ e) {
	if (TSChooseClassBox->SelectedIndex == -1)
		return;
	allClasses[TSChooseClassBox->SelectedIndex].SaveFile();
}
#pragma endregion


















};
}


