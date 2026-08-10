#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
    constexpr float playerHorSpeed{ 350.0f };
    constexpr int blockWidth{80};
    constexpr int blockHeight{20};
    constexpr int numBlocks{32};



    constexpr float blockHorizontalOffset{ 82.5f };
    constexpr float blockVerticalOffset{25.0f};

    //declare fixed constants
    constexpr double FIXED_TIMESTEP = 1.0 / 60.0; // 0.016666 seconds
    constexpr double MAX_FRAME_TIME = 0.25;

}

#endif 