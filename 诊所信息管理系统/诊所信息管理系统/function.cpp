#include"head.h"

string patient::getDoctorName()
{
	return doctors;
}

string patient::getPatientName()
{
	return patientName;
}

float patient::getConsultationFee()
{
	return consultationFee;
}

vector<patient> patient::getPatientRecords()
{
	vector<patient>patientRecords;
	ifstream infile("patientRecords.txt", ios::in | ios::_Nocreate);
	if (!infile)
	{
		cout << "Open error!" << endl;
		exit(1);
	}
	patient temp;
	while (!infile.eof())
	{
		infile >> temp.patientName >> temp.doctors >> temp.medicalFee >> temp.consultationFee;
		patientRecords.push_back(temp);
	}
	infile.close();
	patientRecords.pop_back();
	return patientRecords;
}

void patient::savePatientRecords(vector<patient>patients)
{
	ofstream outfile("patientRecords.txt", ios::out);
	if (!outfile)
	{
		cout << "Open error!" << endl;
		exit(1);
	}
	vector<patient>::iterator it;
	for (it = patients.begin(); it != patients.end(); it++)
	{
		outfile << (*it).patientName << " " << (*it).doctors << " " << (*it).medicalFee
			<< " " << (*it).consultationFee << endl;
	}
	outfile.close();
}

float patient::countConsultationFee(vector<patient>patients)
{
	float doctorFee = 0;
	vector<patient>::iterator it;
	for (it = patients.begin(); it != patients.end(); it++)
	{
		doctorFee += (*it).consultationFee;
	}
	return doctorFee;
}

void patient::changeDoctor(string name)
{
	this->doctors = name;
}

float patient::getMedicalFee()
{
	return medicalFee;
}

unsigned int doctor::findDoctor(vector<doctor>doctors, string name)
{
	int number;
	for (number = 0; number < doctors.size(); number++)
	{
		if (name == doctors[number].getDoctorName())
			return number;
	}
}

string doctor::getDoctorName()
{
	return doctorName;
}

float doctor::getDoctorConsultationFee()
{
	return consultationFee1;
}

vector<doctor> doctor::getDoctorRecords()
{
	vector<doctor>doctorRecords;
	ifstream infile("doctorRecords.txt", ios::in | ios::_Nocreate);
	if (!infile)
	{
		cout << "Open error!" << endl;
		exit(1);
	}
	doctor temp;
	while (!infile.eof())
	{
		infile >> temp.doctorName >> temp.profession >> temp.consultationFee1;
		doctorRecords.push_back(temp);
	}
	infile.close();
	doctorRecords.pop_back();
	return doctorRecords;
}

vector<patient> doctor::findPatient(string name)
{
	vector<patient>patients;
	patient b;
	patients = b.getPatientRecords();
	vector<patient>::iterator it;
	for (it = patients.begin(); it != patients.end();)
	{
		string c = (*it).getDoctorName();
		if (name != c)
		{
			it = patients.erase(it);
		}
		else
		{
			++it;
		}
	}
	return patients;
}

void doctor::saveDoctorRecords(vector<doctor>doctors)
{
	ofstream outfile("doctorRecords.txt", ios::out);
	if (!outfile)
	{
		cout << "Open error!" << endl;
		exit(1);
	}
	vector<doctor>::iterator it;
	for (it = doctors.begin(); it != doctors.end(); it++)
	{
		outfile << (*it).doctorName << " " << (*it).profession << " " <<
			(*it).consultationFee1 << endl;
	}
	outfile.close();
}

void doctor::countFee(float fee)
{
	this->consultationFee1 += fee;
}

void record::modifyPatientRecord(vector<patient>patients, unsigned int number)
{
	doctor b;
	vector<doctor>doctorss = b.getDoctorRecords();
	patient a;
	int count = doctorss.size();
	unsigned int temp2 = 0;
	unsigned int temp3 = 0;
	float pFee = patients[number].getConsultationFee();
	string pDoctor = patients[number].getDoctorName();
	while (true)
	{
		cout << "该患者原本的信息为 " << endl;
		cout << patients[number] << endl;
		cout << "请输入正确信息" << endl;
		cout << "姓名  主治医师 医药费 诊费" << endl;
		cin >> patients[number];
		cout << "修改后该患者的信息为 " << endl;
		cout << patients[number] << endl << endl;
		cout << "你确定吗？" << endl;
		cout << "1.确定  2.再次修改  3.放弃修改" << endl;
		unsigned int temp;
		cin >> temp;
		if (1 == temp)
		{
			for (int i = 0; i < count; i++)
			{
				if (doctorss[i].getDoctorName() == patients[number].getDoctorName())
				{
					if (pDoctor == patients[number].getDoctorName())
					{
						doctorss[i].countFee(patients[number].getConsultationFee() - pFee);
					}
					else
					{
						doctorss[i].countFee(patients[number].getConsultationFee());
						unsigned int number2 = b.findDoctor(doctorss, pDoctor);
						doctorss[number2].countFee(-pFee);
					}
					b.saveDoctorRecords(doctorss);
					temp2 = 1;
					break;
				}
			}
			if (1 == temp2)
			{
				a.savePatientRecords(patients);
				cout << "修改成功！" << endl;
				break;
			}
			else if (0 == temp2)
			{
				cout << "记录中并没有名字为 " << patients[number].getDoctorName() << " 的医生" << endl;
				cout << "是否重新添加患者信息？ " << endl;
				cout << "1.是  2.否" << endl;
				unsigned int u;
				cin >> u;
				if (2 == u)
				{
					cout << "我们需要先生成" << patients[number].getDoctorName() << "的记录" << endl;
					cout << "请输入" << a.getDoctorName() << "的专业" << endl;
					string k;
					cin >> k;
					doctor q(patients[number].getDoctorName(), k, patients[number].getConsultationFee());
					doctorss.push_back(q);
					b.saveDoctorRecords(doctorss);
					a.savePatientRecords(patients);
					cout << "修改成功！" << endl;
					break;
				}
			}
		}
		else if (3 == temp)
		{
			break;
		}
	}
}

void record::modifyDoctorRecord(vector<doctor>doctors, unsigned int number)
{
	doctor a;
	patient b;
	string pName = doctors[number].getDoctorName();
	vector<patient>patients = b.getPatientRecords();
	while (true)
	{
		cout << "该医生原本的信息为 " << endl;
		cout << doctors[number] << endl;
		cout << "请输入正确信息(诊费无法修改)" << endl;
		cout << "姓名   专业 " << endl;
		cin >> doctors[number];
		cout << "修改后医生的信息为 " << endl;
		cout << doctors[number] << endl << endl;
		cout << "你确定吗？" << endl;
		cout << "1.确定  2.再次修改  3.放弃修改" << endl;
		unsigned int temp;
		cin >> temp;
		if (1 == temp)
		{
			if (pName != doctors[number].getDoctorName())
			{
				for (int i = 0; i < patients.size(); i++)
				{
					if (pName == patients[i].getDoctorName())
					{
						patients[i].changeDoctor(doctors[number].getDoctorName());
					}
				}
				b.savePatientRecords(patients);
			}
			a.saveDoctorRecords(doctors);
			cout << "修改成功！" << endl;
			break;
		}
		else if (3 == temp)
		{
			break;
		}
	}
}

void record::addPatientRecord(vector<patient>&patients)
{
	patient a;
	doctor b;
	vector<doctor>doctorss;
	doctorss = b.getDoctorRecords();
	int count = doctorss.size();
	while (true)
	{
		cout << "请输入要加入的患者信息 " << endl;
		cout << "姓名 主治医师 药费 诊费" << endl;
		cin >> a;
		int temp = 0;
		for (int i = 0; i < count; i++)
		{
			string doctorName = doctorss[i].getDoctorName();
			if (doctorName == a.getDoctorName())
			{
				float fee = a.getConsultationFee();
				doctorss[i].countFee(fee);
				temp = 1;
				b.saveDoctorRecords(doctorss);
				break;
			}
		}
		if (0 == temp)
		{
			cout << "记录中并没有名字为 " << a.getDoctorName() << " 的医生" << endl;
			cout << "是否重新添加患者信息？ " << endl;
			cout << "1.是  2.否" << endl;
			unsigned int u;
			cin >> u;
			if (2 == u)
			{
				cout << "我们需要先生成" << a.getDoctorName() << "的记录" << endl;
				cout << "请输入" << a.getDoctorName() << "的专业" << endl;
				string k;
				cin >> k;
				doctor q(a.getDoctorName(), k, a.getConsultationFee());
				doctorss.push_back(q);
				b.saveDoctorRecords(doctorss);
				break;
			}
		}
		else
		{
			break;
		}
	}
	patients.push_back(a);
	a.savePatientRecords(patients);
	cout << "添加成功！" << endl;
}

void record::addDoctorRecord(vector<doctor>&doctors)
{
	doctor a;
	cout << "请输入要加入的医生信息 " << endl;
	cout << " 姓名    专业" << endl;
	cin >> a;
	doctors.push_back(a);
	a.saveDoctorRecords(doctors);
	cout << "添加成功！" << endl;
}

void record::deletePatientRecord(vector<patient>&patients, unsigned int number)
{
	doctor b;
	string name = patients[number].getDoctorName();
	float fee = patients[number].getConsultationFee();
	vector<doctor>doctors = b.getDoctorRecords();
	unsigned int number2 = b.findDoctor(doctors, name);
	doctors[number2].countFee(-fee);
	patients.erase(patients.begin() + number);
	record a;
	b.saveDoctorRecords(doctors);
	a.savePatientRecords(patients);
	cout << "删除成功" << endl;
}

void record::deleteDoctorRecord(vector<doctor>&doctors, unsigned int number)
{
	doctor b;
	patient c;
	string name = doctors[number].getDoctorName();
	vector<patient>patientss = c.getPatientRecords();//全部病人
	vector<patient>patients = b.findPatient(name);//这个医生的病人
	unsigned int len = patients.size();
	if (len == 0)
	{
		doctors.erase(doctors.begin() + number);
		record a;
		a.saveDoctorRecords(doctors);
		cout << "删除成功" << endl;
	}
	if (len > 0)
	{
		cout << "您要删除的这名医生有" << len << "个病人" << endl;
		for (int i = 0; i < len; i++)
		{
			cout << patients[i] << endl;
		}
		cout << "是否还要继续删除这名医生？ " << endl;
		cout << "1.是  2.否" << endl;
		unsigned int temp;
		cin >> temp;
		if (1 == temp)
		{
			doctors.erase(doctors.begin() + number);
			record a;
			a.saveDoctorRecords(doctors);
			cout << "删除成功" << endl;
			for (int i = 0; i < patientss.size(); i++)
			{
				if (patientss[i].getDoctorName() == name)
				{
					string name1;
					int temp2 = 0;
				number1://用于下面的goto
					cout << "您需要将这名医生的病人更换主治医师" << endl;
					cout << "病人 " << patientss[i].getPatientName() << endl;
					cout << "主治医生: ";
					cin >> name1;
					for (int j = 0; j < doctors.size(); j++)
					{
						if (name1 == doctors[j].getDoctorName())
						{
							temp2 = 1;
						}
					}
					if (1 == temp2)
					{
						unsigned int num = b.findDoctor(doctors, name1);
						doctors[num].countFee(patientss[i].getConsultationFee());
						patientss[i].changeDoctor(name1);
						c.savePatientRecords(patientss);
						b.saveDoctorRecords(doctors);
					}
					if (0 == temp2)
					{
						cout << "记录中并没有名字为 " << name1 << "的医生" << endl;
						cout << "是否重新输入？" << endl;
						cout << "1.是    2.否" << endl;
						unsigned int temp3;
						cin >> temp3;
						if (1 == temp3)
						{
							goto number1;
						}
						if (2 == temp3)
						{
							cout << "您需要先生成" << name1 << "的记录" << endl;
							cout << "请输入" << name1 << "的专业" << endl;
							string pro;
							cin >> pro;
							doctor newDoc(name1, pro, patients[i].getConsultationFee());
							doctors.push_back(newDoc);
							b.saveDoctorRecords(doctors);
							patientss[i].changeDoctor(name1);
							c.savePatientRecords(patientss);
						}
					}
				}
			}
		}
	}
}

float record::countConFee(vector<doctor>&doctors)
{
	float allFee = 0;
	for (int i = 0; i < doctors.size(); i++)
	{
		allFee += doctors[i].getDoctorConsultationFee();
	}
	return allFee;
}

float record::countMedFee(vector<patient>&patients)
{
	float allFee = 0;
	for (int i = 0; i < patients.size(); i++)
	{
		allFee += patients[i].getMedicalFee();
	}
	return allFee;
}

void face::mainMenu()
{
	system("cls");
	cout << "欢迎使用 诊所信息管理系统 " << endl << endl;
	cout << "1.查看患者记录   2.查看医生记录   3.查看收费记录   4.关闭" << endl;
	unsigned int a;
	cin >> a;
	if (1 == a)
	{
		patientMenu();
	}
	else if (2 == a)
	{
		doctorMenu();
	}
	else if (3 == a)
	{
		viewIncome();
	}
	else if (4 == a)
	{
		return;
	}
}

void face::patientMenu()
{
	system("cls");
	record re;
	patient p;
	vector<patient>patients = p.getPatientRecords();
	cout << " 患者姓名 主治医生 药费  诊费" << endl;
	for (int i = 0; i < patients.size(); i++)
	{
		cout << 1 + i << "  " << patients[i] << endl;
	}
	cout << endl;
	cout << "请选择操作： " << endl;
	cout << "1.增添   2.修改   3.删除   4.返回" << endl;
	unsigned int a;
	cin >> a;
	if (1 == a)
	{
		re.addPatientRecord(patients);
		cout << endl;
		vector<patient>newPatients = p.getPatientRecords();
		cout << " 患者姓名 主治医生 药费  诊费" << endl;
		for (int i = 0; i < newPatients.size(); i++)
		{
			cout << i + 1 << "  " << newPatients[i] << endl;
		}
		cout << endl;
		cout << "输入 1 返回" << endl;
		unsigned int i;
		cin >> i;
		if (1 == i)
		{
			mainMenu();
		}
	}
	else if (2 == a)
	{
		int q;
		cout << " 患者姓名 主治医生 药费  诊费" << endl;
		for (q = 0; q < patients.size(); q++)
		{
			cout << 1 + q << "  " << patients[q] << endl;
		}
		cout << endl;
		cout << "请输入要修改的病人的编号: ";
		int num;
		cin >> num;
		re.modifyPatientRecord(patients, num - 1);
		cout << endl;
		vector<patient>newPatients = p.getPatientRecords();
		cout << " 患者姓名 主治医生 药费  诊费" << endl;
		for (int i = 0; i < newPatients.size(); i++)
		{
			cout << i + 1 << "  " << newPatients[i] << endl;
		}
		cout << endl;
		cout << "输入 1 返回" << endl;
		unsigned int i;
		cin >> i;
		if (1 == i)
		{
			mainMenu();
		}
	}
	else if (3 == a)
	{
		int q;
		cout << " 患者姓名 主治医生 药费  诊费" << endl;
		for (q = 0; q < patients.size(); q++)
		{
			cout << 1 + q << "  " << patients[q] << endl;
		}
		cout << endl;
		cout << "请输入要删除的病人的编号: ";
		int num;
		cin >> num;
		cout << "你确定要删除患者 " << patients[num - 1].getPatientName() << " 吗？" << endl;
		cout << "1.是   2.否" << endl;
		int ch;
		cin >> ch;
		if (1 == ch)
		{
			re.deletePatientRecord(patients, num - 1);
			cout << endl;
			vector<patient>newPatients = p.getPatientRecords();
			cout << " 患者姓名 主治医生 药费  诊费" << endl;
			for (int i = 0; i < newPatients.size(); i++)
			{
				cout << i + 1 << "  " << newPatients[i] << endl;
			}
			cout << endl;
			cout << "输入 1 返回" << endl;
			unsigned int i;
			cin >> i;
			if (1 == i)
			{
				mainMenu();
			}
		}
		if (2 == ch)
		{
			mainMenu();
		}
	}
	else if (4 == a)
	{
		mainMenu();
	}
}

void face::doctorMenu()
{
	system("cls");
	record re;
	doctor d;
	vector<doctor>doctors = d.getDoctorRecords();
	cout << " 医生姓名    专业     诊费" << endl;
	for (int i = 0; i < doctors.size(); i++)
	{
		cout << i + 1 << "  " << doctors[i] << endl;
	}
	cout << endl;
	cout << "请选择操作：" << endl;
	cout << "1.增添   2.修改   3.查看某医生的患者   4.删除  5.返回" << endl;
	unsigned int k;
	cin >> k;
	if (1 == k)
	{
		re.addDoctorRecord(doctors);
		cout << endl;
		vector<doctor>newDoctors = d.getDoctorRecords();
		cout << " 医生姓名    专业     诊费" << endl;
		for (int i = 0; i < newDoctors.size(); i++)
		{
			cout << i + 1 << "  " << newDoctors[i] << endl;
		}
		cout << endl;
		cout << "输入 1 返回" << endl;
		unsigned int i;
		cin >> i;
		if (1 == i)
		{
			mainMenu();
		}
	}
	if (2 == k)
	{
		cout << " 医生姓名    专业     诊费" << endl;
		for (int u = 0; u < doctors.size(); u++)
		{
			cout << u + 1 << "  " << doctors[u] << endl;
		}
		cout << endl;
		cout << "请输入要修改的医生的编号: ";
		int num;
		cin >> num;
		re.modifyDoctorRecord(doctors, num - 1);
		cout << endl;
		vector<doctor>newDoctors = d.getDoctorRecords();
		cout << " 医生姓名    专业     诊费" << endl;
		for (int i = 0; i < newDoctors.size(); i++)
		{
			cout << i + 1 << "  " << newDoctors[i] << endl;
		}
		cout << endl;
		cout << "输入 1 返回" << endl;
		unsigned int i;
		cin >> i;
		if (1 == i)
		{
			mainMenu();
		}
	}
	else if (3 == k)
	{
		cout << " 医生姓名    专业     诊费" << endl;
		for (int u = 0; u < doctors.size(); u++)
		{
			cout << u + 1 << "  " << doctors[u] << endl;
		}
		cout << endl;
		cout << "请输入要查看的医生的编号: ";
		int num;
		cin >> num;
		vector<patient>myPatients = d.findPatient(doctors[num - 1].getDoctorName());
		if (0 == myPatients.size())
		{
			cout << "这个医生没有患者.." << endl;
		}
		else
		{
			cout << " 患者姓名 主治医生 药费  诊费" << endl;
			for (int i = 0; i < myPatients.size(); i++)
			{
				cout << i + 1 << "  " << myPatients[i] << endl;
			}
		}
		cout << endl;
		cout << "输入 1 返回" << endl;
		unsigned int i;
		cin >> i;
		if (1 == i)
		{
			mainMenu();
		}
	}
	else if (4 == k)
	{
		cout << " 医生姓名    专业     诊费" << endl;
		for (int u = 0; u < doctors.size(); u++)
		{
			cout << u + 1 << "  " << doctors[u] << endl;
		}
		cout << endl;
		cout << "请输入要删除的医生的编号: ";
		int num;
		cin >> num;
		cout << "您确定要删除 " << doctors[num - 1].getDoctorName() << " 吗？" << endl;
		cout << "1.是   2.否" << endl;
		int ch;
		cin >> ch;
		if (1 == ch)
		{
			re.deleteDoctorRecord(doctors, num - 1);
			cout << endl;
			vector<doctor>newDoctors = d.getDoctorRecords();
			cout << " 医生姓名    专业     诊费" << endl;
			for (int i = 0; i < newDoctors.size(); i++)
			{
				cout << i + 1 << "  " << newDoctors[i] << endl;
			}
			cout << endl;
			cout << "输入 1 返回" << endl;
			unsigned int i;
			cin >> i;
			if (1 == i)
			{
				mainMenu();
			}
		}
		else if (2 == ch)
		{
			mainMenu();
		}
	}
	else if (5 == k)
	{
		mainMenu();
	}
}

void face::viewIncome()
{
	system("cls");
	record re;
	patient p;
	vector<patient>patients = p.getPatientRecords();
	cout << " 患者姓名 主治医生 药费  诊费" << endl;
	for (int i = 0; i < patients.size(); i++)
	{
		cout << 1 + i << "  " << patients[i] << endl;
	}
	cout << endl;
	doctor d;
	vector<doctor>doctors = d.getDoctorRecords();
	cout << " 医生姓名    专业     诊费" << endl;
	for (int i = 0; i < doctors.size(); i++)
	{
		cout << i + 1 << "  " << doctors[i] << endl;
	}
	cout << endl;
	cout << "共计" << patients.size() << "位患者" << endl;
	cout << "共计" << doctors.size() << "位医生" << endl;
	cout << "共收入" << re.countMedFee(patients) << "元的医药费" << endl;
	cout << "共收入" << re.countConsultationFee(patients) << "元的诊费" << endl;
	cout << "总收入" << re.countConsultationFee(patients) + re.countMedFee(patients) << "元" << endl;
	cout << endl;
	cout << "输入 1 返回" << endl;
	unsigned int i;
	cin >> i;
	if (1 == i)
	{
		mainMenu();
	}
}