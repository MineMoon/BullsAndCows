#include <string>
#include <iostream>
#include <random>
#include <set>
enum game_state { // добавления перечисления для отслеживания состояния игры
	exit_game,
	repeat_game,
	continue_game,
};
bool check_input(std::string s) {
	std::set<char> numbers;  //для проверки уникальности будем использовать мн-ва
	for (int i = 0; i < s.length(); i++){    // проверяем каждый символ на правильность ввода (нужны только цифры!)
		if ((int)s[i] > 57 || (int)s[i] < 48) {  
			std::cout << "Вводимое значение должно содержать только цифры от 0 до 9\n"; 
			return 0;
		}
		else {
			numbers.insert(s[i]); // Сразу же добавляем их в мн-во 
		}
	}
	if (s[0] == '0') { // проверка на ноль в начале числа 
		std::cout << "Первой цифрой не может быть 0!\n";
		return 0;
	}
	if (s.size() != 4) {  //проверка на нужную длину (4)
		std::cout << "Число должно быть 4-х значным, то есть состоять из 4 цифр!\n";
		return 0;
	}
	if (numbers.size() != 4) { // если размер мн-ва не равняется 4, то есть число не содержит 4 уникальных числа, то возращаем false
		std::cout << "Все цифры в числе должны быть уникальны!\n";
		return 0;
	}
	return 1; //если все хорошо возращаем true
}
void rules() { // вывод правил
	std::cout << "Правила:\n";
	std::cout << "Компьютер или человек загадывает число из 4 уникальных цифр.\n";
	std::cout << "Ваша задача - угадать это число.\n";
	std::cout << "Введите ваше предположение, и вам сообщат количество быков и коров.\n";
	std::cout << "Быки - цифра на правильном месте, коровы - цифра есть, но на неправильном месте.\n";
	std::cout << std::endl;
}
void repeated_input(std::string &input) { // для проверок на правильность ввода
	std::cout << "Введите ваше предположение: ";
	std::cin >> input;
}

void countBullsAndCows(std::string secret, std::string guess, int& bulls, int& cows) {
	bulls = 0;
	cows = 0;
	for (int i = 0; i < secret.length(); i++) {
		if (guess[i] == secret[i]) { 
			// если цифры из загаданного числа и предпологаемого совпали по значению и по месту -> прибавляем быков
			bulls++;
		}
	}
	for (int i = 0; i < guess.length(); i++) {   // Сравниваем каждую цифру из предполагаемого числа  
		for (int j = 0; j < secret.length(); j++) { // с цифрами из загаданного
			if (i != j && guess[i] == secret[j]) { // если есть цифры, присутсвущие в обоих числах,
				cows++;                              // но стоящих не на своих местах (i!=j), прибавляем коров
			}
		}
	}
}
void play_again(std::string choice, game_state &game ) {  //Предложение сыграть еще раз
	std::cout << "Хотите сыграть еще раз или выйти?\n1. Еще раз\n2. Выйти\n";
	std::cin >> choice;
	while (choice.size() > 1 || ((int)choice[0] != 49 && (int)choice[0] != 50)) { 
		// проверка на правильность ввода с помощью размера введенной строки
		// и таблицы аски (ASCII)            
		system("cls");
		std::cout << "Вы можете выбрать только 1 или 2\n";
		std::cout << "Хотите сыграть еще раз или выйти?\n1. Еще раз\n2. Выйти\n";
		std::cin >> choice;
	}
	if (choice == "2") {
		std::cout << "Спасибо за игру!\n";
		game = exit_game; // назначаем статус выхода
	}
	else {
		game = repeat_game; //назначаем переигрывание игры
		system("cls");
	}
}

std::string Random() {
	srand(time(NULL));
	std::string digits = "";
	while (digits.size() != 4) { // Пока размер не достигнет нужного
		char temp = char(48 + rand() % 10);  //С помощью таблицы ASCII 
		//48 эл - 0 к нему прибавляем цифру от 1 до 9 и получаем значение temp
		if (temp == '0' && digits.size() == 0) {  
			// если первой цифрой в будующем числе получается 0 -> генерируем пока не получится другая цифра
			while (temp == '0') {
				temp = char(48 + rand() % 10);
			}
		}
		if (digits.find(temp) == std::string::npos) // если новая цифра не найдена в digit, то есть она уникальна, то добавляем её
			digits += temp;		
	}
	return digits;
}
