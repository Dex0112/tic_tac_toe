import pygame
from settings import SCREEN_WIDTH, SCREEN_HEIGHT
from game import game
from main_menu import main_menu


pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Tic Tac Toe")

running = True
current_state = "main_menu"

while running:
    # Based on current state do that file
    if current_state == "main_menu":
        current_state = main_menu(screen)
    elif current_state == "game":
        current_state = game(screen)
    else:
        print("Unrecognized Scene")
        running = False

pygame.quit()
