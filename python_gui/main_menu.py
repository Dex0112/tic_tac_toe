from settings import SCREEN_WIDTH, SCREEN_HEIGHT
import pygame
import sys


def main_menu(screen):
    clock = pygame.time.Clock()
    font = pygame.font.Font(None, 42)

    start_button = pygame.Rect(0, 0, 125, 50)
    quit_button = pygame.Rect(0, 0, 100, 50)

    start_text = font.render("Start", True, "white")
    quit_text = font.render("Quit", True, "white")

    start_button.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 - 30)
    quit_button.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 + 30)

    start_text_rect = start_text.get_rect(center=start_button.center)
    quit_text_rect = quit_text.get_rect(center=quit_button.center)

    while True:
        # Find out how to get the current mouse position
        # So you can highlight buttons

        # Try creating a button class -> callback and highlighting functions

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if start_button.collidepoint(event.pos):
                    return "game"

                if quit_button.collidepoint(event.pos):
                    pygame.quit()
                    sys.exit()

        screen.fill("white")

        pygame.draw.rect(screen, (41, 41, 41), start_button)
        pygame.draw.rect(screen, (41, 41, 41), quit_button)

        screen.blit(start_text, start_text_rect)
        screen.blit(quit_text, quit_text_rect)

        pygame.display.flip()

        clock.tick(10)
