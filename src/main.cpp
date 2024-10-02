#include "app-window.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>

slint::SharedString get_new_password();

int main(int argc, char **argv)
{
    auto ui = AppWindow::create();

    ui->on_request_generate_password([&]{
        ui->set_password(get_new_password());
    });

    ui->run();
    return 0;
}

slint::SharedString get_new_password() {
    slint::SharedString result {"Haslo"};
    return  result;
}
