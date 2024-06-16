from settings import SCREEN_WIDTH, SCREEN_HEIGHT
import pygame
import sys


# .set_alpha for different version tic tac toe
def load_icon(path, resolution):
    icon = pygame.image.load(path)
    return pygame.transform.scale(icon, resolution)


def grid_to_pixel_coords(x, y):
    return (SCREEN_WIDTH // 3 * x, SCREEN_HEIGHT // 3 * y)


def pixel_to_grid_coords(x, y):
    return (x // (SCREEN_WIDTH // 3), y // (SCREEN_HEIGHT // 3))


def draw_victory_popup(screen, player):
    background = pygame.Rect(0, 0, 600, 600)
    forground = pygame.Rect(0, 0, 575, 575)

    background.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)
    forground.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)

    pygame.draw.rect(screen, (200, 200, 200), background)
    pygame.draw.rect(screen, (230, 230, 230), forground)

    print("Drawing winner popup")


def draw_board(grid, screen, board_icon, x_icon, o_icon):
    screen.blit(BOARD_ICON, (0, 0))

    for x in range(0, len(grid)):
        for y in range(0, len(grid[x])):
            if grid[x][y] is None:
                continue

            icon = x_icon if grid[x][y] == 0 else o_icon
            screen.blit(icon, grid_to_pixel_coords(x, y))


def try_place_token(grid, x, y, index):
    # check if it is a valid place
    if grid[x][y] is not None:
        return False

    grid[x][y] = index

    print(f"Player {index + 1} placed at ({x}, {y})")

    return True


def is_winner(grid, target, player):
    for x in range(0, len(grid)):
        for y in range(0, len(grid[x])):
            if grid[x][y] != player:
                continue

            pivot = (x, y)

            dirs = [(1, 0), (0, 1), (1, 1), (-1, 1)]

            for dir in dirs:
                count = 1

                next_x = pivot[0] + dir[0]
                next_y = pivot[1] + dir[1]

                while (0 <= next_x < len(grid)
                       and 0 <= next_y < len(grid[next_x])
                       and grid[next_x][next_y] == player):

                    count += 1

                    if count >= target:
                        return True

                    next_x += dir[0]
                    next_y += dir[1]
    return False


def game(screen):
    # Maybe draw a menu button?

    font = pygame.font.Font(None, 42)
    large_font = pygame.font.Font(None, 72)

    restart_button = pygame.Rect(0, 0, 125, 50)
    quit_button = pygame.Rect(0, 0, 100, 50)

    result_text = None
    restart_text = font.render("Restart", True, "white")
    quit_text = font.render("Quit", True, "white")

    restart_button.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 - 30)
    quit_button.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 + 30)

    result_text_rect = None
    restart_text_rect = restart_text.get_rect(center=restart_button.center)
    quit_text_rect = quit_text.get_rect(center=quit_button.center)

    background = pygame.Rect(0, 0, 600, 600)
    forground = pygame.Rect(0, 0, 575, 575)

    background.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)
    forground.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)

    clock = pygame.time.Clock()

    grid = [
        [None, None, None],
        [None, None, None],
        [None, None, None],
    ]

    turn_index = 0

    has_result = False

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
                continue

            if event.type == pygame.MOUSEBUTTONDOWN:
                if has_result:
                    if restart_button.collidepoint(event.pos):
                        return "game"
                        continue

                    if quit_button.collidepoint(event.pos):
                        pygame.quit()
                        sys.exit()
                        continue

                    continue

                x, y = event.pos

                x, y = pixel_to_grid_coords(x, y)

                player_turn = turn_index % 2

                if try_place_token(grid, x, y, player_turn):
                    # Check for draw
                    # maybe change has_winner to has result

                    is_draw = turn_index >= len(grid) * len(grid[0]) - 1
                    has_result = is_winner(grid, 3, player_turn) or is_draw

                    if has_result:
                        result_text = large_font.render(
                            f"Player {player_turn +
                                      1} Won!", True, (41, 41, 41)
                        ) if not is_draw else large_font.render(
                            "DRAW", True, (41, 41, 41)
                        )

                        result_text_rect = result_text.get_rect(
                            center=(SCREEN_WIDTH // 2,
                                    SCREEN_HEIGHT // 2 - 100))

                    turn_index += 1

                continue

        screen.fill("white")

        draw_board(grid, screen, BOARD_ICON, X_ICON, O_ICON)

        if has_result:
            pygame.draw.rect(screen, (200, 200, 200), background)
            pygame.draw.rect(screen, (230, 230, 230), forground)

            pygame.draw.rect(screen, (41, 41, 41), restart_button)
            pygame.draw.rect(screen, (41, 41, 41), quit_button)

            screen.blit(restart_text, restart_text_rect)
            screen.blit(quit_text, quit_text_rect)

            screen.blit(result_text, result_text_rect)

        pygame.display.flip()

        clock.tick(10)


BOARD_ICON = load_icon("./gfx/Board.png", (SCREEN_WIDTH, SCREEN_HEIGHT))

X_ICON = load_icon("./gfx/Cross.png", (SCREEN_WIDTH // 3, SCREEN_HEIGHT // 3))
O_ICON = load_icon("./gfx/Circle.png", (SCREEN_WIDTH // 3, SCREEN_HEIGHT // 3))
