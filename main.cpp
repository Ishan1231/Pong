#include "raylib.h"

void playerInput(Rectangle player1, Rectangle player2, int playerSpeed)
{
}

int main()
{
    // Window dimensions
    int width{600};
    int height{400};

    // Player 1 variables
    Rectangle player1{50, (float)(height / 2) - ((height / 4) / 2), 15, (float)height / 4};

    // Player 2 variables
    Rectangle player2{(float)(width - 50 - (width / 40)), (float)(height / 2) - ((height / 4) / 2), 15, (float)height / 4};

    // Win Checkers
    Rectangle leftRect{0, 0, 50, (float)height};
    Rectangle rightRect{(float)width - 50, 0, 50, (float)height};

    InitWindow(width, height, "Pong!");

    // Ball variables
    int radius{7};
    Vector2 ballPosition = {(float)width / 2, (float)height / 2};
    Vector2 ballSpeed = {5, 5};

    // Player speed
    int playerSpeed{10};

    // Player score
    int player1Score{};
    int player2Score{};

    bool isVisible{};
    bool isPlaying{};

    bool player1Win{};
    bool player2Win{};
    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (!isPlaying)
        {
            DrawText("Press Enter to start", 0, 0, 50, RAYWHITE);
            if (IsKeyPressed(KEY_ENTER))
            {
                isPlaying = true;
            }
        }
        if (isPlaying)
        {
            // Input Detection 0_0
            if (IsKeyDown(KEY_W))
            {
                player1.y -= playerSpeed;
            }
            if (IsKeyDown(KEY_S))
            {
                player1.y += playerSpeed;
            }
            if (IsKeyDown(KEY_UP))
            {
                player2.y -= playerSpeed;
            }
            if (IsKeyDown(KEY_DOWN))
            {
                player2.y += playerSpeed;
            }

            // Updating the ball position ;)
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;

            if (ballPosition.x >= width - radius || ballPosition.x <= 0 + radius)
            {
                ballSpeed.x *= -1;
            }
            if (ballPosition.y >= height - radius || ballPosition.y <= 0 + radius)
            {
                ballSpeed.y *= -1;
            }

            // Checking for collision O^O

            if (CheckCollisionCircleRec(ballPosition, radius, player1) ||
                CheckCollisionCircleRec(ballPosition, radius, player2))
            {
                ballSpeed.x = -ballSpeed.x; // Reverse ball's horizontal direction
            }
            // ballPosition.x < player1.x ||
            // (ballPosition.x > (player2.x + player2.width))
            // Winning and Losing o7 o7 o7
            if (CheckCollisionCircleRec(ballPosition, radius, leftRect))
            {
                player2Win = true;
                ballSpeed = {0, 0};
                ballPosition = {(float)width / 2, (float)height / 2};
                player2Score += 1;
                isVisible = false;
            }
            if (CheckCollisionCircleRec(ballPosition, radius, rightRect))
            {
                player1Win = true;
                ballSpeed = {0, 0};
                ballPosition = {(float)width / 2, (float)height / 2};
                player1Score += 1;
                isVisible = false;
            }

            if (player1Win)
            {
                DrawText("Player 1 Wins!", 0, height / 2, 85, RAYWHITE);
                DrawText("Press ENTER to play again!", 0, height / 2 + 100, 20, RAYWHITE);
            }
            if (player2Win)
            {
                DrawText("Player 2 Wins!", 0, height / 2, 85, RAYWHITE);
                DrawText("Press ENTER to play again!", 0, height / 2 + 100, 20, RAYWHITE);
            }

            // Restarting :>
            if (IsKeyPressed(KEY_ENTER))
            {
                ballPosition = {(float)width / 2, (float)height / 2};
                ballSpeed = {5, 5};
                player1 = {50, (float)(height / 2) - ((height / 4) / 2), 15, (float)height / 4};
                player2 = {(float)(width - 50 - (width / 40)), (float)(height / 2) - ((height / 4) / 2), 15, (float)height / 4};
                isVisible = true;
                player1Win = false;
                player2Win = false;
            }

            const char *player1ScoreText = TextFormat("Score: %d", player1Score);
            const char *player2ScoreText = TextFormat("Score: %d", player2Score);

            // Drawing the characters :|
            if (isVisible)
            {
                // Player 1 paddle
                DrawRectangleRec(player1, RAYWHITE);

                // Player 2 paddle
                DrawRectangleRec(player2, RAYWHITE);

                // Ball
                DrawCircle(ballPosition.x, ballPosition.y, radius, RAYWHITE);

                // Divder
                DrawLine(width / 2, 0, width / 2, height, RAYWHITE);

                // Death squares
                DrawRectangleRec(leftRect, BLANK);
                DrawRectangleRec(rightRect, BLANK);

                // Player 1 score
                DrawText(player1ScoreText, 10, 10, 20, RAYWHITE);

                // Player 2 score
                DrawText(player2ScoreText, width / 2 + 10, 10, 20, RAYWHITE);
            }
        }

        EndDrawing();
    }
    CloseWindow();
}