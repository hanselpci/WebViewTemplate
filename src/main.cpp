#include "webview/webview.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string getExecutableDirectory() {
    std::string path;
    char buffer[MAX_PATH];

    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    path = std::string(buffer);
    // Remove the filename to get the directory
    size_t pos = path.find_last_of("\\/");
    if (pos != std::string::npos) {
        path = path.substr(0, pos);
    }
    return path;
}

std::string handleFormSubmit(const std::string &data)
{
    std::cout << "Form Data: " << data << std::endl;
     json jreq = json::parse(data);

    // Handle JSON
     json jdata = {
        {"status", "success"},
        {"message", "Success: " + jreq.dump()}
    };

    return jdata.dump();
}

int main()
{
    try
    {
        webview::webview w(true, nullptr);
        w.set_title("WebView Template");
        w.set_size(720, 480, WEBVIEW_HINT_NONE);

        w.bind("handleFormSubmit", [](const std::string &req) -> std::string
               { return handleFormSubmit(req); });

        std::string url = getExecutableDirectory();
        url.append("/web/index.html");
        w.navigate(url);
        w.run();
    }
    catch (const webview::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
