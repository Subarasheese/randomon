#!/bin/bash

# Check for required dependencies
command -v git >/dev/null 2>&1 || { echo >&2 "Git is required but not installed. Please install Git and try again."; exit 1; }
command -v sdl2-config >/dev/null 2>&1 || { echo >&2 "SDL2 is required but not installed. Please install SDL2 and try again."; exit 1; }

# Install additional dependencies
echo "Installing additional dependencies..."
sudo apt-get update
sudo apt-get install -y libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev

# Build the project
echo "Building Randomon..."
make

# Display success message and exit
echo "Randomon installation is complete. Run './randomon' to start a new game."
exit 0
