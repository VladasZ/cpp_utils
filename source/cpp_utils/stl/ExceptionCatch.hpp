//
//  ExceptionCatch.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 6/26/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <string>

[[maybe_unused]]
static std::string what(const std::exception_ptr& eptr = std::current_exception()) {
    if (!eptr) { throw std::bad_exception(); }
    try   { rethrow_exception(eptr); }
    catch (const std::exception& e) { return e.what(); }
    catch (const std::string&    e) { return e; }
    catch (const char*           e) { return e; }
    catch (...) { return "Unknown exception."; }
}
