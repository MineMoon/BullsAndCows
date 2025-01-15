#include <string>
#include <iostream>
#include <random>
#include <set>
enum game_state { // ���������� ������������ ��� ������������ ��������� ����
	exit_game,
	repeat_game,
	continue_game,
};
bool check_input(std::string s) {
	std::set<char> numbers;  //��� �������� ������������ ����� ������������ ��-��
	for (int i = 0; i < s.length(); i++){    // ��������� ������ ������ �� ������������ ����� (����� ������ �����!)
		if ((int)s[i] > 57 || (int)s[i] < 48) {  
			std::cout << "�������� �������� ������ ��������� ������ ����� �� 0 �� 9\n"; 
			return 0;
		}
		else {
			numbers.insert(s[i]); // ����� �� ��������� �� � ��-�� 
		}
	}
	if (s[0] == '0') { // �������� �� ���� � ������ ����� 
		std::cout << "������ ������ �� ����� ���� 0!\n";
		return 0;
	}
	if (s.size() != 4) {  //�������� �� ������ ����� (4)
		std::cout << "����� ������ ���� 4-� �������, �� ���� �������� �� 4 ����!\n";
		return 0;
	}
	if (numbers.size() != 4) { // ���� ������ ��-�� �� ��������� 4, �� ���� ����� �� �������� 4 ���������� �����, �� ��������� false
		std::cout << "��� ����� � ����� ������ ���� ���������!\n";
		return 0;
	}
	return 1; //���� ��� ������ ��������� true
}
void rules() { // ����� ������
	std::cout << "�������:\n";
	std::cout << "��������� ��� ������� ���������� ����� �� 4 ���������� ����.\n";
	std::cout << "���� ������ - ������� ��� �����.\n";
	std::cout << "������� ���� �������������, � ��� ������� ���������� ����� � �����.\n";
	std::cout << "���� - ����� �� ���������� �����, ������ - ����� ����, �� �� ������������ �����.\n";
	std::cout << std::endl;
}
void repeated_input(std::string &input) { // ��� �������� �� ������������ �����
	std::cout << "������� ���� �������������: ";
	std::cin >> input;
}

void countBullsAndCows(std::string secret, std::string guess, int& bulls, int& cows) {
	bulls = 0;
	cows = 0;
	for (int i = 0; i < secret.length(); i++) {
		if (guess[i] == secret[i]) { 
			// ���� ����� �� ����������� ����� � ��������������� ������� �� �������� � �� ����� -> ���������� �����
			bulls++;
		}
	}
	for (int i = 0; i < guess.length(); i++) {   // ���������� ������ ����� �� ��������������� �����  
		for (int j = 0; j < secret.length(); j++) { // � ������� �� �����������
			if (i != j && guess[i] == secret[j]) { // ���� ���� �����, ������������ � ����� ������,
				cows++;                              // �� ������� �� �� ����� ������ (i!=j), ���������� �����
			}
		}
	}
}
void play_again(std::string choice, game_state &game ) {  //����������� ������� ��� ���
	std::cout << "������ ������� ��� ��� ��� �����?\n1. ��� ���\n2. �����\n";
	std::cin >> choice;
	while (choice.size() > 1 || ((int)choice[0] != 49 && (int)choice[0] != 50)) { 
		// �������� �� ������������ ����� � ������� ������� ��������� ������
		// � ������� ���� (ASCII)            
		system("cls");
		std::cout << "�� ������ ������� ������ 1 ��� 2\n";
		std::cout << "������ ������� ��� ��� ��� �����?\n1. ��� ���\n2. �����\n";
		std::cin >> choice;
	}
	if (choice == "2") {
		std::cout << "������� �� ����!\n";
		game = exit_game; // ��������� ������ ������
	}
	else {
		game = repeat_game; //��������� ������������� ����
		system("cls");
	}
}

std::string Random() {
	srand(time(NULL));
	std::string digits = "";
	while (digits.size() != 4) { // ���� ������ �� ��������� �������
		char temp = char(48 + rand() % 10);  //� ������� ������� ASCII 
		//48 �� - 0 � ���� ���������� ����� �� 1 �� 9 � �������� �������� temp
		if (temp == '0' && digits.size() == 0) {  
			// ���� ������ ������ � �������� ����� ���������� 0 -> ���������� ���� �� ��������� ������ �����
			while (temp == '0') {
				temp = char(48 + rand() % 10);
			}
		}
		if (digits.find(temp) == std::string::npos) // ���� ����� ����� �� ������� � digit, �� ���� ��� ���������, �� ��������� �
			digits += temp;		
	}
	return digits;
}
