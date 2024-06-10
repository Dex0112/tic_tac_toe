import pygame


def place_token(grid, x, y, index):
    # check if it is a valid place
    grid[x][y] = index

    print(f"Player {index + 1} placed at ({x}, {y})")


# .set_alpha for different version tic tac toe
def load_icon(path, resolution):
    icon = pygame.image.load(path)
    return pygame.transform.scale(icon, resolution)


def draw_board(grid, screen, board_icon, x_icon, o_icon):
    screen.blit(BOARD_ICON, (0, 0))
    for x in range(0, len(grid)):
        for y in range(0, len(grid[x])):
            if grid[x][y] is None:
                continue

            icon = x_icon if grid[x][y] == 0 else o_icon
            screen.blit(icon, (WIDTH // 3 * x, HEIGHT // 3 * y))


WIDTH = 720
HEIGHT = 720

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

pygame.display.set_caption("Tic Tac Toe")

running = True

grid = [
    [None, None, None],
    [None, None, None],
    [None, None, None],
]

turn_index = 0

BOARD_ICON = load_icon("./gfx/Board.png", (WIDTH, HEIGHT))

X_ICON = load_icon("./gfx/Cross.png", (WIDTH // 3, HEIGHT // 3))
O_ICON = load_icon("./gfx/Circle.png", (WIDTH // 3, HEIGHT // 3))

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            x, y = event.pos

            x = x // (WIDTH // 3)
            y = y // (HEIGHT // 3)

            place_token(grid, x, y, turn_index)

            # if the place was successful
            turn_index = 1 - turn_index

    screen.fill("white")

    draw_board(grid, screen, BOARD_ICON, X_ICON, O_ICON)

    pygame.display.flip()

    clock.tick(60)

pygame.quit()
