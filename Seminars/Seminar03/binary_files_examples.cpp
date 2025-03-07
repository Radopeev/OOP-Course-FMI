#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

namespace Constants {
	constexpr char FILE_NAME[] = "test_object.bin";
	constexpr int NAME_SIZE = 25;
}

struct Student {
	char *name;
	int fn;
	int age;
};


int main() {
	{
		Student st;

		st.name = new char[4];
		strcpy(st.name, "Ime");

		st.fn = 1234;
		st.age = 33;

		ofstream file(Constants::FILE_NAME, ios::binary);

		if (!file.is_open()) {
			cout << "Did not open." << endl;
			return 1;
		}

		/*file.write((const char*)&st, sizeof(st));*/

		size_t name_len = strlen(st.name);

		file.write((const char*)&name_len, sizeof(name_len));
		file.write(st.name, name_len);
		file.write((const char*)&st.fn, sizeof(st.fn));
		file.write((const char*)&st.age, sizeof(st.age));

		file.close();
	}

	{
		Student st;

		ifstream file(Constants::FILE_NAME, ios::binary);

		if (!file.is_open()) {
			cout << "Did not open" << endl;
			return 1;
		}

		//file.read((char*)&st, sizeof(st));

		size_t name_len;

		file.read((char*)&name_len, sizeof(name_len));

		st.name = new char[name_len + 1];
		file.read(st.name, name_len);
		st.name[name_len] = '\0';

		file.read((char*)&st.fn, sizeof(st.fn));
		file.read((char*)&st.age, sizeof(st.age));

		file.close();

		cout << st.name << " " << st.fn << " " << st.age << endl;
	}

	{
		struct Student {
			char name[Constants::NAME_SIZE];
			int fn;
			int age;
		};

		Student* arr = new Student[4];

		// initialize...

		ofstream file(Constants::FILE_NAME, ios::binary);

		if (!file.is_open()) {
			cout << "not open" << endl;
			delete[] arr; // delete !
			return 1;
		}

		file.write((const char*)arr, 4 * sizeof(Student));

		file.close();
	}

	return 0;
}
