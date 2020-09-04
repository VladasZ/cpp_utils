//
//  ExceptionCatch.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 6/26/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#ifdef __cpp_exceptions

#include <string>

[[maybe_unused]]
static inline std::string what() {
    auto eptr = std::current_exception();
    if (!eptr) Fatal("There is no exception.");
    try   { rethrow_exception(eptr); }
    catch (const std::exception& e) { return e.what(); }
    catch (const std::string&    e) { return e; }
    catch (const char*           e) { return e; }
    catch (...) { return "Unknown exception."; }
}

#else

static std::string what() {
    return "__cpp_exceptions disabled";
}

#endif
