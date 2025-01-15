#include <string>
enum game_state {exit_game, repeat_game,continue_game};
void rules();
bool check_input(std::string s);
void repeated_input(std::string& input);
void play_again(std::string choice, game_state& game);
void countBullsAndCows(std::string secret, std::string guess, int& bulls, int& cows);
std::string Random();

