#include "app-window.h"
#include "jsonwords.h"


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

