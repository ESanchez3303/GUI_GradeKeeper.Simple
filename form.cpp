#include "form.h"
using namespace System;
using namespace System::Windows::Forms;
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GradeCalculator::form form_;                   // ProjectCPP1::MainForm form;
	Application::Run(% form_);
}

