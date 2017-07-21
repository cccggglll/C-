#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include<stdlib.h>
using namespace std;

class doctor;
class patient;
class face;

class patient
{
protected:
	string patientName;
	string doctors;
	float medicalFee;
	float consultationFee;
public:

	friend ostream& operator << (ostream&output, patient&c)
	{
		output << setw(4) << c.patientName << " | " << setw(4) 
			<< c.doctors << " | " << setw(3) << c.medicalFee <<  
			" | " << setw(3) << c.consultationFee;
		return output;
	}

	friend istream& operator >> (istream&input, patient&c)
	{
		input >> c.patientName >> c.doctors >> c.medicalFee >> c.consultationFee;
		return input;
	}

	string getDoctorName();
	
	string getPatientName();

	float getConsultationFee();
	
	vector<patient> getPatientRecords();
	
	void savePatientRecords(vector<patient>patients);
	
	float countConsultationFee(vector<patient>patients);
	
	void changeDoctor(string name);
	
	float getMedicalFee();

};

class doctor
{
protected:
	float consultationFee1;
	string doctorName;
	string profession;
public:
	
	doctor(string name = "某医生", string pro = "某专业", float fee = 0)
	{
		doctorName = name;
		profession = pro;
		consultationFee1 = fee;
	}

	unsigned int findDoctor(vector<doctor>doctors, string name);
	
	string getDoctorName();

	float getDoctorConsultationFee();

	friend ostream& operator << (ostream&output, doctor&c)
	{
		output << setw(5) << c.doctorName << " | " << setw(4) << c.profession 
			<< " | " << setw(3) << c.consultationFee1;
		return output;
	}

	friend istream& operator >> (istream&input, doctor&c)
	{
		input >> c.doctorName >> c.profession;
		return input;
	}

	vector<doctor> getDoctorRecords();
	
	vector<patient> findPatient(string name);

	void saveDoctorRecords(vector<doctor>doctors);

	void countFee(float fee);

};

class record :public doctor, public patient
{
public:

	void modifyPatientRecord(vector<patient>patients, unsigned int number);
	
	void modifyDoctorRecord(vector<doctor>doctors, unsigned int number);

	void addPatientRecord(vector<patient>&patients);
	 
	void addDoctorRecord(vector<doctor>&doctors);

	void deletePatientRecord(vector<patient>&patients, unsigned int number);

	void deleteDoctorRecord(vector<doctor>&doctors, unsigned int number);
	
	float countConFee(vector<doctor>&doctors);
	
	float countMedFee(vector<patient>&patients);

};

class face
{
public:

	void mainMenu();

	void patientMenu();

	void doctorMenu();

	void viewIncome();

};