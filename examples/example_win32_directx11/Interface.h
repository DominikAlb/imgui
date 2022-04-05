//Glowny interfejs uzytkownika
//Po wlaczeniu przycisku Wyjdz proces konczy dzialanie
//Wlaczenie przycisku start uruchamia maszyne losujaca
//Przycisk restart powoduje powrot do poczatkowych ustawien co pozwala ponownie uruchomic gre
//Gracz musi wybrac 6 pilek, jesli pilki beda takie same jak te wylosowane, gracz wygrywa
//Interface odswieza ekran i wyswietla wszystkie obiekty
//Podczas gry uzytkownik moze zmieniac szybkosc pilek w maszynie

#pragma once
#include <d3d11.h>
#include <string>
#include <set>
#include <examples/example_win32_directx11/Logic.h>
#include <examples/example_win32_directx11/Menu.h>

class Interface {
    
public:
    bool init(Menu& menu) {
        bool done = false;
        if (GetAsyncKeyState(VK_DELETE) & 1) {
            menu.setLottoInterface(!*menu.getLottoInterface());
        }

        if (*menu.getLottoInterface()) {

            ImU32 col = IM_COL32(255, 0, 0, 255);
            ImVec2 engineVec(300, 500);
            ImU32 engineCol = IM_COL32(122, 0, 0, 122);
            Engine<float> engine(100, 530, engineVec, engineCol, menu.getForcePtr(), 400);

            Logic<float> bl;
            ImVec2 iv(100, 100);

            Wall<float> w(100.0f, 100.0f, 400.0f, iv, col);
            ImU32 collectorCol = IM_COL32(122, 122, 0, 122);
            ImVec2 iv2(250, 115.0f);
            Collector<float> collector(250.0f, 115.0f, 100, iv2, collectorCol);
            
            ImGui::Begin("lotto");
            ImGui::Checkbox("Wyswietl gre", menu.getGameWindow());
            ImGui::InputFloat("predkosc pilek", menu.getForce());
            ImGui::InputInt("1 losowana liczba", &(*menu.getInputNumbersPtr().get())[0]);
            ImGui::InputInt("2 losowana liczba", &(*menu.getInputNumbersPtr().get())[1]);
            ImGui::InputInt("3 losowana liczba", &(*menu.getInputNumbersPtr().get())[2]);
            ImGui::InputInt("4 losowana liczba", &(*menu.getInputNumbersPtr().get())[3]);
            ImGui::InputInt("5 losowana liczba", &(*menu.getInputNumbersPtr().get())[4]);
            ImGui::InputInt("6 losowana liczba", &(*menu.getInputNumbersPtr().get())[5]);


            if (ImGui::Button("Graj!")) {
                
                menu.setEndGame(true);
                for (int i = 0; i < (*menu.getInputNumbersPtr().get()).size(); i++) {
                    if (menu.getInputNumber(i) <= 0 || menu.getInputNumber(i) >= 50) {
                        menu.setEndGame(false);
                        break;
                    }
                }
                if (*menu.getEndGame()) {
                    menu.setRunGame(true);
                    menu.setWin(false);
                }
            }
            if (!*menu.getEndGame()) {
                std::set<int> set;
                for (int i = 0; i < (*menu.getInputNumbersPtr().get()).size(); i++) {
                    set.insert(menu.getInputNumber(i));
                }
                if (set.size() != (*menu.getInputNumbersPtr().get()).size()) {
                    ImGui::Text("Liczby nie moga sie powtarzac!");
                }
                ImGui::Text("Losowane liczby nie moga byc mniejsze od 1 i wieksze od 49!");
            }

            if (*menu.getGameWindow()) {
                auto draw = ImGui::GetBackgroundDrawList();
                float size = 10;
                bl.init(draw, &size);
                w.init(draw);
                engine.init(draw);
                collector.init(draw);
                if (*menu.getRunGame()) {

                    bl.moveWithCollision();
                    if (bl.wonNumbers.size() == (*menu.getInputNumbersPtr().get()).size()) {
                        menu.setWin(true);
                        menu.setRunGame(!*menu.getRunGame());
                    }
                }
                if (*menu.getWin()) {
                    std::string str = "Wylosowane liczby: ";
                    for (auto i = bl.wonNumbers.begin(); i != bl.wonNumbers.end(); i++) {
                        str = str + std::to_string(*i) + ", ";
                    }
                    ImGui::Text(str.c_str());
                    std::string str2 = "Wybrane liczby: ";
                    for (int i = 0; i < (*menu.getInputNumbersPtr().get()).size(); i++) {
                        str2 = str2 + std::to_string(menu.getInputNumber(i)) + ", ";
                    }
                    ImGui::Text(str2.c_str());
                    std::sort(bl.wonNumbers.begin(), bl.wonNumbers.end());
                    std::vector<int> input = (*menu.getInputNumbersPtr().get());
                    std::sort(input.begin(), input.end());
                    if (bl.wonNumbers.size() != 0) {
                        bool checkNumbers = true;
                        for (int i = 0; i < input.size(); i++) {
                            if (input.at(i) != bl.wonNumbers.at(i)) {
                                checkNumbers = false;
                                break;
                            }
                        }
                        if (checkNumbers) {
                            ImGui::Text("Wygrales!");
                        }
                        else {
                            ImGui::Text("Przegrales!");
                        }
                    }
                }

            }
            if (ImGui::Button("Restart")) {
                Logic<float>::restart();
            }
            if (ImGui::Button("Wyjdz")) {
                done = true;
            }
            ImGui::End();
        }

        
        return done;
    }
};
