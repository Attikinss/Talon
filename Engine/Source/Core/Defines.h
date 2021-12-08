#pragma once
#define BIND_FUNCTION(func) [this](auto&&... args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); }
#define BIT(x) (1 << x)
#define RAW(x) (#x)