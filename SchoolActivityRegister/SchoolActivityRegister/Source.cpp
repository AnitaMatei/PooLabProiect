#include <iostream>
#include "Person.hpp"
#include <vector>
#include "Room.hpp"
#include "Activity.hpp"
#include "Role.hpp"
#include "Person.hpp"
#include "PersonRepository.hpp"
#include "ActivityRepository.hpp"
#include "DidacticActivity.hpp"
#include "RoomRepository.hpp"
#include "StudentRegister.hpp"

using namespace std;


/*



		Person [vector<Role*> mRoles, ]


		Activity  [Room* mLocation, Person* ]

		Room [string nume]


		Role
	/			|				|				\
	StudentRole  GuestRole		TeacherRole		AdministrativeRole


*/




int main() {

	StudentRegister studentRegister;

	PersonRepository pr;

	pr.add(new Person({ new StudentRole(252, "CTI", 7) } ,{ 1 }, "Anita", "Matei", "chidosir94@gmail.com"));
	pr.add(new Person({ new StudentRole(252,"CTI",7) } ,{ 1 }, "Coman", "Valentin", "cv@cv.cv"));
	pr.add(new Person({ new TeacherRole({ "POO" }),new StudentRole(501, "Ceva", 3) }, { 2 }, "Stefan", "Rapeanu", "sr@sr.sr"));



	vector<Person*> students = pr.findStudentsInGroup(252);

	for (int i = 0; i < students.size(); i++) {
		studentRegister.addToRegister(students[i], { "Laborator POO 252" });
	}

	
	RoomRepository rr;

	rr.add(new Room("Laborator 331", 25,Room::LABORATORY_ROOM));
	rr.add(new Room("Amfiteatru Pompeiu", 50, Room::AMPHITHEATER_ROOM));
	rr.add(new Room("Amfiteatru Haret", 100, Room::AMPHITHEATER_ROOM));



	ActivityRepository ar;

	ar.add(new DidacticActivity(rr.findByName("Laborator 331"), pr.findByFullName("Stefan", "Rapeanu"), "Laborator POO 252"));
	ar.add(new DidacticActivity(rr.findByName("Amfiteatru Haret"), pr.findByFullName("Stefan", "Rapeanu"), "Curs POO CTI"));

	rr.findByName("Laborator 331")->setAvailability(false);
	dynamic_cast<DidacticActivity*>(ar.getActivityByDesc("Laborator POO 252"))->startActivity(pr.findStudentsInGroup(252), { true,false });
	dynamic_cast<DidacticActivity*>(ar.getActivityByDesc("Curs POO CTI"))->startActivity(pr.findStudentsInGroup(252), { true,true });
	dynamic_cast<DidacticActivity*>(ar.getActivityByDesc("Laborator POO 252"))->addGrade("Anita", "Matei", 6);



	dynamic_cast<DidacticActivity*>(ar.getActivityByDesc("Laborator POO 252"))->endActivity(studentRegister);
	dynamic_cast<DidacticActivity*>(ar.getActivityByDesc("Curs POO CTI"))->endActivity(studentRegister);

	cout << studentRegister;

	system("pause");
	return 0;
}