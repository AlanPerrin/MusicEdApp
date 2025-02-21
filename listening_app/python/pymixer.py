import pygame

# Initialize pygame mixer
pygame.mixer.init()

# Load a sound file (make sure the path is correct)
sound = pygame.mixer.Sound("\Questions\Note_Questions\g-5.mp3")

# Play the sound
sound.play()
