#include "Route.h"
#include "HttpMethods.h"

Route::Route(const std::string& uri, const std::string& method, const std::string& file_path)
{
    this->uri = uri;
    this->file_path = file_path;
    this->method = extract_method(method.c_str());
}

std::string Route::get_uri() const
{
    return this->uri;
}

std::string Route::get_file_path() const
{
    return this->file_path;
}

HttpMethods Route::get_method() const
{
    return this->method;
}

Route::~Route()
{
    return;
}
