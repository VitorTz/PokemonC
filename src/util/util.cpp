#include "util.h"


std::size_t pk::hash_str(const char* s) {
    std::size_t hash = 5381;
    int c;
    while ((c = *s++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

Vector2 pk::get_direction(
    const int left,
    const int right,
    const int up,
    const int down,
    pk::move_state_t& move_state
) {
    Vector2 d{0.0f, 0.0f};
    move_state.last_direction = move_state.direction;
    move_state.last_is_idle = move_state.is_idle;
    move_state.is_idle = true;
    if (IsKeyDown(up)) {
        d.y = -1.0f;
        move_state.direction = 'u';
        move_state.is_idle = false;
    }
    else if (IsKeyDown(down)) {
        d.y = 1.0f;
        move_state.direction = 'd';
        move_state.is_idle = false;
    }
    if (IsKeyDown(left)) {
        d.x = -1.0f;
        move_state.direction = 'l';
        move_state.is_idle = false;
    }
    else if (IsKeyDown(right)) {
        d.x = 1.0f;
        move_state.direction = 'r';
        move_state.is_idle = false;
    }
    d = Vector2Normalize(d);
    return d;
}

