#include "Route.h"
#include "HttpMethods.h"

Route::Route(const std::string& uri, const std::string& method, const std::function<std::string(HttpRequest& request)>& handler)
{
    this->uri = uri;
    this->handler = handler;
    this->method = extract_method(method.c_str());
}

std::string Route::get_uri() const
{
    return this->uri;
}

HttpMethods Route::get_method() const
{
    return this->method;
}

Route::~Route()
{
    return;
}
