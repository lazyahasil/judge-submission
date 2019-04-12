#include <array>
#include <cstdio>

using namespace std;

enum CubeColor : char {
    WHITE = 'w',
    YELLOW = 'y',
    RED = 'r',
    ORANGE = 'o',
    GREEN = 'g',
    BLUE = 'b',
};

enum CubeSideIndex : int {
    UP = 0,
    DOWN = 1,
    FRONT = 2,
    BACK = 3,
    LEFT = 4,
    RIGHT = 5,
};

struct CubeRot {
    const CubeSideIndex side_index;
    const bool horizontal;
    const size_t line_index;
    const bool line_forward;

    CubeRot(CubeSideIndex side_index, bool horizontal, size_t line_index, bool line_forward)
        : side_index(side_index),
          horizontal(horizontal),
          line_index(line_index),
          line_forward(line_forward) {}
};

const array<const array<const CubeRot, 4>, 6> CUBE_SIDE_DEFS_ARR{{
    // UP
    {
        CubeRot(BACK, true, 0, false),
        CubeRot(RIGHT, true, 0, false),
        CubeRot(FRONT, true, 0, false),
        CubeRot(LEFT, true, 0, false),
    },
    // DOWN
    {
        CubeRot(FRONT, true, 2, true),
        CubeRot(RIGHT, true, 2, true),
        CubeRot(BACK, true, 2, true),
        CubeRot(LEFT, true, 2, true),
    },
    // FRONT
    {
        CubeRot(UP, true, 2, true),
        CubeRot(RIGHT, false, 0, true),
        CubeRot(DOWN, true, 0, false),
        CubeRot(LEFT, false, 2, false),
    },
    // BACK
    {
        CubeRot(UP, true, 0, false),
        CubeRot(LEFT, false, 0, true),
        CubeRot(DOWN, true, 2, true),
        CubeRot(RIGHT, false, 2, false),
    },
    // LEFT
    {
        CubeRot(UP, false, 0, true),
        CubeRot(FRONT, false, 0, true),
        CubeRot(DOWN, false, 0, true),
        CubeRot(BACK, false, 2, false),
    },
    // RIGHT
    {
        CubeRot(UP, false, 2, false),
        CubeRot(BACK, false, 0, true),
        CubeRot(DOWN, false, 2, false),
        CubeRot(FRONT, false, 2, false),
    },
}};

array<array<array<CubeColor, 3>, 3>, 6> cube;

void reset_cube() {
    for (auto i = 0; i < 6; i++) {
        auto& side = cube[i];
        const CubeColor color = side[1][1];
        side[0][0] = color;
        side[0][1] = color;
        side[0][2] = color;
        side[1][2] = color;
        side[1][0] = color;
        side[2][0] = color;
        side[2][1] = color;
        side[2][2] = color;
    }
}

void rotate_one_side_only(CubeSideIndex side_index, bool clockwise) {
    auto& side = cube[side_index];
    CubeColor orig_0_0 = side[0][0];
    CubeColor orig_0_1 = side[0][1];
    if (clockwise) {
        side[0][0] = side[2][0];
        side[2][0] = side[2][2];
        side[2][2] = side[0][2];
        side[0][2] = orig_0_0;
        side[0][1] = side[1][0];
        side[1][0] = side[2][1];
        side[2][1] = side[1][2];
        side[1][2] = orig_0_1;
    } else {
        side[0][0] = side[0][2];
        side[0][2] = side[2][2];
        side[2][2] = side[2][0];
        side[2][0] = orig_0_0;
        side[0][1] = side[1][2];
        side[1][2] = side[2][1];
        side[2][1] = side[1][0];
        side[1][0] = orig_0_1;
    }
}

void copy_cube_line(const CubeRot& cube_rot, array<CubeColor, 3>& buf) {
    auto& side = cube[cube_rot.side_index];
    auto line_index = cube_rot.line_index;
    if (cube_rot.horizontal) {
        if (cube_rot.line_forward) {
            buf[0] = side[line_index][0];
            buf[1] = side[line_index][1];
            buf[2] = side[line_index][2];
        } else {
            buf[0] = side[line_index][2];
            buf[1] = side[line_index][1];
            buf[2] = side[line_index][0];
        }
    } else {
        if (cube_rot.line_forward) {
            buf[0] = side[0][line_index];
            buf[1] = side[1][line_index];
            buf[2] = side[2][line_index];
        } else {
            buf[0] = side[2][line_index];
            buf[1] = side[1][line_index];
            buf[2] = side[0][line_index];
        }
    }
}

void put_cube_line(const CubeRot& cube_rot, const array<CubeColor, 3>& buf) {
    auto& side = cube[cube_rot.side_index];
    auto line_index = cube_rot.line_index;
    if (cube_rot.horizontal) {
        if (cube_rot.line_forward) {
            side[line_index][0] = buf[0];
            side[line_index][1] = buf[1];
            side[line_index][2] = buf[2];
        } else {
            side[line_index][0] = buf[2];
            side[line_index][1] = buf[1];
            side[line_index][2] = buf[0];
        }
    } else {
        if (cube_rot.line_forward) {
            side[0][line_index] = buf[0];
            side[1][line_index] = buf[1];
            side[2][line_index] = buf[2];
        } else {
            side[0][line_index] = buf[2];
            side[1][line_index] = buf[1];
            side[2][line_index] = buf[0];
        }
    }
}

void rotate_near_sides(CubeSideIndex side_index, bool clockwise) {
    static array<CubeColor, 3> first_buffer;
    static array<CubeColor, 3> buffer;
    const auto& side_defs = CUBE_SIDE_DEFS_ARR[side_index];
    if (clockwise) {
        copy_cube_line(side_defs[3], first_buffer);
        for (size_t i = 3; i > 0; i--) {
            copy_cube_line(side_defs[i - 1], buffer);
            put_cube_line(side_defs[i], buffer);
        }
        put_cube_line(side_defs[0], first_buffer);
    } else {
        copy_cube_line(side_defs[0], first_buffer);
        for (size_t i = 1; i < 4; i++) {
            copy_cube_line(side_defs[i], buffer);
            put_cube_line(side_defs[i - 1], buffer);
        }
        put_cube_line(side_defs[3], first_buffer);
    }
}

int main() {
    cube[0][1][1] = WHITE;
    cube[1][1][1] = YELLOW;
    cube[2][1][1] = RED;
    cube[3][1][1] = ORANGE;
    cube[4][1][1] = GREEN;
    cube[5][1][1] = BLUE;

    int m;
    scanf("%d", &m);

    for (auto i = 0; i < m; i++) {
        int n;
        scanf("%d", &n);

        reset_cube();

        for (auto j = 0; j < n; j++) {
            char rotation_input[4];
            scanf("%s", rotation_input);
            CubeSideIndex side_index = UP;
            bool clockwise = rotation_input[1] == '+';
            switch (rotation_input[0]) {
            case 'U':
                side_index = static_cast<CubeSideIndex>(0);
                break;
            case 'D':
                side_index = static_cast<CubeSideIndex>(1);
                break;
            case 'F':
                side_index = static_cast<CubeSideIndex>(2);
                break;
            case 'B':
                side_index = static_cast<CubeSideIndex>(3);
                break;
            case 'L':
                side_index = static_cast<CubeSideIndex>(4);
                break;
            case 'R':
                side_index = static_cast<CubeSideIndex>(5);
            }
            rotate_one_side_only(side_index, clockwise);
            rotate_near_sides(side_index, clockwise);
        }

        for (size_t j = 0; j < 3UL; j++) {
            for (size_t k = 0; k < 3UL; k++) {
                printf("%c", (char)cube[0][j][k]);
            }
            printf("\n");
        }
    }

    return 0;
}
