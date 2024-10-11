#include "app-window.h"
#include <cstdio>
#include <ostream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "jsonwords.h"

// slint::SharedString get_new_password(int words_num);
// std::string get_word_from_json(int words_num);

int main(int argc, char **argv)
{
    auto ui = AppWindow::create();

    ui->on_request_generate_password([&]{
        ui->set_password(JsonHandler::get_new_password(ui->get_words_num(),ui->get_selected_wordset()));
    });

    ui->on_request_change_words_num([&] {
         ui->get_words_num();
    });

    ui->run();
    return 0;
}

