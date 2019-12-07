#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <sstream>

std::vector<std::string> colors = { "RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "INDIGO", "PURPLE", "BLACK", "RAINBOW", "RANDOM"};
std::vector<std::string> hexColors = {"e74c3c", "e67e22", "f1c40f", "2ecc71", "3498db", "1e45a8", "8e44ad", "000000"};

void ui() {
	system("cls");
	std::cout << "Terraria Color Message Generator \n";
	std::cout << "Stable Release 1.0\n\n";
	std::cout << "Type 'commands' to see all commands\nType 'information' for all useful information.\n";
	std::cout << "Type 'instruction' to know how to use this program.\n\n";
}

void information() {
	system("cls");
	std::cout << "Terraria Color Message Generator Information \n\n";
	std::cout << "Version: 1.0\n";
	std::cout << "Made by Alien#0769(discord), @aliendeveloper(telegram)\n";
	std::cout << "Github: (type github to copy link/github_ to open in the browser)\n";
	std::cout << "If you notice any bugs or you have suggestions, please let me know at my github.\nBefore using this program, make sure you read everything.\n";
	std::cout << "Works only with english letters.\n\n";
	std::cout << "Type any letter to go back.\n";
}

void commands() {
	system("cls");
	std::cout << "Terraria Color Message Generator Commands \n\n";
	std::cout << "commands - Lists all commands\n";
	std::cout << "information - Outputs information about the program and it's creator\n";
	std::cout << "colors - Shows all the usable single colors\n";
	std::cout << "new - Resets everything and makes a new line\n";
	std::cout << "copy - Copies all the text and respective colors to clipboard\n";
	std::cout << "instruction - Tells you how to use this program\n";
	std::cout << "github_ - Opens program's github repository in the default browser.\n";
	std::cout << "github - Copies program's github repository to clipboard\n\n";
	std::cout << "Type any letter to go back.\n";
}

void colors_() {
	system("cls");
	std::cout << "Terraria Color Message Generator Colors\n\n";
	for (int i = 0; i < colors.size(); i++) {
		if (colors.at(i) == "RAINBOW") {
			std::cout << colors.at(i) << "\t\t\t" << "Rainbow every word\n";
		}
		else if (colors.at(i) == "RANDOM") {
			std::cout << colors.at(i) << "\t\t\t" << "Random every word\n";
		}
		else {
			std::cout << colors.at(i) << "\t\t\t" << "#" << hexColors.at(i) << "\n";
		}
	}
	std::cout << "\nType any letter to go back.\n";
}

void instruction() {
	system("cls");
	std::cout << "Terraria Color Message Generator Instruction\n\n";
	std::cout << "Type any color you want, type _, and the main message you want to use, \n";
	std::cout << "then, you can either press enter and continue doing the same, or type copy to\n";
	std::cout << "get the text to clipboard and get it ready to use in Terraria.\n";
	std::cout << "You can know more about commands if you type 'commands'. \n\n";
	std::cout << "Type any letter to go back.\n";
}

	
void toClipboard(const std::string& s) {
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size());
	if(!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

std::string concatVector(std::vector<std::string> vec) {
	std::string retMessage;
	for (int i = 0; i < vec.size(); i++) {
		retMessage += (vec.at(i) + " ");
	}
	return retMessage;
}

	
int checkColor(std::string color) {
	for (const auto& c : colors) {
		if (c == color) {
			if (c == "RAINBOW") {
				return 3;
			}
			else if (c == "RANDOM") {
				return 4;
			}
			else {
				return 1;
			}
		}
	}
	return 0;
}

std::vector<std::string> rainbowText(std::string msg, bool word) {
		std::vector<std::string> rainbowWords;
		std::stringstream sstr(msg);
		for (std::string curWord; sstr >> curWord;)
			rainbowWords.push_back(curWord);
		return rainbowWords;
}


int main() {
	SetConsoleTitle("Spectrum");
	ui();

	std::vector<std::string> message;
	while (true) {
		Sleep(10);
		std::string input;
		std::getline(std::cin, input);
		if (input == "new") {
			message.clear();
			input = "";
			ui();
		}
		else if (input == "copy") {
			std::string conVec = concatVector(message);
			toClipboard(conVec);
			message.clear();
			input = "";
			ui();
		}
		else if (input == "github") {
			toClipboard("https://github.com/AlienTheBetrayer/TerrariaColorMessageGenerator");
			ui();
		}
		else if (input == "github_") {
			system("start https://github.com/AlienTheBetrayer/TerrariaColorMessageGenerator");
			ui();
		}
		else if(input == "colors"){
			colors_();
		}
		else if(input == "information") {
			information();
		}
		else if (input == "commands") {
			commands();
		}
		else if (input == "instruction") {
			instruction();
		}
		else {
			std::string tMessage;
			size_t _index = input.find("_");
			std::string color = input.substr(0, _index); //color
			std::string _m = input.substr(_index + 1, (input.length() - (_index + 1)));//message
			int check = checkColor(color);
			if (check == 1) {
				for (int i = 0; i < colors.size(); i++) {
					if (color == colors.at(i)) {
						std::string tColor = hexColors.at(i);
						std::string tMsg = "[c/" + tColor + ":" + _m + "]";
						message.push_back(tMsg);
					}
				}
			}
			else if (check == 3) { // rainbow_word
				int colorIndex = 0;
				std::vector<std::string> rainbow = rainbowText(_m, true);
				for (int i = 0; i < rainbow.size(); i++) {
					if (colorIndex != (hexColors.size() - 1)) {
						std::string _m2 = "[c/" + hexColors.at(colorIndex) + ":" + rainbow.at(i) + "]";
						message.push_back(_m2);
						colorIndex++;
					}
					else {
						colorIndex = 0;
						std::string _m2 = "[c/" + hexColors.at(colorIndex) + ":" + rainbow.at(i) + "]";
						message.push_back(_m2);
						colorIndex = 1;
					}
				}	
			}
			else if (check == 4) { // random-word
				std::vector<std::string> rainbow = rainbowText(_m, true);
				for (int i = 0; i < rainbow.size(); i++) {
					int randIndex = rand() % (hexColors.size() - 1);
					std::string _m2 = "[c/" + hexColors.at(randIndex) + ":" + rainbow.at(i) + "]";
					message.push_back(_m2);
				}
			}
			else {
				ui();
			}
		}

		
	}
	


	std::cin.get();
}