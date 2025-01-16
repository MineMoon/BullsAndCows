
#include <iostream>
#include <random>
#include <time.h>
#include <set>
#include<windows.h>
#include"add.h";
int main() {
	setlocale(LC_ALL, "Russian");  //локализация 
	game_state game; //Назначаем переменную которая будет запоминать состояние игры.
	std::cout << "Добро пожаловать в игру 'Быки и коровы'!" << std::endl;
	rules(); //вывод правил
	do { //цикл, определяющий начать заново игру, или закончить.
		game = continue_game; // если мы оказались в этой строчке, значит игра в процессе
		std::cout << "Выберите противника:\n1. Компьютер\n2. Второй человек\n";
		std::string choice; // Ввод от пользователя
		std::string number; // Загадываемое число
		std::cin >> choice;
		while (choice.size()>1 || ((int)choice[0] != 49 && (int)choice[0] != 50)) { // Проверка на праввильнось ввода
			std::cout << "Неверно выбран противник, попробуйте еще раз: ";
			std::cin >> choice;
		}
		switch (stoi(choice)) {
		case 1:
			number = Random(); //Генерируем число
			break;
		case 2:
			system("cls");
			do {
				std::cout << "Загадайте число из 4 уникальных цифр: ";
				std::cin >> number; // Второй игрок/ противник задает число
				system("cls"); // Чтобы игрок, который угадывает, не увидел ответа
			} while (check_input(number) != 1);
			// check_input - булевая функция. Если с вводом проблемы, 
			//   то она возращает 0, и цикл повторяется
			break;
		}
		system("cls");
		std::cout << "Число загадано!";

		std::string guess;
		int bulls = 0, cows = 0;
		int attempts = 0; // счетчик
		std::cout << std::endl;
		do { // Цикл для отгадывания числа
			std::cout << "Введите ваше предположение: ";
			std::cin >> guess; // Предположение от пользователя
			++attempts;// Считаем попытки
			system("cls");
			while (check_input(guess) != 1) {
				repeated_input(guess);
				system("cls");
				attempts++; // Считаем попытки даже если игрок произвел неправильный ввод
			}
			countBullsAndCows(number, guess, bulls, cows); //Функция подсчета коров и быков
			std::cout << "[" << guess << "] Быки: " << bulls << ", Коровы: " << cows << std::endl;
			if (attempts % 7 == 0) { //С интервалом в 10 попыток игра предлагает сдаться либо продолжить
				std::cout << "Хотите сдаться и узнать ответ?)\n1. Да\n2. Нет\n3. Правила игры\n";
				std::cin >> choice;
				while (choice.size() > 1 || ((int)choice[0] != 49 && (int)choice[0] != 50 && (int)choice[0]!=51)) { //Проверка ввода
					system("cls");
					std::cout << "Вы можете выбрать только 1, 2 или 3\n";
					std::cout << "Хотите сдаться и узнать ответ?)\n1. Да\n2. Нет\n3. Правила игры\n";
					std::cin >> choice;
				}
				switch (stoi(choice)) { //Распределяем выбор с помощью switchы
				case 1: // Показывает ответ, предлагает поиграть еще раз
					std::cout << "Загаданное число: " << number << std::endl;
					std::cout << "Количество попыток: " << attempts << std::endl;
					play_again(choice, game);
					break;
				case 2: //продолжает игру
					system("cls");
					std::cout << "Ну ладно).\n";
					std::cout << "[" << guess << "] Быки: " << bulls << ", Коровы: " << cows << std::endl;
					break;
				case 3: // показывает правила
					rules();
					std::cout << "Хотите сдаться или продолжить?)\n1. Сдаться\n2. Продолжить\n";
					std::cin >> choice;
					while (choice.size() > 1 || ((int)choice[0] != 49 && (int)choice[0] != 50)) { //Проверка ввода
						system("cls");
						std::cout << "Вы можете выбрать только 1, 2\n";
						std::cout << "Хотите сдаться или продолжить?)\n1. Сдаться\n2. Продолжить\n";
						std::cin >> choice;
					}
					switch (stoi(choice)) {
					case 1:
						std::cout << "Загаданное число: " << number << std::endl;
						std::cout << "Количество попыток: " << attempts << std::endl;
						play_again(choice, game);
						break;
					case 2:
						std::cout << "Ладно)\n";
						break;
					}
					break;
				}
			}
			if (bulls == 4) { // если все числа стоят на своих местах - победа
				std::cout << "Поздравляем! вы угадали число " << number << " за " << attempts << " попыток!" << std::endl;
				play_again(choice, game);
			}
		} while (bulls != 4 && game==continue_game); // Пока игрок не выийграет (4 быка), пока игрок не предпочтет выйти 
											//или когда сдастся и захочет повторить(для этого добавили enum game_state и в нём repeat_game)
	} while (game!=exit_game); //Пока игра не будет иметь состояние game_exit, то есть игрок захотел выйти.
}	